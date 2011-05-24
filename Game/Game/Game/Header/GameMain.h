#ifndef __GAMEMAIN_H__
#define __GAMEMAIN_H__

#include "Const.h"

struct HiScoreData 
{
	int hiscore;
	char username[M_USERNAMEMAX];
};

struct GameData
{
	HiScoreData hiscores[M_HISCOREMAX];
};

class GameMain
{
public:
	GameMain();
	~GameMain();

	void Init();

	void ReadHiScores();
	void ReadIni();

	void SaveData();
	void ResetHiScore();
	void ReportHiScore();

	int GetHiScore(int index);
	const char * GetHiScoreUsername(int index);

	bool ResetIni(bool bresetname=false);
	bool SaveIni();

	void SetBGMVol(int bgmvol);
	void SetSEVol(int sevol);
	void SetUsername(const char * username);

	bool InsertScore(int score);

	GameData gamedata;
	int bgmvol;
	int sevol;
	char username[M_USERNAMEMAX];

public:
	static GameMain * getInstance();
};

#endif