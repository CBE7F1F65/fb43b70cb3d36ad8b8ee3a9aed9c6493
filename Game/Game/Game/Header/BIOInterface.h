#ifndef __BIOINTERFACE_H__
#define __BIOINTERFACE_H__

#include "MainDependency.h"

#define BIO_PATHMAX		0x80
#define BIO_STRINGMAX	0x100

struct BIOMemoryFile 
{
	char filename[BIO_PATHMAX];
	BYTE * data;
	DWORD size;
};

struct BIOResourceList
{
	char				filename[BIO_PATHMAX];
	int					password;
	DWORD				filecount;
	BIOMemoryFile*		files;
	BIOResourceList*	next;
};

struct bio3DPoint 
{
	float x;
	float y;
	union {
		float z;
		float scale;
	};
};

#ifndef D3DMATRIX_DEFINED
typedef struct _BIOMATRIX {
	union {
		struct {
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;

		};
		float m[4][4];
	};
} BIOMATRIX;

#define D3DMATRIX_DEFINED

#else
typedef D3DXMATRIX BIOMATRIX;
#define USE_D3D
#endif


#define BIO_PACK_SIGNATURE		0x6850434B
#define BIO_PACK_HEADEROFFSET	0x08
#define BIO_PACK_FILEHEADEROFFSET	(sizeof(DWORD)+BIO_PATHMAX)

/************************************************************************/
/* Pack                                                                 */
/* hPCK	filecount                                                       */
/* size filename content                                                */
/* XOR total size                                                       */
/************************************************************************/

class BIOInterface
{
public:
	BIOInterface();
	~BIOInterface();

public:
	bool	Resource_AccessFile(const char *filename);
	DWORD	Resource_FileSize(const char *filename, FILE * file=NULL);
	void	Resource_DeleteFile(const char *filename);

	void	Resource_SetCurrentDirectory(const char *filename);

	BYTE*	Resource_Load(const char *filename, DWORD *size=0);
	void	Resource_Free(void *res);

	BIOResourceList *	Resource_AttachPack(const char *filename, int password=0);
	void	Resource_RemovePack(const char *filename);
	void	Resource_RemoveAllPacks();

	char*	Resource_SetPath(const char *filename);
	char*	Resource_MakePath(const char *filename);
	char*	Resource_EnumFiles(const char *wildcard=0);
	char*	Resource_EnumFolders(const char *wildcard=0);

	bool	Resource_CreateDirectory(const char *filename);
	bool	Resource_CreatePack(const char * filename, int password, BIOMemoryFile * first, ...);
	bool	Resource_AddFileInPack(const char * filename, int password, BIOMemoryFile * memfile);
private:
	bool	_Resource_RepackHeader(FILE * zipfile, int password, DWORD filecount, DWORD size);
public:

	char*	Resource_GetPackFirstFileName(const char * packfilename);

	/************************************************************************/
	/* Math                                                                 */
	/************************************************************************/

	float			Math_Transform3DPoint(bio3DPoint * pt, bio3DPoint *ptfar=NULL);
	float			Math_Transform3DPoint(float &x, float &y, float &z, bio3DPoint *ptfar=NULL);
	
	char*			Math_itoa(int ival, char * buffer);
	int				Math_atoi(const char * buffer);
	char*			Math_ftoa(float fval, char * buffer);
	float			Math_atof(const char * buffer);
	LONGLONG		Math_atoll(const char * buffer);
	BIOMATRIX*		Math_MatrixIdentity( BIOMATRIX * pOut );
	BIOMATRIX*		Math_MatrixTranslation( BIOMATRIX *pOut, float x, float y, float z );
	BIOMATRIX*		Math_MatrixRotationX( BIOMATRIX *pOut, float angle );
	BIOMATRIX*		Math_MatrixRotationY( BIOMATRIX *pOut, float angle );
	BIOMATRIX*		Math_MatrixRotationZ( BIOMATRIX *pOut, float angle );
	BIOMATRIX*		Math_MatrixScaling( BIOMATRIX *pOut, float sx, float sy, float sz );
	BIOMATRIX*		Math_MatrixMultiply( BIOMATRIX *pOut, const BIOMATRIX *pM1, const BIOMATRIX *pM2 );
	BIOMATRIX*		Math_MatrixOrthoOffCenterLH(BIOMATRIX *pOut, float l, float r, float b, float t, float zn, float zf);

	DWORD			Math_HSVAtoARGB(float h, float s, float v, float a);
	void			Math_ARGBtoHSVA(DWORD col, float *h=NULL, float *s=NULL, float *v=NULL, float *a=NULL);

	/************************************************************************/
	/* System                                                               */
	/************************************************************************/

	void		System_SetLogFile(const char * filename);
	void		System_Log(const char *format, ...);
	void		System_Snapshot(const char *filename=0);
	int			System_MessageBox(const char * text, const char * title, DWORD type=MB_OK);
	void		System_Assert(bool cond, const char * msg);

	int				Random_Seed(int seed=0);
	int				Random_Int(int min, int max, bool bSelf=false);
	float			Random_Float(float min, float max, bool bSelf=false);

	void			Timer_GetSystemTime(WORD *wYear=NULL, WORD *wMonth=NULL, WORD *wDayOfWeek=NULL, WORD *wDay=NULL, WORD *wHour=NULL, WORD *wMinute=NULL, WORD *wSecond=NULL, WORD *wMilliseconds=NULL);
	LONGLONG		Timer_GetFileTime();
	LONGLONG		Timer_GetCurrentSystemTime();
	LONGLONG		Timer_GetPerformanceFrequency();

	/************************************************************************/
	/* Ini                                                                  */
	/************************************************************************/

	void		Ini_SetIniFile(const char * filename);
	void		Ini_SetInt(const char *section, const char *name, int value, char * inifilename=NULL);
	int 		Ini_GetInt(const char *section, const char *name, int def_val, char * inifilename=NULL);
	void		Ini_SetFloat(const char *section, const char *name, float value, char * inifilename=NULL);
	float		Ini_GetFloat(const char *section, const char *name, float def_val, char * inifilename=NULL);
	void		Ini_SetString(const char *section, const char *name, const char *value, char * inifilename=NULL);
	char*		Ini_GetString(const char *section, const char *name, const char *def_val, char * inifilename=NULL);
private:

	DWORD	_IniGetPrivateProfileString(const char * appname, const char * keyname, const char * defval, char * retstr, DWORD size, const char * filename);
	bool	_IniWritePrivateProfileString(const char * appname, const char * keyname, const char * val, const char * filename);



public:
	static BIOInterface* getInstance();

private:

	void DoXOR(DWORD * data, int password, int index);
	void _PostError(const char * str);

	BIOResourceList * reslist;
	char szResourcePath[BIO_PATHMAX];
	char szTmpFilename[BIO_PATHMAX];
#ifdef __WIN32
	HANDLE				hSearch;
	WIN32_FIND_DATAA	SearchData;
#endif


	char			szIniFile[BIO_PATHMAX];
	char			szLogFile[BIO_PATHMAX];

	char			szIniString[BIO_STRINGMAX];

};

#endif