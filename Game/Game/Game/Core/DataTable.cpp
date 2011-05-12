#include "../Header/DataTable.h"
#include "../Header/BResource.h"

#include "cocos2d.h"

using namespace cocos2d;

static DataTable * g_DataTableSingleton = NULL;

enum{
	DATATYPE_DATADEFINE			= 0x50,
};

#define _EOF_DATATABLE	(feof(file))
#define _CHECKEOF_DATATABLE	if (_EOF_DATATABLE)	\
	return false
#define _READSTRINGBUFFERLINE(X)	if (!ReadStringBuffer(X))	\
	return false
#define _BREAKCOMMENTBUFFER	if (!CommentBuffer())	\
	break
#define _INITTINT	ti = -1
#define _LOADTINT	(tint[++ti])
#define _SAVETINT	(&_LOADTINT)

#ifndef __INTEL_COMPILER
#define _DOSWAPTINT	int tbegin = 0;	\
	int tend = ti;	\
	while (tbegin < tend)	\
{	\
	int tswapint = tint[tbegin];	\
	tint[tbegin] = tint[tend];	\
	tint[tend] = tswapint;	\
	++tbegin;	\
	--tend;	\
	}
#else
#define _DOSWAPTINT
#endif

DataTable::DataTable()
{
	CCAssert(g_DataTableSingleton == NULL, ASSERTSTR_SECONDSINGLETON);
	file = NULL;
}

DataTable::~DataTable()
{
	ReleaseFile();
	if (g_DataTableSingleton)
	{
		delete g_DataTableSingleton;
		g_DataTableSingleton = NULL;
	}
}

DataTable * DataTable::getInstance()
{
	if (!g_DataTableSingleton)
	{
		g_DataTableSingleton = new DataTable();
	}
	return g_DataTableSingleton;
}

bool DataTable::ReadStringBuffer(int nCol)
{
	if (!file)
	{
		return false;
	}
	for (int i=0; i<nCol; i++)
	{
		fscanf(file, "%s", buffer);
		_CHECKEOF_DATATABLE;
	}
	return true;
}

bool DataTable::CommentBuffer()
{
	if (!file)
	{
		return false;
	}
	fscanf(file, "%s", buffer);
	_CHECKEOF_DATATABLE;
	if (buffer[0] == '#')
	{
		fscanf(file, "%[^\r\n]", bufferlong);
		_CHECKEOF_DATATABLE;
		CommentBuffer();
	}
	return true;
}

void DataTable::ReleaseFile()
{
	if (file)
	{
		fclose(file);
		file = NULL;
	}
}

char * DataTable::GetTableFileName(BYTE type)
{
	return BResource::getInstance()->getTableFileName(type - DATATYPE_DATADEFINE);
}

bool DataTable::ReadAllTable()
{
	if (!ReadDataDefineTable())
	{
		return false;
	}
	return true;
}

bool DataTable::CheckHeader(BYTE type)
{
	char * nowfilename = GetTableFileName(type);
	if (!nowfilename)
	{
		return false;
	}

	ReleaseFile();

	std::string pathKey = BResource::getInstance()->GetDataPath();
	pathKey += nowfilename;
//	CCFileUtils::ccRemoveHDSuffixFromFile(pathKey);
	pathKey = CCFileUtils::fullPathFromRelativePath(pathKey.c_str());

	file = fopen(pathKey.c_str(), "rb");
	if (!file)
	{
		return false;
	}
	int tgameversion = -1;
	char tsignature[M_STRMAX];
	int tfiletype = -1;

	fscanf(file, "%x%s%x", &tgameversion, tsignature, &tfiletype);
	if (tgameversion != GAME_VERSION || strcmp(tsignature, GAME_SIGNATURE) || tfiletype != type)
	{
		fclose(file);
		return false;
	}
	return true;
}

bool DataTable::ReadDataDefineTable()
{
	if (!CheckHeader(DATATYPE_DATADEFINE))
	{
		return false;
	}

	BResource * pbres = BResource::getInstance();

	_READSTRINGBUFFERLINE(3);
	while (!_EOF_DATATABLE)
	{
		_INITTINT;
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%x", &tindex);

		_CHECKEOF_DATATABLE;

		fscanf(file, "%s", GetTableFileName(tindex));

		_DOSWAPTINT;
		_INITTINT;
	}
	return true;
}