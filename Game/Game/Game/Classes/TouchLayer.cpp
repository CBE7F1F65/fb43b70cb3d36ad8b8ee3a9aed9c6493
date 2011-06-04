#include "TouchLayer.h"

#include "../Header/BGlobal.h"

#include "../Header/BIOInterface.h"

#include "../Export/Export_Lua_Scene.h"

TouchLayer::TouchLayer()
{
	ZeroMemory(&touchdata, sizeof(TouchData)*M_TOUCHMAX);
	initWithRect(NULL, CCRectZero);
}

void TouchLayer::initWithRect(CCLayer * _toplayer, CCRect rect)
{
	toplayer = _toplayer;
	touchrect = rect;
	gesture = M_TOUCHGESTURE_UNKNOWN;
}

TouchLayer::~TouchLayer()
{

}

void TouchLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	if (gesture)
	{
		return;
	}

	CCSetIterator it = pTouches->begin();
	for (; it!=pTouches->end(); ++it)
	{
		int i=0;
		for (; i<M_TOUCHMAX; i++)
		{
			if (!touchdata[i].bPressing)
			{
				break;
			}
		}
		if (i >= M_TOUCHMAX)
		{
			break;
		}

		CCTouch* touch = (CCTouch*)(*it);

		CCPoint beginpos = touch->locationInView( touch->view() );
		beginpos = CCDirector::sharedDirector()->convertToGL(beginpos);
		if (!BGlobal::PointInRect(beginpos, touchrect))
		{
			continue;
		}

		touchdata[i].beginPos = beginpos;		
		touchdata[i].beginPressTime = BIOInterface::getInstance()->Timer_GetCurrentSystemTime();

		touchdata[i].nowPos = touchdata[i].beginPos;
		touchdata[i].nowPressTime = touchdata[i].beginPressTime;

		touchdata[i].endPos = touchdata[i].beginPos;
		touchdata[i].endPressTime = touchdata[i].beginPressTime;

		touchdata[i].bPressing = true;
		touchdata[i].touch = touch;

		Export_Lua_Scene::ExecuteCBTouchLayer(this->getTag(), toplayer, M_CCTOUCHINDICATOR_BEGAN, this, i, gesture);
	}
}

void TouchLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	for (; it!=pTouches->end(); ++it)
	{
		CCTouch* touch = (CCTouch*)(*it);
		for (int i=0; i<M_TOUCHMAX; i++)
		{
			if (touchdata[i].bPressing && touchdata[i].touch == touch)
			{
				touchdata[i].nowPos = touch->locationInView( touch->view() );	
				touchdata[i].nowPos = CCDirector::sharedDirector()->convertToGL(touchdata[i].nowPos);
				touchdata[i].nowPressTime = BIOInterface::getInstance()->Timer_GetCurrentSystemTime();

				touchdata[i].endPos = touchdata[i].nowPos;
				touchdata[i].endPressTime = touchdata[i].nowPressTime;

				if (!gesture)
				{
					gesture = BGlobal::GetGesture(
						touchdata[i].beginPos, 
						touchdata[i].endPos, 
						touchdata[i].beginPressTime, 
						touchdata[i].endPressTime, 
						touchdata[1-i].beginPos, 
						touchdata[1-i].endPos, 
						touchdata[1-i].beginPressTime, 
						touchdata[1-i].endPressTime, 
						touchdata[1-i].bPressing);
				}

				Export_Lua_Scene::ExecuteCBTouchLayer(this->getTag(), toplayer, M_CCTOUCHINDICATOR_MOVED, this, i, gesture);
				break;
			}
		}
	}
}

void TouchLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	for (; it!=pTouches->end(); ++it)
	{
		CCTouch* touch = (CCTouch*)(*it);
		for (int i=0; i<M_TOUCHMAX; i++)
		{
			if (touchdata[i].bPressing && touchdata[i].touch == touch)
			{
				touchdata[i].endPos = touch->locationInView( touch->view() );	
				touchdata[i].endPos = CCDirector::sharedDirector()->convertToGL(touchdata[i].endPos);
				touchdata[i].endPressTime = BIOInterface::getInstance()->Timer_GetCurrentSystemTime();
				touchdata[i].bPressing = false;
				touchdata[i].touch = NULL;

				if (!gesture)
				{
					gesture = BGlobal::GetGesture(
						touchdata[i].beginPos, 
						touchdata[i].endPos, 
						touchdata[i].beginPressTime, 
						touchdata[i].endPressTime, 
						touchdata[1-i].beginPos, 
						touchdata[1-i].endPos, 
						touchdata[1-i].beginPressTime, 
						touchdata[1-i].endPressTime, 
						touchdata[1-i].bPressing, 
						true);
				}

				Export_Lua_Scene::ExecuteCBTouchLayer(this->getTag(), toplayer, M_CCTOUCHINDICATOR_ENDED, this, i, gesture);
				break;
			}
		}
	}
	for (int i=0; i<M_TOUCHMAX; i++)
	{
		if (touchdata[i].bPressing)
		{
			return;
		}
	}
	gesture = M_TOUCHGESTURE_UNKNOWN;
}

void TouchLayer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	for (; it!=pTouches->end(); ++it)
	{
		CCTouch* touch = (CCTouch*)(*it);
		for (int i=0; i<M_TOUCHMAX; i++)
		{
			if (touchdata[i].bPressing && touchdata[i].touch == touch)
			{
				touchdata[i].endPos = touch->locationInView( touch->view() );	
				touchdata[i].endPos = CCDirector::sharedDirector()->convertToGL(touchdata[i].endPos);
				touchdata[i].endPressTime = BIOInterface::getInstance()->Timer_GetCurrentSystemTime();
				touchdata[i].bPressing = false;
				touchdata[i].touch = NULL;

				if (!gesture)
				{
					gesture = BGlobal::GetGesture(
						touchdata[i].beginPos, 
						touchdata[i].endPos, 
						touchdata[i].beginPressTime, 
						touchdata[i].endPressTime, 
						touchdata[1-i].beginPos, 
						touchdata[1-i].endPos, 
						touchdata[1-i].beginPressTime, 
						touchdata[1-i].endPressTime, 
						touchdata[1-i].bPressing, 
						true);
				}

				Export_Lua_Scene::ExecuteCBTouchLayer(this->getTag(), toplayer, M_CCTOUCHINDICATOR_ENDED, this, i, gesture);
				break;
			}
		}
	}
	for (int i=0; i<M_TOUCHMAX; i++)
	{
		if (touchdata[i].bPressing)
		{
			return;
		}
	}
	gesture = M_TOUCHGESTURE_UNKNOWN;
}

void TouchLayer::onEnter()
{
	CCLayer::onEnter();

	setIsTouchEnabled(true);
}

bool TouchLayer::GetTouchData(int index, int flag, float *_x/* =NULL */, float *_y /* = NULL */, LONGLONG *_time/* =NULL */, CCRect * _rect/* =NULL */)
{
	if (index < 0 || index >= M_TOUCHMAX)
	{
		return false;
	}

	float x = 0;
	float y = 0;
	LONGLONG time = 0;

	switch (flag)
	{
	case M_CCTOUCHINDICATOR_BEGAN:
		x = touchdata[index].beginPos.x;
		y = touchdata[index].beginPos.y;
		time = touchdata[index].beginPressTime;
		break;
	case M_CCTOUCHINDICATOR_MOVED:
		x = touchdata[index].nowPos.x;
		y = touchdata[index].nowPos.y;
		time = touchdata[index].nowPressTime;
		break;
	case M_CCTOUCHINDICATOR_ENDED:
		x = touchdata[index].endPos.x;
		y = touchdata[index].endPos.y;
		time = touchdata[index].endPressTime;
		break;
	}

	if (_x)
	{
		*_x = x;
	}
	if (_y)
	{
		*_y = y;
	}
	if (_time)
	{
		*_time = time;
	}
	if (_rect)
	{
		*_rect = touchrect;
	}
	return true;
}