#ifndef __DATATABLE_H__
#define __DATATABLE_H__

#include "Const.h"
#include "MainDependency.h"

class DataTable
{
public:
	DataTable();
	~DataTable();

	bool ReadStringBuffer(int nCol);
	bool CommentBuffer();

	bool ReadAllTable();

	void ReleaseFile();

	char * GetTableFileName(BYTE type);
	bool CheckHeader(BYTE type);

	bool ReadDataDefineTable();
	bool ReadCustomConstTable();
	bool ReadMusicDefineTable();
	bool ReadSEDefineTable();
	bool ReadTextureDefineTable();
	bool ReadSpriteDefineTable();
	bool ReadEffectDefineTable();
	bool ReadWeaponDefineTable();
	bool ReadItemDefineTable();
	bool ReadEnemyBaseDefineTable();
	bool ReadEnemyDefineTable();
	bool ReadMissionDefineTable();
	bool ReadMissionTargetDefineTable();
	bool ReadMissionEnemyDefineTable();

public:
	FILE * file;
	char buffer[M_STRMAX];
	char strbuffer[4][M_STRMAX];
	char bufferlong[M_STRMAX*4];
	int tindex;
	int tint[32];
	int ti;

	static DataTable * getInstance();
};

#endif