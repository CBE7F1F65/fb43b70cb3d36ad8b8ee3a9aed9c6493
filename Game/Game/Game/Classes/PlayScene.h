#ifndef __PLAYSCENE_H__
#define __PLAYSCENE_H__

#include "BaseScene.h"

class PlayScene :public BaseScene
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene();

	virtual void onEnter();

	LAYER_NODE_FUNC(PlayScene);

	virtual void MenuCallbackFunc(CCObject *sender);
	virtual void NodeCallbackFunc(CCNode *sender, void * data);

private:
};

#endif