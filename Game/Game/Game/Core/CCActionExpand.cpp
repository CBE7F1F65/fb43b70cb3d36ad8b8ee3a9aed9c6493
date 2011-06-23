#include "../Header/CCActionExpand.h"
#include "CCNode.h"
#include "CCSprite.h"

namespace cocos2d {

	// CCActionDelete
	CCActionDelete* CCActionDelete::action()
	{
		CCActionDelete* pRet = new CCActionDelete();
		pRet->autorelease();
		return pRet;
	}
	void CCActionDelete::startWithTarget(CCNode *pTarget)
	{
		CCActionInstant::startWithTarget(pTarget);
//		pTarget->setIsVisible(false);
		if (pTarget->getParent())
		{
			pTarget->removeFromParentAndCleanup(true);
		}
		else
		{
			pTarget->cleanup();
		}
	}

	// CCActionDeleteChildren
	CCActionDeleteChildren* CCActionDeleteChildren::action()
	{
		CCActionDeleteChildren* pRet = new CCActionDeleteChildren();
		pRet->autorelease();
		return pRet;
	}
	void CCActionDeleteChildren::startWithTarget(CCNode *pTarget)
	{
		CCActionInstant::startWithTarget(pTarget);
		/*
		CCArray * m_pChildren = pTarget->getChildren();
		if ( m_pChildren && m_pChildren->count() > 0 )
		{
			CCObject* child;
			CCARRAY_FOREACH(m_pChildren, child)
			{
				CCNode* pNode = (CCNode*) child;
				if (pNode)
				{
					pNode->setIsVisible(false);
				}
			}
		}
		*/
		pTarget->removeAllChildrenWithCleanup(true);
	}
}