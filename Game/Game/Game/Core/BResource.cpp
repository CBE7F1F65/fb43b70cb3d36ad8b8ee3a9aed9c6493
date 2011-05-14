#include "../Header/BResource.h"
#include "../Header/DataTable.h"
#include "cocos2d.h"

#include "../Export/Export_Lua.h"
#include "../Export/Export_Lua_Scene.h"

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

#define RESOURCE_RESBINPASSWORD	0x8f4b2491

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
	ClearCustomConstData();
}

void BResource::ReleaseCustomConst()
{
	if (customconstdata)
	{
		free(customconstdata);
		customconstdata = NULL;
	}
}

void BResource::ClearCustomConstData()
{
	if (customconstdata)
	{
		ZeroMemory(customconstdata, RSIZE_CUSTOMCONST);
	}
}

void BResource::ClearMusicData()
{
	ZeroMemory(musdata, RSIZE_MUSIC);
}

void BResource::ClearSEData()
{
	ZeroMemory(sedata, RSIZE_SE);
}
void BResource::ClearTextureData()
{
	ZeroMemory(texturedata, RSIZE_TEXTURE);
}
void BResource::ClearSpriteData()
{
	ZeroMemory(spritedata, RSIZE_SPRITE);
}
void BResource::ClearEffectData()
{
	ZeroMemory(effdata, RSIZE_EFFECT);
}
void BResource::ClearWeaponData()
{
	ZeroMemory(weapondata, RSIZE_WEAPON);
}
void BResource::ClearItemData()
{
	ZeroMemory(itemdata, RSIZE_ITEM);
}
void BResource::ClearEnemyData()
{
	ZeroMemory(enemydata, RSIZE_ENEMY);
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
	Export_Lua::LuaRegistConst();
	Export_Lua::LuaRegistFunction();
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
	if (!Export_Lua_Scene::InitCallbacks())
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
	DWORD size =
		RSIZE_CUSTOMCONST + 
		RSIZE_MUSIC + 
		RSIZE_SE + 
		RSIZE_TEXTURE + 
		RSIZE_SPRITE + 
		RSIZE_EFFECT + 
		RSIZE_WEAPON + 
		RSIZE_ITEM + 
		RSIZE_ENEMY;
	BYTE * content = (BYTE *)malloc(size);

	DWORD offset = 0;

	memcpy(content+offset, customconstdata, RSIZE_CUSTOMCONST);
	offset += RSIZE_CUSTOMCONST;
	memcpy(content+offset, musdata, RSIZE_MUSIC);
	offset += RSIZE_MUSIC;
	memcpy(content+offset, sedata, RSIZE_SE);
	offset += RSIZE_SE;
	memcpy(content+offset, texturedata, RSIZE_TEXTURE);
	offset += RSIZE_TEXTURE;
	memcpy(content+offset, spritedata, RSIZE_SPRITE);
	offset += RSIZE_SPRITE;
	memcpy(content+offset, effdata, RSIZE_EFFECT);
	offset += RSIZE_EFFECT;
	memcpy(content+offset, weapondata, RSIZE_WEAPON);
	offset += RSIZE_WEAPON;
	memcpy(content+offset, itemdata, RSIZE_ITEM);
	offset += RSIZE_ITEM;
	memcpy(content+offset, enemydata, RSIZE_ENEMY);
	offset += RSIZE_ENEMY;

	BIOMemoryFile memfile;
	memfile.data = content;
	strcpy(memfile.filename, RESOURCE_RESBINFILE);
	memfile.size = size;

	bool bret = BIOInterface::getInstance()->Resource_CreatePack(RESOURCE_RESBINFILE, RESOURCE_RESBINPASSWORD, &memfile, NULL);

	free(content);
	return bret;
}

bool BResource::GainData()
{
	BIOInterface * pbres = BIOInterface::getInstance();

	BYTE * content = NULL;
	DWORD size = 0;
	DWORD offset = 0;

	if (pbres->Resource_AttachPack(RESOURCE_RESBINFILE, RESOURCE_RESBINPASSWORD))
	{
		content = pbres->Resource_Load(RESOURCE_RESBINFILE, &size);
		pbres->Resource_RemovePack(RESOURCE_RESBINFILE);
	}

	if (!content)
	{
		return false;
	}

	if (!customconstdata)
	{
		MallocCustomConst();
	}

	if (size != 
		RSIZE_CUSTOMCONST + 
		RSIZE_MUSIC + 
		RSIZE_SE + 
		RSIZE_TEXTURE + 
		RSIZE_SPRITE + 
		RSIZE_EFFECT + 
		RSIZE_WEAPON + 
		RSIZE_ITEM + 
		RSIZE_ENEMY)
	{
		return false;
	}

	memcpy(customconstdata, content+offset, RSIZE_CUSTOMCONST);
	offset += RSIZE_CUSTOMCONST;
	memcpy(musdata, content+offset, RSIZE_MUSIC);
	offset += RSIZE_MUSIC;
	memcpy(sedata, content+offset, RSIZE_SE);
	offset += RSIZE_SE;
	memcpy(texturedata, content+offset, RSIZE_TEXTURE);
	offset += RSIZE_TEXTURE;
	memcpy(spritedata, content+offset, RSIZE_SPRITE);
	offset += RSIZE_SPRITE;
	memcpy(effdata, content+offset, RSIZE_EFFECT);
	offset += RSIZE_EFFECT;
	memcpy(weapondata, content+offset, RSIZE_WEAPON);
	offset += RSIZE_WEAPON;
	memcpy(itemdata, content+offset, RSIZE_ITEM);
	offset += RSIZE_ITEM;
	memcpy(enemydata, content+offset, RSIZE_ENEMY);
	offset += RSIZE_ENEMY;

	pbres->Resource_Free(content);

	return true;
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