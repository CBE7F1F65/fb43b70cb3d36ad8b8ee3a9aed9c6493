#include "../Header/DataTable.h"
#include "../Header/BResource.h"

#include "../Header/BIOInterface.h"

#include "cocos2d.h"

#include "../Header/SpriteItemManager.h"
#include "../Header/GameMain.h"

using namespace cocos2d;

static DataTable * g_DataTableSingleton = NULL;

#define DATATYPE_DATATABLEBEGIN			0x50

#define DATATYPE_DATADEFINE				DATATYPE_DATATABLEBEGIN
#define DATATYPE_CUSTOMCONSTDEFINE		0x51
#define DATATYPE_MUSICDEFINE			0x52
#define DATATYPE_SEDEFINE				0x53
#define DATATYPE_TEXTUREDEFINE			0x54
#define DATATYPE_SPRITEDEFINE			0x55
#define DATATYPE_EFFECTDEFINE			0x56
#define DATATYPE_WEAPONDEFINE			0x57
#define DATATYPE_ITEMDEFINE				0x58
#define DATATYPE_ENEMYDEFINE			0x59
#define DATATYPE_MISSIONDEFINE			0x5A

#define DATAINDEX_DATADEFINE			(DATATYPE_DATADEFINE-DATATYPE_DATATABLEBEGIN)
#define DATAINDEX_CUSTOMCONSTDEFINE		(DATATYPE_CUSTOMCONSTDEFINE-DATATYPE_DATATABLEBEGIN)
#define DATAINDEX_MUSICDEFINE			(DATATYPE_MUSICDEFINE-DATATYPE_DATATABLEBEGIN)
#define DATAINDEX_SEDEFINE				(DATATYPE_SEDEFINE-DATATYPE_DATATABLEBEGIN)
#define DATAINDEX_TEXTUREDEFINE			(DATATYPE_TEXTUREDEFINE-DATATYPE_DATATABLEBEGIN)
#define DATAINDEX_SPRITEDEFINE			(DATATYPE_SPRITEDEFINE-DATATYPE_DATATABLEBEGIN)
#define DATAINDEX_EFFECTDEFINE			(DATATYPE_EFFECTDEFINE-DATATYPE_DATATABLEBEGIN)
#define DATAINDEX_WEAPONDEFINE			(DATATYPE_WEAPONDEFINE-DATATYPE_DATATABLEBEGIN)
#define DATAINDEX_ITEMDEFINE			(DATATYPE_ITEMDEFINE-DATATYPE_DATATABLEBEGIN)
#define DATAINDEX_ENEMYDEFINE			(DATATYPE_ENEMYDEFINE-DATATYPE_DATATABLEBEGIN)
#define DATAINDEX_MISSIONDEFINE			(DATATYPE_MISSIONDEFINE-DATATYPE_DATATABLEBEGIN)

#define ERRORSTR_DATATABLE	"Error in Reading Data Table File!"

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
	BIOInterface::getInstance()->System_Assert(g_DataTableSingleton == NULL, ASSERTSTR_SECONDSINGLETON);
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
	return BResource::getInstance()->getTableFileName(type - DATATYPE_DATATABLEBEGIN);
}

