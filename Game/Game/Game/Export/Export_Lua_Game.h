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

	static int LuaFn_Game_Random_Int(LuaState * ls);
	static int LuaFn_Game_Random_Float(LuaState * ls);

	static int LuaFn_Game_LoadTexture(LuaState * ls);
	static int LuaFn_Game_FreeTexture(LuaState * ls);

	static int LuaFn_Game_CreateSprite(LuaState * ls);
	static int LuaFn_Game_AddSpriteChild(LuaState * ls);

	static int LuaFn_Game_CreateMenuItem(LuaState * ls);
	static int LuaFn_Game_AddMenuChild(LuaState * ls);

	static CCNode * _GetNowNode(_LObjNode * cnode, bool topnode=false, int * scenetag=NULL);
	static bool _GetXYZT(_LObjNode * cnode, float *x=NULL, float *y=NULL, int *zOrder=NULL, int *tag=NULL);

public:

	static _LObjNode node;
};

#endif