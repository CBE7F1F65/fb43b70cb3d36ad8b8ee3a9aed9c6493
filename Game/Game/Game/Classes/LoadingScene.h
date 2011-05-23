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

	virtual void MenuCallbackFunc(CCObject *sender);
	virtual void NodeCallbackFunc(CCNode *sender, void * data);

private:
};

#endif