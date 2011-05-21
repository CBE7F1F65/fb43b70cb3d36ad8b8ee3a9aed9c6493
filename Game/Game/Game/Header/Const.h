#ifndef __CONST_H__
#define __CONST_H__

#include <stdio.h>

#define GAME_VERSION	0x130
#define GAME_SIGNATURE	"h5nc"

#define M_PATHMAX		260	//_MAX_PATH
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
	ZORDER_FG		= 0x7fffffff,
};

#endif

// Assert
#define ASSERTSTR_SECONDSINGLETON	"Attempted to allocate a second instance of a singleton."
#define ASSERTSTR_NILCHECK			"Nil value!"

#define M_SCREEN_WIDTH	960.0f
#define M_SCREEN_HEIGHT	640.0f

#define M_DEFAULT_FONTNAME	"Arial-BoldMT"

#define M_CCACTIONFLAG_NULL		0x0000
#define M_CCACTIONFLAG_IN		0x0001
#define M_CCACTIONFLAG_OUT		0x0002
#define M_CCACTIONFLAG_INOUT	(M_CCACTIONFLAG_IN|M_CCACTIONFLAG_OUT)
#define M_CCACTIONFLAG_TO		0x0010
#define M_CCACTIONFLAG_BY		0x0020

#define M_USERNAMEMAX	0x20
#define M_HISCOREMAX	0x10


#define LOG_FILENAME		"log.log"
#define INI_FILENAME		"config.ini"
#define DATA_FILENAME		"data.dat"

#define M_TOUCH_ALLOWABLEMOVEMENT		10.0f
#define M_TOUCH_MINIMUMPRESSDURATION	0.5f