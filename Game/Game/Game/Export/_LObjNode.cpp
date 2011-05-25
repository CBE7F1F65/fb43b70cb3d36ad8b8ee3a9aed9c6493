#include "_LObjNode.h"
#include "../Header/BIOInterface.h"

_LObjNode::_LObjNode()
{
	_init(NULL, NULL, NULL, NULL);
}

_LObjNode::_LObjNode(LuaState * _ls, LuaStack * args)
{
	_init(_ls, NULL, args, this);
}

_LObjNode::_LObjNode(LuaState * _ls, LuaObject * obj, _LObjNode *root)
{
	_init(_ls, obj, NULL, root);
}


_LObjNode::~_LObjNode()
{

}

void _LObjNode::_init(LuaState * _ls, LuaObject * obj, LuaStack * args, _LObjNode *_root)
{
	objbase = obj;
	argsbase = args;
	root = _root;
	bhavenext = false;
	ii = 0;
	argscount = 0;
	retcount = 0;
	ls = _ls;
	if (_isStack())
	{
		argscount = argsbase->Count();
	}
}

bool _LObjNode::ObjIsTable()
{
	return _obj.IsTable();
}

bool _LObjNode::ObjIsString()
{
	return _obj.IsString();
}

bool _LObjNode::_isStack()
{
	if (argsbase)
	{
		return true;
	}
	return false;
}

bool _LObjNode::NilCheck()
{
	return _obj.IsNil();
}

LuaObject _LObjNode::jNextGet()
{
	++ii;
	if (_isStack())
	{
		_obj = (*argsbase)[ii];
	}
	if (objbase)
	{
		_obj = (*objbase).GetByIndex(ii);
	}
	bhavenext = !NilCheck();
	return _obj;
}

int _LObjNode::iGet()
{
	if (NilCheck())
	{
		BIOInterface::getInstance()->System_MessageBox(ERRORSTR_NILCHECK, ERRORSTR_TITLE);
		return 0;
	}
	return _obj.GetInteger();
}

int _LObjNode::iNextGet()
{
	jNextGet();
	return iGet();
}

float _LObjNode::fGet()
{
	if (NilCheck())
	{
		BIOInterface::getInstance()->System_MessageBox(ERRORSTR_NILCHECK, ERRORSTR_TITLE);
		return 0.0f;
	}
	return _obj.GetFloat();
}

float _LObjNode::fNextGet()
{
	jNextGet();
	return fGet();
}

bool _LObjNode::bGet()
{
	if (NilCheck())
	{
		BIOInterface::getInstance()->System_MessageBox(ERRORSTR_NILCHECK, ERRORSTR_TITLE);
		return false;
	}
	return _obj.GetBoolean();
}

bool _LObjNode::bNextGet()
{
	jNextGet();
	return bGet();
}

const char * _LObjNode::sGet()
{
	if (NilCheck())
	{
		BIOInterface::getInstance()->System_MessageBox(ERRORSTR_NILCHECK, ERRORSTR_TITLE);
		return NULL;
	}
	return _obj.GetString();
}

const char * _LObjNode::sNextGet()
{
	jNextGet();
	return sGet();
}

DWORD _LObjNode::cGet()
{
	return Export_Lua::_LuaHelper_GetColor(&_obj);
}

DWORD _LObjNode::cNextGet()
{
	jNextGet();
	return cGet();
}

DWORD _LObjNode::dGet()
{
	return Export_Lua::_LuaHelper_GetDWORD(&_obj);
}

DWORD _LObjNode::dNextGet()
{
	jNextGet();
	return dGet();
}

void _LObjNode::PInt(int ival)
{
	if (ls && root)
	{
		ls->PushInteger(ival);
		root->retcount++;
	}
}

void _LObjNode::PFloat(float fval)
{
	if (ls && root)
	{
		ls->PushNumber(fval);
		root->retcount++;
	}
}

void _LObjNode::PBoolean(bool bval)
{
	if (ls && root)
	{
		ls->PushBoolean(bval);
		root->retcount++;
	}
}

void _LObjNode::PString(const char * sval)
{
	if (ls && root)
	{
		Export_Lua::_LuaHelper_PushString(ls, sval);
		root->retcount++;
	}
}

void _LObjNode::PDword(DWORD dval)
{
	if (ls && root)
	{
		Export_Lua::_LuaHelper_PushDWORD(ls, dval);
		root->retcount++;
	}
}

void _LObjNode::PLongLong(LONGLONG llval)
{
	if (ls && root)
	{
		Export_Lua::_LuaHelper_PushLONGLONG(ls, llval);
		root->retcount++;
	}
}