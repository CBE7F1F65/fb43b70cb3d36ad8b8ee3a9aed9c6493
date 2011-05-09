#ifndef __CONST_H__
#define __CONST_H__

// Resource

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#define RESOURCE_PATH	"..\\Game\\Resource\\"

#else

#define RESOURCE_PATH	""

#endif	// CC_PLATFORM_WIN32

#define RESOURCE_SCRIPT_PATH	"Script\\"
#define RESOURCE_SCRIPTBINFILE	"Script.dat"
#define RESOURCE_DATA_PATH		"Data\\"
#define RESOURCE_DATATABLEFILE	"Data\\DataTable.table"
#define RESOURCE_RESBINFILE		"Data\\Resource.bin"


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