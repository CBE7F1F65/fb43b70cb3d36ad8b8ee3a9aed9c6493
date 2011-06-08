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
		pTarget->removeAllChildrenWithCleanup(true);
	}
}