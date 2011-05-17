#ifndef __TITLESCENE_H__
#define __TITLESCENE_H__

#include "BaseScene.h"

class TitleScene :public BaseScene
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene();

	virtual void onEnter();

	LAYER_NODE_FUNC(TitleScene);

	static CCScene * thisScene;
	static CCLayer * thisLayer;

	void MenuCallbackFunc(CCObject *sender);

private:
};

#endif