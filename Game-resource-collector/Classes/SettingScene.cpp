#include "HelloWorldScene.h"
#include "SettingScene.h"

USING_NS_CC;

Scene* Setting::createScene()
{
	return Setting::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Setting::init()
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
	auto background = Sprite::create("setting background.jpg");
	if (background == nullptr)
	{
		problemLoading("'setting background.jpg'");
	}
	auto size = background->getContentSize();
	float scaleX = visibleSize.width / size.width;
	float scaleY = visibleSize.height / size.height;
	float scale = scaleX > scaleY ? scaleX : scaleY;
	background->setScale(scale);
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(background);

	//返回按钮
	auto back_button = MenuItemImage::create("back_button1.png",
		"back_button2.png",
		CC_CALLBACK_1(Setting::BackButtonCallback,this));
	back_button->setPosition(Vec2(400,80));

	Menu* setting_menu = Menu::create(back_button, NULL);
	
	setting_menu->setPosition(Vec2::ZERO);

	this->addChild(setting_menu);

	return true;
}
void Setting::BackButtonCallback(Ref*pSender)
{
	Director::getInstance()->popScene();
}
