#ifndef __NOTUSELUA

#include "../Export/Export_Lua.h"
#include "../Export/Export_Lua_Const.h"
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
	int customconstcount = DATASTRUCT_CUSTOMCONSTMAX;
	for (int i=0; i<customconstcount; i++)
	{
		if (strlen(pbres->customconstdata[i].name))
		{
			obj->SetInteger(pbres->customconstdata[i].name, pbres->customconstdata[i].value);
		}
	}

	return true;
}

#endif