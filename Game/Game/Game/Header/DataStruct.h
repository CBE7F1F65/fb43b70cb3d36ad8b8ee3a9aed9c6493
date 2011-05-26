#ifndef __DATASTRUCT_H__
#define __DATASTRUCT_H__

#define DATASTRUCT_CUSTOMCONSTMAX	0x100
#define DATASTRUCT_TEXMAX			0x40
#define DATASTRUCT_MUSICMAX			0x10
#define DATASTRUCT_SEMAX			0x40
#define DATASTRUCT_EFFECTMAX		0x40
#define DATASTRUCT_SPRITEMAX		0x400
#define DATASTRUCT_WEAPONMAX		0x10
#define DATASTRUCT_ITEMMAX			0x20
#define DATASTRUCT_ENEMYMAX			0x40
#define DATASTRUCT_MISSIONMAX		0xA0

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
	int siid;
};

struct itemData
{
	int siid;
};

struct enemyData
{
	int siid;
};

#define M_MISSIONTARGETMAX	3
#define M_MISSIONRANKMAX	3
#define M_MISSIONHELPMAX	3

// mission

struct missionTargetData{
	BYTE enemytype;
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
	int bgsiid;
	BYTE missiontype;
	BYTE weatherflag;
	missionDefendData defend;
	missionTargetData targets[M_MISSIONTARGETMAX];
	missionRankData ranks[M_MISSIONRANKMAX];
	missionHelpData helps[M_MISSIONHELPMAX];
};

#define RSIZE_CUSTOMCONST	(sizeof(customconstData) * DATASTRUCT_CUSTOMCONSTMAX)
#define RSIZE_TEXTURE		(sizeof(textureData) * DATASTRUCT_TEXMAX)
#define RSIZE_MUSIC			(sizeof(musicData) * DATASTRUCT_MUSICMAX)
#define RSIZE_SE			(sizeof(seData) * DATASTRUCT_SEMAX)
#define RSIZE_EFFECT		(sizeof(effectData) * DATASTRUCT_EFFECTMAX)
#define RSIZE_SPRITE		(sizeof(spriteData) * DATASTRUCT_SPRITEMAX)
#define RSIZE_WEAPON		(sizeof(weaponData) * DATASTRUCT_WEAPONMAX)
#define RSIZE_ITEM			(sizeof(itemData) * DATASTRUCT_ITEMMAX)
#define RSIZE_ENEMY			(sizeof(enemyData) * DATASTRUCT_ENEMYMAX)
#define RSIZE_MISSION		(sizeof(missionData) * DATASTRUCT_MISSIONMAX)

#endif