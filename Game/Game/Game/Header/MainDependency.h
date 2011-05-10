#ifndef __MAINDEPENDENCY_H__
#define __MAINDEPENDENCY_H__

#ifdef __WIN32
#include <windows.h>
#endif // __WIN32
#include <list>
#include <vector>

#ifndef min
#define min(x,y) ((x) < (y)) ? (x) : (y)
#endif
#ifndef max
#define max(x,y) ((x) > (y)) ? (x) : (y)
#endif

#ifndef ZeroMemory
#define ZeroMemory(Destination,Length) memset((Destination),0,(Length))
#endif

/*
** Common data types
*/
#ifndef DWORD
#if defined __IPHONE
typedef unsigned int       DWORD;
#else
typedef unsigned long       DWORD;
#endif
typedef unsigned short      WORD;
typedef unsigned char       BYTE;
#endif

#ifndef QWORD
#if defined __WIN32
typedef unsigned __int64	QWORD;
#elif defined __PSP
typedef u64	QWORD;
#elif defined __IPHONE
typedef uint64_t QWORD;
#endif // __WIN32
#endif

#ifndef LONGLONG
#if defined __WIN32
typedef __int64			LONGLONG;
#elif __PSP
typedef s64	LONGLONG;
#elif __IPHONE
typedef int64_t LONGLONG;

#endif // __WIN32
typedef QWORD ULONGLONG;
#endif

#ifndef NULL
#define NULL	(0)
#endif

#ifndef isspace
#define isspace(X) ((X)==0x20 || (X)>=0x09&&(X)<=0x0D)
#endif
#ifndef iswspace
#define iswspace	isspace
#endif

#ifndef isdigit
#define isdigit(X) ((X)>='0' && (X)<='9')
#endif
#ifndef iswdigit
#define iswdigit	isdigit
#endif

#ifndef islower
#define islower(X) ((X)>='a' && (X)<='z')
#endif
#ifndef iswlower
#define iswlower	islower
#endif

#ifndef isupper
#define isupper(X) ((X)>='A' && (X)<='Z')
#endif
#ifndef iswupper
#define iswupper	isupper
#endif
/*
** Common math constants
*/
#ifndef M_PI
#define M_PI	3.14159265358979323846f
#define M_PI_2	1.57079632679489661923f
#define M_PI_4	0.785398163397448309616f
#define M_1_PI	0.318309886183790671538f
#define M_2_PI	0.636619772367581343076f
#endif

/************************************************************************/
/* These defines are added by h5nc (h5nc@yahoo.com.cn)                  */
/************************************************************************/
#ifndef M_E
#define M_E        2.71828182845904523536f
#define M_LOG2E    1.44269504088896340736f
#define M_LOG10E   0.434294481903251827651f
#define M_LN2      0.693147180559945309417f
#define M_LN10     2.30258509299404568402f
#define M_2_SQRTPI 1.12837916709551257390f
#define M_SQRT2    1.41421356237309504880f
#define M_SQRT1_2  0.707106781186547524401f
#endif

#ifndef __IPHONE
#define M_FOLDER_SLASH			'\\'
#define M_FOLDER_SLASH_WRONG	'/'
#else
#define M_FOLDER_SLASH			'/'
#define M_FOLDER_SLASH_WRONG	'\\'
#endif

#endif