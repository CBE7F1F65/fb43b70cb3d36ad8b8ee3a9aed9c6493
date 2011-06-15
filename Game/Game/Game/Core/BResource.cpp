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

#define RESOURCE_PATH	"Resource"

#endif	// CC_PLATFORM_WIN32

#define RESOURCE_SCRIPT_PATH	"Script\\"
#define RESOURCE_SCRIPTBINFILE	"Script.dat"
#define RESOURCE_DATA_PATH		"Data\\"
#define RESOURCE_DATADEFINEFILE	"DataDefine.table"
#define RESOURCE_RESBINFILE		"Resource.bin"

#define RESOURCE_RESBINPASSWORD	0x8f4b2491

static BResource * g_BResourceSingleton = NULL;


BResource::BResource()
{
	BIOInterface::getInstance()->System_Assert(g_BResourceSingleton == NULL, ASSERTSTR_SECONDSINGLETON);
	ZeroMemory(datatablefilename, sizeof(char)*DATATABLEMAX*M_STRMAX);
	strcpy(datatablefilename[0], RESOURCE_DATADEFINEFILE);
	ZeroMemory(tex, sizeof(HTEXTURE) * DATASTRUCT_TEXMAX);
	ZeroMemory(texinfo, sizeof(hTextureInfo) * DATASTRUCT_TEXMAX);
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
	FreeTexture();
}

bool BResource::Init()
{
	
	CCFileUtils::setResourcePath(CCFileUtils::fullPathFromRelativePath(RESOURCE_PATH));
	
	BIOInterface * bio = BIOInterface::getInstance();
	bio->Resource_SetCurrentDirectory(RESOURCE_PATH);
#if defined __WIN32
	bio->Resource_SetPath(RESOURCE_PATH);
	bio->System_SetLogFile(LOG_FILENAME);
	bio->Ini_SetIniFile(INI_FILENAME);
	bio->Data_SetDataFile(DATA_FILENAME);
#elif defined __IPHONE
	bio->Resource_SetPath(CCFileUtils::fullPathFromRelativePath(RESOURCE_PATH));
	std::string writablepath = CCFileUtils::getWriteablePath();
//	writablepath += M_FOLDER_SLASH;
	bio->System_SetLogFile((writablepath+LOG_FILENAME).c_str());
	bio->Ini_SetIniFile((writablepath+INI_FILENAME).c_str());
	bio->Data_SetDataFile((writablepath+DATA_FILENAME).c_str());
#endif
	
	return true;

}

void BResource::MallocCustomConst()
{
	ReleaseCustomConst();
	customconstdata = (customconstData *)malloc(RSIZE_CUSTOMCONST);
	ClearCustomConstData();
}

bool BResource::GetCustomConstDataByName(const char * name, int * value)
{
	if (customconstdata)
	{
		for (int i=0; i<DATASTRUCT_CUSTOMCONSTMAX; i++)
		{
			if (!strcmp(name, customconstdata[i].name))
			{
				if (value)
				{
					*value = customconstdata[i].value;
					return true;
				}
				break;
			}
		}
	}
	return false;
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
void BResource::ClearEnemyBaseData()
{
	ZeroMemory(enemybasedata, RSIZE_ENEMYBASE);
}
void BResource::ClearEnemyData()
{
	ZeroMemory(enemydata, RSIZE_ENEMY);
}
void BResource::ClearMissionData()
{
	ZeroMemory(missiondata, RSIZE_MISSION);
}
void BResource::ClearMissionAimHelpData()
{
	ZeroMemory(missionaimhelpdata, RSIZE_MISSIONAIMHELP);
}
void BResource::ClearMissionEnemyData()
{
	ZeroMemory(missionenemydata, RSIZE_MISSIONENEMY);
	missionenemymax = 0;
}

int BResource::GetMissionDataIndexByStageMission(BYTE stageindex, BYTE missionindex)
{
	return stageindex*M_STAGEMISSIONMAX+missionindex;
}

BYTE BResource::GetEnemyBaseType(BYTE etype)
{
	return enemydata[etype].type;
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
	Export_Lua::Init();
	Export_Lua::LuaRegistConst();
	Export_Lua::LuaRegistFunction();
	int iret = 0;
#ifdef __WIN32
	iret = Export_Lua::ReadLuaFileTable();
	if (iret == 0)
	{
		iret = Export_Lua::PackLuaFiles();
		if (iret != 0)
		{
			return false;
		}
	}
#endif
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
		RSIZE_ENEMYBASE + 
		RSIZE_ENEMY + 
		RSIZE_MISSION + 
		RSIZE_MISSIONAIMHELP + 
		RSIZE_MISSIONENEMY + 
		RSIZE_MISSIONENEMYMAX;
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
	memcpy(content+offset, enemybasedata, RSIZE_ENEMYBASE);
	offset += RSIZE_ENEMYBASE;
	memcpy(content+offset, enemydata, RSIZE_ENEMY);
	offset += RSIZE_ENEMY;
	memcpy(content+offset, missiondata, RSIZE_MISSION);
	offset += RSIZE_MISSION;
	memcpy(content+offset, missionaimhelpdata, RSIZE_MISSIONAIMHELP);
	offset += RSIZE_MISSIONAIMHELP;
	memcpy(content+offset, missionenemydata, RSIZE_MISSIONENEMY);
	offset += RSIZE_MISSIONENEMY;
	memcpy(content+offset, &missionenemymax, RSIZE_MISSIONENEMYMAX);
	offset += RSIZE_MISSIONENEMYMAX;

	BIOMemoryFile memfile;
	memfile.data = content;
	strcpy(memfile.filename, RESOURCE_RESBINFILE);
	memfile.size = size;

	bool bret = BIOInterface::getInstance()->Resource_CreatePack(RESOURCE_RESBINFILE, RESOURCE_RESBINPASSWORD, &memfile, NULL);

	ClearCustomConstData();
	ClearMusicData();
	ClearSEData();
	ClearTextureData();
	ClearSpriteData();
	ClearEffectData();
	ClearWeaponData();
	ClearItemData();
	ClearEnemyBaseData();
	ClearEnemyData();
	ClearMissionData();
	ClearMissionAimHelpData();
	ClearMissionEnemyData();

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
		RSIZE_ENEMYBASE + 
		RSIZE_ENEMY + 
		RSIZE_MISSION + 
		RSIZE_MISSIONAIMHELP + 
		RSIZE_MISSIONENEMY + 
		RSIZE_MISSIONENEMYMAX)
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
	memcpy(enemybasedata, content+offset, RSIZE_ENEMYBASE);
	offset += RSIZE_ENEMYBASE;
	memcpy(enemydata, content+offset, RSIZE_ENEMY);
	offset += RSIZE_ENEMY;
	memcpy(missiondata, content+offset, RSIZE_MISSION);
	offset += RSIZE_MISSION;
	memcpy(missionaimhelpdata, content+offset, RSIZE_MISSIONAIMHELP);
	offset += RSIZE_MISSIONAIMHELP;
	memcpy(missionenemydata, content+offset, RSIZE_MISSIONENEMY);
	offset += RSIZE_MISSIONENEMY;
	memcpy(&missionenemymax, content+offset, RSIZE_MISSIONENEMYMAX);
	offset += RSIZE_MISSIONENEMYMAX;

	pbres->Resource_Free(content);

	return true;
}

