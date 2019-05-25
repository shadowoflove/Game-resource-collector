#ifndef __Game_SCENE_H__
#define __Game_SCENE_H__

#include "cocos2d.h"


class Game : public cocos2d::Scene
{

	cocos2d::TMXLayer* pengzhuang_layer;
	cocos2d::TMXTiledMap* tile_map;

	cocos2d::Sprite* hero;

	cocos2d::Vec2 last_position;

	bool  is_walk;

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	//virtual void onEnter();

	//virtual void update(float dt);

	bool touchBegin(cocos2d::Touch* touch, cocos2d::Event* event);
	void touchMove(cocos2d::Touch* touch, cocos2d::Event* event);
	void touchEnd(cocos2d::Touch* touch, cocos2d::Event* event);

	void pengzhuang_check();
	bool if_peng_stop();
	void updateView(float dt);
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);

	//Animate*create_Animate(int direction, const char* action);
	CREATE_FUNC(Game);
};


#endif // __Setting_SCENE_H__#pragma once
