#ifndef __HISCORESCENE_H__
#define __HISCORESCENE_H__

#include "BaseScene.h"

class HiScoreScene :public BaseScene
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene();

	virtual void onEnter();

	LAYER_NODE_FUNC(HiScoreScene);

	static CCScene * thisScene;
	static CCLayer * thisLayer;

	void MenuCallbackFunc(CCObject *sender);

private:
};

#endif