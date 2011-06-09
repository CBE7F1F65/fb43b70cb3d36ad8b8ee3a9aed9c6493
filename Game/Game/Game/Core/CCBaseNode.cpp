#include "../Header/CCBaseNode.h"

namespace cocos2d {

	CCBaseNode::CCBaseNode()
	{
		init();
	}
	CCBaseNode::~CCBaseNode()
	{
	}


	CCBaseNode * CCBaseNode::node(void)
	{
		CCBaseNode * pRet = new CCBaseNode();
		pRet->autorelease();
		return pRet;
	}

	void CCBaseNode::init()
	{
		m_nOpacity = 255;
		m_sColor = ccWHITE;
	}

	void CCBaseNode::setColor(ccColor3B color)
	{
		m_sColor = color;

		CCArray * pChildren = this->getChildren();
		if (pChildren && pChildren->count() > 0)
		{
			CCObject* pObject = NULL;
			CCARRAY_FOREACH(pChildren, pObject)
			{
				CCNode* pChild = (CCNode*) pObject;
				if (pChild)
				{
					CCRGBAProtocol *pRGBAProtoco = pChild->convertToRGBAProtocol();
					if (pRGBAProtoco)
					{
						/*
						ccColor3B oricol = pRGBAProtoco->getColor();
						ccColor3B blendcol = color;
						blendcol.r = (GLubyte)(((float)color.r)/(255.0f)*((float)oricol.r));
						blendcol.g = (GLubyte)(((float)color.g)/(255.0f)*((float)oricol.g));
						blendcol.b = (GLubyte)(((float)color.b)/(255.0f)*((float)oricol.b));
						pRGBAProtoco->setColor(blendcol);
						*/
						pRGBAProtoco->setColor(color);
					}
				}
			}
		}	
	}

	ccColor3B CCBaseNode::getColor()
	{
		return m_sColor;
	}

	void CCBaseNode::setOpacity(GLubyte opacity)
	{
		m_nOpacity = opacity;

		CCArray * pChildren = this->getChildren();
		if (pChildren && pChildren->count() > 0)
		{
			CCObject* pObject = NULL;
			CCARRAY_FOREACH(pChildren, pObject)
			{
				CCNode* pChild = (CCNode*) pObject;
				if (pChild)
				{
					CCRGBAProtocol *pRGBAProtoco = pChild->convertToRGBAProtocol();
					if (pRGBAProtoco)
					{
						/*
						GLubyte oriopa = pRGBAProtoco->getOpacity();
						GLubyte blendopa = opacity;
						blendopa = (GLubyte)(((float)opacity)/(255.0f)*((float)oriopa));
						pRGBAProtoco->setOpacity(blendopa);
						*/
						pRGBAProtoco->setOpacity(opacity);
					}
				}
			}
		}	
	}

	GLubyte CCBaseNode::getOpacity()
	{
		return m_nOpacity;
	}

}