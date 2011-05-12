#ifndef __EXPORT_LUA_H__
#define __EXPORT_LUA_H__

#include "../Header/MainDependency.h"
#include "../../../../LuaPlus/LuaPlus/LuaPlus.h"
using namespace LuaPlus;

class Export_Lua
{
public:
	Export_Lua();
	~Export_Lua();
public:

	void Release(LuaState * ls = NULL);

	int LoadLuaFile(LuaState * ls, const char * filename, bool bDoFile = false, int * filecount = NULL, FILE * outputfile = NULL);
private:
	int _LoadLuaFile(LuaState * ls, const char * filename, bool bDoFile = false, int * filecount = NULL, FILE * outputfile = NULL);
public:
	int DoLuaFile(LuaState * ls, const char * filename){return LoadLuaFile(ls, filename, true);};

	int DoLuaFileInMemroy(LuaState * ls, const char * buffer, DWORD size, const char * name);

	bool CheckUseUnpackedFiles(LuaState * ls);
	int PackLuaFiles(LuaState * ls = NULL);
	int LoadPackedLuaFiles(LuaState * ls = NULL);

	static int LuaChunkWriter(lua_State *L, const void* p, size_t sz, void* ud);

	int ReadLuaFileTable(LuaState * ls = NULL);

	void ShowError(int errortype, const char * err);

public:

	static Export_Lua * getInstance();

public:
	LuaStateOwner state;
};

#endif