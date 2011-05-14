#ifndef __EXPORT_LUA_SCENE_H__
#define __EXPORT_LUA_SCENE_H__

#include "Export_Lua.h"

#define LUASCENE_IOFLAG_ONINIT		0x01
#define LUASCENE_IOFLAG_ONENTER		0x02
#define LUASCENE_IOFLAG_ONENTERTDF	0x04
#define LUASCENE_IOFLAG_ONEXIT		0x08
#define LUASCENE_IOFLAG_ONTOUCHBEGIN	0x10
#define LUASCENE_IOFLAG_ONTOUCHEND		0x10

class Export_Lua_Scene : public Export_Lua
{
public:
	static bool _LuaRegistConst(LuaObject * obj);
	static bool _LuaRegistFunction(LuaObject * obj);

	static bool InitCallbacks();

	static bool ExecuteIOLoadingScene(BYTE flag);
	static bool ExceuteCBLoadingScene(int tag, int eventtag);

public:
	static LuaFunction<bool> * ioLoadingScene;
	static LuaFunction<bool> * cbLoadingScene;
};

#endif