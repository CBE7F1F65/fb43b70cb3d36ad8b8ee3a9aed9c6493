#include "../Header/SpriteItemManager.h"
#include "../Header/BResource.h"
#include "../Header/BGlobal.h"

SpriteItemManager::SpriteItemManager()
{

}

SpriteItemManager::~SpriteItemManager()
{

}

HTEXTURE SpriteItemManager::GetTexture(int index)
{
	if (index < 0 || index >= DATASTRUCT_SPRITEMAX)
	{
		return NULL;
	}
	BResource * pbres = BResource::getInstance();
	return pbres->tex[pbres->spritedata[index].tex];
}

float SpriteItemManager::GetTexX(int index)
{
	if (index < 0 || index >= DATASTRUCT_SPRITEMAX)
	{
		return 0;
	}
	BResource * pbres = BResource::getInstance();
	return pbres->spritedata[index].tex_x;
}

float SpriteItemManager::GetTexY(int index)
{
	if (index < 0 || index >= DATASTRUCT_SPRITEMAX)
	{
		return 0;
	}
	BResource * pbres = BResource::getInstance();
	return pbres->spritedata[index].tex_y;
}

float SpriteItemManager::GetTexW(int index)
{
	if (index < 0 || index >= DATASTRUCT_SPRITEMAX)
	{
		return 0;
	}
	BResource * pbres = BResource::getInstance();
	return pbres->spritedata[index].tex_w;
}

float SpriteItemManager::GetTexH(int index)
{
	if (index < 0 || index >= DATASTRUCT_SPRITEMAX)
	{
		return 0;
	}
	BResource * pbres = BResource::getInstance();
	return pbres->spritedata[index].tex_h;
}

int SpriteItemManager::GetIndexByName(const char * spritename)
{
	if (!spritename)
	{
		return -1;
	}
	if (!strlen(spritename))
	{
		return -1;
	}
	BResource * pbres = BResource::getInstance();
	for (int i=0; i<DATASTRUCT_SPRITEMAX; i++)
	{
		if (!strcmp(spritename, pbres->spritedata[i].spritename))
		{
			return i;
			break;
		}
	}
	return -1;
}

spriteData * SpriteItemManager::CastSprite(int index)
{
	if (index >= 0 && index < DATASTRUCT_SPRITEMAX)
	{
		BResource * pbres = BResource::getInstance();
		return &(pbres->spritedata[index]);
	}
	return NULL;
}

bool SpriteItemManager::SetSprite(int index, CCSprite * sprite)
{
	if (!sprite)
	{
		return false;
	}
	if (index < 0)
	{
		SetSpriteTextureRect(sprite, 0, 0, 0, 0);
		return true;
	}
	spriteData * _sd = CastSprite(index);
	if (!_sd)
	{
		return false;
	}
	BResource * pbres = BResource::getInstance();
	HTEXTURE tex(_sd->tex, NULL);
	SetSpriteData(sprite, tex, _sd->tex_x, _sd->tex_y, 
		_sd->tex_w < 0 ? pbres->Texture_GetWidth(tex)-_sd->tex_x : _sd->tex_w, 
		_sd->tex_h < 0 ? pbres->Texture_GetHeight(tex)-_sd->tex_y : _sd->tex_h);
	return true;
}

CCSprite * SpriteItemManager::CreateNullSprite()
{
	CCSprite * sprite;
	sprite = CreateSprite(SI_NULL_INDEX);
	return sprite;
}

CCSprite * SpriteItemManager::CreateSprite(int index)
{
	CCSprite * sprite;
	//	sprite = CreateNullSprite();
	sprite = new CCSprite();
//	sprite->autorelease();
	if (index < 0)
	{
		return sprite;
	}
	BResource * pbres = BResource::getInstance();
	HTEXTURE tex(pbres->spritedata[index].tex, NULL);
	
	if (sprite)
	{
		if (!SetSpriteData(sprite, tex, pbres->spritedata[index].tex_x, pbres->spritedata[index].tex_y, pbres->spritedata[index].tex_w, pbres->spritedata[index].tex_h))
		{
			delete sprite;
			sprite = NULL;
		}
		else
		{
//			sprite->autorelease();
		}
	}
	return sprite;
}

