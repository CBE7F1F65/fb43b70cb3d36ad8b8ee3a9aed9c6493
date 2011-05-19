#ifndef __BGLOBAL_H__
#define __BGLOBAL_H__

#include "cocos2d.h"
using namespace cocos2d;

class BGlobal
{
public:
	static CCPoint TranslatePosition(float x, float y);
	static float ScalerX(float val);
	static float ScalerY(float val);
	static int pushedscenecount;
};

#endif