#include "../Header/BIOInterface.h"

#include "cocos2d.h"
using namespace cocos2d;

#include "../Header/Const.h"
#include "../Header/SimpleAudioEngineExpand.h"
using namespace CocosDenshion;

static BIOInterface * g_BIOInterface = NULL;

#define BIOINDERFACE_XORTABLE_SIZE	64
static DWORD g_BIOXORTable[] = {
	0xD2B522B0,
	0x9A86651F,
	0xBE9CDAE3,
	0x356CAFA1,
	0x71E9426F,
	0xCFB05528,
	0x9EEFD8E1,
	0xE26BDB5D,
	0x88EFAE9B,
	0x6E7D586A,
	0xA3DEA752,
	0xF9BB71DA,
	0x23407E3E,
	0xD1EF4B77,
	0x6671E83F,
	0xDBF51CF3,
	0x28C2CF1D,
	0xB4CF999F,
	0x935C4DF2,
	0x69258D93,
	0xD47F7775,
	0x8F433F14,
	0xCDB5E24D,
	0xC3ECC15C,
	0xD06C613B,
	0x804D2BF9,
	0x675377A1,
	0xCAC915F8,
	0xDC715AD3,
	0xAAF76547,
	0xF2D2DF25,
	0xF8CC197B,
	0x85D0E145,
	0xD8E3D330,
	0x579C1860,
	0x5D8E38DE,
	0x52BBD3E7,
	0x3C1F1989,
	0x4A91DA82,
	0x24C03961,
	0x4D189BFD,
	0xA69C113A,
	0x9CD25EB0,
	0x9B3D9832,
	0xEF5BD3EF,
	0xACEFF1DC,
	0xFB73A5B7,
	0xD85A542B,
	0xCDB4E57E,
	0x5B39EFFB,
	0x29D83943,
	0x4A4E3218,
	0x393BC196,
	0x57B45E89,
	0xD3533F88,
	0x32359D80,
	0xF37061D2,
	0x77A33347,
	0xAECD8325,
	0x6CBF776E,
	0xE3AEF133,
	0xFA531878,
	0x5B68FA86,
	0x3DCF5743,
};

BIOInterface::BIOInterface()
{
	System_Assert(g_BIOInterface == NULL, ASSERTSTR_SECONDSINGLETON);
	reslist = NULL;
#ifdef __WIN32
	hSearch = NULL;
	GetModuleFileNameA(GetModuleHandle(NULL), szResourcePath, sizeof(szResourcePath));
#else
	strcpy(szResourcePath, "");
#endif

	int i;
	for(i=strlen(szResourcePath)-1; i>0; i--) if(szResourcePath[i]==M_FOLDER_SLASH) break;
	szResourcePath[i+1]=0;

	strcpy(szLogFile, "");
	strcpy(szIniFile, "");
	strcpy(szDataFile, "");

	_listSoundFileKey.clear();
}

BIOInterface::~BIOInterface()
{
	Resource_RemoveAllPacks();
	if (g_BIOInterface)
	{
		delete g_BIOInterface;
		g_BIOInterface = NULL;
	}
	SimpleAudioEngineExpand::end();
}

BIOInterface* BIOInterface::getInstance()
{
	if (g_BIOInterface == NULL)
	{
		g_BIOInterface = new BIOInterface();
	}
	return g_BIOInterface;
}

bool BIOInterface::Resource_AccessFile(const char *filename)
{
#if defined __WIN32
	if (_access(Resource_MakePath(filename), 00) == -1)
	{
		return false;
	}
#else

	FILE * file = fopen(Resource_MakePath(filename), "rb");
	if (!file)
	{
		return false;
	}
	fclose(file);

#endif // __WIN32
	return true;
}

DWORD BIOInterface::Resource_FileSize(const char *filename, FILE * file/* =NULL */)
{
	if (!filename)
	{
		return 0;
	}
	bool toclose = false;
	DWORD nowseek = 0;
	if (!file)
	{
		file = fopen(Resource_MakePath(filename), "rb");
		toclose = true;
	}

	if (!file)
	{
		return 0;
	}
	nowseek = ftell(file);
	fseek(file, 0, SEEK_END);
	DWORD size = ftell(file);
	fseek(file, nowseek, SEEK_SET);
	if (toclose)
	{
		fclose(file);
	}
	return size;
}

