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

	obj->SetInteger("CCAF_Null", M_CCACTIONFLAG_NULL);
	obj->SetInteger("CCAF_In", M_CCACTIONFLAG_IN);
	obj->SetInteger("CCAF_Out", M_CCACTIONFLAG_OUT);
	obj->SetInteger("CCAF_InOut", M_CCACTIONFLAG_INOUT);
	obj->SetInteger("CCAF_To", M_CCACTIONFLAG_TO);
	obj->SetInteger("CCAF_By", M_CCACTIONFLAG_BY);

	obj->SetInteger("CCET_Null", M_CCEVENTTAG_NULL);
	obj->SetInteger("CCET_Enter", M_CCEVENTTAG_ENTER);
	obj->SetInteger("CCET_Leave", M_CCEVENTTAG_LEAVE);

	obj->SetInteger("CCTI_Began", M_CCTOUCHINDICATOR_BEGAN);
	obj->SetInteger("CCTI_Moved", M_CCTOUCHINDICATOR_MOVED);
	obj->SetInteger("CCTI_Ended", M_CCTOUCHINDICATOR_ENDED);
	obj->SetInteger("CCTI_Canceled", M_CCTOUCHINDICATOR_CANCELED);

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