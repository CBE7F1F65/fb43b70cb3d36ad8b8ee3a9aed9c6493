#include "Export_Lua_Scene.h"
#include "Export_Lua_Const.h"

#include "../Header/SceneConst.h"

#include "../Classes/LoadingScene.h"

#define LUASCENE_LOADINGSCENE_IO	"LoadingScene_IO"
#define LUASCENE_LOADINGSCENE_CB	"LoadingScene_CB"

LuaFunction<bool> * Export_Lua_Scene::ioLoadingScene;
LuaFunction<bool> * Export_Lua_Scene::cbLoadingScene;

bool Export_Lua_Scene::_LuaRegistConst(LuaObject * obj)
{
	obj->SetInteger("SceneIOFlag_OnInit", LUASCENE_IOFLAG_ONINIT);
	obj->SetInteger("SceneIOFlag_OnEnter", LUASCENE_IOFLAG_ONENTER);
	obj->SetInteger("SceneIOFlag_OnEnterTDF", LUASCENE_IOFLAG_ONENTERTDF);
	obj->SetInteger("SceneIOFlag_OnExit", LUASCENE_IOFLAG_ONEXIT);
	obj->SetInteger("SceneIOFlag_OnTouchBegin", LUASCENE_IOFLAG_ONTOUCHBEGIN);
	obj->SetInteger("SceneIOFlag_OnTouchEnd", LUASCENE_IOFLAG_ONTOUCHEND);

	obj->SetInteger("ktag_LoadingSceneLayer", KTAG_LOADINGSCENELAYER);

	return true;
}

bool Export_Lua_Scene::_LuaRegistFunction(LuaObject * obj)
{
	return true;
}


bool Export_Lua_Scene::InitCallbacks()
{
	LuaState * ls = state;
	LuaObject _obj = ls->GetGlobal(LUASCENE_LOADINGSCENE_IO);
	if (!_obj.IsFunction())
	{
		ShowError(LUAERROR_NOTFUNCTION, LUASCENE_LOADINGSCENE_IO);
		return false;
	}
	static LuaFunction<bool> _fioLoading = _obj;
	_fioLoading = _obj;
	ioLoadingScene = &_fioLoading;

	_obj = ls->GetGlobal(LUASCENE_LOADINGSCENE_CB);
	if (!_obj.IsFunction())
	{
		ShowError(LUAERROR_NOTFUNCTION, LUASCENE_LOADINGSCENE_CB);
		return false;
	}
	static LuaFunction<bool> _fcbLoading = _obj;
	_fcbLoading = _obj;
	cbLoadingScene = &_fcbLoading;

	return true;
}

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
			*cbfunc = menu_selector(LoadingScene::LoadingCallbackFunc);
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
	}
}


bool Export_Lua_Scene::ExecuteIOLoadingScene(BYTE flag)
{
	LuaState * ls = state;
	bool bret = (*ioLoadingScene)(flag);
	if (state->CheckError())
	{
		Export_Lua::ShowError(LUAERROR_LUAERROR, state->GetError());
	}
	return bret;
}

bool Export_Lua_Scene::ExecuteCBLoadingScene(int tag, int eventtag)
{
	LuaState * ls = state;
	bool bret = (*cbLoadingScene)(tag, eventtag);
	if (state->CheckError())
	{
		Export_Lua::ShowError(LUAERROR_LUAERROR, state->GetError());
	}
	return bret;
}