#ifndef __EXPORT_LUA_SCENE_H__
#define __EXPORT_LUA_SCENE_H__

#include "Export_Lua.h"

#include "cocos2d.h"
using namespace cocos2d;

#define LUASCENE_IOFLAG_ONINIT		0x01
#define LUASCENE_IOFLAG_ONENTER		0x02
#define LUASCENE_IOFLAG_ONENTERA	0x03
#define LUASCENE_IOFLAG_ONENTERTDF	0x04
#define LUASCENE_IOFLAG_ONENTERTDFA	0x05
#define LUASCENE_IOFLAG_ONUPDATE	0x06
#define LUASCENE_IOFLAG_ONEXIT		0x08
#define LUASCENE_IOFLAG_ONTOUCHBEGIN	0x10
#define LUASCENE_IOFLAG_ONTOUCHEND		0x10

class Export_Lua_Scene : public Export_Lua
{
public:
	static bool _LuaRegistConst(LuaObject * obj);
	static bool _LuaRegistFunction(LuaObject * obj);

	static bool InitCallbacks();

	static bool ExecuteIOScene(BYTE flag, CCLayer *toplayer, int toptag);
	static bool ExecuteCBScene(int tag, CCLayer * toplayer, int dataindex=-1);

	static bool ExecuteCBInputLayer(int tag, CCLayer * toplayer, int eventtag, const char * text);

	static bool ExecuteCBTouchLayer(int tag, CCLayer * toplayer, int eventtag, CCLayer * thislayer, int index);

	static void _GetSceneMenuCallback(int scenetag, SEL_MenuHandler * cbfunc=NULL, SEL_CallFuncND * cbndfunc=NULL);

	static int inline _GetTopTag(int itemtag);
	static int inline _GetSubLayerTag(int itemtag);
	static int inline _GetMenuGroupTag(int itemtag);
	static int inline _GetMenuItemTag(int itemtag);

	static CCScene * _GetNewScene(int scenetag);

public:
	static LuaFunction<bool> * ioScene;
	static LuaFunction<bool> * cbScene;
	static LuaFunction<bool> * cbInputLayer;
	static LuaFunction<bool> * cbTouchLayer;
};

#endif