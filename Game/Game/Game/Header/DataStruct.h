#ifndef __DATASTRUCT_H__
#define __DATASTRUCT_H__

#define DATASTRUCT_CUSTOMCONSTMAX	0x100
#define DATASTRUCT_TEXMAX			0x80
#define DATASTRUCT_MUSICMAX			0x10
#define DATASTRUCT_SEMAX			0x40
#define DATASTRUCT_EFFECTMAX		0x40
#define DATASTRUCT_SPRITEMAX		0x400
#define DATASTRUCT_WEAPONMAX		0x10
#define DATASTRUCT_ITEMMAX			0x20
#define DATASTRUCT_ENEMYBASEMAX		M_ENEMYTYPEMAX
#define DATASTRUCT_ENEMYMAX			0x100
#define DATASTRUCT_MISSIONMAX		(M_STAGEMAX*M_STAGEMISSIONMAX)
#define DATASTRUCT_MISSIONENEMYMAX	0x1000

struct customconstData{
	char name[M_STRMAX];
	int value;
};

struct textureData
{
	char texfilename[M_STRMAX];
	int width;
	int height;
};

struct musicData{
	char musicname[M_STRMAX];
	char musicfilename[M_PATHMAX];
#ifdef __IPHONE
	char _unused[4];
#endif
	LONGLONG startpos;
	LONGLONG introlength;
	LONGLONG alllength;
};

struct spriteData 
{
	char spritename[M_STRMAX];
	float tex_x;
	float tex_y;
	float tex_w;
	float tex_h;
	int tex;
};

struct seData
{
	char filename[M_STRMAX];
};

struct effectData
{
	char filename[M_STRMAX];
};

struct weaponData 
{
	int apcost;
	int atk;
	int para;
};

struct itemData
{
	int siid;
};

struct enemyCollisionData
{
	float x;
	float y;
	float rh;
	float rv;
};

struct enemyBaseData
{
	enemyCollisionData headcollision;
	enemyCollisionData bodycollision;
	float headshotscale;
	float blowdistance;
	float boxr;

	int siid;
	int sidesiid;
	int sidearrowsiid;
	int elayer;
	int elayeradvance;

	BYTE attackflag;

	BYTE normalframe;
	BYTE idleframe;
	BYTE attackframe;
	BYTE woundframe;
	BYTE deadframe;
	BYTE specialframe;
};

struct enemyData
{
	int atk[M_ENEMY_ELAYERMAX];
	int def[M_WEAPONTYPEMAX];
	int life;
	BYTE type;
};

#define M_MISSIONTARGETMAX	3
#define M_MISSIONRANKMAX	3
#define M_MISSIONHELPMAX	3

// mission

struct missionTargetData{
	BYTE enemybasetype;
	BYTE num;
};

struct missionRankData{
	int hiscore;
};

struct missionDefendData{
	BYTE defendturn;
};

struct missionHelpData{
	BYTE helptype;
	BYTE helpindex;
};

struct missionData{
	missionHelpData helps[M_MISSIONHELPMAX];
	missionTargetData targets[M_MISSIONTARGETMAX];
	missionRankData ranks[M_MISSIONRANKMAX];
	missionDefendData defend;
	int bgsiid;
	BYTE missiontype;
	BYTE placement;
	BYTE weatherflag;
	BYTE sp;
};

struct missionEnemyData{
	int enemytype;
	int elayerangle;
	float x;
	float y;
	BYTE stageindex;
	BYTE missionindex;
	BYTE turn;
	BYTE flag;
};

#define RSIZE_CUSTOMCONST	(sizeof(customconstData) * DATASTRUCT_CUSTOMCONSTMAX)
#define RSIZE_TEXTURE		(sizeof(textureData) * DATASTRUCT_TEXMAX)
#define RSIZE_MUSIC			(sizeof(musicData) * DATASTRUCT_MUSICMAX)
#define RSIZE_SE			(sizeof(seData) * DATASTRUCT_SEMAX)
#define RSIZE_EFFECT		(sizeof(effectData) * DATASTRUCT_EFFECTMAX)
#define RSIZE_SPRITE		(sizeof(spriteData) * DATASTRUCT_SPRITEMAX)
#define RSIZE_WEAPON		(sizeof(weaponData) * DATASTRUCT_WEAPONMAX)
#define RSIZE_ITEM			(sizeof(itemData) * DATASTRUCT_ITEMMAX)
#define RSIZE_ENEMYBASE		(sizeof(enemyBaseData) * DATASTRUCT_ENEMYBASEMAX)
#define RSIZE_ENEMY			(sizeof(enemyData) * DATASTRUCT_ENEMYMAX)
#define RSIZE_MISSION		(sizeof(missionData) * DATASTRUCT_MISSIONMAX)
#define RSIZE_MISSIONENEMY	(sizeof(missionEnemyData) * DATASTRUCT_MISSIONENEMYMAX)
#define RSIZE_MISSIONENEMYMAX	(sizeof(int))

#endif