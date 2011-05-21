#include "../Header/BIOInterface.h"

#include "../Header/MainDependency.h"

#include "cocos2d.h"
using namespace cocos2d;

/************************************************************************/
/* System                                                               */
/************************************************************************/

void BIOInterface::System_SetLogFile(const char * filename)
{
	strcpy(szLogFile, Resource_MakePath(filename));
	Resource_DeleteFile(szLogFile);
}

void BIOInterface::System_Log(const char *szFormat, ...)
{
	FILE *hf = NULL;
	va_list ap;

	if(!szLogFile[0]) return;
	hf = fopen(szLogFile, "a");
	if(!hf) return;

	va_start(ap, szFormat);
	vfprintf(hf, szFormat, ap);

	char buffer[_MAX_PATH];
	vsprintf(buffer, szFormat, ap);

	va_end(ap);

	fprintf(hf, "\n");
	fclose(hf);

	CCLOG(buffer);
}

void BIOInterface::System_Snapshot(const char *filename/* =0 */)
{
}

int BIOInterface::System_MessageBox(const char * text, const char * title, DWORD type)
{
	System_Log("%s\t%s", title, text);
#if defined __WIN32
	return MessageBoxA(NULL, text, title, type);
#elif defined __PSP
	pspDebugScreenPrintf("%s\n%s", title, text);
	return IDOK;
#elif defined __IPHONE
	printf("%s\n%s\n", title, text);
	CCMessageBox(text, title);
	return 0;
#endif // __WIN32
}

void BIOInterface::System_Assert(bool cond, const char * msg)
{
	CCAssert(cond, msg);
}

unsigned int g_seed=0;
unsigned int g_seed_self=0;

/************************************************************************/
/* Random                                                               */
/************************************************************************/

int BIOInterface::Random_Seed(int seed/* =0 */)
{
	if (!seed)
	{
		g_seed=Timer_GetCurrentSystemTime();
		g_seed_self=g_seed;
	}
	else
	{
		g_seed=seed;
	}
	return g_seed;
}

int BIOInterface::Random_Int(int min, int max, bool bSelf)
{
	unsigned int * usingseed = bSelf ? (&g_seed_self) : (&g_seed);
	*usingseed=214013*(*usingseed)+2531011;
	if (max-min+1 == 0)
	{
		return min;
	}
	return min+((*usingseed) ^ (*usingseed)>>15)%(max-min+1);
}

float BIOInterface::Random_Float(float min, float max, bool bSelf)
{
	unsigned int * usingseed = bSelf ? (&g_seed_self) : (&g_seed);
	*usingseed=214013*(*usingseed)+2531011;
	if (max == min)
	{
		return min;
	}
	return min+(((*usingseed)>>16)*(max-min))*(1.0f/65535.0f);
}

/************************************************************************/
/* Timer                                                                */
/************************************************************************/


#ifdef __PSP
#include <psprtc.h>
#endif // __PSP

#ifdef __IPHONE
#include <mach/mach_time.h>
#endif

LONGLONG BIOInterface::Timer_GetCurrentSystemTime()
{
#ifdef __WIN32
	LARGE_INTEGER Counter;
	QueryPerformanceCounter(&Counter);
	return Counter.QuadPart;
#else

#ifdef __PSP
	u64 ticks;
	sceRtcGetCurrentTick(&ticks);
	return ticks;
#endif // __PSP

#ifdef __IPHONE
	return mach_absolute_time();
#endif;

#endif // __WIN32
}

LONGLONG BIOInterface::Timer_GetPerformanceFrequency()
{
#ifdef __WIN32
	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);
	return Frequency.QuadPart;
#else

#ifdef __PSP
	return sceRtcGetTickResolution();
#endif // __PSP

#ifdef __IPHONE
	mach_timebase_info_data_t info;
	mach_timebase_info(&info);
	return info.numer*1000000000/info.denom;
#endif;

#endif // __WIN32
}

