#ifndef __SPRITEITEMMANAGER_H__
#define __SPRITEITEMMANAGER_H__

#include "MainDependency.h"
#include "cocos2d.h"
#include "HTexture.h"
#include "DataStruct.h"

#define SI_NULL_INDEX	0

using namespace cocos2d;

class SpriteItemManager {

public:
	SpriteItemManager();
	~SpriteItemManager();

	static CCSprite * CreateSprite(int index);
	static bool CreateSprite(int index, CCSprite ** sprite);
	static bool ChangeSprite(int index, CCSprite * sprite);
	static int GetIndexByName(const char * spritename);
	static CCSprite * CreateSpriteByName(const char * spritename);
	static bool CreateSpriteByName(const char * spritename, CCSprite ** sprite);
	static void FreeSprite(CCSprite ** sprite);
	static spriteData * CastSprite(int index);

	static CCSprite * CreateNullSprite();
	static bool SetSpriteData(CCSprite * sprite, HTEXTURE tex, float texx, float texy, float texw, float texh, bool flipx=false, bool flipy=false);
	static bool SetSpriteTextureRect(CCSprite * sprite, float texx, float texy, float texw, float texh);
	static bool SetSpriteFlip(CCSprite * sprite, bool flipx=false, bool flipy=false);
	static bool SetSpriteHotSpot(CCSprite * sprite, float hotx, float hoty);

	static bool SetRenderEx(CCSprite * sprite, float x, float y, int angle=0, float hscale=1.0f, float vscale=0.0f);

	static bool SetSprite(int index, CCSprite * sprite);

	static HTEXTURE GetTexture(int index);
	static float GetTexX(int index);
	static float GetTexY(int index);
	static float GetTexW(int index);
	static float GetTexH(int index);

	static bool LoadTextureWhenNeeded(HTEXTURE tex);
};

#endif