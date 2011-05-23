#ifndef __HELPSCENE_H__
#define __HELPSCENE_H__

#include "BaseScene.h"

class HelpScene :public BaseScene
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene();

	virtual void onEnter();

	LAYER_NODE_FUNC(HelpScene);

	virtual void MenuCallbackFunc(CCObject *sender);
	virtual void NodeCallbackFunc(CCNode *sender, void * data);

private:
};

#endif