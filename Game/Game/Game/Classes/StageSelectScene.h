#ifndef __STAGESELECTSCENE_H__
#define __STAGESELECTSCENE_H__

#include "BaseScene.h"

class StageSelectScene :public BaseScene
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene();

	virtual void onEnter();

	LAYER_NODE_FUNC(StageSelectScene);

	static CCScene * thisScene;
	static CCLayer * thisLayer;

	void MenuCallbackFunc(CCObject *sender);

private:
};

#endif