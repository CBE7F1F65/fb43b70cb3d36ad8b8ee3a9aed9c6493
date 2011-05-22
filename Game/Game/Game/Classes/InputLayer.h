#ifndef __INPUTLAYER_H__
#define __INPUTLAYER_H__

#include "cocos2d.h"
using namespace cocos2d;

#include "../Header/Const.h"
#include "../Header/MainDependency.h"

class InputLayer : public CCLayer, public CCIMEDelegate, public CCTextFieldDelegate
{
public:
	InputLayer();
	~InputLayer();

	void initWithInputData(CCLayer * toplayer, CCRect rect, const char * text, const char * fontname, float fontsize, int inputmax, const char * defaulttext);

	LAYER_NODE_FUNC(InputLayer);

	virtual void registerWithTouchDispatcher();

	// CCLayer
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual bool onTextFieldInsertText(CCTextFieldTTF * pSender, const char * text, int nLen);

	virtual bool onTextFieldAttachWithIME(CCTextFieldTTF * pSender);
	virtual bool onTextFieldDetachWithIME(CCTextFieldTTF * pSender);

	virtual void onEnter();

public:

	CCLayer * toplayer;

	CCRect touchrect;
	char defaulttext[M_STRMAX];
	char fontname[M_STRMAX];
	float fontsize;
	int inputmax;

	char text[M_STRMAX];

public:
	CCTextFieldTTF * m_pTextField;
	CCPoint  m_beginPos;
	LONGLONG m_beginPressTime;
};

#endif