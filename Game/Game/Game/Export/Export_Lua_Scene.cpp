#include "Export_Lua_Scene.h"
#include "Export_Lua_Const.h"

#include "../Header/SceneConst.h"

#include "../Classes/LoadingScene.h"
#include "../Classes/TitleScene.h"

#define LUASCENE_SCENE_IO	"Scene_IO"
#define LUASCENE_SCENE_CB	"Scene_CB"

LuaFunction<bool> * Export_Lua_Scene::ioScene;
LuaFunction<bool> * Export_Lua_Scene::cbScene;

bool Export_Lua_Scene::_LuaRegistConst(LuaObject * obj)
{
	obj->SetInteger("SceneIOFlag_OnInit", LUASCENE_IOFLAG_ONINIT);
	obj->SetInteger("SceneIOFlag_OnEnter", LUASCENE_IOFLAG_ONENTER);
	obj->SetInteger("SceneIOFlag_OnEnterTDF", LUASCENE_IOFLAG_ONENTERTDF);
	obj->SetInteger("SceneIOFlag_OnExit", LUASCENE_IOFLAG_ONEXIT);
	obj->SetInteger("SceneIOFlag_OnTouchBegin", LUASCENE_IOFLAG_ONTOUCHBEGIN);
	obj->SetInteger("SceneIOFlag_OnTouchEnd", LUASCENE_IOFLAG_ONTOUCHEND);

	obj->SetInteger("ktag_BaseSceneLayer", KTAG_BASESCENELAYER);
	obj->SetInteger("ktag_LoadingSceneLayer", KTAG_LOADINGSCENELAYER);
	obj->SetInteger("ktag_TitleSceneLayer", KTAG_TITLESCENELAYER);

	return true;
}

bool Export_Lua_Scene::_LuaRegistFunction(LuaObject * obj)
{
	return true;
}


bool Export_Lua_Scene::InitCallbacks()
{
	LuaState * ls = state;
	LuaObject _obj = ls->GetGlobal(LUASCENE_SCENE_IO);
	if (!_obj.IsFunction())
	{
		ShowError(LUAERROR_NOTFUNCTION, LUASCENE_SCENE_IO);
		return false;
	}
	static LuaFunction<bool> _fioLoading = _obj;
	_fioLoading = _obj;
	ioScene = &_fioLoading;

	_obj = ls->GetGlobal(LUASCENE_SCENE_CB);
	if (!_obj.IsFunction())
	{
		ShowError(LUAERROR_NOTFUNCTION, LUASCENE_SCENE_CB);
		return false;
	}
	static LuaFunction<bool> _fcbLoading = _obj;
	_fcbLoading = _obj;
	cbScene = &_fcbLoading;

	return true;
}

/************************************************************************/
/* SceneGet                                                             */
/************************************************************************/
void Export_Lua_Scene::_GetSceneMenuCallback(int scenetag, SelectorProtocol ** proto, SEL_MenuHandler * cbfunc)
{
	scenetag = scenetag & KTAG_SCENELAYERMASK;
	switch (scenetag)
	{
	case KTAG_LOADINGSCENELAYER:
		if (proto)
		{
			*proto = LoadingScene::thisLayer;
		}
		if (cbfunc)
		{
			*cbfunc = menu_selector(LoadingScene::MenuCallbackFunc);
		}
		break;
	case KTAG_TITLESCENELAYER:
		if (proto)
		{
			*proto = TitleScene::thisLayer;
		}
		if (cbfunc)
		{
			*cbfunc = menu_selector(TitleScene::MenuCallbackFunc);
		}
		break;
	}
}

CCNode * Export_Lua_Scene::_GetSceneNode(int * scenetag)
{
	if (!scenetag)
	{
		return NULL;
	}
	*scenetag = (*scenetag) & KTAG_SCENELAYERMASK;
	switch (*scenetag)
	{
	case KTAG_LOADINGSCENELAYER:
		return LoadingScene::thisLayer;
		break;
	case KTAG_TITLESCENELAYER:
		return TitleScene::thisLayer;
		break;
	}
	return NULL;
}

CCScene * Export_Lua_Scene::_GetNewScene(int scenetag)
{
	scenetag = scenetag & KTAG_SCENELAYERMASK;
	switch (scenetag)
	{
	case KTAG_LOADINGSCENELAYER:
		return LoadingScene::scene();
		break;
	case KTAG_TITLESCENELAYER:
		return TitleScene::scene();
		break;
	}
	return NULL;
}

/************************************************************************/
/* Callback                                                             */
/************************************************************************/

bool Export_Lua_Scene::ExecuteIOScene(BYTE flag, CCNode *topnode, int toptag)
{
	LuaState * ls = state;
	bool bret = (*ioScene)(flag, topnode, toptag);
	if (state->CheckError())
	{
		Export_Lua::ShowError(LUAERROR_LUAERROR, state->GetError());
	}
	return bret;
}

bool Export_Lua_Scene::ExecuteCBScene(int tag, int eventtag)
{
	LuaState * ls = state;
	bool bret = (*cbScene)(tag, eventtag, tag&KTAG_SCENELAYERMASK, tag&KTAG_MENUGROUPMASK, tag&KTAG_MENUITEMMASK);
	if (state->CheckError())
	{
		Export_Lua::ShowError(LUAERROR_LUAERROR, state->GetError());
	}
	return bret;
}