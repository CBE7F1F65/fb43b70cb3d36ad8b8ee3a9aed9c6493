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
};

#endif