void BIOInterface::Resource_DeleteFile(const char *filename)
{
#if defined __WIN32
	DeleteFileA(Resource_MakePath(filename));
#elif defined __PSP
	sceIoRemove(Resource_MakePath(filename));
#elif defined __IPHONE
	unlink(Resource_MakePath(filename));
#endif // __WIN32
}

void BIOInterface::Resource_SetCurrentDirectory(const char *filename)
{
#if defined __WIN32
	SetCurrentDirectoryA(Resource_MakePath(filename));
#elif defined __PSP
	//	sceIoChdir(Resource_MakePath(filename));
#elif defined __IPHONE
#endif // __WIN32
}

void BIOInterface::_PostError(const char * str)
{
	System_Log(str);
}

void BIOInterface::DoXOR(DWORD * data, int password, int index)
{
	if (!data)
	{
		return;
	}

	*data ^= (password)^g_BIOXORTable[index%BIOINDERFACE_XORTABLE_SIZE];
}

BYTE * BIOInterface::Resource_Load(const char *filename, DWORD *size/* =0 */)
{
	static char *res_err="Can't load resource: %s";

	BIOResourceList *resItem=reslist;

	char szName[BIO_PATHMAX];
	char szZipName[BIO_PATHMAX];
	DWORD filesize = 0;

	BYTE * ptr;

#if defined __WIN32
	HANDLE hF;
#else
	FILE * hF;
#endif

	if(size)
		*size = 0;

	if(filename[0]==M_FOLDER_SLASH || filename[0]==M_FOLDER_SLASH_WRONG || filename[1]==':') goto _fromfile; // skip absolute paths

	// Load from pack

	strcpy(szName,filename);
	strupr(szName);
	for(int i=0; szName[i]; i++) { if(szName[i]==M_FOLDER_SLASH_WRONG) szName[i]=M_FOLDER_SLASH; }

	while(resItem)
	{
		for (int j=0; j<resItem->filecount; j++)
		{
			BIOMemoryFile * memfile = &(resItem->files[j]);
			strcpy(szZipName, memfile->filename);
			strupr(szZipName);
			for(int i=0; szZipName[i]; i++) { if(szZipName[i]==M_FOLDER_SLASH_WRONG) szZipName[i]=M_FOLDER_SLASH; }

			if (!strcmp(szName, szZipName))
			{
				if (!memfile->data)
				{
					FILE * zipfile = fopen(resItem->filename, "rb");
					if (!zipfile)
					{
						return NULL;
					}
					int offset = BIO_PACK_HEADEROFFSET+BIO_PACK_FILEHEADEROFFSET;
					for (int k=0; k<j; k++)
					{
						offset += resItem->files[k].size + BIO_PACK_FILEHEADEROFFSET;
					}
					fseek(zipfile, offset, SEEK_SET);
					memfile->data = (BYTE *)malloc(memfile->size);
					fread(memfile->data, memfile->size, 1, zipfile);
					fclose(zipfile);
					for (int k=0; k*sizeof(DWORD)<memfile->size; k++)
					{
						DoXOR((DWORD *)(&(memfile->data[k*sizeof(DWORD)])), resItem->password, k);
					}
				}
				if (size)
				{
					*size = memfile->size;
				}
				ptr = (BYTE *)malloc(memfile->size);
				memcpy(ptr, memfile->data, memfile->size);
				return ptr;
			}
		}
		resItem=resItem->next;
	}

	// Load from file
_fromfile:
#if defined __WIN32
	hF = CreateFileA(Resource_MakePath(filename), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS, NULL);
	if (hF == INVALID_HANDLE_VALUE)
#else
	hF = fopen(Resource_MakePath(filename), "rb");
	if (!hF)
#endif
	{
		sprintf(szName, res_err, filename);
		_PostError(szName);
#ifdef __IPHONE
		_PostError(Resource_MakePath(szName));
#endif
		return 0;
	}
#if defined __WIN32
	filesize = GetFileSize(hF, NULL);
#else
	filesize = Resource_FileSize(filename, hF);
#endif
	ptr = (BYTE *)malloc(filesize);
	if(!ptr)
	{
#if defined __WIN32
		CloseHandle(hF);
#else
		fclose(hF);
#endif
		sprintf(szName, res_err, filename);
		_PostError(szName);
		return 0;
	}
#if defined __WIN32
	if (ReadFile(hF, ptr, filesize, &filesize, NULL ) == 0)
#else
	if (fread(ptr, filesize, 1, hF) == 0)
#endif
	{
#if defined __WIN32
		CloseHandle(hF);
#else
		fclose(hF);
#endif
		free(ptr);
		sprintf(szName, res_err, filename);
		_PostError(szName);
		return 0;
	}

#if defined __WIN32
	CloseHandle(hF);
#else
	fclose(hF);
#endif
	if(size) *size=filesize;
	return ptr;
}

