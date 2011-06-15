#ifndef __BRESOURCE_H__
#define __BRESOURCE_H__

#include "Const.h"
#include "MainDependency.h"
#include "DataStruct.h"
#include "HTexture.h"

#define DATATABLEMAX	0x10

class BResource
{
public:
	BResource();
	~BResource();

	bool Init();

	bool ReadAllScript();

	bool ReadAllTable();
	bool PackData();
	bool GainData();

	void InitTexinfo();
	bool LoadTexture(int texindex = -1);
	bool FreeTexture(int texindex = -1);

	void ReleaseCustomConst();
	void MallocCustomConst();
	bool GetCustomConstDataByName(const char * name, int * value);

	void ClearCustomConstData();
	void ClearMusicData();
	void ClearSEData();
	void ClearTextureData();
	void ClearSpriteData();
	void ClearEffectData();
	void ClearWeaponData();
	void ClearItemData();
	void ClearEnemyBaseData();
	void ClearEnemyData();
	void ClearMissionData();
	void ClearMissionEnemyData();

	int GetMissionDataIndexByStageMission(BYTE stageindex, BYTE missionindex);
	BYTE GetEnemyBaseType(BYTE etype);

	int Texture_GetWidth(HTEXTURE tex);
	int Texture_GetHeight(HTEXTURE tex);
	DWORD Texture_GetTexture(HTEXTURE tex);

	const char * GetDataPath();
	char * getTableFileName(int index);

	const char * getLoadingFileName();

public:
	char datatablefilename[DATATABLEMAX][M_STRMAX];

	customconstData * customconstdata;
	musicData musdata[DATASTRUCT_MUSICMAX];
	seData sedata[DATASTRUCT_SEMAX];
	textureData texturedata[DATASTRUCT_TEXMAX];
	spriteData spritedata[DATASTRUCT_SPRITEMAX];
	effectData effdata[DATASTRUCT_EFFECTMAX];
	weaponData weapondata[DATASTRUCT_WEAPONMAX];
	itemData itemdata[DATASTRUCT_ITEMMAX];
	enemyBaseData enemybasedata[DATASTRUCT_ENEMYBASEMAX];
	enemyData enemydata[DATASTRUCT_ENEMYMAX];
	missionData missiondata[DATASTRUCT_MISSIONMAX];
	missionEnemyData missionenemydata[DATASTRUCT_MISSIONENEMYMAX];
	int missionenemymax;

	HTEXTURE tex[DATASTRUCT_TEXMAX];
	hTextureInfo texinfo[DATASTRUCT_TEXMAX];

	static BResource * getInstance();
};

#endif