#ifndef __BGLOBAL_H__
#define __BGLOBAL_H__

#include "cocos2d.h"
using namespace cocos2d;

#include "MainDependency.h"

#include "../Classes/TouchLayer.h"

class BGlobal
{
public:
	static CCPoint TranslatePosition(float x, float y);

	static float ScalerX(float val);
	static float ScalerY(float val);
	static float Scaler(float val);
	static CCPoint ScalerPoint(CCPoint point);
	static CCSize ScalerSize(CCSize size);
	static CCRect ScalerRect(CCRect rect);

	static CCPoint RTranslatePosition(float x, float y);

	static float RScalerX(float val);
	static float RScalerY(float val);
	static float RScaler(float val);
	static CCPoint RScalerPoint(CCPoint point);
	static CCSize RScalerSize(CCSize size);
	static CCRect RScalerRect(CCRect rect);

	static bool IsTap(CCPoint beginpos, CCPoint endpos, LONGLONG begintime, LONGLONG endtime);
	static bool IsHold(CCPoint beginpos, CCPoint endpos, LONGLONG begintime, LONGLONG endtime);
	static bool IsMove(CCPoint beginpos, CCPoint endpos, LONGLONG begintime, LONGLONG endtime);

	static bool PointInRect(CCPoint point, CCRect rect);

	static BYTE GetGesture(CCPoint beginpos0, CCPoint endpos0, LONGLONG begintime0, LONGLONG endtime0, CCPoint beginpos1, CCPoint endpos1, LONGLONG begintime1, LONGLONG endtime1, bool bTwoFingers=false, bool bFinal=false);

public:
	static int pushedscenecount;
};

#endif