bool SpriteItemManager::SetSpriteData(CCSprite * sprite, HTEXTURE _tex, float texx, float texy, float texw, float texh, bool flipx/* =false */, bool flipy/* =false */)
{
	if (!sprite)
	{
		return false;
	}
	LoadTextureWhenNeeded(_tex);
	BResource * pbres = BResource::getInstance();
	
	sprite->initWithTexture((CCTexture2D *)pbres->Texture_GetTexture(_tex));
	if (!SetSpriteTextureRect(sprite, texx, texy, texw, texh))
	{
		return false;
	}
	if (!SetSpriteFlip(sprite, flipx, flipy))
	{
		return false;
	}
	return true;
}

bool SpriteItemManager::SetSpriteTextureRect(CCSprite * sprite, float texx, float texy, float texw, float texh)
{
	if (!sprite)
	{
		return false;
	}
	sprite->setTextureRect(CCRectMake(texx, texy, texw, texh));
	return true;
}

bool SpriteItemManager::SetSpriteHotSpot(CCSprite * sprite, float hotx, float hoty)
{
	if (!sprite)
	{
		return false;
	}
	sprite->setAnchorPoint(ccp(hotx, hoty));
	return true;
}

bool SpriteItemManager::SetSpriteFlip(CCSprite * sprite, bool flipx/* =false */, bool flipy/* =false */)
{
	if (!sprite)
	{
		return false;
	}
	sprite->setFlipX(flipx);
	sprite->setFlipY(flipy);
	return true;
}

bool SpriteItemManager::CreateSprite(int index, CCSprite ** sprite)
{
	if (!sprite)
	{
		return false;
	}
	*sprite = CreateSprite(index);
	if (*sprite)
	{
		return true;
	}
	return false;
}

bool SpriteItemManager::ChangeSprite(int index, CCSprite * sprite)
{
	if (!sprite || index < 0)
	{
		return false;
	}
	BResource * pbres = BResource::getInstance();
	HTEXTURE tex(pbres->spritedata[index].tex, NULL);
	SetSpriteData(sprite, tex, pbres->spritedata[index].tex_x, pbres->spritedata[index].tex_y, pbres->spritedata[index].tex_w, pbres->spritedata[index].tex_h);
	return true;
}

CCSprite * SpriteItemManager::CreateSpriteByName(const char * spritename)
{
	int index = GetIndexByName(spritename);
	if (index >= 0)
	{
		return CreateSprite(index);
	}
	return NULL;
}

bool SpriteItemManager::CreateSpriteByName(const char * spritename, CCSprite ** sprite)
{
	if (!sprite)
	{
		return false;
	}
	*sprite = CreateSpriteByName(spritename);
	if (*sprite)
	{
		return true;
	}
	return false;
}

void SpriteItemManager::FreeSprite(CCSprite ** sprite)
{
	if (sprite && *sprite)
	{
		free(*sprite);
		*sprite = NULL;
	}
}

bool SpriteItemManager::SetRenderEx(CCSprite * sprite, float x, float y, int angle/* =0 */, float hscale/* =1.0f */, float vscale/* =0.0f */)
{
	if (!sprite)
	{
		return false;
	}
	sprite->setPosition(BGlobal::TranslatePosition(x, y));
	sprite->setRotation(ARC(angle));
	sprite->setScaleX(BGlobal::ScalerX(hscale));
	if (vscale == 0.0f)
	{
		vscale = hscale;
	}
	sprite->setScaleY(BGlobal::ScalerY(vscale));
	return true;
}

bool SpriteItemManager::LoadTextureWhenNeeded(HTEXTURE tex)
{	
	BResource * pbres = BResource::getInstance();
	if (pbres->Texture_GetTexture(tex) == NULL)
	{
		pbres->LoadTexture(tex.texindex);
		return true;
	}
	return false;
}
