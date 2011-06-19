#include "../Header/CCLabelAtlasExpand.h"

namespace cocos2d{

	CCLabelAtlasExpand::CCLabelAtlasExpand()
	{

	}

	CCLabelAtlasExpand::~CCLabelAtlasExpand()
	{

	}

	CCLabelAtlasExpand * CCLabelAtlasExpand::labelWithString(const char *label, CCTexture2D * texture, int itemWidth, int itemHeight, char startCharMap)
	{
		CCLabelAtlasExpand *pRet = new CCLabelAtlasExpand();
		if(pRet && pRet->initWithString(label, texture, itemWidth, itemHeight, startCharMap))
		{
			pRet->autorelease();
			return pRet;
		}
		CC_SAFE_DELETE(pRet)
			return NULL;
	}

	bool CCLabelAtlasExpand::initWithString(const char *label, CCTexture2D * texture, int itemWidth, int itemHeight, char startCharMap)
	{
		assert(label != NULL);
		if (CCAtlasNode::initWithTileTexture(texture, itemWidth, itemHeight, strlen(label)))
		{
			m_cMapStartChar = startCharMap;
			this->setString(label);
			return true;
		}
		return false;
	}
}