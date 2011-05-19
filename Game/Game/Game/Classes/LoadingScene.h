#ifndef __LOADINGSCENE_H__
#define __LOADINGSCENE_H__

#include "BaseScene.h"

class LoadingScene :public BaseScene
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene();

	virtual void onEnter();

	LAYER_NODE_FUNC(LoadingScene);

	static CCScene * thisScene;
	static CCLayer * thisLayer;

	void MenuCallbackFunc(CCObject *sender);
	void NodeCallbackFunc(CCNode *sender, void *data);

private:
};

#endif