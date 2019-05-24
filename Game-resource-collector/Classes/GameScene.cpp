#include "HelloWorldScene.h"
#include "GameScene.h"
#include"math.h"

USING_NS_CC;

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


	auto hero = Sprite::create("hero.png");
	hero->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height / 2));
	this->addChild(hero,1);//将英雄放在第一层

	this->scheduleUpdate();
	

	auto touch = EventListenerTouchOneByOne::create();
	touch->setSwallowTouches(true);
	touch->onTouchBegan = CC_CALLBACK_2(Game::touchBegin,this);
	touch->onTouchMoved = CC_CALLBACK_2(Game::touchMove, this);
	touch->onTouchEnded = CC_CALLBACK_2(Game::touchEnd, this);

	EventDispatcher* touch_jianting = Director::getInstance()->getEventDispatcher();

	touch_jianting->addEventListenerWithSceneGraphPriority(touch, hero);



	return true;
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
Animate* create_Animate(int direction, const char* action)//建立动作类动画
{
	Animation* animation = Animation::create();
	Vector <SpriteFrame*> frameArray;
	if (action == "stop")//八个方向上的最后站立
	{
	     for (int i = 0; i < 2; i++)
		{
			/*__String* frame_name = __String::createWithFormat("hero/stop_%d.png", direction);
			SpriteFrame* sprite_frame = SpriteFrameCache::getInstance()->
											getSpriteFrameByName(frame_name->getCString());
			animation->addSpriteFrame(sprite_frame);*/

			/*auto* frameCache = SpriteFrameCache::getInstance();
			auto* frame = frameCache->getSpriteFrameByName
								(String::createWithFormat("stop_%d.png", direction)->getCString());
			frameArray.pushBack(frame);
			Animation* animation = Animation::createWithSpriteFrames(frameArray);*/

			 char  file_name[20] = { 0 };
			 sprintf(file_name, "stop_%d.png", direction);
			 animation->addSpriteFrameWithFile(file_name);
		 }
	}
	if (action == "run")//奔跑时的动画
	{
		char  file_name[20] = { 0 };
		for (int i = 0; i < 2; i++)
		{
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

			sprintf(file_name, "run_%d_%d.png", direction,i);
			animation->addSpriteFrameWithFile(file_name);
		}
		animation->setLoops(-1);
		animation->setDelayPerUnit(0.1f);
	}
	Animate* animate = Animate::create(animation);
	return animate;
}

bool Game::touchBegin(Touch* touch, Event* event)
{
	auto hero = static_cast<Sprite*>(event->getCurrentTarget());//将event转化为sprite类型
	hero->stopAllActions();
	Vec2 current_position = hero->getPosition();
	Vec2 touch_position =touch->getLocation();
	Vec2 diff = hero->convertToNodeSpace(touch->getLocation());//是触点和和hero之间的距离
	float iv = 100;//iv是移动速度
	float juli = sqrt(pow(diff.x, 2) + pow(diff.y, 2));

	auto* move_action = MoveTo::create(juli / iv, touch_position);
	auto* run_animate = create_Animate(getDirection(diff.x,diff.y),"run");
	auto* stop_action = create_Animate(getDirection(diff.x, diff.y), "stop");
	//hero->runAction(MoveTo::create(juli /iv, touch_position));//间隔动作:移动
	auto* sequence = Sequence::create(move_action, run_animate, NULL);
	hero->runAction(run_animate);
	hero->runAction(sequence);
	return true;
}
void Game::touchMove(Touch* touch, Event* event)
{

}
void Game::touchEnd(Touch* touch, Event* event)
{
	
}

void  Game::update(float dt)
{
	//Vec2 hero_position
}


