#ifndef __BASESCENE_H__
#define __BASESCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class BaseScene : public CCLayer
{
public:
	BaseScene();
	~BaseScene();

	bool toenter;
	bool toentertdf;

	virtual void MenuCallbackFunc(CCObject *sender) = 0;
	virtual void NodeCallbackFunc(CCNode *sender, void * data) = 0;
};

#endif