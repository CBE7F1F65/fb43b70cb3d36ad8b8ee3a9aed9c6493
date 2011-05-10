#include "../Header/BResource.h"
#include "../Header/DataTable.h"
#include "cocos2d.h"

using namespace cocos2d;

// Resource

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#define RESOURCE_PATH	"..\\Game\\Resource\\"

#else

#define RESOURCE_PATH	""

#endif	// CC_PLATFORM_WIN32

#define RESOURCE_SCRIPT_PATH	"Script\\"
#define RESOURCE_SCRIPTBINFILE	"Script.dat"
#define RESOURCE_DATA_PATH		"Data\\"
#define RESOURCE_DATADEFINEFILE	"Data\\DataDefine.table"
#define RESOURCE_RESBINFILE		"Data\\Resource.bin"

static BResource * g_BResourceSingleton = NULL;


BResource::BResource()
{
	CCAssert(g_BResourceSingleton == NULL, ASSERTSTR_SECONDSINGLETON);
	ZeroMemory(datatablefilename, sizeof(char)*DATATABLEMAX*M_STRMAX);
}

BResource::~BResource()
{

}

bool BResource::Init()
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

	CCFileUtils::setResourcePath(CCFileUtils::fullPathFromRelativePath(RESOURCE_PATH));

#endif  // CC_PLATFORM_WIN32

	return true;

}

BResource * BResource::getInstance()
{
	if (!g_BResourceSingleton)
	{
		g_BResourceSingleton = new BResource();
	}
	return g_BResourceSingleton;
}

char * BResource::getTableFileName(int index)
{
	if (index < 0 || index >= DATATABLEMAX)
	{
		return NULL;
	}
	return datatablefilename[index];
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