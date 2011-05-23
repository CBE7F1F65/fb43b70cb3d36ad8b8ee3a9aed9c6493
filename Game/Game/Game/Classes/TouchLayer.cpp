#include "TouchLayer.h"

#include "../Header/BGlobal.h"

#include "../Header/BIOInterface.h"

#include "../Export/Export_Lua_Scene.h"

TouchLayer::TouchLayer()
{
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
	for (int i=0; it!=pTouches->end(); ++it, ++i)
	{
		if (i >= M_TOUCHMAX)
		{
			break;
		}
		CCTouch* touch = (CCTouch*)(*it);

		touchdata[i].beginPos = touch->locationInView( touch->view() );	
		touchdata[i].beginPos = CCDirector::sharedDirector()->convertToGL(touchdata[i].beginPos);
		touchdata[i].beginPressTime = BIOInterface::getInstance()->Timer_GetCurrentSystemTime();
		touchdata[i].bPressing = true;
	}
	Export_Lua_Scene::ExecuteCBTouchLayer(this->getTag(), toplayer, M_CCTOUCHINDICATOR_BEGAN, pTouches, this);
}

void TouchLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	for (int i=0; it!=pTouches->end(); ++it, ++i)
	{
		if (i >= M_TOUCHMAX)
		{
			break;
		}
		CCTouch* touch = (CCTouch*)(*it);

		touchdata[i].nowPos = touch->locationInView( touch->view() );	
		touchdata[i].nowPos = CCDirector::sharedDirector()->convertToGL(touchdata[i].nowPos);
		touchdata[i].nowPressTime = BIOInterface::getInstance()->Timer_GetCurrentSystemTime();
	}
	Export_Lua_Scene::ExecuteCBTouchLayer(this->getTag(), toplayer, M_CCTOUCHINDICATOR_MOVED, pTouches, this);
}

void TouchLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	for (int i=0; it!=pTouches->end(); ++it, ++i)
	{
		if (i >= M_TOUCHMAX)
		{
			break;
		}
		CCTouch* touch = (CCTouch*)(*it);

		touchdata[i].endPos = touch->locationInView( touch->view() );	
		touchdata[i].endPos = CCDirector::sharedDirector()->convertToGL(touchdata[i].endPos);
		touchdata[i].endPressTime = BIOInterface::getInstance()->Timer_GetCurrentSystemTime();
		touchdata[i].bPressing = false;
	}
	Export_Lua_Scene::ExecuteCBTouchLayer(this->getTag(), toplayer, M_CCTOUCHINDICATOR_ENDED, pTouches, this);
}

void TouchLayer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	for (int i=0; it!=pTouches->end(); ++it, ++i)
	{
		if (i >= M_TOUCHMAX)
		{
			break;
		}
		CCTouch* touch = (CCTouch*)(*it);

		touchdata[i].endPos = touch->locationInView( touch->view() );	
		touchdata[i].endPos = CCDirector::sharedDirector()->convertToGL(touchdata[i].endPos);
		touchdata[i].endPressTime = BIOInterface::getInstance()->Timer_GetCurrentSystemTime();
		touchdata[i].bPressing = false;
	}
	Export_Lua_Scene::ExecuteCBTouchLayer(this->getTag(), toplayer, M_CCTOUCHINDICATOR_CANCELED, pTouches, this);
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