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

	// Scene
	_gameobj.Register("PushScene", LuaFn_Game_PushScene);
	_gameobj.Register("PopScene", LuaFn_Game_PopScene);
	_gameobj.Register("ReplaceScene", LuaFn_Game_ReplaceScene);

	// Node
	_gameobj.Register("GetNode", LuaFn_Game_GetNode);

	_gameobj.Register("AddNullChild", LuaFn_Game_AddNullChild);

	// Sprite
	_gameobj.Register("CreateSprite", LuaFn_Game_CreateSprite);
	_gameobj.Register("AddSpriteChild", LuaFn_Game_AddSpriteChild);
	// Menu
	_gameobj.Register("CreateMenuItem", LuaFn_Game_CreateMenuItem);
	_gameobj.Register("AddMenuChild", LuaFn_Game_AddMenuChild);

	// Action
	_gameobj.Register("RunAction", LuaFn_Game_RunAction);

	_gameobj.Register("ActionMove", LuaFn_Game_ActionMove);
	_gameobj.Register("ActionRotate", LuaFn_Game_ActionRotate);
	_gameobj.Register("ActionScale", LuaFn_Game_ActionScale);
	_gameobj.Register("ActionEase", LuaFn_Game_ActionEase);
	_gameobj.Register("ActionFade", LuaFn_Game_ActionFade);
	_gameobj.Register("ActionSequence", LuaFn_Game_ActionSequence);
	_gameobj.Register("ActionSpawn", LuaFn_Game_ActionSpawn);
	_gameobj.Register("ActionRepeat", LuaFn_Game_ActionRepeat);
	_gameobj.Register("ActionDelay", LuaFn_Game_ActionDelay);
	_gameobj.Register("ActionCallFunc", LuaFn_Game_ActionCallFunc);

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

/************************************************************************/
/* Scene                                                                */
/************************************************************************/

