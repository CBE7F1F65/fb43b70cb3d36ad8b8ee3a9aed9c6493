#ifndef __GAMEMAIN_H__
#define __GAMEMAIN_H__

#include "GameData.h"
#include "StageMissionData.h"

#define GAMESTATE_STMASK		0xff0000
#define GAMESTATE_ACTIONMASK	0x00ff00
#define GAMESTATE_STEPMASK		0x0000ff

#define GAMESTATE_ST_NULL			0x000000
#define GAMESTATE_ST_STANDBY		0x010000
#define GAMESTATE_ST_PROGRESSING	0x020000
#define GAMESTATE_ST_STEPFORWARD	0x030000
#define GAMESTATE_ST_ERROR			0x040000
#define GAMESTATE_ST_FINISHED		0x050000

#define GAMESTATE_WAITING		0x000000
#define GAMESTATE_SHOWHELP		0x000100
#define GAMESTATE_SHOWTARGET	0x000200
#define GAMESTATE_ENEMYENTER	0x000300
#define GAMESTATE_HPAPREGAIN	0x000400
#define GAMESTATE_SHOWTURNSTART	0x000500
#define GAMESTATE_PLANNING		0x000600
#define GAMESTATE_SELFACTION	0x000700
#define GAMESTATE_ENEMYACTION	0x000800
#define GAMESTATE_OVER			0x000800


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

	bool HelpIsEnabled(BYTE type, int index=-1);
	bool EnableHelp(BYTE type, BYTE index);
	void SetHelpIndex(BYTE type, BYTE index);

	int GetItemData(BYTE type, int * siid=NULL);
	int BuyItem(BYTE type);
	bool UseItem(BYTE type);

	// In Game
	int GetMissionBGSIID();
	void GetMissionHelpData(BYTE * helptypes, BYTE * helpindexs);

	void EnterMission();
	bool ClearMission();

	int GetState(int *stateST=NULL, int *stateAction=NULL, int *stateStep=NULL);
	int SetState(int stateST, int stateAction=-1, int stateStep=-1);

	void Update();
	bool CheckMissionOver();

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

	int nowhp;
	int nowap;
	int nowsp;

	BYTE helptype;
	BYTE helpindex;

	int missionscore;
	int totalscore;
	int nowturn;

	BYTE itemtypecount;

	int stateflag;

public:
	static GameMain * getInstance();
};

#endif