#ifndef __LOADINGSCENE_H__
#define __LOADINGSCENE_H__

#include "cocos2d.h"

class LoadingScene :public cocos2d::CCLayer
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene();

	virtual void onEnter();

	LAYER_NODE_FUNC(LoadingScene);

	void LoadingCallbackFunc();

private:
};

#endif