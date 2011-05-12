#ifndef __BIOINTERFACE_H__
#define __BIOINTERFACE_H__

#include "MainDependency.h"

#define BIO_PATHMAX	0x80

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

};

#endif