void BResource::InitTexinfo()
{
	for (int i=0; i<DATASTRUCT_TEXMAX; i++)
	{
		texinfo[i].tex = NULL;
		texinfo[i].texw = texturedata[i].width;
		texinfo[i].texh = texturedata[i].height;
	}
	for (int i=0; i<DATASTRUCT_TEXMAX; i++)
	{
		tex[i].texindex = i;
		texinfo[i].tex = &tex[i].tex;
	}
}


bool BResource::LoadTexture(int texindex /* = -1 */)
{
	if (texindex < 0)
	{
		for (int i=0; i<DATASTRUCT_TEXMAX; i++)
		{
			LoadTexture(i);
		}
		return true;
	}

	char tnbuffer[M_STRMAX];
	CCTexture2D * ptex = (CCTexture2D *)tex[texindex].tex;
	if (ptex)
	{
		ptex->release();
		ptex = NULL;
	}

	strcpy(tnbuffer, texturedata[texindex].texfilename);
	if(strlen(tnbuffer))
	{
		BYTE * content = NULL;
		DWORD size;
		content = BIOInterface::getInstance()->Resource_Load(tnbuffer, &size);
		if (content)
		{
			ptex = new CCTexture2D;

			CCImage image;
			image.initWithImageData(content, size);
			ptex->initWithImage(&image);

			tex[texindex] = (DWORD)ptex;

			BIOInterface::getInstance()->Resource_Free(content);
		}
	}

	if(tex[texindex].tex == NULL)
	{
		return false;
	}
	tex[texindex].texindex = texindex;
	return true;
}

bool BResource::FreeTexture(int texindex /* = -1 */)
{
	if (texindex < 0)
	{
		for (int i=0; i<DATASTRUCT_TEXMAX; i++)
		{
			FreeTexture(i);
		}
		return true;
	}

	if (tex[texindex].tex)
	{
		CCTexture2D * ptex = (CCTexture2D *)tex[texindex].tex;
		ptex->release();
		tex[texindex] = NULL;
		tex[texindex].texindex = texindex;
		return true;
	}
	return false;
}


DWORD BResource::Texture_GetTexture(HTEXTURE tex)
{
	return tex.GetTexture(DATASTRUCT_TEXMAX, texinfo);
}

int BResource::Texture_GetWidth(HTEXTURE tex)
{
	DWORD ttex = Texture_GetTexture(tex);
	if (!ttex)
	{
		return tex.GetTextureWidthByInfo(DATASTRUCT_TEXMAX, texinfo);
	}
	CCTexture2D * ptex = (CCTexture2D *)ttex;
	return ptex->getContentSize().width;
}

int BResource::Texture_GetHeight(HTEXTURE tex)
{
	DWORD ttex = Texture_GetTexture(tex);
	if (!ttex)
	{
		return tex.GetTextureWidthByInfo(DATASTRUCT_TEXMAX, texinfo);
	}
	CCTexture2D * ptex = (CCTexture2D *)ttex;
	return ptex->getContentSize().height;
}

#define RESOURCE_LOADINGFILENAME	"Loading.png"

const char * BResource::getLoadingFileName()
{
	return RESOURCE_LOADINGFILENAME;
}
