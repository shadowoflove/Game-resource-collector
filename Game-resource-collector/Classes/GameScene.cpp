#include "HelloWorldScene.h"
#include "GameScene.h"
#include"math.h"

USING_NS_CC;

//Vec2 hero_position;

Scene* Game::createScene()
{
	return Game::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Game::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//////////添加自己的代码

    tile_map = TMXTiledMap::create("Tiled Map/ditu111.tmx");//添加瓦片地图

	//tile_map->setPosition(Vec2(0,0));

	addChild(tile_map, 0, 100);//将瓦片地图放在第0层
	pengzhuang_layer = tile_map->getLayer("pengzhuang");//将wall层设置为碰撞层
	/*TMXObjectGroup* group =tile_map->getObjectGroup("");
	ValueMap spawn_point = group->getObject("");

	float spawn_x = spawn_point["x"].asFloat;
	float spawn_y = spawn_point["y"].asFloat;*/


	hero = Sprite::create("hero/hero.png");//添加英雄
	hero->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y)); \
		last_position = hero->getPosition();
	//hero->setTag(001);
	this->addChild(hero,1);//将英雄放在第一层

	this->schedule(schedule_selector(Game::updateView),0.005f);

	this->scheduleUpdate();
	
	auto touch = EventListenerTouchOneByOne::create();//触摸事件
	//touch->setSwallowTouches(true);
	touch->onTouchBegan = CC_CALLBACK_2(Game::touchBegin,this);
	touch->onTouchMoved = CC_CALLBACK_2(Game::touchMove, this);
	touch->onTouchEnded = CC_CALLBACK_2(Game::touchEnd, this);

	EventDispatcher* touch_jianting = Director::getInstance()->getEventDispatcher();//触摸事件 监听器

	touch_jianting->addEventListenerWithSceneGraphPriority(touch, hero);

	return true;
}



void Game::pengzhuang_check()//hero_position就是当前位置
{
	Vec2 position_now = hero->getPosition();//hero_position是精灵时刻的位置
	Vec2 tile_position_now = this->tileCoordFromPosition(position_now);//从像素点 坐标转化为瓦片坐标
	int tile_gid_now = pengzhuang_layer->getTileGIDAt(tile_position_now);//获得英雄 瓦片的gid
	Vec2 diff = last_position - position_now;
	if (tile_gid_now > 0 
		&&(diff.x*diff.x>1 )
		&&(diff.y*diff.y>1))//给一点缓冲量防止卡住
	{
			hero->stopAllActions();
			last_position = position_now;
	}

}
Vec2 Game::tileCoordFromPosition(Vec2 pos)
{
	int x = pos.x / tile_map->getTileSize().width;
	int y = ((tile_map->getMapSize().height * tile_map->getTileSize().height) - pos.y)
		/ tile_map->getTileSize().height;
	return Vec2(x, y);
}
int getDirection(int x,int y)//获得 行走的 方向
{
	/////////////////1-8是从12点方向顺时针//////////////
	int direction = 0;
	if (x == 0 || y == 0)
		direction =1;
	else if (x > 0 && x * x / (y * y) >10)		//RIGHT
		direction = 3;
	else if (x < 0 && x * x / (y * y)>10)		//LEFT
		direction = 7;
	else if (y > 0 && y * y / (x * x) > 10)	 //UP
		direction = 1;
	else if (y < 0 && y * y / (x * x)  >10)	//DOWN
		direction = 5;
	else if (x > 0 && y < 0)					    //RIGHT-DOWN
		direction = 4;
	else if (x < 0 && y < 0)					   //LEFT-DOWN
		direction = 6;
	else if (x < 0 && y > 0)			          //LEFT-UP
			direction = 8;
	else if (x > 0 && y > 0)					 //RIGHT-UP
		direction = 2;

    return direction;
}
Animate* create_Animate(int direction, const char* action,float time)//建立动作类动画
{
	Animation* animation = Animation::create();
	
	//Vector <SpriteFrame*> frameArray;
	if (action == "run")//奔跑时的动画
	{
		char  file_name[20] = { 0 };
		for (int i = 0; i < 2; i++)
		{
			sprintf(file_name, "hero/run_%d_%d.png", direction, i);
			animation->addSpriteFrameWithFile(file_name);

			/*__String* frame_name = __String::createWithFormat("hero/run_%d_%d.png", direction,i);
			SpriteFrame* sprite_frame = SpriteFrameCache::getInstance()->
				getSpriteFrameByName(frame_name->getCString());
				animation->addSpriteFrame(sprite_frame);*/

				/*auto* frameCache = SpriteFrameCache::getInstance();
				for (int i = 0; i < 2; i++)
				{
					auto* frame = frameCache->getSpriteFrameByName
					(String::createWithFormat("run_%d_%d.png", direction, i)->getCString());
					frameArray.pushBack(frame);
					}
				Animation* animation = Animation::createWithSpriteFrames(frameArray);*/
		}
	}
		else//八个方向上的最后站立
		{
			//auto hero = static_cast<Sprite*>(event->getCurrentTarget());
			//hero->stopAllActions();
			char  file_name[20] = { 0 };
			sprintf(file_name, "hero/stop_%d.png", direction);
			animation->addSpriteFrameWithFile(file_name);
		}
		
		animation->setDelayPerUnit(0.1f);
		if(action=="stop")
		animation->setLoops(1);
		else
			animation->setLoops(time/0.2);//几张图片的走路动画就/0.1*几

		Animate* animate = Animate::create(animation);
		return animate;
}

bool Game::touchBegin(Touch* touch, Event* event)
{
	/*if (is_walk == true)
		return true;
	is_walk = true;*/
	auto hero = static_cast<Sprite*>(event->getCurrentTarget());//将event转化为sprite类型
	hero->stopAllActions();
	Vec2 current_position = hero->getPosition();
	Vec2 touch_position =touch->getLocation();
	Vec2 diff = hero->convertToNodeSpace(touch->getLocation());//是触点和和hero之间的距离
	float iv = 50;//iv是移动速度
	float juli = sqrt(pow(diff.x, 2) + pow(diff.y, 2));

	auto* move_action = MoveTo::create(juli / iv, touch_position);
	auto* run_animate = create_Animate(getDirection(diff.x,diff.y),"run", juli / iv);
	auto* stop_animate = create_Animate(getDirection(diff.x, diff.y), "stop",0);
	auto* sequence = Sequence::create(move_action, stop_animate, NULL);

	Vec2 tileCoord = this->tileCoordFromPosition(touch_position);
	//获得瓦片的GID
	int tileGid = pengzhuang_layer->getTileGIDAt(tileCoord);//只有碰撞层时
	//log("new Gid %d", tileGid);
	if (tileGid > 0) {
		//is_walk = false;
		hero->stopAllActions();
		return true;
	}
	hero->runAction(run_animate);
	hero->runAction(sequence);
	//is_walk = false;
	return true;
}
void Game::touchMove(Touch* touch, Event* event)
{

}
void Game::touchEnd(Touch* touch, Event* event)
{
	
}

void  Game::updateView(float dt)
{
	pengzhuang_check();
	
}



