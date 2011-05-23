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

	virtual void MenuCallbackFunc(CCObject *sender);
	virtual void NodeCallbackFunc(CCNode *sender, void * data);

private:
};

#endif