void BIOInterface::Timer_GetSystemTime(WORD *wYear, WORD *wMonth, WORD *wDayOfWeek, WORD *wDay, WORD *wHour, WORD *wMinute, WORD *wSecond, WORD *wMilliseconds)
{
#if defined __WIN32
	SYSTEMTIME systime;
	GetLocalTime(&systime);
	if (wYear)
	{
		*wYear = systime.wYear;
	}
	if (wMonth)
	{
		*wMonth = systime.wMonth;
	}
	if (wDayOfWeek)
	{
		*wDayOfWeek = systime.wDayOfWeek;
	}
	if (wDay)
	{
		*wDay = systime.wDay;
	}
	if (wHour)
	{
		*wHour = systime.wHour;
	}
	if (wMinute)
	{
		*wMinute = systime.wMinute;
	}
	if (wSecond)
	{
		*wSecond = systime.wSecond;
	}
	if (wMilliseconds)
	{
		*wMilliseconds = systime.wMilliseconds;
	}
#elif defined __PSP
	pspTime psptime;
	u64 filetime;
	sceRtcGetWin32FileTime(&psptime, &filetime);
	if (wYear)
	{
		*wYear = psptime.year;
	}
	if (wMonth)
	{
		*wMonth = psptime.month;
	}
	if (wDayOfWeek)
	{
		*wDayOfWeek = 0;
	}
	if (wDay)
	{
		*wDay = psptime.day;
	}
	if (wHour)
	{
		*wHour = psptime.hour;
	}
	if (wMinute)
	{
		*wMinute = psptime.minutes;
	}
	if (wSecond)
	{
		*wSecond = psptime.seconds;
	}
	if (wMilliseconds)
	{
		*wMilliseconds = psptime.microseconds;
	}
#elif defined __IPHONE

	if (wYear)
	{
		*wYear = 0;
	}
	if (wMonth)
	{
		*wMonth = 0;
	}
	if (wDayOfWeek)
	{
		*wDayOfWeek = 0;
	}
	if (wDay)
	{
		*wDay = 0;
	}
	if (wHour)
	{
		*wHour = 0;
	}
	if (wMinute)
	{
		*wMinute = 0;
	}
	if (wSecond)
	{
		*wSecond = 0;
	}
	if (wMilliseconds)
	{
		*wMilliseconds = 0;
	}

#else
	if (wYear)
	{
		*wYear = 0;
	}
	if (wMonth)
	{
		*wMonth = 0;
	}
	if (wDayOfWeek)
	{
		*wDayOfWeek = 0;
	}
	if (wDay)
	{
		*wDay = 0;
	}
	if (wHour)
	{
		*wHour = 0;
	}
	if (wMinute)
	{
		*wMinute = 0;
	}
	if (wSecond)
	{
		*wSecond = 0;
	}
	if (wMilliseconds)
	{
		*wMilliseconds = 0;
	}


#endif
}

LONGLONG BIOInterface::Timer_GetFileTime()
{
#if defined __WIN32
	FILETIME filetime;
	SYSTEMTIME systime;
	GetLocalTime(&systime);
	SystemTimeToFileTime(&systime, &filetime);
	return (((ULONGLONG)filetime.dwHighDateTime)<<32)|(filetime.dwLowDateTime);
#elif defined __PSP
	pspTime psptime;
	u64 filetime;
	sceRtcGetWin32FileTime(&psptime, &filetime);
	return filetime;
#elif defined __IPHONE
	return 0;
#else
	return 0;

#endif
}

#define DATA_PASSWORD	0x3786dc8a

void BIOInterface::Data_SetDataFile(const char * filename)
{
	strcpy(szDataFile, Resource_MakePath(filename));
}

bool BIOInterface::Data_Save(BYTE * data, DWORD size)
{
	BIOMemoryFile memfile;
	strcpy(memfile.filename, DATA_FILENAME);
	memfile.data = data;
	memfile.size = size;
	return Resource_CreatePack(szDataFile, DATA_PASSWORD, &memfile, NULL);
}

BYTE * BIOInterface::Data_Read(DWORD * size/* =NULL */)
{
	BYTE * _data = NULL;
	if (Resource_AttachPack(szDataFile))
	{
		_data = Resource_Load(DATA_FILENAME, size);
		Resource_RemovePack(szDataFile);
	}
	return _data;
}

void BIOInterface::Data_Free(BYTE * data)
{
	Resource_Free(data);
}