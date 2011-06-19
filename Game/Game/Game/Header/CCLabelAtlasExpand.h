#ifndef __CCLABELATLASEXPAND_H__
#define __CCLABELATLASEXPAND_H__

#include "CCLabelAtlas.h"

namespace cocos2d{

	class CCLabelAtlasExpand : public CCLabelAtlas
	{
	public:
		CCLabelAtlasExpand();
		~CCLabelAtlasExpand();

		static CCLabelAtlasExpand * labelWithString(const char *label, CCTexture2D * texture, int itemWidth, int itemHeight, char startCharMap);

		bool initWithString(const char *label, CCTexture2D * texture, int itemWidth, int itemHeight, char startCharMap);
	};
}

#endif