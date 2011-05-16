#include "Export_Lua_Game.h"
#include "../Header/BResource.h"

#include "cocos2d.h"
#include "../Header/SpriteItemManager.h"

#include "Export_Lua_Scene.h"

#include "../Header/BGlobal.h"

using namespace cocos2d;

_LObjNode Export_Lua_Game::node;

bool Export_Lua_Game::_LuaRegistConst(LuaObject * obj)
{
	return true;
}

bool Export_Lua_Game::_LuaRegistFunction(LuaObject * obj)
{
	LuaObject _gameobj;
	_gameobj = obj->CreateTable("game");

	_gameobj.Register("Random_Int", LuaFn_Game_Random_Int);
	_gameobj.Register("Random_Float", LuaFn_Game_Random_Float);

	_gameobj.Register("FreeTexture", LuaFn_Game_LoadTexture);
	_gameobj.Register("FreeTexture", LuaFn_Game_FreeTexture);

	// Sprite
	_gameobj.Register("CreateSprite", LuaFn_Game_CreateSprite);
	_gameobj.Register("AddSpriteChild", LuaFn_Game_AddSpriteChild);
	//Menu
	_gameobj.Register("CreateMenuItem", LuaFn_Game_CreateMenuItem);
	_gameobj.Register("AddMenuChild", LuaFn_Game_AddMenuChild);

	return true;
}

