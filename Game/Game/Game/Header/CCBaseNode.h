#ifndef __CCBASENODE_H__
#define __CCBASENODE_H__

#include "CCNode.h"
#include "CCProtocols.h"

namespace cocos2d {

	class CCBaseNode : public CCNode, public CCRGBAProtocol
	{
	public:
		CCBaseNode();
		~CCBaseNode();

		static CCBaseNode * node(void);

		virtual CCRGBAProtocol* convertToRGBAProtocol() { return (CCRGBAProtocol *)this; }

		virtual void setColor(ccColor3B color);
		virtual ccColor3B getColor(void);
		virtual GLubyte getOpacity(void);
		virtual void setOpacity(GLubyte opacity);

		void init();

	protected:
		GLubyte m_nOpacity;
		ccColor3B m_sColor;
	};

}
#endif