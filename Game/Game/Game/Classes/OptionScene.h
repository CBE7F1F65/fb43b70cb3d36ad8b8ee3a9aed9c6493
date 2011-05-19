#ifndef __OPTIONSCENE_H__
#define __OPTIONSCENE_H__

#include "BaseScene.h"

class OptionScene :public BaseScene
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene();

	virtual void onEnter();

	LAYER_NODE_FUNC(OptionScene);

	static CCScene * thisScene;
	static CCLayer * thisLayer;

	void MenuCallbackFunc(CCObject *sender);
	void NodeCallbackFunc(CCNode *sender, void *data);

private:
};

#endif