bool DataTable::ReadAllTable()
{
	BIOInterface * bio = BIOInterface::getInstance();
	BResource * pbres = BResource::getInstance();
	if (!ReadDataDefineTable())
	{
		bio->System_MessageBox(ERRORSTR_DATATABLE, pbres->getTableFileName(DATAINDEX_DATADEFINE));
		return false;
	}
	if (!ReadCustomConstTable())
	{
		bio->System_MessageBox(ERRORSTR_DATATABLE, pbres->getTableFileName(DATAINDEX_CUSTOMCONSTDEFINE));
		return false;
	}
	if (!ReadMusicDefineTable())
	{
		bio->System_MessageBox(ERRORSTR_DATATABLE, pbres->getTableFileName(DATAINDEX_MUSICDEFINE));
		return false;
	}
	if (!ReadSEDefineTable())
	{
		bio->System_MessageBox(ERRORSTR_DATATABLE, pbres->getTableFileName(DATAINDEX_SEDEFINE));
		return false;
	}
	if (!ReadTextureDefineTable())
	{
		bio->System_MessageBox(ERRORSTR_DATATABLE, pbres->getTableFileName(DATAINDEX_TEXTUREDEFINE));
		return false;
	}
	if (!ReadSpriteDefineTable())
	{
		bio->System_MessageBox(ERRORSTR_DATATABLE, pbres->getTableFileName(DATAINDEX_SPRITEDEFINE));
		return false;
	}
	if (!ReadEffectDefineTable())
	{
		bio->System_MessageBox(ERRORSTR_DATATABLE, pbres->getTableFileName(DATAINDEX_EFFECTDEFINE));
		return false;
	}
	if (!ReadWeaponDefineTable())
	{
		bio->System_MessageBox(ERRORSTR_DATATABLE, pbres->getTableFileName(DATAINDEX_WEAPONDEFINE));
		return false;
	}
	if (!ReadItemDefineTable())
	{
		bio->System_MessageBox(ERRORSTR_DATATABLE, pbres->getTableFileName(DATAINDEX_ITEMDEFINE));
		return false;
	}
	if (!ReadEnemyDefineTable())
	{
		bio->System_MessageBox(ERRORSTR_DATATABLE, pbres->getTableFileName(DATAINDEX_ENEMYDEFINE));
		return false;
	}
	if (!ReadMissionDefineTable())
	{
		bio->System_MessageBox(ERRORSTR_DATATABLE, pbres->getTableFileName(DATAINDEX_MISSIONDEFINE));
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

	BResource * pbres = BResource::getInstance();
	char tablefilename[M_PATHMAX];
	strcpy(tablefilename, pbres->GetDataPath());
	strcat(tablefilename, nowfilename);
	
	BIOInterface * bio = BIOInterface::getInstance();
	file = fopen(bio->Resource_MakePath(tablefilename), "rb");
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

bool DataTable::ReadCustomConstTable()
{
	if (!CheckHeader(DATATYPE_CUSTOMCONSTDEFINE))
	{
		return false;
	}

	BResource * pbres = BResource::getInstance();

	pbres->MallocCustomConst();
//	pbres->ClearCustomConst();

	char _tbuffer[M_STRMAX];
	_READSTRINGBUFFERLINE(4);
	while (!feof(file))
	{
		_INITTINT;
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		_CHECKEOF_DATATABLE;

		customconstData * item = &(pbres->customconstdata[tindex]);
		fscanf(file, "%s%s", 
			item->name, 
			_tbuffer);

		if (_tbuffer[0] == '0' && (_tbuffer[1] == 'x' || _tbuffer[1] == 'X'))
		{
			sscanf(_tbuffer, "%x", &(item->value));
		}
		else
		{
			sscanf(_tbuffer, "%d", &(item->value));
		}

		_DOSWAPTINT;
		_INITTINT;
	}
	return true;
}

bool DataTable::ReadMusicDefineTable()
{
	if (!CheckHeader(DATATYPE_MUSICDEFINE))
	{
		return false;
	}

	BResource * pbres = BResource::getInstance();

	pbres->ClearMusicData();
//	ZeroMemory(BResource::bres.musdata, RSIZE_MUSIC);
	_READSTRINGBUFFERLINE(7);
	while (!feof(file))
	{
		_INITTINT;
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		musicData * item = &(pbres->musdata[tindex]);
		_CHECKEOF_DATATABLE;

		fscanf(file, "\t%[^\t]%s%d%d%d", 
			item->musicname, 
			item->musicfilename, 
			&(item->startpos), 
			&(item->introlength), 
			&(item->alllength));

		_DOSWAPTINT;
		_INITTINT;
	}
	return true;
}

bool DataTable::ReadSEDefineTable()
{
	if (!CheckHeader(DATATYPE_SEDEFINE))
	{
		return false;
	}

	BResource * pbres = BResource::getInstance();

	pbres->ClearSEData();

	_READSTRINGBUFFERLINE(3);
	while (!feof(file))
	{
		_INITTINT;
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		seData * item = &(pbres->sedata[tindex]);
		_CHECKEOF_DATATABLE;

		fscanf(file, "%s", item->filename);

		_DOSWAPTINT;
		_INITTINT;
	}
	return true;
}

bool DataTable::ReadTextureDefineTable()
{
	if (!CheckHeader(DATATYPE_TEXTUREDEFINE))
	{
		return false;
	}

	BResource * pbres = BResource::getInstance();

	pbres->ClearTextureData();

	_READSTRINGBUFFERLINE(5);
	while (!feof(file))
	{
		_INITTINT;
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		_CHECKEOF_DATATABLE;
		textureData * item = &(pbres->texturedata[tindex]);

		fscanf(file, "%s%d%d",
			item->texfilename,
			&(item->width),
			&(item->height)
			);

		_DOSWAPTINT;
		_INITTINT;
	}
	return true;
}

bool DataTable::ReadSpriteDefineTable()
{
	if (!CheckHeader(DATATYPE_SPRITEDEFINE))
	{
		return false;
	}

	BResource * pbres = BResource::getInstance();

	pbres->ClearSpriteData();

	_READSTRINGBUFFERLINE(8);
	while (!feof(file))
	{
		_INITTINT;
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		_CHECKEOF_DATATABLE;
		spriteData * item = &(pbres->spritedata[tindex]);

		fscanf(file, "%s%d%f%f%f%f", 
			item->spritename, 
			&(item->tex),
			&(item->tex_x), 
			&(item->tex_y), 
			&(item->tex_w), 
			&(item->tex_h));

		_DOSWAPTINT;
		_INITTINT;
	}
	return true;
}

bool DataTable::ReadEffectDefineTable()
{
	if (!CheckHeader(DATATYPE_EFFECTDEFINE))
	{
		return false;
	}

	BResource * pbres = BResource::getInstance();

	pbres->ClearEffectData();

	_READSTRINGBUFFERLINE(3);
	while (!feof(file))
	{
		_INITTINT;
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		effectData * item = &(pbres->effdata[tindex]);
		_CHECKEOF_DATATABLE;

		fscanf(file, "%s", item->filename);

		_DOSWAPTINT;
		_INITTINT;
	}
	return true;
}

bool DataTable::ReadWeaponDefineTable()
{
	BResource * pbres = BResource::getInstance();
	pbres->ClearWeaponData();
	return true;
}

bool DataTable::ReadItemDefineTable()
{
	if (!CheckHeader(DATATYPE_ITEMDEFINE))
	{
		return false;
	}

	BResource * pbres = BResource::getInstance();

	pbres->ClearItemData();

	int itemtypecount = 0;

	_READSTRINGBUFFERLINE(3);
	while (!feof(file))
	{
		_INITTINT;
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		itemData * item = &(pbres->itemdata[tindex]);
		_CHECKEOF_DATATABLE;

		fscanf(file, "%s", strbuffer[0]);

		_DOSWAPTINT;
		_INITTINT;

		item->siid = SpriteItemManager::GetIndexByName(strbuffer[0]);

		itemtypecount++;
	}

	GameMain::getInstance()->itemtypecount = itemtypecount;

	return true;
}

bool DataTable::ReadEnemyDefineTable()
{
	if (!CheckHeader(DATATYPE_ENEMYDEFINE))
	{
		return false;
	}

	BResource * pbres = BResource::getInstance();

	pbres->ClearEnemyData();


	_READSTRINGBUFFERLINE(13);
	while (!feof(file))
	{
		_INITTINT;
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		enemyData * item = &(pbres->enemydata[tindex]);
		_CHECKEOF_DATATABLE;

		fscanf(file, "%s%s%s%d%s%s%x%d%d%d%d", 
			strbuffer[0], 
			strbuffer[1], 
			strbuffer[2], 
			&(item->life), 
			strbuffer[3], 
			strbuffer[4], 
			_SAVETINT, 
			&(item->atk[0]), 
			&(item->atk[1]), 
			&(item->atk[2]), 
			&(item->atk[3]));

		_DOSWAPTINT;
		_INITTINT;

		item->siid = SpriteItemManager::GetIndexByName(strbuffer[0]);
		item->sidesiid = SpriteItemManager::GetIndexByName(strbuffer[1]);
		item->sidearrowsiid = SpriteItemManager::GetIndexByName(strbuffer[2]);
		BResource::getInstance()->GetCustomConstDataByName(strbuffer[3], &item->elayer);
		BResource::getInstance()->GetCustomConstDataByName(strbuffer[4], &item->elayeradvance);
		item->attackflag = _LOADTINT;
	}

	return true;
}

bool DataTable::ReadMissionDefineTable()
{
	if (!CheckHeader(DATATYPE_MISSIONDEFINE))
	{
		return false;
	}

	BResource * pbres = BResource::getInstance();

	pbres->ClearMissionData();

	_READSTRINGBUFFERLINE(18);
	while (!feof(file))
	{
		_INITTINT;
		_BREAKCOMMENTBUFFER;
		fscanf(file, "%d", &tindex);
		_CHECKEOF_DATATABLE;
		missionData * item = &(pbres->missiondata[tindex]);

		fscanf(file, "%x%s%x%d%d%d%d%d%d%d%d%d%d%d%x%x%x", 
			_SAVETINT,
//			&(item->missiontype), 
			strbuffer[0],
			&(item->weatherflag), 
			_SAVETINT,
			_SAVETINT,
			_SAVETINT,
			_SAVETINT,
			_SAVETINT,
			_SAVETINT,
			_SAVETINT,
			_SAVETINT,
/*			&(item->targets[0].enemytype), 
			&(item->targets[0].num), 
			&(item->targets[1].enemytype), 
			&(item->targets[1].num), 
			&(item->targets[2].enemytype), 
			&(item->targets[2].num), 
			&(item->defend.defendturn), 
*/			&(item->ranks[0].hiscore), 
			&(item->ranks[1].hiscore), 
			&(item->ranks[2].hiscore), 
			_SAVETINT,
			_SAVETINT,
			_SAVETINT
//			&(item->helps[0].helpindex), 
//			&(item->helps[1].helpindex), 
//			&(item->helps[2].helpindex)
			);


		_DOSWAPTINT;
		_INITTINT;

		item->missiontype = _LOADTINT;
		item->bgsiid = SpriteItemManager::GetIndexByName(strbuffer[0]);
		item->sp = _LOADTINT;
		item->targets[0].enemytype = _LOADTINT;
		item->targets[0].num = _LOADTINT;
		item->targets[1].enemytype = _LOADTINT;
		item->targets[1].num = _LOADTINT;
		item->targets[2].enemytype = _LOADTINT;
		item->targets[2].num = _LOADTINT;
		item->defend.defendturn = _LOADTINT;

		int _tindex = _LOADTINT;
		item->helps[0].helptype = _tindex>>8;
		item->helps[0].helpindex = _tindex&0xff;
		_tindex = _LOADTINT;
		item->helps[1].helptype = _tindex>>8;
		item->helps[1].helpindex = _tindex&0xff;
		_tindex = _LOADTINT;
		item->helps[2].helptype = _tindex>>8;
		item->helps[2].helpindex = _tindex&0xff;

	}
	return true;
}