#ifndef __EXPORT_LUA_GAME_H__
#define __EXPORT_LUA_GAME_H__

#include "Export_Lua.h"
#include "_LObjNode.h"

#include "cocos2d.h"
using namespace cocos2d;

#define _ENTERFUNC_LUA(X)	LuaStack args(ls);\
							node._init(ls, NULL, &args, &node);\
							if (node.argscount >= (X))\
							{\
								do\
								{

#define _LEAVEFUNC_LUA			} while(false);\
							}\
							else\
							{\
								return -1;\
							}\
							return node.retcount

class Export_Lua_Game : Export_Lua
{
public:
	static bool _LuaRegistConst(LuaObject * obj);
	static bool _LuaRegistFunction(LuaObject * obj);
	static bool _LuaRegistFunction_Mission(LuaObject * obj);

	static int LuaFn_Game_Random_Int(LuaState * ls);
	static int LuaFn_Game_Random_Float(LuaState * ls);

	static int LuaFn_Game_LoadTexture(LuaState * ls);
	static int LuaFn_Game_FreeTexture(LuaState * ls);

	static int LuaFn_Game_PushScene(LuaState * ls);
	static int LuaFn_Game_PopScene(LuaState * ls);
	static int LuaFn_Game_ReplaceScene(LuaState * ls);

	static int LuaFn_Game_GetNode(LuaState * ls);

	static int LuaFn_Game_AddNullChild(LuaState * ls);
	static int LuaFn_Game_RemoveChild(LuaState * ls);
	static int LuaFn_Game_RemoveAllChildren(LuaState * ls);

	static int LuaFn_Game_GetSIData(LuaState * ls);

	static int LuaFn_Game_CreateSprite(LuaState * ls);
	static int LuaFn_Game_AddSpriteChild(LuaState * ls);

	static int LuaFn_Game_AddTextChild(LuaState * ls);

	static int LuaFn_Game_CreateMenuItem(LuaState * ls);
	static int LuaFn_Game_SetMenuItemEnabled(LuaState * ls);
	static int LuaFn_Game_AddMenuChild(LuaState * ls);

	static int LuaFn_Game_AddInputLayerChild(LuaState * ls);

	static int LuaFn_Game_AddTouchLayerChild(LuaState * ls);
	static int LuaFn_Game_GetTouchInfo(LuaState * ls);

	static int LuaFn_Game_RunAction(LuaState * ls);
	static int LuaFn_Game_StopAction(LuaState * ls);

	static int LuaFn_Game_SetTouchEnabled(LuaState * ls);
	static int LuaFn_Game_SetIsVisible(LuaState * ls);

	static int LuaFn_Game_SetPosition(LuaState * ls);
	static int LuaFn_Game_GetPosition(LuaState * ls);
	static int LuaFn_Game_SetAngle(LuaState * ls);
	static int LuaFn_Game_GetAngle(LuaState * ls);
	static int LuaFn_Game_SetScale(LuaState * ls);
	static int LuaFn_Game_GetScale(LuaState * ls);
	static int LuaFn_Game_SetColor(LuaState * ls);
	static int LuaFn_Game_GetColor(LuaState * ls);
	static int LuaFn_Game_SetAnchor(LuaState * ls);

	static int LuaFn_Game_ActionMove(LuaState * ls);
	static int LuaFn_Game_ActionRotate(LuaState * ls);
	static int LuaFn_Game_ActionScale(LuaState * ls);
	static int LuaFn_Game_ActionEase(LuaState * ls);
	static int LuaFn_Game_ActionFade(LuaState * ls);
	static int LuaFn_Game_ActionTint(LuaState * ls);
	static int LuaFn_Game_ActionSequence(LuaState * ls);
	static int LuaFn_Game_ActionSpawn(LuaState * ls);
	static int LuaFn_Game_ActionRepeat(LuaState * ls);
	static int LuaFn_Game_ActionDelay(LuaState * ls);
	static int LuaFn_Game_ActionDelete(LuaState * ls);
	static int LuaFn_Game_ActionCallFunc(LuaState * ls);

public:

	static int LuaFn_Game_GetUsername(LuaState * ls);
	static int LuaFn_Game_SetUsername(LuaState * ls);

	static int LuaFn_Game_GetHiScoreData(LuaState * ls);
	static int LuaFn_Game_InsertHiScore(LuaState * ls);
	static int LuaFn_Game_ResetHiScoreData(LuaState * ls);

	static int LuaFn_Game_GetItemData(LuaState * ls);
	static int LuaFn_Game_UseItem(LuaState * ls);
	static int LuaFn_Game_BuyItem(LuaState * ls);

	static int LuaFn_Game_StageIsEnabled(LuaState * ls);
	static int LuaFn_Game_MissionIsEnabled(LuaState * ls);
	static int LuaFn_Game_EnableMission(LuaState * ls);
	static int LuaFn_Game_TryStage(LuaState * ls);
	static int LuaFn_Game_TryMission(LuaState * ls);
	static int LuaFn_Game_GetNowStageMissionTurn(LuaState * ls);

	// In Game

	static int LuaFn_Game_Update(LuaState * ls);

	static int LuaFn_Game_AddTurn(LuaState * ls);

	static int LuaFn_Game_GetMissionBGData(LuaState * ls);
	static int LuaFn_Game_GetMissionHelpData(LuaState * ls);

	static int LuaFn_Game_EnterMission(LuaState * ls);
	static int LuaFn_Game_ClearMission(LuaState * ls);

	static int LuaFn_Game_GetHelpAccessInfo(LuaState * ls);
	static int LuaFn_Game_SetHelpIndex(LuaState * ls);

	static int LuaFn_Game_GetHPAPSP(LuaState * ls);

	static int LuaFn_Game_GetEnemyTypeData(LuaState * ls);
	static int LuaFn_Game_GetEnemyATK(LuaState * ls);
	static int LuaFn_Game_GetEnemyELayerAdvance(LuaState * ls);

	static int LuaFn_Game_AddEnemy(LuaState * ls);
	static int LuaFn_Game_RemoveEnemy(LuaState * ls);
	static int LuaFn_Game_DoRemoveEnemy(LuaState * ls);
	static int LuaFn_Game_GetActiveEnemyData(LuaState * ls);

	static int LuaFn_Game_GetState(LuaState * ls);
	static int LuaFn_Game_SetState(LuaState * ls);

	static int LuaFn_Game_GetBGMSEVol(LuaState * ls);
	static int LuaFn_Game_SetBGMSEVol(LuaState * ls);
	static int LuaFn_Game_SaveIni(LuaState * ls);
	static int LuaFn_Game_ResetIni(LuaState * ls);


	static CCNode * _GetNowNode(_LObjNode * cnode, bool topnode=false, int * scenetag=NULL);
	static bool _GetXYZT(_LObjNode * cnode, float *x=NULL, float *y=NULL, int *zOrder=NULL, int *tag=NULL);
	static CCRect _GetRect(_LObjNode* cnode);

public:

	static _LObjNode node;
};

#endif