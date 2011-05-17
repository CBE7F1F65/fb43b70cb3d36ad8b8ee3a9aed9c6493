#ifndef ___LOBJNODE_H__
#define ___LOBJNODE_H__

#include "Export_Lua.h"

class _LObjNode
{
public:
	_LObjNode();
	_LObjNode(LuaState * ls, LuaStack *args);
	_LObjNode(LuaState * ls, LuaObject *obj, _LObjNode *root);
	~_LObjNode();

	bool NilCheck();

	int iGet();
	int iNextGet();
	float fGet();
	float fNextGet();
	bool bGet();
	bool bNextGet();
	const char * sGet();
	const char * sNextGet();
	DWORD cGet();
	DWORD cNextGet();
	DWORD dGet();
	DWORD dNextGet();

	LuaObject jNextGet();

	void PInt(int ival);
	void PFloat(float fval);
	void PBoolean(bool bval);
	void PString(char * sval);
	void PDword(DWORD dval);

	bool _isStack();
	void _init(LuaState * ls, LuaObject *obj, LuaStack *args, _LObjNode *root);

	bool ObjIsTable();
	bool ObjIsString();

public:
	bool bhavenext;
	int ii;
	int argscount;
	int retcount;

	LuaObject _obj;
	LuaState * ls;
	LuaObject * objbase;
	LuaStack * argsbase;
	_LObjNode *root;
};

#endif