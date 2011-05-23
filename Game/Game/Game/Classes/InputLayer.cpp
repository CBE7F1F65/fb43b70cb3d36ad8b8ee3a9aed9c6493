#include "../Classes/InputLayer.h"

#include "../Header/Const.h"
#include "../Header/BGlobal.h"

#include "../Header/BIOInterface.h"

#include "../Export/Export_Lua_Scene.h"

InputLayer::InputLayer()
{
	initWithInputData(NULL, CCRectZero, "", "", 0, 0, "");
}

void InputLayer::initWithInputData(CCLayer * _toplayer, CCRect rect, const char * _text, const char * _fontname, float _fontsize, int _inputmax, const char * _defaulttext)
{
	toplayer = _toplayer;
	touchrect = rect;//BGlobal::ScalerRect(rect);
	strcpy(fontname, _fontname);

	fontsize = _fontsize;//BGlobal::Scaler(_fontsize);
	inputmax = _inputmax;
	strcpy(defaulttext, _defaulttext);
	strcpy(text, _text);

	m_pTextField = NULL;
	m_beginPos = CCPointZero;
	m_beginPressTime = 0;
}

InputLayer::~InputLayer()
{

}

void InputLayer::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, false);
}

bool InputLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	m_beginPos = pTouch->locationInView(pTouch->view());	
	m_beginPos = CCDirector::sharedDirector()->convertToGL(m_beginPos);
	m_beginPressTime = BIOInterface::getInstance()->Timer_GetCurrentSystemTime();
//	m_beginPos = BGlobal::TranslatePosition(m_beginPos.x, m_beginPos.y);
	return true;
}

void InputLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint endPos = pTouch->locationInView(pTouch->view());
	endPos = CCDirector::sharedDirector()->convertToGL(endPos);
//	endPos = BGlobal::TranslatePosition(endPos.x, endPos.y);

	bool bIsMove = BGlobal::IsMove(m_beginPos, endPos, m_beginPressTime, BIOInterface::getInstance()->Timer_GetCurrentSystemTime());

	if (!bIsMove)
	{
		if (BGlobal::PointInRect(endPos, touchrect))
		{
			m_pTextField->attachWithIME();
		}
		else
		{
			m_pTextField->detachWithIME();
		}
	}
}

bool InputLayer::onTextFieldInsertText(CCTextFieldTTF * pSender, const char * text, int nLen)
{
	if (pSender->getCharCount() > inputmax)
	{
		return true;
	}
	return false;
}

// CCTextFieldDelegate protocol
bool InputLayer::onTextFieldAttachWithIME(CCTextFieldTTF * pSender)
{
	if (m_pTextField)
	{
		m_pTextField->runAction(
			CCRepeatForever::actionWithAction(
			(CCActionInterval*)CCSequence::actions(
					CCScaleTo::actionWithDuration(0.3f, 1.05f, 1.05f),
					CCScaleTo::actionWithDuration(0.3f, 1.0f, 1.0f),
//					CCFadeTo::actionWithDuration(0.5f, 0xaf),
//					CCFadeTo::actionWithDuration(1.0f, 0xff),
					NULL
					)
				)
				);
		Export_Lua_Scene::ExecuteCBInputLayer(pSender->getTag(), toplayer, M_CCEVENTTAG_ENTER, m_pTextField->getString());
	}
	return false;
}

bool InputLayer::onTextFieldDetachWithIME(CCTextFieldTTF * pSender)
{
	if (m_pTextField)
	{
		m_pTextField->stopAllActions();
		m_pTextField->setOpacity(0xff);
		Export_Lua_Scene::ExecuteCBInputLayer(pSender->getTag(), toplayer, M_CCEVENTTAG_LEAVE, m_pTextField->getString());
	}
	return false;
}

void InputLayer::onEnter()
{
	CCLayer::onEnter();

	setIsTouchEnabled(true);
//	registerWithTouchDispatcher();
	if (!m_pTextField)
	{
		m_pTextField = CCTextFieldTTF::textFieldWithPlaceHolder(defaulttext, fontname, fontsize);
		if (strlen(text))
		{
			m_pTextField->setString(text);
		}
		m_pTextField->setDelegate(this);
		addChild(m_pTextField, this->getZOrder(), this->getTag());
		m_pTextField->setPosition(ccp(touchrect.origin.x+touchrect.size.width/2, touchrect.origin.y+touchrect.size.height/2));
		m_pTextField->setColorSpaceHolder(ccc3(0xff, 0xff, 0xff));
	}
}