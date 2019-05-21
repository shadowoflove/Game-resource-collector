/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "SettingScene.h"
#include "HelpScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // 设置开始界面
	//精灵
    auto background = Sprite::create("menubackground.jpg");
    if (background == nullptr)
    {
        problemLoading("'menubackground.jpg'");
    }
    else
    {
        // position the sprite on the center of the screen
		background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(background, 0);
    }
	auto background_word = Sprite::create("wangzhe2.png");
		background_word->setPosition(Vec2(visibleSize.width / 2 + origin.x,150));
		this->addChild(background_word, 0);
	//菜单
		/////////////注意，我发现这个的初始为480*320，以后设坐标位置按照这个来
		 MenuItemImage* begin_button = MenuItemImage::create("start_button1.png",
									"start_button2.png",
					CC_CALLBACK_1(HelloWorld::menuItemBeginCallback,this));//开始按钮
		begin_button->setPosition(Vec2(visibleSize.width / 2, 
										visibleSize.height / 2 -50));

		MenuItemImage* setting_button = MenuItemImage::create("setting_button1.png",
			"setting_button2.png",
			CC_CALLBACK_1(HelloWorld::menuItemSettingCallback, this));//设置按钮
		setting_button->setPosition(Vec2(visibleSize.width*1.5/ 5, 
										visibleSize.height / 2 -10));

		MenuItemImage* help_button = MenuItemImage::create("help_button1.png",
			"help_button2.png",
			CC_CALLBACK_1(HelloWorld::menuItemHelpCallback, this));//帮助按钮
		help_button->setPosition(Vec2(visibleSize.width*3.5 / 5 , 
										visibleSize.height / 2-10));

		Menu* begin = Menu::create(begin_button, setting_button, help_button, NULL);
		//begin->alignItemsVertically();
		begin->setPosition(Vec2::ZERO);
		this->addChild(begin);


    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
void HelloWorld::menuItemBeginCallback(Ref* pSender)
{
	MenuItem* item = (MenuItem*)pSender;
}

void HelloWorld::menuItemSettingCallback(Ref* pSender)
{
	auto setting_scene = Setting::createScene();
	Director::getInstance()->pushScene(setting_scene);

}

void HelloWorld::menuItemHelpCallback(Ref* pSender)
{
	auto help_scene = Help::createScene();
	auto dong_help_scene = TransitionSlideInL::create(0.5f, help_scene);
	Director::getInstance()->pushScene(dong_help_scene);
}
