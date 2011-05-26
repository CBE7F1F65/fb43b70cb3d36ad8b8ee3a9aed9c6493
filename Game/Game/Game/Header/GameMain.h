#ifndef __GAMEMAIN_H__
#define __GAMEMAIN_H__

#include "GameData.h"
#include "StageMissionData.h"


class GameMain
{
public:
	GameMain();
	~GameMain();

	void Init();

	bool ReadData();
	void ReadIni();

	void SaveData();
	void ResetHiScore();
	void ReportHiScore();

	bool StageIsEnabled(int index);
	bool MissionIsEnabled(int missionindex, int stageindex=-1);
	int GetMissionTryCount(int missionindex, int stageindex=-1);
	bool EnableMission(int missionindex, int stageindex=-1);

	bool TryStage(int index);
	bool TryMission(int missionindex, int stageindex=-1);
	bool ClearMission(int missionindex, int stageindex=-1);

	bool HelpIsEnabled(BYTE type, int index=-1);
	bool EnableHelp(BYTE type, BYTE index);
	void SetHelpIndex(BYTE type, BYTE index);

	// In Game
	int GetMissionBGSIID();
	void GetMissionHelpData(BYTE * helptypes, BYTE * helpindexs);

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

	int nowstage;
	int nowmission;

	BYTE helptype;
	BYTE helpindex;

	int missionscore;
	int totalscore;
	int nowturn;

public:
	static GameMain * getInstance();
};

#endif