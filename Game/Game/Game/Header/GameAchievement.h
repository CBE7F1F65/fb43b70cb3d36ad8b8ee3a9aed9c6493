#ifndef __ACHIEVEMENTDATA_H__
#define __ACHIEVEMENTDATA_H__

#include "Const.h"
#include "MainDependency.h"

#define M_ACHIEVEMENTSTATE_NOTCOMPLETE	0x00
#define M_ACHIEVEMENTSTATE_TOSUBMIT		0x01
#define M_ACHIEVEMENTSTATE_ACHIEVED		0x02

#define M_ACHIEVEMENTMAX	0x40

struct AchievementStateData
{
	BYTE st[M_ACHIEVEMENTMAX];
};

struct AchievementData
{
	AchievementStateData statedata;
	int beatcount[M_ENEMYTYPEMAX];
	BYTE storyclearcount[M_STAGEMAX];
	BYTE missionclearcount[M_STAGEMAX];
	int rankmaxcount;
	int survivalturncount;
	int hiscore;
	int survivalhiscore;
	int hpcostinoneturn;
	int eggcount;
	float bestscorerate;
	BYTE weaponusecount[M_WEAPONTYPEMAX];
	BYTE weaponbeatinoneturn[M_WEAPONTYPEMAX];
	BYTE bestturn_reverse;
	BYTE goldeneggcount;
	BYTE beatinoneturn;
	BYTE waitinouneturn;
	BYTE headshotcount;
	BYTE blindheadshotcount;
	BYTE singlemissiontrycount;
	BYTE ratelevel;
	BYTE itempurcahsecount;
};

class GameAchievement
{
public:
	GameAchievement();
	~GameAchievement();

	static void AchievementAcceptedCallback(BYTE index);

	static void Init(AchievementData * adata);

	static bool BeatCountAdd(BYTE enemytype);
	static bool MissionClearAdd(BYTE stageindex, bool bStory=false);
	static bool Rank3Add();
	static bool SurvivalTurnSet(int turn);	// TODO:
	static bool HiScoreSet(int hiscore);
	static bool SurvivalHiScoreSet(int hiscore);
	static bool HPCostInOneTurnSet(int hpcost);	// TODO:
	static bool EggCountAdd();	// TODO:
	static bool BestScoreRateSet(float scorerate);
	static bool WeaponUseAdd(BYTE weaponindex);	// TODO:
	static bool WeaponBeatInOneTurnSet(BYTE weaponindex, int count);	// TODO:
	static bool BestTurnSet(int turn);
	static bool GoldenEggCountAdd();	// TODO:
	static bool BeatInOneTurnSet(int count);
	static bool WaitInOneTurnSet(BYTE count);	// TODO:
	static bool HeadShotAdd();	// TODO:
	static bool BlindHeadShotAdd();	// TODO:
	static bool SingleMissionTryCountSet(int count);
	static bool RateLevelSet(BYTE rate);	// TODO:
	static bool ItemPurchaseAdd();	// TODO:

	static bool UpdateAchievement();
	static bool UpdateAchievement(BYTE index);
	static bool SubmitAchievement();
	static bool SubmitAchievement(BYTE index);

public:
	static AchievementData * adata;
};

#endif