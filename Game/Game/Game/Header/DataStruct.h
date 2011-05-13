#ifndef __DATASTRUCT_H__
#define __DATASTRUCT_H__

#define DATASTRUCT_CUSTOMCONSTMAX	0x100

struct customconstData{
	char name[M_STRMAX];
	int value;
};

#define RSIZE_CUSTOMCONST	(sizeof(customconstData) * DATASTRUCT_CUSTOMCONSTMAX)

#endif