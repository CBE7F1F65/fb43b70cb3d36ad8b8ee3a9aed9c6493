#include "Export_Lua_Game.h"
#include "../Header/BResource.h"

#include "cocos2d.h"
#include "../Header/SpriteItemManager.h"

#include "Export_Lua_Scene.h"

#include "../Header/BGlobal.h"

#include "../Classes/InputLayer.h"
#include "../Classes/TouchLayer.h"

#include "../Header/GameMain.h"

#include "../Header/CCActionExpand.h"
#include "../Header/SceneConst.h"


#if defined __IPHONE
#define M_DEFAULT_FONTNAME	"CourierNewPS-BoldMT"
#else
#define M_DEFAULT_FONTNAME	"Courier New Bold"
#endif

#define M_CAMERA_EYE	0x00
#define M_CAMERA_CENTER	0x01
#define M_CAMERA_UP		0x02

using namespace cocos2d;

_LObjNode Export_Lua_Game::node;

bool Export_Lua_Game::_LuaRegistConst(LuaObject * obj)
{
	obj->SetInteger("STATE_ST_Null", GAMESTATE_ST_NULL);
	obj->SetInteger("STATE_ST_Standby", GAMESTATE_ST_STANDBY);
	obj->SetInteger("STATE_ST_Progressing", GAMESTATE_ST_PROGRESSING);
	obj->SetInteger("STATE_ST_StepForward", GAMESTATE_ST_STEPFORWARD);
	obj->SetInteger("STATE_ST_Error", GAMESTATE_ST_ERROR);
	obj->SetInteger("STATE_ST_Finished", GAMESTATE_ST_FINISHED);

	obj->SetInteger("STATE_Waiting", GAMESTATE_WAITING);
	obj->SetInteger("STATE_ShowHelp", GAMESTATE_SHOWHELP);
	obj->SetInteger("STATE_ShowTarget", GAMESTATE_SHOWTARGET);
	obj->SetInteger("STATE_EnemyEnter", GAMESTATE_ENEMYENTER);

	obj->SetInteger("STATE_AddEnemy", GAMESTATE_ADDENEMY);
	obj->SetInteger("STATE_HPAPRegain", GAMESTATE_HPAPREGAIN);
	obj->SetInteger("STATE_ShowTurnStart", GAMESTATE_SHOWTURNSTART);
	obj->SetInteger("STATE_Planning", GAMESTATE_PLANNING);
	obj->SetInteger("STATE_SelfAction", GAMESTATE_SELFACTION);
	obj->SetInteger("STATE_EnemyAction", GAMESTATE_ENEMYACTION);
	obj->SetInteger("STATE_Over", GAMESTATE_OVER);

	obj->SetInteger("GESTURE_Unknown", M_TOUCHGESTURE_UNKNOWN);
	obj->SetInteger("GESTURE_OneNoMove", M_TOUCHGESTURE_ONE_NOMOVE);
	obj->SetInteger("GESTURE_OneMoved", M_TOUCHGESTURE_ONE_MOVED);
	obj->SetInteger("GESTURE_TwoNoMove", M_TOUCHGESTURE_TWO_NOMOVE);
	obj->SetInteger("GESTURE_TwoMoved", M_TOUCHGESTURE_TWO_MOVED);

	obj->SetInteger("TOUCH_Tap", M_CCTOUCH_TAP);
	obj->SetInteger("TOUCH_Hold", M_CCTOUCH_HOLD);
	obj->SetInteger("TOUCH_Move", M_CCTOUCH_MOVE);
	obj->SetInteger("TOUCH_HoldAndMove", M_CCTOUCH_HOLDANDMOVE);

	obj->SetInteger("CAMERA_Eye", M_CAMERA_EYE);
	obj->SetInteger("CAMERA_Center", M_CAMERA_CENTER);
	obj->SetInteger("CAMERA_Up", M_CAMERA_UP);

	obj->SetInteger("WEAPON_Laser", M_WEAPON_LASER);
	obj->SetInteger("WEAPON_Bomb", M_WEAPON_BOMB);
	obj->SetInteger("WEAPON_Sniper", M_WEAPON_SNIPER);

	obj->SetInteger("ENEMY_InScene", ENEMY_INSCENE);
	obj->SetInteger("ENEMY_OnSide", ENEMY_ONSIDE);

	obj->SetInteger("HPMax", M_GAMEHPMAX);
	obj->SetInteger("APMax", M_GAMEAPMAX);
	obj->SetInteger("SPMax", M_GAMESPMAX);

	return true;
}