int Export_Lua_Game::LuaFn_Game_PushScene(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// toptag

	int _tag = node.iNextGet();
	float _duration = 0.0f;
	node.jNextGet();
	if (node.bhavenext)
	{
		_duration = node.fGet();
	}
	CCScene * pScene = Export_Lua_Scene::_GetNewScene(_tag);
	if (pScene)
	{
		if (_duration)
		{
			CCDirector::sharedDirector()->pushScene(CCTransitionCrossFade::transitionWithDuration(_duration, pScene));
		}
		else
		{
			CCDirector::sharedDirector()->pushScene(pScene);
		}
		BGlobal::pushedscenecount++;
	}
	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_PopScene(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	if (BGlobal::pushedscenecount)
	{
		BGlobal::pushedscenecount--;
		CCDirector::sharedDirector()->popScene();
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_ReplaceScene(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// toptag
	int _tag = node.iNextGet();
	float _duration = 0.0f;
	node.jNextGet();
	if (node.bhavenext)
	{
		_duration = node.fGet();
	}
	CCScene * pScene = Export_Lua_Scene::_GetNewScene(_tag);
	if (pScene)
	{
		if (_duration)
		{
			CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::transitionWithDuration(_duration, pScene));
		}
		else
		{
			CCDirector::sharedDirector()->replaceScene(pScene);
		}
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetNode(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	node.jNextGet();
	if (node.ObjIsTable())
	{
		_LObjNode cnode(ls, &(node._obj), &node);
		CCNode * retval = _GetNowNode(&cnode);
		node.PDword((DWORD)retval);
	}

	_LEAVEFUNC_LUA;
}


int Export_Lua_Game::LuaFn_Game_AddNullChild(LuaState * ls)
{
	_ENTERFUNC_LUA(2);

	// {nodelist} {XYZT}
	node.jNextGet();
	if (node.ObjIsTable())
	{
		_LObjNode cnode(ls, &(node._obj), &node);
		CCNode * nownode = _GetNowNode(&cnode);
		if (!nownode)
		{
			break;
		}

		node.jNextGet();
		if (node.ObjIsTable())
		{
			float _x = 0.0f;
			float _y = 0.0f;
			int _zOrder = 0;
			int _tag = kCCNodeTagInvalid;
			_LObjNode tcnode(ls, &(node._obj), &node);
			_GetXYZT(&tcnode, &_x, &_y, &_zOrder, &_tag);

			CCNode * ccnode = CCNode::node();
			ccnode->setPosition(BGlobal::TranslatePosition(_x, _y));
			nownode->addChild(ccnode, _zOrder, _tag);

			node.PDword((DWORD)ccnode);
		}
	}

	_LEAVEFUNC_LUA;
}

/************************************************************************/
/* Sprite                                                               */
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
	// ({nodelist}, {XYZT}, labelstr, fontsize, font)

	CCMenuItem * item = NULL;

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

		char * _labelstr = NULL;
		char * _fontname = NULL;
		float _fontsize = 0;

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

			node.jNextGet();
			if (node.bhavenext)
			{
				// string
				if (node.ObjIsString())
				{
					_labelstr = (char *)node.sGet();
					node.jNextGet();
					if (node.bhavenext)
					{
						_fontsize = node.fGet();
						node.jNextGet();
						if (node.bhavenext)
						{
							_fontname = (char *)node.sGet();
						}
					}
				}
				else
				{
					// sprites
					_spnormal = (CCSprite *)node.dGet();
					if (_spnormal)
					{
						_spnormal->setContentSize(_spnormal->boundingBox().size);
					}
					node.jNextGet();
					if (node.bhavenext)
					{
						_spselected = (CCSprite *)node.dGet();
						if (_spselected)
						{
							_spselected->setContentSize(_spselected->boundingBox().size);
						}
						node.jNextGet();
						if (node.bhavenext)
						{
							_spdisabled = (CCSprite *)node.dGet();
							if (_spdisabled)
							{
								_spdisabled->setContentSize(_spdisabled->boundingBox().size);
							}
						}
					}
				}
			}

		}
		if (_labelstr)
		{
			CCLabelTTF* label = CCLabelTTF::labelWithString(_labelstr, _fontname?_fontname:M_DEFAULT_FONTNAME, _fontsize);
			item = CCMenuItemLabel::itemWithLabel(label, proto, cbfunc);
		}
		else
		{
			if (_spdisabled)
			{
				item = CCMenuItemSprite::itemFromNormalSprite(_spnormal, _spselected, _spdisabled, proto, cbfunc);
			}
			else
			{
				item = CCMenuItemSprite::itemFromNormalSprite(_spnormal, _spselected, proto, cbfunc);
			}
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

		if (!menu)
		{
			break;
		}

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

			if (!nownode)
			{
				break;
			}

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

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_RunAction(LuaState * ls)
{
	_ENTERFUNC_LUA(2);

	// item, action

	CCNode * _item = (CCNode *)node.dNextGet();

	if (!_item)
	{
		break;
	}

	CCAction * _action = (CCAction *)node.dNextGet();

	if (!_action)
	{
		break;
	}

	bool _repeatforever = false;

	CCAction * retval = NULL;

	node.jNextGet();
	if (node.bhavenext)
	{
		_repeatforever = node.bGet();
	}
	if (_repeatforever)
	{
		retval = _item->runAction(CCRepeatForever::actionWithAction((CCActionInterval *)_action));
	}
	else
	{
		retval = _item->runAction(_action);
	}

	node.PDword((DWORD)retval);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_ActionMove(LuaState * ls)
{
	_ENTERFUNC_LUA(2);

	// x y time relative

	float _x = node.fNextGet();
	float _y = node.fNextGet();
	float _time = 0;
	bool  _relative = false;

	node.jNextGet();
	if (node.bhavenext)
	{
		_time = node.fGet();
		node.jNextGet();
		if (node.bhavenext)
		{
			_relative = node.bGet();
		}
	}

	CCAction * retval = NULL;
	if (_relative)
	{
		retval = CCMoveBy::actionWithDuration(_time, BGlobal::TranslatePosition(_x, _y));
	}
	else
	{
		retval = CCMoveTo::actionWithDuration(_time, BGlobal::TranslatePosition(_x, _y));
	}
	node.PDword((DWORD)retval);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_ActionRotate(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// angle time relative

	int _angle = node.iNextGet();
	float _time = 0;
	bool _relative = false;

	node.jNextGet();
	if (node.bhavenext)
	{
		_time = node.fGet();
		node.jNextGet();
		if (node.bhavenext)
		{
			_relative = node.bGet();
		}
	}

	CCAction * retval = NULL;
	if (_relative)
	{
		retval = CCRotateBy::actionWithDuration(_time, ARC(_angle));
	}
	else
	{
		retval = CCRotateTo::actionWithDuration(_time, ARC(_angle));
	}
	node.PDword((DWORD)retval);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_ActionScale(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// sx sy time relative

	float _scalex = node.fNextGet();
	float _scaley = _scalex;
	float _time = 0;
	bool _relative = false;

	node.jNextGet();
	if (node.bhavenext)
	{
		_scaley = node.fGet();
		node.jNextGet();
		if (node.bhavenext)
		{
			_time = node.fGet();
			node.jNextGet();
			if (node.bhavenext)
			{
				_relative = node.bGet();
			}
		}
	}

	CCAction * retval = NULL;
	if (_relative)
	{
		retval = CCScaleBy::actionWithDuration(_time, _scalex, _scaley);
	}
	else
	{
		retval = CCScaleTo::actionWithDuration(_time, _scalex, _scaley);
	}
	node.PDword((DWORD)retval);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_ActionEase(LuaState * ls)
{
	_ENTERFUNC_LUA(3);

	// flag action rate

	int _flag = node.iNextGet();
	CCAction * _action = (CCAction *)node.dNextGet();
	if (!_action)
	{
		break;
	}
	float _rate = node.fNextGet();

	CCAction * retval = NULL;

	switch (_flag)
	{
	case M_CCACTIONFLAG_IN:
		retval = CCEaseIn::actionWithAction((CCActionInterval *)_action, _rate);
		break;
	case M_CCACTIONFLAG_OUT:
		retval = CCEaseOut::actionWithAction((CCActionInterval *)_action, _rate);
		break;
	case M_CCACTIONFLAG_INOUT:
		retval = CCEaseInOut::actionWithAction((CCActionInterval *)_action, _rate);
		break;
	}

	node.PDword((DWORD)retval);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_ActionFade(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// flag toval time
	int _flag = node.iNextGet();
	int _toval = -1;
	float _time = 0;

	node.jNextGet();
	if (node.bhavenext)
	{
		_toval = node.iGet();
		node.jNextGet();
		if (node.bhavenext)
		{
			_time = node.fGet();
		}
	}

	CCAction * retval = NULL;
	switch (_flag)
	{
	case M_CCACTIONFLAG_IN:
		retval = CCFadeIn::actionWithDuration(_time);
		break;
	case M_CCACTIONFLAG_OUT:
		retval = CCFadeOut::actionWithDuration(_time);
		break;
	default:
		retval = CCFadeTo::actionWithDuration(_time, _toval);
		break;
	}

	node.PDword((DWORD)retval);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_ActionSequence(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// {actionlist}

	node.jNextGet();
	if (node.ObjIsTable())
	{
		_LObjNode cnode(ls, &(node._obj), &node);
		cnode.jNextGet();
		if (!cnode.bhavenext)
		{
			break;
		}
		CCFiniteTimeAction * _pPrev = (CCFiniteTimeAction *)cnode.dGet();
		if (!_pPrev)
		{
			break;
		}

		cnode.jNextGet();
		while (cnode.bhavenext)
		{
			CCFiniteTimeAction * _pNow = (CCFiniteTimeAction *)cnode.dGet();
			if (!_pNow)
			{
				break;
			}
			_pPrev = CCSequence::actionOneTwo(_pPrev, _pNow);
			cnode.jNextGet();
		}
		node.PDword((DWORD)_pPrev);
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_ActionSpawn(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// {actionlist}

	node.jNextGet();
	if (node.ObjIsTable())
	{
		_LObjNode cnode(ls, &(node._obj), &node);
		cnode.jNextGet();
		if (!cnode.bhavenext)
		{
			break;
		}
		CCFiniteTimeAction * _pPrev = (CCFiniteTimeAction *)cnode.dGet();
		if (!_pPrev)
		{
			break;
		}

		cnode.jNextGet();
		while (cnode.bhavenext)
		{
			CCFiniteTimeAction * _pNow = (CCFiniteTimeAction *)cnode.dGet();
			if (!_pNow)
			{
				break;
			}
			_pPrev = CCSpawn::actionOneTwo(_pPrev, _pNow);
			cnode.jNextGet();
		}
		node.PDword((DWORD)_pPrev);
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_ActionRepeat(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// action, repeattime

	CCFiniteTimeAction * _action = (CCFiniteTimeAction *)node.dNextGet();
	if (!_action)
	{
		break;
	}
	int _repeattime = -1;

	node.jNextGet();
	if (node.bhavenext)
	{
		_repeattime = node.iGet();
	}

	CCAction * retval = NULL;
//	if (_repeattime < 0)
//	{
//		retval = CCRepeatForever::actionWithAction((CCActionInterval *)_action);
//	}
//	else
//	{
		retval = CCRepeat::actionWithAction(_action, _repeattime);
//	}
	node.PDword((DWORD)retval);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_ActionDelay(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// time

	float _time = node.fNextGet();
	CCAction * retval = CCDelayTime::actionWithDuration(_time);
	node.PDword((DWORD)retval);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_ActionCallFunc(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// {nodelist}
	node.jNextGet();
	if (node.ObjIsTable())
	{
		int scenetag = kCCNodeTagInvalid;
		_LObjNode tcnode(ls, &(node._obj), &node);
		CCNode * nownode = _GetNowNode(&tcnode, true, &scenetag);
		if (!nownode)
		{
			break;
		}
		SelectorProtocol * proto = NULL;
		SEL_MenuHandler cbfunc = NULL;
		SEL_CallFuncND cbndfunc = NULL;
		Export_Lua_Scene::_GetSceneMenuCallback(scenetag, &proto, &cbfunc, &cbndfunc);
		if (!proto || !cbfunc)
		{
			break;
		}
		CCAction * retval = CCCallFuncND::actionWithTarget(proto, (SEL_CallFuncND)cbndfunc, NULL);
		node.PDword((DWORD)retval);
	}

	_LEAVEFUNC_LUA;
}