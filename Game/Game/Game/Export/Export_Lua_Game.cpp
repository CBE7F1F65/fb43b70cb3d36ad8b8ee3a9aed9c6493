#include "Export_Lua_Game.h"
#include "../Header/BResource.h"


bool Export_Lua_Game::_LuaRegistConst(LuaObject * obj)
{
	return true;
}

bool Export_Lua_Game::_LuaRegistFunction(LuaObject * obj)
{
	LuaObject _gameobj;
	_gameobj = obj->CreateTable("game");

	_gameobj.Register("Random_Int", LuaFn_Game_Random_Int);
	_gameobj.Register("Random_Float", LuaFn_Game_Random_Float);

	_gameobj.Register("FreeTexture", LuaFn_Game_LoadTexture);
	_gameobj.Register("FreeTexture", LuaFn_Game_FreeTexture);

	return true;
}

int Export_Lua_Game::LuaFn_Game_Random_Int(LuaState * ls)
{
	LuaStack args(ls);

	int argscount = args.Count();
	int _imin = 0;
	int _imax = RAND_MAX;
	int _seed;
	int * _pseed = NULL;
	if (argscount > 0)
	{
		_imin = args[1].GetInteger();
		if (argscount > 1)
		{
			_imax = args[2].GetInteger();
			if (argscount > 2)
			{
				_seed = args[3].GetInteger();
				_pseed = &_seed;
			}
		}
	}
	int _iret = randt(_imin, _imax, _pseed);
	ls->PushInteger(_iret);
	if (_pseed)
	{
		ls->PushInteger(_seed);
		return 2;
	}
	return 1;
}

int Export_Lua_Game::LuaFn_Game_Random_Float(LuaState * ls)
{
	LuaStack args(ls);

	int argscount = args.Count();
	float _fmin = 0.0f;
	float _fmax = 1.0f;
	int _seed;
	int * _pseed = NULL;
	if (argscount > 0)
	{
		_fmin = args[1].GetFloat();
		if (argscount > 1)
		{
			_fmax = args[2].GetFloat();
			if (argscount > 2)
			{
				_seed = args[3].GetInteger();
				_pseed = &_seed;
			}
		}
	}
	float _fret = randtf(_fmin, _fmax);
	ls->PushNumber(_fret);
	if (_pseed)
	{
		ls->PushInteger(_seed);
		return 2;
	}
	return 1;
}

int Export_Lua_Game::LuaFn_Game_LoadTexture(LuaState * ls)
{
	LuaStack args(ls);
	int _texindex = -1;

	if (args.Count() > 0)
	{
		_texindex = args[1].GetInteger();
	}

	bool bret = BResource::getInstance()->LoadTexture(_texindex);
	ls->PushBoolean(bret);
	return 1;
}

int Export_Lua_Game::LuaFn_Game_FreeTexture(LuaState * ls)
{
	LuaStack args(ls);
//#ifndef _WIN32
	int _texindex = -1;

	if (args.Count() > 0)
	{
		_texindex = args[1].GetInteger();
	}

	bool bret = BResource::getInstance()->FreeTexture(_texindex);
	ls->PushBoolean(bret);
//#else
//	ls->PushBoolean(true);
//#endif // _WIN32

	return 1;
}