bool Export_Lua_Game::_LuaRegistFunction(LuaObject * obj)
{
	LuaObject _gameobj;
	_gameobj = obj->CreateTable("game");

	_LuaRegistFunction_Mission(&_gameobj);

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
	_gameobj.Register("RemoveChild", LuaFn_Game_RemoveChild);
	_gameobj.Register("RemoveAllChildren", LuaFn_Game_RemoveAllChildren);

	// RenderTexture
	_gameobj.Register("AddRenderTextureChild", LuaFn_Game_AddRenderTextureChild);
	_gameobj.Register("RenderTextureBegin", LuaFn_Game_RenderTextureBegin);
	_gameobj.Register("RenderTextureEnd", LuaFn_Game_RenderTextureEnd);
	_gameobj.Register("NodeVisit", LuaFn_Game_NodeVisit);

	// Sprite
	_gameobj.Register("GetSIData", LuaFn_Game_GetSIData);

	_gameobj.Register("CreateSprite", LuaFn_Game_CreateSprite);
	_gameobj.Register("AddSpriteChild", LuaFn_Game_AddSpriteChild);

	// Text
	_gameobj.Register("AddTextChild", LuaFn_Game_AddTextChild);

	// Menu
	_gameobj.Register("CreateMenuItem", LuaFn_Game_CreateMenuItem);
	_gameobj.Register("SetMenuEnabled", LuaFn_Game_SetMenuEnabled);
	_gameobj.Register("SetMenuItemEnabled", LuaFn_Game_SetMenuItemEnabled);
	_gameobj.Register("AddMenuChild", LuaFn_Game_AddMenuChild);
	
	// Overlay
	_gameobj.Register("AddOverlayLayerChild", LuaFn_Game_AddOverlayChild);
	_gameobj.Register("GetOverlayLayer", LuaFn_Game_GetOverlayLayer);

	// Input
	_gameobj.Register("AddInputLayerChild", LuaFn_Game_AddInputLayerChild);

	// Touch
	_gameobj.Register("AddTouchLayerChild", LuaFn_Game_AddTouchLayerChild);
	_gameobj.Register("SetTouchLayerRect", LuaFn_Game_SetTouchLayerRect);
	_gameobj.Register("GetTouchInfo", LuaFn_Game_GetTouchInfo);

	// Action
	_gameobj.Register("RunAction", LuaFn_Game_RunAction);
	_gameobj.Register("StopAction", LuaFn_Game_StopAction);

	// Layer
	_gameobj.Register("SetTouchEnabled", LuaFn_Game_SetTouchEnabled);
	_gameobj.Register("SetIsVisible", LuaFn_Game_SetIsVisible);

	_gameobj.Register("GetSubTags", LuaFn_Game_GetSubTags);

	// Camera
	_gameobj.Register("CameraGet", LuaFn_Game_CameraGet);
	_gameobj.Register("CameraSet", LuaFn_Game_CameraSet);

	_gameobj.Register("SetPosition", LuaFn_Game_SetPosition);
	_gameobj.Register("GetPosition", LuaFn_Game_GetPosition);
	_gameobj.Register("SetZ", LuaFn_Game_SetZ);
	_gameobj.Register("GetZ", LuaFn_Game_GetZ);
	_gameobj.Register("SetAngle", LuaFn_Game_SetAngle);
	_gameobj.Register("GetAngle", LuaFn_Game_GetAngle);
	_gameobj.Register("SetScale", LuaFn_Game_SetScale);
	_gameobj.Register("GetScale", LuaFn_Game_GetScale);
	_gameobj.Register("SetColor", LuaFn_Game_SetColor);
	_gameobj.Register("GetColor", LuaFn_Game_GetColor);
	_gameobj.Register("SetAnchor", LuaFn_Game_SetAnchor);

	_gameobj.Register("ActionMove", LuaFn_Game_ActionMove);
	_gameobj.Register("ActionRotate", LuaFn_Game_ActionRotate);
	_gameobj.Register("ActionScale", LuaFn_Game_ActionScale);
	_gameobj.Register("ActionEase", LuaFn_Game_ActionEase);
	_gameobj.Register("ActionFade", LuaFn_Game_ActionFade);
	_gameobj.Register("ActionTint", LuaFn_Game_ActionTint);
	_gameobj.Register("ActionSequence", LuaFn_Game_ActionSequence);
	_gameobj.Register("ActionSpawn", LuaFn_Game_ActionSpawn);
	_gameobj.Register("ActionRepeat", LuaFn_Game_ActionRepeat);
	_gameobj.Register("ActionDelay", LuaFn_Game_ActionDelay);
	_gameobj.Register("ActionDelete", LuaFn_Game_ActionDelete);
	_gameobj.Register("ActionDeleteChildren", LuaFn_Game_ActionDeleteChildren);
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

	CCLayer * toplayer = (CCLayer *)cnode->dGet();
	if (!toplayer)
	{
		return NULL;
	}
	nownode = toplayer;

	cnode->jNextGet();
	if (!cnode->bhavenext)
	{
		return NULL;
	}

	int _ktag = cnode->iGet();

	int _ktagtop = Export_Lua_Scene::_GetTopTag(_ktag);
	int _ktagsublayer = Export_Lua_Scene::_GetSubLayerTag(_ktag);
	int _ktagmenugroup = Export_Lua_Scene::_GetMenuGroupTag(_ktag);
	int _ktagmenuitem = Export_Lua_Scene::_GetMenuItemTag(_ktag);
//	nownode = toplayer->getChildByTag(_ktagtop);

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

	//
	int _nowktag = _ktagtop;
	if (_nowktag != _ktag && nownode)
	{
		_nowktag += _ktagsublayer;
		nownode = nownode->getChildByTag(_nowktag);
		if (_nowktag != _ktag && nownode)
		{
			_nowktag += _ktagmenugroup;
			nownode = nownode->getChildByTag(_nowktag);
			if (_nowktag != _ktag && nownode)
			{
				_nowktag += _ktagmenuitem;
				nownode = nownode->getChildByTag(_nowktag);
				if (_nowktag != _ktag && nownode)
				{
					nownode = nownode->getChildByTag(_ktag);
				}
			}
		}
	}

	do
	{
		cnode->jNextGet();
		if (cnode->bhavenext)
		{
			_ktag = cnode->iGet();
			if (!nownode)
			{
				return NULL;
			}
			nownode = nownode->getChildByTag(_ktag);
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

CCRect Export_Lua_Game::_GetRect(_LObjNode* cnode)
{
	if (!cnode)
	{
		return CCRectZero;
	}

	float x=0;
	float y=0;
	float width=0;
	float height=0;
	cnode->jNextGet();
	if (cnode->bhavenext)
	{
		x = cnode->fGet();
		cnode->jNextGet();
		if (cnode->bhavenext)
		{
			y = cnode->fGet();
			cnode->jNextGet();
			if (cnode->bhavenext)
			{
				width = cnode->fGet();
				cnode->jNextGet();
				if (cnode->bhavenext)
				{
					height = cnode->fGet();
				}
			}
		}
	}
	return BGlobal::ScalerRect(CCRectMake(x, y, width, height));
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

	CCNode * retval = NULL;
	node.jNextGet();
	if (node.ObjIsTable())
	{
		_LObjNode cnode(ls, &(node._obj), &node);
		retval = _GetNowNode(&cnode);
	}
	node.PDword((DWORD)retval);

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

			CCLayer * addednode = CCLayer::node();
			addednode->setPosition(BGlobal::TranslatePosition(_x, _y));
			nownode->addChild(addednode, _zOrder, _tag);

			node.PDword((DWORD)addednode);
		}
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_RemoveChild(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// {nodelist}, bcleanup
	// item, bcleanup

	CCNode * nownode = NULL;
	node.jNextGet();
	if (node.ObjIsTable())
	{
		_LObjNode cnode(ls, &(node._obj), &node);
		nownode = _GetNowNode(&cnode);
	}
	else
	{
		nownode = (CCNode *)node.dGet();
	}

	if (!nownode)
	{
		break;
	}

	bool _bcleanup = true;
	node.jNextGet();
	if (node.bhavenext)
	{
		_bcleanup = node.bGet();
	}
	nownode->removeFromParentAndCleanup(_bcleanup);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_RemoveAllChildren(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// {nodelist}, bcleanup
	// item, bcleanup
	CCNode * nownode = NULL;
	node.jNextGet();
	if (node.ObjIsTable())
	{
		_LObjNode cnode(ls, &(node._obj), &node);
		nownode = _GetNowNode(&cnode);
	}
	else
	{
		nownode = (CCNode *)node.dGet();
	}

	if (!nownode)
	{
		break;
	}

	bool _bcleanup = true;
	node.jNextGet();
	if (node.bhavenext)
	{
		_bcleanup = node.bGet();
	}
	nownode->removeAllChildrenWithCleanup(_bcleanup);

	_LEAVEFUNC_LUA;
}

/************************************************************************/
/* RenderTexture                                                        */
/************************************************************************/

int Export_Lua_Game::LuaFn_Game_AddRenderTextureChild(LuaState * ls)
{
	_ENTERFUNC_LUA(3);

	// (width, height, {nodelist}, {XYZT})
	float _width = BGlobal::ScalerX(node.fNextGet());
	float _height = BGlobal::ScalerY(node.fNextGet());
	node.jNextGet();
	if (node.ObjIsTable())
	{
		_LObjNode tcnode(ls, &(node._obj), &node);
		CCNode * nownode = _GetNowNode(&tcnode);
		if (!nownode)
		{
			break;
		}
		float _x = 0;
		float _y = 0;
		int _zOrder = 0;
		int _tag = kCCNodeTagInvalid;

		node.jNextGet();
		if (node.bhavenext)
		{
			_LObjNode cnode(ls, &(node._obj), &node);
			_GetXYZT(&cnode, &_x, &_y, &_zOrder, &_tag);
		}

		CCRenderTexture * item = CCRenderTexture::renderTextureWithWidthAndHeight(_width, _height);
		nownode->addChild(item, _zOrder, _tag);
		item->setPosition(BGlobal::TranslatePosition(_x, _y));

		node.PDword((DWORD)item);
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_RenderTextureBegin(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// item bclean
	CCRenderTexture * _item = (CCRenderTexture *)node.dNextGet();
	if (!_item)
	{
		break;
	}
	bool _bclean = false;
	node.jNextGet();
	if (node.bhavenext)
	{
		_bclean = node.bGet();
	}
	if (_bclean)
	{
		_item->beginWithClear(0, 0, 0, 0);
	}
	else
	{
		_item->begin();
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_RenderTextureEnd(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// item
	CCRenderTexture * _item = (CCRenderTexture *)node.dNextGet();
	if (!_item)
	{
		break;
	}
	_item->end();

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_NodeVisit(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// item, x, y
	CCNode * _item = (CCNode *)node.dNextGet();

	node.jNextGet();
	if (node.bhavenext)
	{
		float _x = node.fGet();
		float _y = BGlobal::RScalerY(_item->getPosition().y);
		node.jNextGet();
		if (node.bhavenext)
		{
			_y = node.fGet();
		}
		_item->setPosition(BGlobal::TranslatePosition(_x, _y));
	}
	_item->visit();

	_LEAVEFUNC_LUA;
}

/************************************************************************/
/* Sprite                                                               */
/************************************************************************/

int Export_Lua_Game::LuaFn_Game_GetSIData(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// siid -> width, height
	int _siid = node.iNextGet();
	float _width = 0;
	float _height = 0;
	spriteData * spdata = SpriteItemManager::CastSprite(_siid);
	if (spdata)
	{
		_width = spdata->tex_w;
		_height = spdata->tex_h;
	}
	node.PFloat(_width);
	node.PFloat(_height);

	_LEAVEFUNC_LUA;
}

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

			node.jNextGet();
			if (node.bhavenext)
			{
				_zOrder = node.iGet();
			}
			nownode->addChild(sprite, _zOrder);

		}
	}
	node.PDword((DWORD)sprite);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_AddTextChild(LuaState * ls)
{
	_ENTERFUNC_LUA(4);

	// {nodelist}, {XYZT}, str, fontsize, font

	CCLabelTTF * item = NULL;

	float _x = 0.0f;
	float _y = 0.0f;
	int _zOrder = 0;
	int _tag = kCCNodeTagInvalid;

	char * _labelstr = NULL;
	char * _fontname = NULL;
	float _fontsize = 0;
	node.jNextGet();
	if (node.ObjIsTable())
	{
		_LObjNode tcnode(ls, &(node._obj), &node);
		CCNode * nownode = _GetNowNode(&tcnode);
		if (!nownode)
		{
			break;
		}

		node.jNextGet();
		if (node.ObjIsTable())
		{
			_LObjNode cnode(ls, &(node._obj), &node);
			_GetXYZT(&cnode, &_x, &_y, &_zOrder, &_tag);
		}

		_labelstr = (char *)node.sNextGet();
		_fontsize = node.fNextGet();
		_fontsize = BGlobal::Scaler(_fontsize);
		node.jNextGet();
		if (node.bhavenext)
		{
			_fontname = (char *)node.sGet();
		}
		item = CCLabelTTF::labelWithString(_labelstr, _fontname?(strlen(_fontname)?_fontname:M_DEFAULT_FONTNAME):M_DEFAULT_FONTNAME, _fontsize);
		if (item)
		{
			nownode->addChild(item, _zOrder, _tag);
			item->setPosition(BGlobal::TranslatePosition(_x, _y));
			node.PDword((DWORD)item);
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
		Export_Lua_Scene::_GetSceneMenuCallback(scenetag, &cbfunc);
		proto = nownode;
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
						_fontsize = BGlobal::Scaler(_fontsize);
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
			CCLabelTTF* label = CCLabelTTF::labelWithString(_labelstr, _fontname?(strlen(_fontname)?_fontname:M_DEFAULT_FONTNAME):M_DEFAULT_FONTNAME, _fontsize);
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

int Export_Lua_Game::LuaFn_Game_SetMenuEnabled(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	CCMenu * _item = (CCMenu *)node.dNextGet();
	if (!_item)
	{
		break;
	}
	bool _benable = true;
	node.jNextGet();
	if (node.bhavenext)
	{
		_benable = node.bGet();
	}

	CCArray * pChildren = _item->getChildren();
	if (pChildren && pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(pChildren, pObject)
		{
			CCMenuItem* pChild = (CCMenuItem*) pObject;
			if (pChild)
			{
				pChild->setIsEnabled(_benable);
			}
		}
	}	


	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_SetMenuItemEnabled(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	CCMenuItem * _item = (CCMenuItem *)node.dNextGet();
	if (!_item)
	{
		break;
	}
	bool _benable = true;
	node.jNextGet();
	if (node.bhavenext)
	{
		_benable = node.bGet();
	}

	_item->setIsEnabled(_benable);

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
		node.PDword((DWORD)menu);
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_AddOverlayChild(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	CCLayer * _toplayer = (CCLayer *)node.dNextGet();
	if (!_toplayer)
	{
		break;
	}
	float _x = 0.0f;
	float _y = 0.0f;
	int _zOrder = 0;
	int _tag = KTAG_OVERLAYLAYER;
	node.jNextGet();
	if (node.bhavenext && node.ObjIsTable())
	{
		int _ttag;
		_LObjNode tcnode(ls, &(node._obj), &node);
		_GetXYZT(&tcnode, &_x, &_y, &_zOrder, &_ttag);
	}
	CCLayer * addednode = CCLayer::node();
	addednode->setPosition(BGlobal::TranslatePosition(_x, _y));
	_toplayer->getParent()->addChild(addednode, _zOrder, _tag);
	node.PDword((DWORD)addednode);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetOverlayLayer(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	CCLayer * _toplayer = (CCLayer *)node.dNextGet();
	if (!_toplayer)
	{
		break;
	}
	CCNode * layer = _toplayer->getParent()->getChildByTag(KTAG_OVERLAYLAYER);
	node.PDword((DWORD)layer);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_AddInputLayerChild(LuaState * ls)
{
	_ENTERFUNC_LUA(2);

	// {toplayer, Rect, text, fontname, fontsize, inputmax, defaulttext}, {nodelist}, {XYZT}
	node.jNextGet();
	if (node.ObjIsTable())
	{
		_LObjNode cnode(ls, &(node._obj), &node);
		CCLayer * _toplayer = (CCLayer *)cnode.dNextGet();
		if (!_toplayer)
		{
			break;
		}
		cnode.jNextGet();
		if (cnode.bhavenext && cnode.ObjIsTable())
		{
			_LObjNode ccnode(ls, &(cnode._obj), &node);
			CCRect _rect = _GetRect(&ccnode);
			const char * _text = cnode.sNextGet();
			const char * _fontname = cnode.sNextGet();
			float _fontsize = BGlobal::Scaler(cnode.fNextGet());
			int _inputmax = cnode.iNextGet();
			const char * _defaulttext = cnode.sNextGet();

			node.jNextGet();
			_LObjNode tcnode(ls, &(node._obj), &node);
			CCNode * nownode = _GetNowNode(&tcnode);

			InputLayer * pInputLayer = NULL;
			if (nownode)
			{
				float _x = 0;
				float _y = 0;
				int _zOrder = 0;
				int _tag = kCCNodeTagInvalid;

				node.jNextGet();
				if (node.bhavenext)
				{
					_LObjNode ttcnode(ls, &(node._obj), &node);
					_GetXYZT(&ttcnode, &_x, &_y, &_zOrder, &_tag);
				}

				pInputLayer = InputLayer::node();
				if (pInputLayer)
				{
					pInputLayer->initWithInputData(_toplayer, _rect, _text, strlen(_fontname)?_fontname:M_DEFAULT_FONTNAME, _fontsize, _inputmax, _defaulttext);
					nownode->addChild(pInputLayer, _zOrder, _tag);
					pInputLayer->setPosition(BGlobal::TranslatePosition(_x, _y));
				}
			}

			node.PDword((DWORD)pInputLayer);
		}
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_AddTouchLayerChild(LuaState * ls)
{
	_ENTERFUNC_LUA(2);

	// {toplayer, Rect}, {nodelist}, {XYZT}
	node.jNextGet();
	if (node.ObjIsTable())
	{
		_LObjNode cnode(ls, &(node._obj), &node);
		CCLayer * _toplayer = (CCLayer *)cnode.dNextGet();
		if (!_toplayer)
		{
			break;
		}
		cnode.jNextGet();
		if (cnode.bhavenext && cnode.ObjIsTable())
		{
			_LObjNode ccnode(ls, &(cnode._obj), &node);
			CCRect _rect = _GetRect(&ccnode);

			node.jNextGet();
			_LObjNode tcnode(ls, &(node._obj), &node);
			CCNode * nownode = _GetNowNode(&tcnode);

			TouchLayer * pTouchLayer = NULL;
			if (nownode)
			{
				float _x = 0;
				float _y = 0;
				int _zOrder = 0;
				int _tag = kCCNodeTagInvalid;

				node.jNextGet();
				if (node.bhavenext)
				{
					_LObjNode ttcnode(ls, &(node._obj), &node);
					_GetXYZT(&ttcnode, &_x, &_y, &_zOrder, &_tag);
				}

				pTouchLayer = TouchLayer::node();
				if (pTouchLayer)
				{
					pTouchLayer->initWithRect(_toplayer, _rect);
					nownode->addChild(pTouchLayer, _zOrder, _tag);
					pTouchLayer->setPosition(BGlobal::TranslatePosition(_x, _y));
				}
				node.PDword((DWORD)pTouchLayer);
			}
		}
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_SetTouchLayerRect(LuaState * ls)
{
	_ENTERFUNC_LUA(2);

	TouchLayer * _touchlayer = (TouchLayer *)node.dNextGet();
	if (!_touchlayer)
	{
		break;
	}
	node.jNextGet();
	if (node.ObjIsTable())
	{
		_LObjNode cnode(ls, &(node._obj), &node);
		CCRect _rect = _GetRect(&cnode);
		_touchlayer->setTouchRect(_rect);
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetTouchInfo(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// touchlayer, index, ccti -> x, y, time, touchtype, rectx, recty, rectw, recth

	TouchLayer * _touchlayer = (TouchLayer *)node.dNextGet();
	if (!_touchlayer)
	{
		break;
	}

	int _index = 0;
	int _flag = M_CCTOUCHINDICATOR_BEGAN;
	node.jNextGet();
	if (node.bhavenext)
	{
		_index = node.iGet();
		node.jNextGet();
		if (node.bhavenext)
		{
			_flag = node.iGet();
		}
	}
	float x;
	float y;
	LONGLONG time;
	CCRect rect;

	_touchlayer->GetTouchData(_index, _flag, &x, &y, &time, &rect);
	int touchtype = M_CCTOUCH_TAP;
	if (_flag != M_CCTOUCHINDICATOR_BEGAN)
	{
		touchtype = _touchlayer->GetTouchType(_index);
	}

	x = BGlobal::RScalerX(x);
	y = BGlobal::RScalerX(y);
	rect = BGlobal::RScalerRect(rect);
	node.PFloat(x);
	node.PFloat(y);
	node.PLongLong(time);
	node.PInt(touchtype);
	node.PFloat(rect.origin.x);
	node.PFloat(rect.origin.y);
	node.PFloat(rect.size.width);
	node.PFloat(rect.size.height);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_RunAction(LuaState * ls)
{
	_ENTERFUNC_LUA(2);

	// item, action bRepeatForever

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

int Export_Lua_Game::LuaFn_Game_StopAction(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// item action
	CCNode * _item = (CCNode *)node.dNextGet();
	if (_item)
	{
		CCAction * _action = NULL;
		node.jNextGet();
		if (node.bhavenext)
		{
			_action = (CCAction *)node.dNextGet();
		}
		if (_action)
		{
			_item->stopAction(_action);
		}
		else
		{
			_item->stopAllActions();
		}
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_SetTouchEnabled(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// item benabled
	CCLayer * _item = (CCLayer *)node.dNextGet();
	if (_item)
	{
		bool _touchenabled = true;
		node.jNextGet();
		if (node.bhavenext)
		{
			_touchenabled = node.bGet();
		}
		_item->setIsTouchEnabled(_touchenabled);
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_SetIsVisible(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// item bvisible
	CCNode * _item = (CCNode *)node.dNextGet();
	if (_item)
	{
		bool _visible = true;
		node.jNextGet();
		if (node.bhavenext)
		{
			_visible = node.bGet();
		}
		_item->setIsVisible(_visible);
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetSubTags(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	int _itemtag = node.iNextGet();
	int toptag = Export_Lua_Scene::_GetTopTag(_itemtag);
	int sublayertag = Export_Lua_Scene::_GetSubLayerTag(_itemtag);
	int menugrouptag = Export_Lua_Scene::_GetMenuGroupTag(_itemtag);
	int menuitemtag = Export_Lua_Scene::_GetMenuItemTag(_itemtag);

	node.PInt(toptag);
	node.PInt(sublayertag);
	node.PInt(menugrouptag);
	node.PInt(menuitemtag);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_CameraGet(LuaState * ls)
{
	_ENTERFUNC_LUA(2);

	CCNode * _item = (CCNode *)node.dNextGet();
	if (!_item)
	{
		break;
	}

	float x=0;
	float y=0;
	float z=0;
	int _flag = node.iNextGet();
	switch (_flag)
	{
	case M_CAMERA_EYE:
		_item->getCamera()->getEyeXYZ(&x, &y, &z);
		break;
	case M_CAMERA_CENTER:
		_item->getCamera()->getCenterXYZ(&x, &y, &z);
		break;
	case M_CAMERA_UP:
		_item->getCamera()->getUpXYZ(&x, &y, &z);
		break;
	}

	x = BGlobal::RScalerX(x);
	y = BGlobal::RScalerY(y);
	z = BGlobal::RScaler(z);

	node.PFloat(x);
	node.PFloat(y);
	node.PFloat(z);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_CameraSet(LuaState * ls)
{
	_ENTERFUNC_LUA(2);

	CCNode * _item = (CCNode *)node.dNextGet();
	if (!_item)
	{
		break;
	}

	float x=0;
	float y=0;
	float z=0;
	int _flag = node.iNextGet();
	switch (_flag)
	{
	case M_CAMERA_EYE:
		_item->getCamera()->getEyeXYZ(&x, &y, &z);
		break;
	case M_CAMERA_CENTER:
		_item->getCamera()->getCenterXYZ(&x, &y, &z);
		break;
	case M_CAMERA_UP:
		_item->getCamera()->getUpXYZ(&x, &y, &z);
		break;
	}

	node.jNextGet();
	if (node.bhavenext)
	{
		x = BGlobal::ScalerX(node.fGet());
		node.jNextGet();
		if (node.bhavenext)
		{
			y = BGlobal::ScalerY(node.fGet());
			node.jNextGet();
			if (node.bhavenext)
			{
				z = BGlobal::Scaler(node.fGet());
			}
		}
	}
	switch (_flag)
	{
	case M_CAMERA_EYE:
		_item->getCamera()->setEyeXYZ(x, y, z);
		break;
	case M_CAMERA_CENTER:
		_item->getCamera()->setCenterXYZ(x, y, z);
		break;
	case M_CAMERA_UP:
		_item->getCamera()->setUpXYZ(x, y, z);
		break;
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_SetPosition(LuaState * ls)
{
	_ENTERFUNC_LUA(3);

	// item x y
	CCNode * _item = (CCNode *)node.dNextGet();
	if (!_item)
	{
		break;
	}
	float _x = node.fNextGet();
	float _y = node.fNextGet();
	_item->setPosition(BGlobal::ScalerPoint(ccp(_x, _y)));

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetPosition(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// item
	CCNode * _item = (CCNode *)node.dNextGet();
	if (!_item)
	{
		break;
	}
	CCPoint pos = _item->getPosition();
	pos = BGlobal::RScalerPoint(pos);
	node.PFloat(pos.x);
	node.PFloat(pos.y);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_SetZ(LuaState * ls)
{
	_ENTERFUNC_LUA(2);

	// item z
	CCNode * _item = (CCNode *)node.dNextGet();
	if (!_item)
	{
		break;
	}
	int _z = node.iNextGet();
	_item->getParent()->reorderChild(_item, _z);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetZ(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// item
	CCNode * _item = (CCNode *)node.dNextGet();
	if (!_item)
	{
		break;
	}
	int zOrder = _item->getZOrder();
	node.PInt(zOrder);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_SetAngle(LuaState * ls)
{
	_ENTERFUNC_LUA(2);

	// item angle
	CCNode * _item = (CCNode *)node.dNextGet();
	if (!_item)
	{
		break;
	}
	int _angle = node.iNextGet();
	_item->setRotation(CCARC(_angle));

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetAngle(LuaState * ls)
{
	_ENTERFUNC_LUA(1);
	// item
	CCNode * _item = (CCNode *)node.dNextGet();
	if (!_item)
	{
		break;
	}
	float rot = _item->getRotation();
	node.PInt(CCANGLE(rot)); 
	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_SetScale(LuaState * ls)
{
	_ENTERFUNC_LUA(2);

	// item sx sy
	CCNode * _item = (CCNode *)node.dNextGet();
	if (!_item)
	{
		break;
	}
	float _scalex = node.fNextGet();
	float _scaley = _scalex;

	node.jNextGet();
	if (node.bhavenext)
	{
		_scaley = node.fGet();
	}
	_item->setScaleX(BGlobal::ScalerX(_scalex));
	_item->setScaleY(BGlobal::ScalerY(_scaley));

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetScale(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// item -> sx, sy
	CCNode * _item = (CCNode *)node.dNextGet();
	if (!_item)
	{
		break;
	}
	float scalex = BGlobal::RScalerX(_item->getScaleX());
	float scaley = BGlobal::RScalerY(_item->getScaleY());

	node.PFloat(scalex);
	node.PFloat(scaley);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_SetColor(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// item color
	CCNode * _item = (CCNode *)node.dNextGet();
	DWORD _col = 0xffffffff;

	if (_item)
	{
		CCRGBAProtocol * pRGBAProtocol = _item->convertToRGBAProtocol();
		node.jNextGet();
		if (node.bhavenext)
		{
			_col = _LuaHelper_GetColor(&(node._obj));
		}
		pRGBAProtocol->setOpacity(GETA(_col));
		pRGBAProtocol->setColor(ccc3(GETR(_col), GETG(_col), GETB(_col)));
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetColor(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// item -> alpha color
	CCNode * _item = (CCNode *)node.dNextGet();
	if (_item)
	{
		CCRGBAProtocol * pRGBAProtocol = _item->convertToRGBAProtocol();
		node.PInt(pRGBAProtocol->getOpacity());
		ccColor3B col3b = pRGBAProtocol->getColor();
		node.PInt(ARGB(0, col3b.r, col3b.g, col3b.b));
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_SetAnchor(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	// item anchorx anchory
	CCNode * _item = (CCNode *)node.dNextGet();
	float _anchorx = _item->getAnchorPoint().x;
	float _anchory = _item->getAnchorPoint().y;

	if (_item)
	{
		node.jNextGet();
		if (node.bhavenext)
		{
			_anchorx = node.fGet();
			node.jNextGet();
			if (node.bhavenext)
			{
				_anchory = node.fGet();
			}
		}
		_item->setAnchorPoint(ccp(_anchorx, _anchory));
	}

	_LEAVEFUNC_LUA;
}


int Export_Lua_Game::LuaFn_Game_ActionMove(LuaState * ls)
{
	_ENTERFUNC_LUA(3);

	// flag x y time

	int _flag = node.iNextGet();
	float _x = node.fNextGet();
	float _y = node.fNextGet();
	float _time = 0;

	node.jNextGet();
	if (node.bhavenext)
	{
		_time = node.fGet();
		node.jNextGet();
	}

	CCAction * retval = NULL;
	switch (_flag)
	{
	case M_CCACTIONFLAG_TO:
		retval = CCMoveTo::actionWithDuration(_time, BGlobal::TranslatePosition(_x, _y));
		break;
	case M_CCACTIONFLAG_BY:
		retval = CCMoveBy::actionWithDuration(_time, BGlobal::TranslatePosition(_x, _y));
		break;
	}
	node.PDword((DWORD)retval);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_ActionRotate(LuaState * ls)
{
	_ENTERFUNC_LUA(2);

	// flag angle time relative

	int _flag = node.iNextGet();
	int _angle = node.iNextGet();
	float _time = 0;
	bool _relative = false;

	node.jNextGet();
	if (node.bhavenext)
	{
		_time = node.fGet();
		node.jNextGet();
	}

	CCAction * retval = NULL;
	switch (_flag)
	{
	case M_CCACTIONFLAG_TO:
		retval = CCRotateTo::actionWithDuration(_time, CCARC(_angle));
		break;
	case M_CCACTIONFLAG_BY:
		retval = CCRotateBy::actionWithDuration(_time, CCARC(_angle));
		break;
	}
	node.PDword((DWORD)retval);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_ActionScale(LuaState * ls)
{
	_ENTERFUNC_LUA(2);

	// flag sx sy time bglobal

	int _flag = node.iNextGet();
	float _scalex = node.fNextGet();
	float _scaley = _scalex;
	float _time = 0;
	bool _bglobal = false;

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
				_bglobal = node.bGet();
			}
		}
	}

	if (_bglobal)
	{
		_scalex = BGlobal::ScalerX(_scalex);
		_scaley = BGlobal::ScalerX(_scaley);
	}

	CCAction * retval = NULL;
	switch (_flag)
	{
	case M_CCACTIONFLAG_TO:
		retval = CCScaleTo::actionWithDuration(_time, _scalex, _scaley);
		break;
	case M_CCACTIONFLAG_BY:
		retval = CCScaleBy::actionWithDuration(_time, _scalex, _scaley);
		break;
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

int Export_Lua_Game::LuaFn_Game_ActionTint(LuaState * ls)
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
	case M_CCACTIONFLAG_TO:
		retval = CCTintTo::actionWithDuration(_time, GETR(_toval), GETG(_toval), GETB(_toval));
		break;
	case M_CCACTIONFLAG_BY:
		retval = CCTintBy::actionWithDuration(_time, GETR(_toval), GETG(_toval), GETB(_toval));
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

int Export_Lua_Game::LuaFn_Game_ActionDelete(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	// time
	float _delaytime = 0;
	node.jNextGet();
	if (node.bhavenext)
	{
		_delaytime = node.fGet();
	}
	CCAction * retval = CCActionDelete::action();
	if (_delaytime > 0)
	{
		CCFiniteTimeAction * delayaction = CCDelayTime::actionWithDuration(_delaytime);
		CCFiniteTimeAction * delaydeleteaction = CCSequence::actionOneTwo(delayaction, (CCFiniteTimeAction*)retval);
		node.PDword((DWORD)delaydeleteaction);
	}
	else
	{
		node.PDword((DWORD)retval);
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_ActionDeleteChildren(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	// time
	float _delaytime = 0;
	node.jNextGet();
	if (node.bhavenext)
	{
		_delaytime = node.fGet();
	}
	CCAction * retval = CCActionDeleteChildren::action();
	if (_delaytime > 0)
	{
		CCFiniteTimeAction * delayaction = CCDelayTime::actionWithDuration(_delaytime);
		CCFiniteTimeAction * delaydeletechildrenaction = CCSequence::actionOneTwo(delayaction, (CCFiniteTimeAction*)retval);
		node.PDword((DWORD)delaydeletechildrenaction);
	}
	else
	{
		node.PDword((DWORD)retval);
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_ActionCallFunc(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// {nodelist}, delaytime, dataindex
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
		Export_Lua_Scene::_GetSceneMenuCallback(scenetag, &cbfunc, &cbndfunc);
		proto = nownode;
		if (!proto || !cbfunc)
		{
			break;
		}

		float _delaytime = 0;
		int _dataindex = -1;
		node.jNextGet();
		if (node.bhavenext)
		{
			_delaytime = node.fGet();
			node.jNextGet();
			if (node.bhavenext)
			{
				_dataindex = node.iGet();
			}
		}

		CCAction * callfuncaction = CCCallFuncND::actionWithTarget(proto, (SEL_CallFuncND)cbndfunc, (void*)_dataindex);

		if (_delaytime > 0)
		{
			CCFiniteTimeAction * delayaction = CCDelayTime::actionWithDuration(_delaytime);
			CCFiniteTimeAction * delayedcallfuncaction = CCSequence::actionOneTwo(delayaction, (CCFiniteTimeAction*)callfuncaction);
			node.PDword((DWORD)delayedcallfuncaction);
		}
		else
		{
			node.PDword((DWORD)callfuncaction);
		}
	}

	_LEAVEFUNC_LUA;
}