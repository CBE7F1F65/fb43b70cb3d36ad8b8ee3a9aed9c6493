#include "Export_Lua_Scene.h"
#include "Export_Lua_Const.h"

#include "../Header/SceneConst.h"

#include "../Classes/LoadingScene.h"
#include "../Classes/TitleScene.h"
#include "../Classes/HiScoreScene.h"
#include "../Classes/OptionScene.h"
#include "../Classes/OnlineScene.h"
#include "../Classes/HelpScene.h"
#include "../Classes/StageSelectScene.h"
#include "../Classes/MissionSelectScene.h"
#include "../Classes/PlayScene.h"

#define LUASCENE_SCENE_IO	"Scene_IO"
#define LUASCENE_SCENE_CB	"Scene_CB"
#define LUASCENE_INPUTLAYER_CB	"InputLayer_CB"

LuaFunction<bool> * Export_Lua_Scene::ioScene;
LuaFunction<bool> * Export_Lua_Scene::cbScene;
LuaFunction<bool> * Export_Lua_Scene::cbInputLayer;

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

	obj->SetInteger("ktag_HiScoreSceneLayer", KTAG_HISCORESCENELAYER);
	obj->SetInteger("ktag_OptionSceneLayer", KTAG_OPTIONSCENELAYER);
	obj->SetInteger("ktag_OnlineSceneLayer", KTAG_ONLINESCENELAYER);
	obj->SetInteger("ktag_HelpSceneLayer", KTAG_HELPSCENELAYER);

	obj->SetInteger("ktag_StageSelectSceneLayer", KTAG_STAGESELECTSCENELAYER);
	obj->SetInteger("ktag_MissionSelectSceneLayer", KTAG_MISSIONSELECTSCENELAYER);

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
	case KTAG_HISCORESCENELAYER:
		if (cbfunc)
		{
			*cbfunc = menu_selector(HiScoreScene::MenuCallbackFunc);
		}
		if (cbndfunc)
		{
			*cbndfunc = callfuncND_selector(HiScoreScene::NodeCallbackFunc);
		}
		break;
	case KTAG_OPTIONSCENELAYER:
		if (cbfunc)
		{
			*cbfunc = menu_selector(OptionScene::MenuCallbackFunc);
		}
		if (cbndfunc)
		{
			*cbndfunc = callfuncND_selector(OptionScene::NodeCallbackFunc);
		}
		break;
	case KTAG_ONLINESCENELAYER:
		if (cbfunc)
		{
			*cbfunc = menu_selector(OnlineScene::MenuCallbackFunc);
		}
		if (cbndfunc)
		{
			*cbndfunc = callfuncND_selector(OnlineScene::NodeCallbackFunc);
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
	case KTAG_PLAYSCENELAYER:
		if (cbfunc)
		{
			*cbfunc = menu_selector(PlayScene::MenuCallbackFunc);
		}
		if (cbfunc)
		{
			*cbndfunc = callfuncND_selector(PlayScene::NodeCallbackFunc);
		}
		break;
	}
}

int Export_Lua_Scene::_GetTopTag(int scenetag)
{
	return scenetag & KTAG_SCENELAYERMASK;
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
	case KTAG_HISCORESCENELAYER:
		return HiScoreScene::scene();
		break;
	case KTAG_OPTIONSCENELAYER:
		return OptionScene::scene();
		break;
	case KTAG_ONLINESCENELAYER:
		return OnlineScene::scene();
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

bool Export_Lua_Scene::ExecuteCBScene(int tag, CCLayer * toplayer)
{
	LuaState * ls = state;
	bool bret = (*cbScene)(tag, CDOUBLEN(toplayer), tag&KTAG_SCENELAYERMASK, tag&KTAG_SUBLAYERMASK, tag&KTAG_MENUGROUPMASK, tag&KTAG_MENUITEMMASK);
	if (state->CheckError())
	{
		Export_Lua::ShowError(LUAERROR_LUAERROR, state->GetError());
	}
	return bret;
}

bool Export_Lua_Scene::ExecuteCBInputLayer(int tag, CCLayer * toplayer, int eventtag, const char * text)
{
	LuaState * ls = state;
	bool bret = (*cbInputLayer)(tag, CDOUBLEN(toplayer), eventtag, tag&KTAG_SCENELAYERMASK, tag&KTAG_SUBLAYERMASK, text);
	if (state->CheckError())
	{
		Export_Lua::ShowError(LUAERROR_LUAERROR, state->GetError());
	}
	return bret;
}