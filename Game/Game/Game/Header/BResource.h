#ifndef __BRESOURCE_H__
#define __BRESOURCE_H__

#include "Const.h"
#include "MainDependency.h"

#define DATATABLEMAX	0x10

class BResource
{
public:
	BResource();
	~BResource();

	bool Init();

	bool ReadAllTable();
	bool PackData();
	bool GainData();

	bool LoadTexture(int texindex = -1);
	bool FreeTexture(int texindex = -1);

	char * getTableFileName(int index);

public:
	char datatablefilename[DATATABLEMAX][M_STRMAX];

	static BResource * getInstance();
};

#endif