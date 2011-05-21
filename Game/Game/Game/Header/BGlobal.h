#ifndef __BGLOBAL_H__
#define __BGLOBAL_H__

#include "cocos2d.h"
using namespace cocos2d;

#include "MainDependency.h"

class BGlobal
{
public:
	static CCPoint TranslatePosition(float x, float y);

	static float ScalerX(float val);
	static float ScalerY(float val);
	static float Scaler(float val);
	static CCPoint ScalerPoint(CCPoint rect);
	static CCSize ScalerSize(CCSize size);
	static CCRect ScalerRect(CCRect rect);

	static bool IsTap(CCPoint beginpos, CCPoint endpos, LONGLONG begintime, LONGLONG endtime);
	static bool IsHold(CCPoint beginpos, CCPoint endpos, LONGLONG begintime, LONGLONG endtime);
	static bool IsMove(CCPoint beginpos, CCPoint endpos, LONGLONG begintime, LONGLONG endtime);

	static bool PointInRect(CCPoint point, CCRect rect);

public:
	static int pushedscenecount;
};

#endif