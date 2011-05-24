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
}

TouchLayer::~TouchLayer()
{

}

void TouchLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
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
		touchdata[i].bPressing = true;
		touchdata[i].touch = touch;
		Export_Lua_Scene::ExecuteCBTouchLayer(this->getTag(), toplayer, M_CCTOUCHINDICATOR_BEGAN, this, i);
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
				Export_Lua_Scene::ExecuteCBTouchLayer(this->getTag(), toplayer, M_CCTOUCHINDICATOR_MOVED, this, i);
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
				Export_Lua_Scene::ExecuteCBTouchLayer(this->getTag(), toplayer, M_CCTOUCHINDICATOR_ENDED, this, i);
				break;
			}
		}
	}
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
				Export_Lua_Scene::ExecuteCBTouchLayer(this->getTag(), toplayer, M_CCTOUCHINDICATOR_ENDED, this, i);
				break;
			}
		}
	}
}

void TouchLayer::onEnter()
{
	CCLayer::onEnter();

	setIsTouchEnabled(true);
}

bool TouchLayer::GetTouchData(int index, int flag, float *_x/* =NULL */, float *_y /* = NULL */, LONGLONG *_time/* =NULL */)
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
	return true;
}