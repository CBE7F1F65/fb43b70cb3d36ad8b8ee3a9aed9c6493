#include "CCActionExpand.h"
#include "CCNode.h"
#include "CCSprite.h"

namespace cocos2d {

	CCActionDelete* CCActionDelete::action()
	{
		CCActionDelete* pRet = new CCActionDelete();
		pRet->autorelease();
		return pRet;
	}
	void CCActionDelete::startWithTarget(CCNode *pTarget)
	{
		CCActionInstant::startWithTarget(pTarget);
		pTarget->removeFromParentAndCleanup(true);
	}

}