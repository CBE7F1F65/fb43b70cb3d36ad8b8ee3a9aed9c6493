#include "Export_Lua_Scene.h"
#include "Export_Lua_Const.h"

#include "../Header/SceneConst.h"

#include "../Classes/LoadingScene.h"
#include "../Classes/TitleScene.h"
#include "../Classes/HelpScene.h"
#include "../Classes/StageSelectScene.h"
#include "../Classes/MissionSelectScene.h"
#include "../Classes/StoryScene.h"
#include "../Classes/PlayScene.h"

#define LUASCENE_SCENE_IO	"Scene_IO"
#define LUASCENE_SCENE_CB	"Scene_CB"
#define LUASCENE_INPUTLAYER_CB	"InputLayer_CB"
#define LUASCENE_TOUCHLAYER_CB	"TouchLayer_CB"

LuaFunction<bool> * Export_Lua_Scene::ioScene;
LuaFunction<bool> * Export_Lua_Scene::cbScene;
LuaFunction<bool> * Export_Lua_Scene::cbInputLayer;
LuaFunction<bool> * Export_Lua_Scene::cbTouchLayer;

bool Export_Lua_Scene::_LuaRegistConst(LuaObject * obj)
{
	obj->SetInteger("SceneIOFlag_OnInit", LUASCENE_IOFLAG_ONINIT);
	obj->SetInteger("SceneIOFlag_OnEnter", LUASCENE_IOFLAG_ONENTER);
	obj->SetInteger("SceneIOFlag_OnEnterA", LUASCENE_IOFLAG_ONENTERA);
	obj->SetInteger("SceneIOFlag_OnEnterTDF", LUASCENE_IOFLAG_ONENTERTDF);
	obj->SetInteger("SceneIOFlag_OnEnterTDFA", LUASCENE_IOFLAG_ONENTERTDFA);
	obj->SetInteger("SceneIOFlag_OnUpdate", LUASCENE_IOFLAG_ONUPDATE);
	obj->SetInteger("SceneIOFlag_OnExit", LUASCENE_IOFLAG_ONEXIT);
	obj->SetInteger("SceneIOFlag_OnTouchBegin", LUASCENE_IOFLAG_ONTOUCHBEGIN);
	obj->SetInteger("SceneIOFlag_OnTouchEnd", LUASCENE_IOFLAG_ONTOUCHEND);

	obj->SetInteger("ktag_BaseSceneLayer", KTAG_BASESCENELAYER);
	obj->SetInteger("ktag_LoadingSceneLayer", KTAG_LOADINGSCENELAYER);

	obj->SetInteger("ktag_TitleSceneLayer", KTAG_TITLESCENELAYER);

	obj->SetInteger("ktag_HelpSceneLayer", KTAG_HELPSCENELAYER);

	obj->SetInteger("ktag_StageSelectSceneLayer", KTAG_STAGESELECTSCENELAYER);
	obj->SetInteger("ktag_MissionSelectSceneLayer", KTAG_MISSIONSELECTSCENELAYER);
	obj->SetInteger("ktag_StorySceneLayer", KTAG_STORYSCENELAYER);

	obj->SetInteger("ktag_PlaySceneLayer", KTAG_PLAYSCENELAYER);

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
	static LuaFunction<bool> _fsceneio = _obj;
	_fsceneio = _obj;
	ioScene = &_fsceneio;

	_obj = ls->GetGlobal(LUASCENE_SCENE_CB);
	if (!_obj.IsFunction())
	{
		ShowError(LUAERROR_NOTFUNCTION, LUASCENE_SCENE_CB);
		return false;
	}
	static LuaFunction<bool> _fscenecb = _obj;
	_fscenecb = _obj;
	cbScene = &_fscenecb;

	_obj = ls->GetGlobal(LUASCENE_INPUTLAYER_CB);
	if (!_obj.IsFunction())
	{
		ShowError(LUAERROR_NOTFUNCTION, LUASCENE_INPUTLAYER_CB);
		return false;
	}
	static LuaFunction<bool> _finputlayercb = _obj;
	_finputlayercb = _obj;
	cbInputLayer = &_finputlayercb;

	_obj = ls->GetGlobal(LUASCENE_TOUCHLAYER_CB);
	if (!_obj.IsFunction())
	{
		ShowError(LUAERROR_NOTFUNCTION, LUASCENE_TOUCHLAYER_CB);
		return false;
	}
	static LuaFunction<bool> _ftouchlayercb = _obj;
	_ftouchlayercb = _obj;
	cbTouchLayer = &_ftouchlayercb;

	return true;
}