void BIOInterface::Resource_Free(void *res)
{
	if (res)
	{
		free(res);
	}
}

BIOResourceList * BIOInterface::Resource_AttachPack(const char *filename, int password/* =0 */)
{
	char *szName;
	BIOResourceList *resItem=reslist;

	szName=Resource_MakePath(filename);
	strupr(szName);

	while(resItem)
	{
		if(!strcmp(szName,resItem->filename)) return resItem;
		resItem=resItem->next;
	}

	FILE * zipfile = fopen(szName, "rb");
	if (!zipfile)
	{
		return NULL;
	}

	DWORD signature = 0;
	DWORD filecount = 0;
	DWORD size = 0;

	size = Resource_FileSize(filename, zipfile);
	fseek(zipfile, 0, SEEK_SET);
	fread(&signature, sizeof(DWORD), 1, zipfile);
	fread(&filecount, sizeof(DWORD), 1, zipfile);

	DoXOR(&signature, password, size);
	DoXOR(&filecount, password, size);

	if (signature != BIO_PACK_SIGNATURE)
	{
		fclose(zipfile);
		return NULL;
	}

	resItem=new BIOResourceList;
	strcpy(resItem->filename, szName);
	if(password)
		resItem->password = password;
	else resItem->password=0;

	resItem->filecount = filecount;
	resItem->files = (BIOMemoryFile *)malloc(sizeof(BIOMemoryFile) * filecount);

	DWORD nowoffset = BIO_PACK_HEADEROFFSET;
	DWORD _size;
	BYTE _filename[BIO_PATHMAX];
	for (int i=0; i<filecount; i++)
	{
		fseek(zipfile, nowoffset, SEEK_SET);

		fread(&_size, sizeof(DWORD), 1, zipfile);
		fread(&_filename, BIO_PATHMAX, 1, zipfile);

		DoXOR(&_size, password, i);

		for (int j=0; j*sizeof(DWORD)<sizeof(BYTE)*BIO_PATHMAX; j++)
		{
			DoXOR((DWORD*)&(_filename[j*sizeof(DWORD)]), password, j);
		}

		resItem->files[i].size = _size;
		strcpy(resItem->files[i].filename, (const char *)_filename);

		resItem->files[i].data = NULL;
	}

	resItem->next=reslist;
	reslist=resItem;

	fclose(zipfile);

	return resItem;
}

void BIOInterface::Resource_RemovePack(const char *filename)
{
	char *szName;
	BIOResourceList *resItem=reslist, *resPrev=NULL;

	szName=Resource_MakePath(filename);
	strupr(szName);

	while(resItem)
	{
		if(!strcmp(szName,resItem->filename) || !strlen(filename))
		{
			if(resPrev) resPrev->next=resItem->next;
			else reslist=resItem->next;

			if (resItem->files)
			{
				for (int i=0; i<resItem->filecount; i++)
				{
					if (resItem->files[i].data)
					{
						free(resItem->files[i].data);
						resItem->files[i].data = NULL;
					}
				}
				free(resItem->files);
				resItem->files = NULL;
			}

			if (strlen(filename))
			{
				delete resItem;
			}

			break;
		}

		resPrev=resItem;
		resItem=resItem->next;
	}
}

void BIOInterface::Resource_RemoveAllPacks()
{
	Resource_RemovePack("");
}

