#ifndef __NOTUSELUA

#include "Export_Lua.h"
#include "Export_Lua_Const.h"
#include "../Header/BResource.h"

#include "../Header/DataStruct.h"

bool Export_Lua::_LuaRegistConst(LuaObject * obj)
{
	// System
	obj->SetInteger("NULL",	NULL);
#ifdef _DEBUG
	obj->SetBoolean("_DEBUG", true);
#else
	obj->SetBoolean("_DEBUG", false);
#endif // _DEBUG

	obj->SetNumber("ScreenWidth", M_SCREEN_WIDTH);
	obj->SetNumber("ScreenHeight", M_SCREEN_HEIGHT);

	return true;
}

bool Export_Lua::_LuaRegistCustomConst(LuaObject * obj)
{
	// CustomConst
	BResource * pbres = BResource::getInstance();
	if (!pbres->customconstdata)
	{
		return false;
	}
	for (int i=0; i<DATASTRUCT_CUSTOMCONSTMAX; i++)
	{
		if (strlen(pbres->customconstdata[i].name))
		{
			obj->SetInteger(pbres->customconstdata[i].name, pbres->customconstdata[i].value);
		}
	}

	return true;
}

bool Export_Lua::_LuaRegistSIID(LuaObject * obj)
{
	// SIID
	BResource * pbres = BResource::getInstance();
	for (int i=0; i<DATASTRUCT_SPRITEMAX; i++)
	{
		if (strlen(pbres->spritedata[i].spritename))
		{
			obj->SetInteger(pbres->spritedata[i].spritename, i);
		}
	}
	return true;
}

#endif