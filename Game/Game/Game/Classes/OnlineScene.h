#ifndef __ONLINESCENE_H__
#define __ONLINESCENE_H__

#include "BaseScene.h"

class OnlineScene :public BaseScene
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene();

	virtual void onEnter();

	LAYER_NODE_FUNC(OnlineScene);

	static CCScene * thisScene;
	static CCLayer * thisLayer;

	void MenuCallbackFunc(CCObject *sender);

private:
};

#endif