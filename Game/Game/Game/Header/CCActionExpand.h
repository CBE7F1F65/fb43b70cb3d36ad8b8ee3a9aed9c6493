#ifndef __CCACTIONEXPAND_H__
#define __CCACTIONEXPAND_H__

#include "CCActionInstant.h"

namespace cocos2d {

	class CCActionDelete : public CCActionInstant
	{
	public:
		CCActionDelete(){}
		virtual ~CCActionDelete(){}
		//super methods
		virtual void startWithTarget(CCNode *pTarget);
	public:
		//override static method
		/** Allocates and initializes the action */
		static CCActionDelete * action();
	};

}

namespace cocos2d {

	class CCActionDeleteChildren : public CCActionInstant
	{
	public:
		CCActionDeleteChildren(){}
		virtual ~CCActionDeleteChildren(){}
		//super methods
		virtual void startWithTarget(CCNode *pTarget);
	public:
		//override static method
		/** Allocates and initializes the action */
		static CCActionDeleteChildren * action();
	};

}

#endif