/************************************************************************/
/* SceneGet                                                             */
/************************************************************************/
void Export_Lua_Scene::_GetSceneMenuCallback(int scenetag, SEL_MenuHandler * cbfunc, SEL_CallFuncND * cbndfunc)
{
	scenetag = scenetag & KTAG_SCENELAYERMASK;
	switch (scenetag)
	{
	case KTAG_LOADINGSCENELAYER:
		if (cbfunc)
		{
			*cbfunc = menu_selector(LoadingScene::MenuCallbackFunc);
		}
		if (cbndfunc)
		{
			*cbndfunc = callfuncND_selector(LoadingScene::NodeCallbackFunc);
		}
		break;
	case KTAG_TITLESCENELAYER:
		if (cbfunc)
		{
			*cbfunc = menu_selector(TitleScene::MenuCallbackFunc);
		}
		if (cbndfunc)
		{
			*cbndfunc = callfuncND_selector(TitleScene::NodeCallbackFunc);
		}
		break;
	case KTAG_HELPSCENELAYER:
		if (cbfunc)
		{
			*cbfunc = menu_selector(HelpScene::MenuCallbackFunc);
		}
		if (cbndfunc)
		{
			*cbndfunc = callfuncND_selector(HelpScene::NodeCallbackFunc);
		}
		break;
	case KTAG_STAGESELECTSCENELAYER:
		if (cbfunc)
		{
			*cbfunc = menu_selector(StageSelectScene::MenuCallbackFunc);
		}
		if (cbndfunc)
		{
			*cbndfunc = callfuncND_selector(StageSelectScene::NodeCallbackFunc);
		}
		break;
	case KTAG_MISSIONSELECTSCENELAYER:
		if (cbfunc)
		{
			*cbfunc = menu_selector(MissionSelectScene::MenuCallbackFunc);
		}
		if (cbndfunc)
		{
			*cbndfunc = callfuncND_selector(MissionSelectScene::NodeCallbackFunc);
		}
		break;
	case KTAG_STORYSCENELAYER:
		if (cbfunc)
		{
			*cbfunc = menu_selector(StoryScene::MenuCallbackFunc);
		}
		if (cbndfunc)
		{
			*cbndfunc = callfuncND_selector(StoryScene::NodeCallbackFunc);
		}
		break;
	case KTAG_PLAYSCENELAYER:
		if (cbfunc)
		{
			*cbfunc = menu_selector(PlayScene::MenuCallbackFunc);
		}
		if (cbndfunc)
		{
			*cbndfunc = callfuncND_selector(PlayScene::NodeCallbackFunc);
		}
		break;
	}
}

int Export_Lua_Scene::_GetTopTag(int itemtag)
{
	return itemtag & KTAG_SCENELAYERMASK;
}

int Export_Lua_Scene::_GetSubLayerTag(int itemtag)
{
	return itemtag & KTAG_SUBLAYERMASK;
}

int Export_Lua_Scene::_GetMenuGroupTag(int itemtag)
{
	return itemtag & KTAG_MENUGROUPMASK;
}

int Export_Lua_Scene::_GetMenuItemTag(int itemtag)
{
	return itemtag & KTAG_MENUITEMMASK;
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
	case KTAG_HELPSCENELAYER:
		return HelpScene::scene();
		break;
	case KTAG_STAGESELECTSCENELAYER:
		return StageSelectScene::scene();
		break;
	case KTAG_MISSIONSELECTSCENELAYER:
		return MissionSelectScene::scene();
		break;
	case KTAG_STORYSCENELAYER:
		return StoryScene::scene();
		break;
	case KTAG_PLAYSCENELAYER:
		return PlayScene::scene();
		break;
	}
	return NULL;
}

/************************************************************************/
/* Callback                                                             */
/************************************************************************/

bool Export_Lua_Scene::ExecuteIOScene(BYTE flag, CCLayer *toplayer, int toptag)
{
	LuaState * ls = state;
	bool bret = (*ioScene)(flag, CDOUBLEN(toplayer), toptag);
	if (state->CheckError())
	{
		Export_Lua::ShowError(LUAERROR_LUAERROR, state->GetError());
	}
	return bret;
}

bool Export_Lua_Scene::ExecuteCBScene(int tag, CCLayer * toplayer, int dataindex /* = -1 */)
{
	LuaState * ls = state;
	bool bret = (*cbScene)(tag, CDOUBLEN(toplayer), _GetTopTag(tag), _GetSubLayerTag(tag), _GetMenuGroupTag(tag), _GetMenuItemTag(tag), dataindex);
	if (state->CheckError())
	{
		Export_Lua::ShowError(LUAERROR_LUAERROR, state->GetError());
	}
	return bret;
}

bool Export_Lua_Scene::ExecuteCBInputLayer(int tag, CCLayer * toplayer, int eventtag, const char * text)
{
	LuaState * ls = state;
	bool bret = (*cbInputLayer)(tag, CDOUBLEN(toplayer), eventtag, _GetTopTag(tag), _GetSubLayerTag(tag), text);
	if (state->CheckError())
	{
		Export_Lua::ShowError(LUAERROR_LUAERROR, state->GetError());
	}
	return bret;
}

bool Export_Lua_Scene::ExecuteCBTouchLayer(int tag, CCLayer * toplayer, int eventtag, CCLayer * thislayer, int index, BYTE gesture)
{
	LuaState * ls = state;
	bool bret = (*cbTouchLayer)(CDOUBLEN(toplayer), eventtag, _GetTopTag(tag), tag&KTAG_SUBLAYERMASK, CDOUBLEN(thislayer), index, gesture);
	if (state->CheckError())
	{
		Export_Lua::ShowError(LUAERROR_LUAERROR, state->GetError());
	}
	return bret;
}