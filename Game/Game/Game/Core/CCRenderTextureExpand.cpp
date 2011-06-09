#include "../Header/CCRenderTextureExpand.h"

namespace cocos2d{

	CCRenderTextureExpand::CCRenderTextureExpand()
	{

	}
	CCRenderTextureExpand::~CCRenderTextureExpand()
	{

	}

	CCRenderTextureExpand * CCRenderTextureExpand::renderTextureWithWidthAndHeight(int w, int h, CCTexture2DPixelFormat eFormat)
	{
		CCRenderTextureExpand *pRet = new CCRenderTextureExpand();

		if(pRet && pRet->initWithWidthAndHeight(w, h, eFormat))
		{
			pRet->autorelease();
			return pRet;
		}
		CC_SAFE_DELETE(pRet);
		return NULL;
	}

	CCRenderTextureExpand * CCRenderTextureExpand::renderTextureWithWidthAndHeight(int w, int h)
	{
		CCRenderTextureExpand *pRet = new CCRenderTextureExpand();

		if(pRet && pRet->initWithWidthAndHeight(w, h, kCCTexture2DPixelFormat_RGBA8888))
		{
			pRet->autorelease();
			return pRet;
		}
		CC_SAFE_DELETE(pRet)
			return NULL;
	}

	void CCRenderTextureExpand::setColor(ccColor3B color)
	{
		CCSprite * sprite = getSprite();
		if (sprite)
		{
			sprite->setColor(color);
		}
	}

	ccColor3B CCRenderTextureExpand::getColor()
	{
		CCSprite * sprite = getSprite();
		if (sprite)
		{
			return sprite->getColor();
		}
		return ccWHITE;
	}

	void CCRenderTextureExpand::setOpacity(GLubyte opacity)
	{
		CCSprite * sprite = getSprite();
		if (sprite)
		{
			sprite->setOpacity(opacity);
		}
	}

	GLubyte CCRenderTextureExpand::getOpacity()
	{
		CCSprite * sprite = getSprite();
		if (sprite)
		{
			return sprite->getOpacity();
		}
		return 255;
	}
}