#include "../Header/BGlobal.h"
#include "../Header/Const.h"
#include "../Header/BIOInterface.h"

int BGlobal::pushedscenecount = 0;

CCPoint BGlobal::TranslatePosition(float x, float y)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	x = x * size.width / M_SCREEN_WIDTH;
	y = y * size.height / M_SCREEN_HEIGHT;
	return ccp(x, y);
}

float BGlobal::ScalerX(float val)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	return val * size.width / M_SCREEN_WIDTH;
}

float BGlobal::ScalerY(float val)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	return val * size.height / M_SCREEN_HEIGHT;
}

float BGlobal::Scaler(float val)
{
	return (ScalerX(val)+ScalerY(val))/2.0f;
}

CCPoint BGlobal::ScalerPoint(CCPoint point)
{
	return CCPointMake(ScalerX(point.x), ScalerY(point.y));
}

CCSize BGlobal::ScalerSize(CCSize size)
{
	return CCSizeMake(ScalerX(size.width), ScalerY(size.height));
}

CCRect BGlobal::ScalerRect(CCRect rect)
{
	CCPoint point = ScalerPoint(rect.origin);
	CCSize size = ScalerSize(rect.size);
	return CCRectMake(point.x, point.y, size.width, size.height);
}

CCPoint BGlobal::RTranslatePosition(float x, float y)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	x = x * M_SCREEN_WIDTH / size.width;
	y = y * M_SCREEN_HEIGHT / size.height;
	return ccp(x, y);
}

float BGlobal::RScalerX(float val)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	return val * M_SCREEN_WIDTH / size.width;
}

float BGlobal::RScalerY(float val)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	return val * M_SCREEN_HEIGHT / size.height;
}

float BGlobal::RScaler(float val)
{
	return (RScalerX(val)+RScalerY(val))/2.0f;
}

CCPoint BGlobal::RScalerPoint(CCPoint point)
{
	return CCPointMake(RScalerX(point.x), RScalerY(point.y));
}

CCSize BGlobal::RScalerSize(CCSize size)
{
	return CCSizeMake(RScalerX(size.width), RScalerY(size.height));
}

CCRect BGlobal::RScalerRect(CCRect rect)
{
	CCPoint point = RScalerPoint(rect.origin);
	CCSize size = RScalerSize(rect.size);
	return CCRectMake(point.x, point.y, size.width, size.height);
}

bool BGlobal::IsHold(CCPoint beginpos, CCPoint endpos, LONGLONG begintime, LONGLONG endtime)
{
	if (!((endtime-begintime) < BIOInterface::getInstance()->Timer_GetPerformanceFrequency() * M_TOUCH_MINIMUMPRESSDURATION))
	{
		return true;
	}
	return false;
}

bool BGlobal::IsMove(CCPoint beginpos, CCPoint endpos, LONGLONG begintime, LONGLONG endtime)
{
	if (DIST2(beginpos.x, beginpos.y, endpos.x, endpos.y) >= M_TOUCH_ALLOWABLEMOVEMENT*M_TOUCH_ALLOWABLEMOVEMENT)
	{
		return true;
	}
	return false;
}

bool BGlobal::PointInRect(CCPoint point, CCRect rect)
{
	return CCRect::CCRectContainsPoint(rect, point);
}

BYTE BGlobal::GetGesture(CCPoint beginpos0, CCPoint endpos0, LONGLONG begintime0, LONGLONG endtime0, CCPoint beginpos1, CCPoint endpos1, LONGLONG begintime1, LONGLONG endtime1, bool bTwoFingers /*=false*/, bool bFinal /*=false*/)
{
	if (!bTwoFingers)
	{
		if (bFinal)
		{
			if (!IsMove(beginpos0, endpos0, begintime0, endtime0))
			{
				return M_TOUCHGESTURE_ONE_NOMOVE;
			}
			else
			{
				return M_TOUCHGESTURE_ONE_MOVED;
			}
		}
		else
		{
			if ((endtime0-begintime0) < BIOInterface::getInstance()->Timer_GetPerformanceFrequency() * M_TOUCH_DOUBLEPRESSWAITDURATION)
			{
				return M_TOUCHGESTURE_UNKNOWN;
			}
			else
			{
				if (IsMove(beginpos0, endpos0, begintime0, endtime0))
				{
					return M_TOUCHGESTURE_ONE_MOVED;
				}
				else
				{
					return M_TOUCHGESTURE_UNKNOWN;
				}
			}
		}
	}
	else
	{
		if (IsMove(beginpos0, endpos0, begintime0, endtime0) || IsMove(beginpos1, endpos1, begintime1, endtime1))
		{
			return M_TOUCHGESTURE_TWO_MOVED;
		}
		else
		{
			if (bFinal)
			{
				return M_TOUCHGESTURE_TWO_NOMOVE;
			}
			else
			{
				return M_TOUCHGESTURE_UNKNOWN;
			}
		}
	}
	return M_TOUCHGESTURE_UNKNOWN;
}