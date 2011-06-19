#ifndef __GAMEMAIN_H__
#define __GAMEMAIN_H__

#include "GameData.h"
#include "StageMissionData.h"
#include "VectorList.h"
#include "BIOInterface.h"
#include "DataStruct.h"

#include "cocos2d.h"
using namespace cocos2d;

#define GAMESTATE_STMASK		0xff0000
#define GAMESTATE_ACTIONMASK	0x00ff00
#define GAMESTATE_STEPMASK		0x0000ff

#define GAMESTATE_ST_NULL			0x000000
#define GAMESTATE_ST_STANDBY		0x010000
#define GAMESTATE_ST_PROGRESSING	0x020000
#define GAMESTATE_ST_STEPFORWARD	0x030000
#define GAMESTATE_ST_ERROR			0x040000
#define GAMESTATE_ST_FINISHED		0x050000

#define GAMESTATE_WAITING				0x000000
#define GAMESTATE_SHOWHELP				0x000100
#define GAMESTATE_ENEMYENTER			0x000200
#define GAMESTATE_SPECIALENEMYACTION	0x000300
#define GAMESTATE_ADDENEMY				0x000400
#define GAMESTATE_HPREGAIN				0x000500
#define GAMESTATE_SHOWTURNSTART			0x000600
#define GAMESTATE_PLANNING				0x000700
#define GAMESTATE_SELFACTION			0x000800
#define GAMESTATE_APREGAIN				0x000900
#define GAMESTATE_ENEMYACTION			0x000A00
#define GAMESTATE_OVER					0x000B00

#define ENEMY_INSCENE	0
#define ENEMY_ONSIDE	1
#define ENEMY_VECTORTYPEMAX	2

#define ENEMYATK_HP			0x00
#define ENEMYATK_AP			0x01
#define ENEMYATK_HPREGAIN	0x02

#define ENEMYSTATUS_NORMAL	0x00
#define ENEMYSTATUS_BLOWED	0x01
#define ENEMYSTATUS_CLEAR	0xf0
#define ENEMYSTATUS_SETMASK	0xf0

struct EnemyInGameData 
{
	int itemtag;
	float x;
	float y;
	int life;
	int elayer;
	int angle;
	BYTE etype;
	BYTE status;
};

class GameMain
{
public:
	GameMain();
	~GameMain();

	// TODO:
	void OnlineLinkedCallback();

	void Init();

	bool ReadData();
	void ReadIni();

	void SaveData();
	void ResetSurvivalHiScore();
	void ReportHiScore();
	void ReportSurvivalHiScore();

	bool StageIsEnabled(int index);
	bool MissionIsEnabled(int missionindex, int stageindex=-1);
	int GetMissionTryCount(int missionindex, int stageindex=-1);
	int GetMissionClearCount(int missionindex, int stageindex=-1);
	bool EnableMission(int missionindex, int stageindex=-1);

	int GetMissionHiScore(int missionindex=-1, int stageindex=-1);
	BYTE GetMissionRank(int missionindex=-1, int stageindex=-1);
	missionData * GetMissionData(int missionindex=-1, int stageindex=-1);
	missionAimHelpData * GetMissionAimHelpData(int missionindex=-1, int stageindex=-1);

	bool GetNextAvailableMission(int * missionindex, int * stageindex);

	bool TryStage(int index);
	bool TryMission(int missionindex, int stageindex=-1);

	bool HelpIsEnabled(BYTE type, int index=-1);
	bool EnableHelp(BYTE type, BYTE index);
	void SetHelpIndex(BYTE type, BYTE index);

	int GetItemData(BYTE type, int * siid=NULL);
	int BuyItem(BYTE type);
	bool UseItem(BYTE type);

	void EnableFunctionAccess(BYTE index);
	bool IsFunctionAccessEnabled(BYTE index);

	void SetEnemyPositionRect(CCRect rect);

	// In Game
	int GetMissionBGSIID();
	void GetMissionHelpData(BYTE * helptypes, BYTE * helpindexs);

	void EnterMission();
	bool ClearMission();

	void SetHPAPSP(int hp, int ap, int sp);

	int GetState(int *stateST=NULL, int *stateAction=NULL, int *stateStep=NULL);
	int SetState(int stateST, int stateAction=-1, int stateStep=-1);

	void Update();
	BYTE CheckMissionOver(bool checkap=false);

	int GetMissionEnemy(float * x, float * y, int * etype, int * elayerangle, int nowturnoffset=0);
	int AddEnemy(int itemtag, float x, float y, BYTE etype, int elayer, BYTE enemiesindex, int angle=0);
	void SetEnemyPosition(EnemyInGameData * edata, float x, float y);
	int DoRemoveEnemy(BYTE enemiesindex);
	void RemoveEnemy(int index, BYTE enemiesindex);
	EnemyInGameData * GetEnemyByIndex(int index, BYTE enemiesindex);
	void GetEnemyXYScale(EnemyInGameData * item, float * x, float * y, float * scale);

	void SetMissionRateScore(float scorerate, int score);

	int GetHiScore(int index);
	const char * GetHiScoreUsername(int index);

	bool ResetIni(bool bresetname=false);
	bool SaveIni();

	void SetBGMVol(int bgmvol);
	void SetSEVol(int sevol);
	void SetUsername(const char * username);

	bool InsertSurvivalHiScore(int score);

	GameData gamedata;
	int bgmvol;
	int sevol;
	char username[M_USERNAMEMAX];

	int nowstage;
	int nowmission;

	int missionenemyindex;

	int nowhp;
	int nowap;
	int nowsp;

	float nowscorerate;

	CCRect enemypositionrect;

	BYTE helptype;
	BYTE helpindex;

	int missionscore;
	int nowturn;

	missionTargetData targetcount[M_MISSIONTARGETMAX];

	BYTE itemtypecount;

	int stateflag;

	//
	int enemyelayerbase;

	bio3DPoint ptfar;

	vector< list<EnemyInGameData> > enemies;

public:
	static GameMain * getInstance();
};

#endif