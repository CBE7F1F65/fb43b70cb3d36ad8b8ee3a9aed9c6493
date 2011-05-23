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

	virtual void MenuCallbackFunc(CCObject *sender);
	virtual void NodeCallbackFunc(CCNode *sender, void * data);

private:
};

#endif