char * BIOInterface::Resource_SetPath(const char *filename)
{
	int i;

	if(filename[0]==M_FOLDER_SLASH || filename[0]==M_FOLDER_SLASH_WRONG|| filename[1]==':')
		strcpy(szResourcePath, filename);

	else
	{
		char szTmp[BIO_PATHMAX];
		strcpy(szTmp, filename);
		while(szTmp[0] == '.' && szTmp[1] == '.')
		{
			i = strlen(szResourcePath) - 1;
			if(szResourcePath[i] == M_FOLDER_SLASH || szResourcePath[i] == M_FOLDER_SLASH_WRONG)
				szResourcePath[i] = 0;
			for(i = strlen(szResourcePath) - 1; i >= 0; i--)
			{
				if(szResourcePath[i] != M_FOLDER_SLASH && szResourcePath[i] != M_FOLDER_SLASH_WRONG)
					szResourcePath[i] = 0;
				else
					break;
			}
			for(i = 0; i < (int)(strlen(szTmp) - 2); i++)
			{
				szTmp[i] = szTmp[i+3];
			}
		}
		if(szTmp) strcat(szResourcePath, szTmp);
	}
	for(i=0; szResourcePath[i]; i++) { if(szResourcePath[i]==M_FOLDER_SLASH_WRONG) szResourcePath[i]=M_FOLDER_SLASH; }
	if(szResourcePath[i-1] != M_FOLDER_SLASH)
	{
		szResourcePath[i] = M_FOLDER_SLASH;
		szResourcePath[i+1] = 0;
	}
	return szResourcePath;
}

char * BIOInterface::BIOInterface::Resource_MakePath(const char *filename)
{
	int i;

	if(!filename)
		strcpy(szTmpFilename, szResourcePath);
	else if(filename[0]==M_FOLDER_SLASH || filename[0]==M_FOLDER_SLASH_WRONG || filename[1]==':'
#ifndef __WIN32
		|| strlen(filename) >= strlen(szResourcePath) && !strncmp(filename, szResourcePath, strlen(szResourcePath))
#endif // __WIN32
		)
	{
		strcpy(szTmpFilename, filename);
	}
	else
	{
		char szTmp[BIO_PATHMAX];
		strcpy(szTmpFilename, szResourcePath);
		strcpy(szTmp, filename);
		while(szTmp[0] == '.' && szTmp[1] == '.')
		{
			i = strlen(szTmpFilename) - 1;
			if(szTmpFilename[i] == M_FOLDER_SLASH || szTmpFilename[i] == M_FOLDER_SLASH_WRONG)
				szTmpFilename[i] = 0;
			for(i = strlen(szTmpFilename) - 1; i >= 0; i--)
			{
				if(szTmpFilename[i] != M_FOLDER_SLASH && szTmpFilename[i] != M_FOLDER_SLASH_WRONG)
					szTmpFilename[i] = 0;
				else
					break;
			}
			for(i = 0; i < (int)(strlen(szTmp) - 2); i++)
			{
				szTmp[i] = szTmp[i+3];
			}
		}
		if(szTmp) strcat(szTmpFilename, szTmp);
	}

	for(i=0; szTmpFilename[i]; i++) { if(szTmpFilename[i]==M_FOLDER_SLASH_WRONG) szTmpFilename[i]=M_FOLDER_SLASH; }
	return szTmpFilename;
}

