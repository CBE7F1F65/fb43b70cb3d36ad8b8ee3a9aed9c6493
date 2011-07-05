#ifndef __BGLOBAL_H__
#define __BGLOBAL_H__

#include "cocos2d.h"
using namespace cocos2d;

#include "MainDependency.h"

#include "../Classes/TouchLayer.h"

class BGlobal
{
public:
	static CCSize GetWinSize();

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

	static bool IsHold(CCPoint beginpos, CCPoint endpos, LONGLONG begintime, LONGLONG endtime);
	static bool IsMove(CCPoint beginpos, CCPoint endpos, LONGLONG begintime, LONGLONG endtime);

	static bool PointInRect(CCPoint point, CCRect rect);

	static bool PointInRect(float x1, float y1, float x2, float y2, float rh2, float rv2);
	static bool CollisionRectangleRectangle(float x1, float y1, float rh1, float rv1, float x2, float y2, float rh2, float rv2);
	static bool CollisionCircleCircle(float x1, float y1, float r1, float x2, float y2, float r2);
	static bool CollisionEllipseCircle(float x1, float y1, float rh1, float rv1, float x2, float y2, float r2);
	static bool CollisionCircleLine(float r1, float x21, float y21, float x22, float y22);
	static bool CollisionCircleLine(float x1, float y1, float r1, float x21, float y21, float x22, float y22);
	static bool CollisionEllipseLine(float x1, float y1, float rh1, float rv1, float x21, float y21, float x22, float y22);

	static BYTE GetGesture(CCPoint beginpos0, CCPoint endpos0, LONGLONG begintime0, LONGLONG endtime0, CCPoint beginpos1, CCPoint endpos1, LONGLONG begintime1, LONGLONG endtime1, bool bTwoFingers=false, bool bFinal=false);

public:
	static int pushedscenecount;
};

#endif