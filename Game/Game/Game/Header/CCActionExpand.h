#ifndef __CCACTIONEXPAND_H__
#define __CCACTIONEXPAND_H__

#include "CCActionInstant.h"

namespace cocos2d {

	class CCActionBreakPoint : public CCActionInstant
	{
	public:
		CCActionBreakPoint(){};
		virtual ~CCActionBreakPoint(){};
		//super methods
		virtual void startWithTarget(CCNode *pTarget);
	public:
		//override static method
		/** Allocates and initializes the action */
		static CCActionBreakPoint * action();
	};

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