#ifndef __Setting_SCENE_H__
#define __Setting_SCENE_H__

#include "cocos2d.h"


class Setting : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void BackButtonCallback(cocos2d::Ref* sPender);





	//void menuItem2Callback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Setting);
};


#endif // __Setting_SCENE_H__