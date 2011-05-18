#ifndef __MISSIONSELECTSCENE_H__
#define __MISSIONSELECTSCENE_H__

#include "BaseScene.h"

class MissionSelectScene :public BaseScene
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene();

	virtual void onEnter();

	LAYER_NODE_FUNC(MissionSelectScene);

	static CCScene * thisScene;
	static CCLayer * thisLayer;

	void MenuCallbackFunc(CCObject *sender);

private:
};

#endif