char * BIOInterface::Resource_EnumFiles(const char *wildcard/* =0 */)
{
#if defined __WIN32
	if(wildcard)
	{
		if(hSearch) { FindClose(hSearch); hSearch=0; }
		hSearch=FindFirstFileA(Resource_MakePath(wildcard), &SearchData);
		if(hSearch==INVALID_HANDLE_VALUE) { hSearch=0; return 0; }

		if(!(SearchData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) return (char*)SearchData.cFileName;
		else return Resource_EnumFiles();
	}
	else
	{
		if(!hSearch) return 0;
		for(;;)
		{
			if(!FindNextFileA(hSearch, &SearchData))	{ FindClose(hSearch); hSearch=0; return 0; }
			if(!(SearchData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) return (char*)SearchData.cFileName;
		}
	}
#endif
	return NULL;
}

char * BIOInterface::Resource_EnumFolders(const char *wildcard/* =0 */)
{
#if defined __WIN32
	if(wildcard)
	{
		if(hSearch) { FindClose(hSearch); hSearch=0; }
		hSearch=FindFirstFileA(Resource_MakePath(wildcard), &SearchData);
		if(hSearch==INVALID_HANDLE_VALUE) { hSearch=0; return 0; }

		if((SearchData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
			strcmp(SearchData.cFileName,".") && strcmp(SearchData.cFileName,".."))
			return (char*)SearchData.cFileName;
		else return Resource_EnumFolders();
	}
	else
	{
		if(!hSearch) return 0;
		for(;;)
		{
			if(!FindNextFileA(hSearch, &SearchData))	{ FindClose(hSearch); hSearch=0; return 0; }
			if((SearchData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
				strcmp(SearchData.cFileName,".") && strcmp(SearchData.cFileName,".."))
				return (char*)SearchData.cFileName;
		}
	}
#endif
	return NULL;
}

bool BIOInterface::Resource_CreateDirectory(const char *filename)
{
#if defined __WIN32
	return CreateDirectoryA(Resource_MakePath(filename), NULL);
#elif defined __PSP
	return !sceIoMkdir(Resource_MakePath(filename), 0777);
#elif defined __IPHONE
	return false;
#endif // __WIN32
}

bool BIOInterface::_Resource_RepackHeader(FILE * zipfile, int password, DWORD filecount, DWORD size)
{
	if (!zipfile)
	{
		return false;
	}

	DWORD nowfilepos = ftell(zipfile);

	fseek(zipfile, 0, SEEK_SET);
	DWORD signature = BIO_PACK_SIGNATURE;
	DoXOR(&signature, password, size);
	DoXOR(&filecount, password, size);
	fwrite(&signature, sizeof(DWORD), 1, zipfile);
	fwrite(&filecount, sizeof(DWORD), 1, zipfile);

	fseek(zipfile, nowfilepos, SEEK_SET);

	return true;
}

bool BIOInterface::Resource_CreatePack(const char * filename, int password, BIOMemoryFile * first, ...)
{
	Resource_RemovePack(filename);

	FILE * zipfile = fopen(Resource_MakePath(filename), "wb");
	if (!_Resource_RepackHeader(zipfile, password, 0, BIO_PACK_HEADEROFFSET))
	{
		fclose(zipfile);
		return false;
	}
	fclose(zipfile);

	va_list ap;
	va_start(ap, first);

	BIOMemoryFile * vai = first;
	while(vai != NULL)
	{
		if (!Resource_AddFileInPack(filename, password, vai))
		{
			va_end(ap);
			return false;
		}
		vai = (BIOMemoryFile *)va_arg(ap, BIOMemoryFile *);
	}
	
	va_end(ap);

	bool bret = Resource_AttachPack(filename, password);
	Resource_RemovePack(filename);
	return bret;
}

bool BIOInterface::Resource_AddFileInPack(const char * filename, int password, BIOMemoryFile * memfile)
{
	if (!memfile)
	{
		return false;
	}
	if (!memfile->data)
	{
		return true;
	}

	BIOResourceList * resItem = Resource_AttachPack(filename, password);

	if(!resItem)
	{
		return Resource_CreatePack(filename, password, memfile, NULL);
	}

	DWORD nowoffset = Resource_FileSize(filename);

	FILE * zipfile = fopen(Resource_MakePath(filename), "wb+");

	if(!zipfile)
		return false;

	DWORD savesize = memfile->size;
	if (savesize % sizeof(DWORD))
	{
		savesize = (savesize / sizeof(DWORD) + 1) * sizeof(DWORD);
	}
	DWORD totalsize = nowoffset + BIO_PACK_FILEHEADEROFFSET + savesize;

	BYTE * ptr = (BYTE *)malloc(sizeof(BYTE)*totalsize);
	ZeroMemory(ptr, sizeof(BYTE)*totalsize);
	fread(ptr, nowoffset, 1, zipfile);

	*(DWORD*)(&(ptr[nowoffset])) = memfile->size;
	DoXOR((DWORD*)&(ptr[nowoffset]), password, resItem->filecount);
	nowoffset += sizeof(DWORD);

	strcpy((char *)&(ptr[nowoffset]), memfile->filename);
	for (int i=0; i*sizeof(DWORD)<sizeof(BYTE)*BIO_PATHMAX; i++)
	{
		DoXOR((DWORD*)&ptr[nowoffset+i*sizeof(DWORD)], password, i);
	}
	nowoffset += sizeof(BYTE)*BIO_PATHMAX;

	memcpy(&(ptr[nowoffset]), memfile->data, memfile->size);
	for (int i=0; i*sizeof(DWORD)<memfile->size; i++)
	{
		DoXOR((DWORD*)&(ptr[nowoffset+i*sizeof(DWORD)]), password, i);
	}

	fwrite(ptr, totalsize, 1, zipfile);

	_Resource_RepackHeader(zipfile, password, resItem->filecount+1, totalsize);

	free(ptr);
	fclose(zipfile);

	Resource_RemovePack(filename);

	return true;
}
