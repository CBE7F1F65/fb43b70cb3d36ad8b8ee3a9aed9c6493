#ifndef __MISSIONSELECTSCENE_H__
#define __MISSIONSELECTSCENE_H__

#include "BaseScene.h"

class MissionSelectScene :public BaseScene
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene();

	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();

	LAYER_NODE_FUNC(MissionSelectScene);

	virtual void MenuCallbackFunc(CCObject *sender);
	virtual void NodeCallbackFunc(CCNode *sender, void * data);

private:
};

#endif