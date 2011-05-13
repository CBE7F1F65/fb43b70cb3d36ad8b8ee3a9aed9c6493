#include "../Header/BResource.h"
#include "../Header/DataTable.h"
#include "cocos2d.h"

#include "../Export/Export_Lua.h"

#include "../Header/BIOInterface.h"

using namespace cocos2d;

// Resource

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#define RESOURCE_PATH	"../Game/Resource/"

#else

#define RESOURCE_PATH	""

#endif	// CC_PLATFORM_WIN32

#define RESOURCE_SCRIPT_PATH	"Script\\"
#define RESOURCE_SCRIPTBINFILE	"Script.dat"
#define RESOURCE_DATA_PATH		"Data\\"
#define RESOURCE_DATADEFINEFILE	"DataDefine.table"
#define RESOURCE_RESBINFILE		"Resource.bin"

#define LOG_FILENAME		"log.log"
#define INI_FILENAME		"config.ini"

static BResource * g_BResourceSingleton = NULL;


BResource::BResource()
{
	BIOInterface::getInstance()->System_Assert(g_BResourceSingleton == NULL, ASSERTSTR_SECONDSINGLETON);
	ZeroMemory(datatablefilename, sizeof(char)*DATATABLEMAX*M_STRMAX);
	strcpy(datatablefilename[0], RESOURCE_DATADEFINEFILE);
	customconstdata = NULL;
}

BResource::~BResource()
{
	ReleaseCustomConst();
	if (g_BResourceSingleton)
	{
		delete g_BResourceSingleton;
		g_BResourceSingleton = NULL;
	}
}

bool BResource::Init()
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

	CCFileUtils::setResourcePath(CCFileUtils::fullPathFromRelativePath(RESOURCE_PATH));

	BIOInterface * bio = BIOInterface::getInstance();
	bio->Resource_SetCurrentDirectory(RESOURCE_PATH);
	bio->Resource_SetPath(RESOURCE_PATH);
	bio->System_SetLogFile(LOG_FILENAME);
	bio->Ini_SetIniFile(INI_FILENAME);

#endif  // CC_PLATFORM_WIN32

	return true;

}

void BResource::MallocCustomConst()
{
	ReleaseCustomConst();
	customconstdata = (customconstData *)malloc(RSIZE_CUSTOMCONST);
}

void BResource::ReleaseCustomConst()
{
	if (customconstdata)
	{
		free(customconstdata);
		customconstdata = NULL;
	}
}

BResource * BResource::getInstance()
{
	if (!g_BResourceSingleton)
	{
		g_BResourceSingleton = new BResource();
	}
	return g_BResourceSingleton;
}

const char * BResource::GetDataPath()
{
	return RESOURCE_DATA_PATH;
}

char * BResource::getTableFileName(int index)
{
	if (index < 0 || index >= DATATABLEMAX)
	{
		return NULL;
	}
	return datatablefilename[index];
}

bool BResource::ReadAllScript()
{
	int iret = Export_Lua::ReadLuaFileTable();
	if (iret == 0)
	{
		iret = Export_Lua::PackLuaFiles();
		if (iret != 0)
		{
			return false;
		}
	}
	iret = Export_Lua::LoadPackedLuaFiles();
	if (iret != 0)
	{
		return false;
	}
	return true;
}

bool BResource::ReadAllTable()
{
	return DataTable::getInstance()->ReadAllTable();
}

bool BResource::PackData()
{
	return false;
}

bool BResource::GainData()
{
	return false;
}

bool BResource::LoadTexture(int texindex /* = -1 */)
{
	return false;
}

bool BResource::FreeTexture(int texindex /* = -1 */)
{
	return false;
}

#define RESOURCE_LOADINGFILENAME	"Loading.png"

const char * BResource::getLoadingFileName()
{
	return RESOURCE_LOADINGFILENAME;
}