int Export_Lua_Game::LuaFn_Game_Random_Int(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	int _imin = 0;
	int _imax = RAND_MAX;
	int _seed;
	int * _pseed = NULL;

	node.jNextGet();
	if (node.bhavenext)
	{
		_imin = node.iGet();
		node.jNextGet();
		if (node.bhavenext)
		{
			_imax = node.iGet();
			node.jNextGet();
			if (node.bhavenext)
			{
				_seed = node.iGet();
				_pseed = &_seed;
			}
		}
	}

	int _iret = randt(_imin, _imax, _pseed);
	node.PInt(_iret);
	if (_pseed)
	{
		node.PInt(_seed);
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_Random_Float(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	float _fmin = 0.0f;
	float _fmax = 1.0f;
	int _seed;
	int * _pseed = NULL;

	node.jNextGet();
	if (node.bhavenext)
	{
		_fmin = node.fGet();
		node.jNextGet();
		if (node.bhavenext)
		{
			_fmax = node.fGet();
			node.jNextGet();
			if (node.bhavenext)
			{
				_seed = node.iGet();
				_pseed = &_seed;
			}
		}
	}

	float _fret = randtf(_fmin, _fmax, _pseed);
	node.PFloat(_fret);
	if (_pseed)
	{
		node.PInt(_seed);
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_LoadTexture(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	int _texindex = -1;

	node.jNextGet();
	if (node.bhavenext)
	{
		_texindex = node.iGet();
	}

	bool bret = BResource::getInstance()->LoadTexture(_texindex);
	node.PBoolean(bret);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_FreeTexture(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	int _texindex = -1;

	node.jNextGet();
	if (node.bhavenext)
	{
		_texindex = node.iGet();
	}

	bool bret = BResource::getInstance()->FreeTexture(_texindex);
	node.PBoolean(bret);

	_LEAVEFUNC_LUA;
}

/************************************************************************/
/* Game                                                                 */
/************************************************************************/

CCNode * Export_Lua_Game::_GetNowNode(_LObjNode * cnode, bool topnode /* = false */, int * scenetag /* = NULL */)
{
	if (!cnode)
	{
		return NULL;
	}
	CCNode * nownode = NULL;
	if (scenetag)
	{
		*scenetag = kCCNodeTagInvalid;
	}

	cnode->jNextGet();
	if (!cnode->bhavenext)
	{
		return NULL;
	}

	int _ktag = cnode->iGet();
	int _ktagtop = _ktag;
	nownode = Export_Lua_Scene::_GetSceneNode(&_ktagtop);
	if (scenetag)
	{
		*scenetag = _ktagtop;
	}
	
	if (topnode)
	{
		return nownode;
	}

	if (!nownode)
	{
		return NULL;
	}

	if (_ktagtop != _ktag)
	{
		nownode = nownode->getChildByTag(_ktag);
	}

	do
	{
		cnode->jNextGet();
		if (cnode->bhavenext)
		{
			_ktag = cnode->iGet();
			nownode = nownode->getChildByTag(_ktag);
			if (!nownode)
			{
				return NULL;
			}
		}
	} while (cnode->bhavenext);

	return nownode;
}

bool Export_Lua_Game::_GetXYZT(_LObjNode * cnode, float *x/* =NULL */, float *y/* =NULL */, int *zOrder/* =NULL */, int *tag/* =NULL */)
{
	if (!cnode)
	{
		return false;
	}

	cnode->jNextGet();
	if (cnode->bhavenext)
	{
		if (x)
		{
			*x = cnode->fGet();
		}
		cnode->jNextGet();
		if (cnode->bhavenext)
		{
			if (y)
			{
				*y = cnode->fGet();
			}
			cnode->jNextGet();
			if (cnode->bhavenext)
			{
				if (zOrder)
				{
					*zOrder = cnode->iGet();
				}
				cnode->jNextGet();
				if (cnode->bhavenext)
				{
					if (tag)
					{
						*tag = cnode->iGet();
					}
				}
			}
		}
	}

	return true;
}

/************************************************************************/
/* Func                                                                 */
/************************************************************************/

int Export_Lua_Game::LuaFn_Game_CreateSprite(LuaState * ls)
{
	// (siid, {x, y, angle, hscale, vscale}, tag)

	_ENTERFUNC_LUA(1);

	// siid
	int _siid = node.iNextGet();
	CCSprite * sprite = SpriteItemManager::CreateSprite(_siid);
	node.PDword((DWORD)sprite);

	float _x = 0.0f;
	float _y = 0.0f;
	int _angle = 0;
	float _hscale = 1.0f;
	float _vscale = 0.0f;
	int _tag = kCCNodeTagInvalid;

	node.jNextGet();
	if (node.bhavenext && node.ObjIsTable())
	{
		_LObjNode cnode(ls, &(node._obj), &node);

		cnode.jNextGet();
		if (cnode.bhavenext)
		{
			_x = cnode.fGet();
			cnode.jNextGet();
			if (cnode.bhavenext)
			{
				_y = cnode.fGet();
				cnode.jNextGet();
				if (cnode.bhavenext)
				{
					_angle = cnode.iGet();
					cnode.jNextGet();
					if (cnode.bhavenext)
					{
						_hscale = cnode.fGet();
						cnode.jNextGet();
						if (cnode.bhavenext)
						{
							_vscale = cnode.fGet();
						}
					}
				}
			}
		}

		node.jNextGet();
		if (node.bhavenext)
		{
			_tag = node.iGet();
			if (sprite)
			{
				sprite->setTag(_tag);
			}
		}
	}

	SpriteItemManager::SetRenderEx(sprite, _x, _y, _angle, _hscale, _vscale);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_AddSpriteChild(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// (sprite, {nodelist}, zOrder)

	CCSprite * sprite = (CCSprite *)node.dNextGet();
	if (!sprite)
	{
		break;
	}

	// kTag
	node.jNextGet();

	if (node.bhavenext && node.ObjIsTable())
	{
		_LObjNode tcnode(ls, &(node._obj), &node);
		CCNode * nownode = _GetNowNode(&tcnode);

		if (nownode)
		{
			int _zOrder = 0;
			int _tag = kCCNodeTagInvalid;

			node.jNextGet();
			if (node.bhavenext)
			{
				_zOrder = node.iGet();
			}
			nownode->addChild(sprite, _zOrder);
		}
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_CreateMenuItem(LuaState * ls)
{
	_ENTERFUNC_LUA(4);

	// ({nodelist}, {XYZT}, spnormal, spselected, spdisabled)

	CCMenuItemSprite * item = NULL;

	// nodelist
	node.jNextGet();
	if (node.bhavenext && node.ObjIsTable())
	{
		int scenetag = kCCNodeTagInvalid;
		_LObjNode tcnode(ls, &(node._obj), &node);
		CCNode * nownode = _GetNowNode(&tcnode, true, &scenetag);
		SelectorProtocol * proto = NULL;
		SEL_MenuHandler cbfunc = NULL;
		Export_Lua_Scene::_GetSceneMenuCallback(scenetag, &proto, &cbfunc);
		if (!proto || !cbfunc)
		{
			break;
		}

		CCSprite * _spnormal = NULL;
		CCSprite * _spselected = NULL;
		CCSprite * _spdisabled = NULL;
		float _x = 0.0f;
		float _y = 0.0f;
		int _zOrder = 0;
		int _tag = kCCNodeTagInvalid;

		// xyzt
		node.jNextGet();
		if (node.bhavenext && node.ObjIsTable())
		{
			_LObjNode cnode(ls, &(node._obj), &node);
			_GetXYZT(&cnode, &_x, &_y, &_zOrder, &_tag);

			// sprites
			node.jNextGet();
			if (node.bhavenext)
			{
				_spnormal = (CCSprite *)node.dGet();
				node.jNextGet();
				if (node.bhavenext)
				{
					_spselected = (CCSprite *)node.dGet();
					node.jNextGet();
					if (node.bhavenext)
					{
						_spdisabled = (CCSprite *)node.dGet();
					}
				}
			}

		}
		if (_spdisabled)
		{
			item = CCMenuItemSprite::itemFromNormalSprite(_spnormal, _spselected, _spdisabled, proto, cbfunc);
		}
		else
		{
			item = CCMenuItemSprite::itemFromNormalSprite(_spnormal, _spselected, proto, cbfunc);
		}
		item->setPosition(BGlobal::TranslatePosition(_x, _y));
		item->setTag(_tag);
	}

	node.PDword((DWORD)item);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_AddMenuChild(LuaState * ls)
{
	_ENTERFUNC_LUA(3);

	// ({menulist}, {nodelist}, {x, y, z, t})

	// menus
	node.jNextGet();
	if (node.bhavenext && node.ObjIsTable())
	{
		_LObjNode cnode(ls, &(node._obj), &node);
		CCMenuItem * _item = (CCMenuItem *)cnode.dNextGet();
		CCMenu * menu = CCMenu::menuWithItems(_item, NULL);

		if (menu)
		{
			do 
			{
				cnode.jNextGet();
				if (cnode.bhavenext)
				{
					CCMenuItem * _titem = (CCMenuItem *)cnode.dGet();
					menu->addChild(_titem, _titem->getZOrder());
				}
			} while (cnode.bhavenext);

			// nodelist
			node.jNextGet();
			if (node.bhavenext)
			{
				_LObjNode _ttcnode(ls, &(node._obj), &node);
				CCNode * nownode = _GetNowNode(&_ttcnode);
				if (nownode)
				{
					float _x = 0.0f;
					float _y = 0.0f;
					int _zOrder = 0;
					int _tag = kCCNodeTagInvalid;

					// XYZT
					node.jNextGet();
					if (node.bhavenext && node.ObjIsTable())
					{
						_LObjNode tcnode(ls, &(node._obj), &node);
						_GetXYZT(&tcnode, &_x, &_y, &_zOrder, &_tag);
					}
					nownode->addChild(menu, _zOrder, _tag);
					menu->setPosition(BGlobal::TranslatePosition(_x, _y));
				}
			}
		}
	}

	_LEAVEFUNC_LUA;
}