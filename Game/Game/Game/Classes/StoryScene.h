#ifndef __STORYSCENE_H__
#define __STORYSCENE_H__

#include "BaseScene.h"

class StoryScene :public BaseScene
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene();

	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();

	LAYER_NODE_FUNC(StoryScene);

	virtual void MenuCallbackFunc(CCObject *sender);
	virtual void NodeCallbackFunc(CCNode *sender, void * data);

private:
};

#endif