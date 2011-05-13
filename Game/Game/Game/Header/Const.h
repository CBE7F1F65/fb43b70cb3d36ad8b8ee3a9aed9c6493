#ifndef __CONST_H__
#define __CONST_H__

#include <stdio.h>

#define GAME_VERSION	0x130
#define GAME_SIGNATURE	"h5nc"

#define M_PATHMAX		_MAX_PATH
#define M_STRMAX		0x80
#define M_MESSAGESTRMAX 0x100
#define M_STRITOAMAX	0x10


// Zorder
enum
{
	ZORDER_BG		= 0,
	ZORDER_MENU_10	= 10,
	ZORDER_MENU_9,
	ZORDER_MENU_8,
	ZORDER_MENU_7,
	ZORDER_MENU_6,
	ZORDER_MENU_5,
	ZORDER_MENU_4,
	ZORDER_MENU_3,
	ZORDER_MENU_2,
	ZORDER_MENU_1,
	ZORDER_MENU_0,
	ZORDER_FG		= 1000,
};

#endif

// Assert
#define ASSERTSTR_SECONDSINGLETON	"Attempted to allocate a second instance of a singleton."