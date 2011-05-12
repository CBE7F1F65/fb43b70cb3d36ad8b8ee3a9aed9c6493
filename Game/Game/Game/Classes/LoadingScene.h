#ifndef __LOADINGSCENE_H__
#define __LOADINGSCENE_H__

#include "cocos2d.h"

class LoadingScene :public cocos2d::CCLayer
{
public:
	LoadingScene(void);
	~LoadingScene(void);

	virtual bool init();

	virtual void onEnter();

	static cocos2d::CCScene* scene();

	LAYER_NODE_FUNC(LoadingScene);

	void LoadingCallBackFunc();

private:
	int nCallBackCount;
};

#endif