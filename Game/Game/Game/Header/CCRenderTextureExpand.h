#ifndef __CCRENDERTEXTUREEXPAND_H__
#define __CCRENDERTEXTUREEXPAND_H__

#include "CCRenderTexture.h"
#include "CCProtocols.h"

namespace cocos2d {
	class CCRenderTextureExpand : public CCRenderTexture, public CCRGBAProtocol
	{
	public:
		CCRenderTextureExpand();
		~CCRenderTextureExpand();

		virtual CCRGBAProtocol* convertToRGBAProtocol() { return (CCRGBAProtocol *)this; }

		static CCRenderTextureExpand * renderTextureWithWidthAndHeight(int w, int h, CCTexture2DPixelFormat eFormat);
		static CCRenderTextureExpand * renderTextureWithWidthAndHeight(int w, int h);

		virtual void setColor(ccColor3B color);
		virtual ccColor3B getColor(void);
		virtual GLubyte getOpacity(void);
		virtual void setOpacity(GLubyte opacity);
	};
}

#endif