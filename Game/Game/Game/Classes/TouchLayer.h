#ifndef __TOUCHLAYER_H__
#define __TOUCHLAYER_H__

#include "cocos2d.h"
using namespace cocos2d;

#include "../Header/Const.h"
#include "../Header/MainDependency.h"

struct TouchData 
{
	CCPoint		beginPos;
	CCPoint		lastPos;
	CCPoint		nowPos;
	CCPoint		endPos;

	LONGLONG	beginPressTime;
	LONGLONG	lastPressTime;
	LONGLONG	nowPressTime;
	LONGLONG	endPressTime;

	bool bPressing;

	CCTouch * touch;
};

class TouchLayer : public CCLayer, public CCStandardTouchDelegate
{
public:
	TouchLayer();
	~TouchLayer();

	void initWithRect(CCLayer * toplayer, CCRect rect);
	void setTouchRect(CCRect rect);

	LAYER_NODE_FUNC(TouchLayer);

	// CCLayer
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);

	virtual void onEnter();

	int GetTouchType(int index);
	bool GetTouchData(int index, int flag, float *x=NULL, float *y = NULL, LONGLONG *time=NULL, CCRect *rect=NULL);

	void TerminateTouch(int index=-1);

public:
	CCLayer * toplayer;
	CCRect touchrect;

	BYTE gesture;
	TouchData touchdata[M_TOUCHMAX];
};

#endif