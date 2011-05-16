#ifndef __HTEXTURE_H__
#define __HTEXTURE_H__

#include "MainDependency.h"

typedef struct tagHTextureInfo
{
	DWORD * tex;
	float texw;
	float texh;
}hTextureInfo;

class HTEXTURE
{
public:
	HTEXTURE()
	{
		_Init();
	};
	HTEXTURE(int _texindex, DWORD _tex)
	{
		_Init(_texindex, _tex);
	};
	HTEXTURE(DWORD _tex)
	{
		_Init(0, _tex);
	};

	HTEXTURE & operator = (DWORD _tex)
	{
		_Init(0, _tex);
		return *this;
	};
	DWORD GetTexture(int ntexinfo, hTextureInfo * texinfo)
	{
		if (!tex && texinfo && texindex<ntexinfo)
		{
			if (texinfo[texindex].tex)
			{
				return *texinfo[texindex].tex;
			}
			return NULL;
		}
		return tex;
	};
	int GetTextureWidthByInfo(int ntexinfo, hTextureInfo * texinfo)
	{
		if (!texinfo || texindex>=ntexinfo)
		{
			return 1;
		}
		return texinfo[texindex].texw;
	};
	int GetTextureHeightByInfo(int ntexinfo, hTextureInfo * texinfo)
	{
		if (!texinfo || texindex>=ntexinfo)
		{
			return 1;
		}
		return texinfo[texindex].texh;
	};
private:
	void _Init(int _texindex=0, DWORD _tex=NULL)
	{
		texindex=_texindex;
		tex = _tex;
	};
public:
	int texindex;
	DWORD tex;
};

#endif