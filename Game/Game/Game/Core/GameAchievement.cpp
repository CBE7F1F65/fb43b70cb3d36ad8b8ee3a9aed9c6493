#include "../Header/GameAchievement.h"
#include "../Header/GameMain.h"

AchievementData * GameAchievement::adata = NULL;

GameAchievement::GameAchievement()
{
}

GameAchievement::~GameAchievement()
{
}

void GameAchievement::Init(AchievementData * _adata)
{
	adata = _adata;
}

bool GameAchievement::BeatCountAdd(BYTE enemytype)
{
	if (adata->beatcount[enemytype] < 0xff)
	{
		adata->beatcount[enemytype]++;
		return UpdateAchievement();
	}
	return false;
}

bool GameAchievement::MissionClearAdd(BYTE stageindex, bool bStory/* =false */)
{
	if (adata->missionclearcount[stageindex] < 0xff)
	{
		adata->missionclearcount[stageindex]++;
		if (bStory)
		{
			if (adata->storyclearcount[stageindex] < 0xff)
			{
				adata->storyclearcount[stageindex]++;
			}
		}
		return UpdateAchievement();
	}
	return false;
}

bool GameAchievement::Rank3Add()
{
	adata->rankmaxcount++;
	return UpdateAchievement();
}

bool GameAchievement::SurvivalTurnSet(int turn)
{
	if (adata->survivalturncount < turn)
	{
		adata->survivalturncount = turn;
		return UpdateAchievement();
	}
	return false;
}

bool GameAchievement::SurvivalHiScoreSet(int hiscore)
{
	if (adata->survivalhiscore < hiscore)
	{
		adata->survivalhiscore = hiscore;
		return UpdateAchievement();
	}
	return false;
}

bool GameAchievement::HiScoreSet(int hiscore)
{
	if (adata->hiscore < hiscore)
	{
		adata->hiscore = hiscore;
		return UpdateAchievement();
	}
	return false;
}

bool GameAchievement::HPCostInOneTurnSet(int hpcost)
{
	if (adata->hpcostinoneturn < hpcost)
	{
		adata->hpcostinoneturn = hpcost;
		return UpdateAchievement();
	}
	return false;
}

bool GameAchievement::EggCountAdd()
{
	adata->eggcount++;
	return UpdateAchievement();
}

bool GameAchievement::BestScoreRateSet(float scorerate)
{
	if (adata->bestscorerate < scorerate)
	{
		adata->bestscorerate = scorerate;
		return UpdateAchievement();
	}
	return false;
}

bool GameAchievement::WeaponUseAdd(BYTE weaponindex)
{
	if (adata->weaponusecount[weaponindex] < 0xff)
	{
		adata->weaponusecount[weaponindex]++;
		return UpdateAchievement();
	}
	return false;
}

bool GameAchievement::WeaponBeatInOneTurnSet(BYTE weaponindex, int count)
{
	if (count > 0xff)
	{
		count = 0xff;
	}
	if (adata->weaponbeatinoneturn[weaponindex] < count)
	{
		adata->weaponbeatinoneturn[weaponindex] = count;
		return UpdateAchievement();
	}
	return false;
}

bool GameAchievement::BestTurnSet(int turn)
{
	if (turn > 0xff)
	{
		turn = 0xff;
	}
	turn = 0xff-turn;
	if (adata->bestturn_reverse < turn)
	{
		adata->bestturn_reverse = turn;
		return UpdateAchievement();
	}
	return false;
}

bool GameAchievement::GoldenEggCountAdd()
{
	if (adata->goldeneggcount < 0xff)
	{
		adata->goldeneggcount++;
		return UpdateAchievement();
	}
	return false;
}

bool GameAchievement::BeatInOneTurnSet(int count)
{
	if (count > 0xff)
	{
		count = 0xff;
	}
	if (adata->beatinoneturn < count)
	{
		adata->beatinoneturn = count;
		return UpdateAchievement();
	}
	return false;
}

bool GameAchievement::WaitInOneTurnSet(BYTE count)
{
	if (adata->waitinouneturn < count)
	{
		adata->waitinouneturn = count;
		return UpdateAchievement();
	}
	return false;
}

bool GameAchievement::HeadShotAdd()
{
	if (adata->headshotcount < 0xff)
	{
		adata->headshotcount++;
		return UpdateAchievement();
	}
	return false;
}

bool GameAchievement::BlindHeadShotAdd()
{
	if (adata->blindheadshotcount < 0xff)
	{
		adata->blindheadshotcount++;
		return UpdateAchievement();
	}
	return false;
}

bool GameAchievement::SingleMissionTryCountSet(int count)
{
	if (count > 0xff)
	{
		count = 0xff;
	}
	if (adata->singlemissiontrycount < count)
	{
		adata->singlemissiontrycount = count;
		return UpdateAchievement();
	}
	return false;
}

bool GameAchievement::RateLevelSet(BYTE rate)
{
	if (adata->ratelevel < rate)
	{
		adata->ratelevel = rate;
		return UpdateAchievement();
	}
	return false;
}

bool GameAchievement::ItemPurchaseAdd()
{
	if (adata->itempurcahsecount < 0xff)
	{
		adata->itempurcahsecount++;
		return UpdateAchievement();
	}
	return false;
}

bool GameAchievement::UpdateAchievement()
{
	bool bret = false;
	bool brettemp = false;
	for (int i=0; i<M_ACHIEVEMENTMAX; i++)
	{
		if (adata->statedata.st[i] == M_ACHIEVEMENTSTATE_NOTCOMPLETE)
		{
			brettemp = UpdateAchievement(i);
			if (brettemp)
			{
				bret = true;
			}
		}
	}
	GameMain::getInstance()->SaveData();
	return bret;
}

bool GameAchievement::UpdateAchievement(BYTE index)
{
	// TODO:
	switch (index)
	{
	}
	return true;
}

bool GameAchievement::SubmitAchievement()
{
	bool bret = false;
	bool brettemp = false;
	for (int i=0; i<M_ACHIEVEMENTMAX; i++)
	{
		if (adata->statedata.st[i] == M_ACHIEVEMENTSTATE_TOSUBMIT)
		{
			brettemp = SubmitAchievement(i);
			if (brettemp)
			{
				bret = true;
			}
		}
	}
//	GameMain::getInstance()->SaveData();
	return bret;
}

bool GameAchievement::SubmitAchievement(BYTE index)
{
	// TODO:
	return true;
}

void GameAchievement::AchievementAcceptedCallback(BYTE index)
{
	if (adata->statedata.st[index] == M_ACHIEVEMENTSTATE_TOSUBMIT)
	{
		adata->statedata.st[index] = M_ACHIEVEMENTSTATE_ACHIEVED;
	}
	GameMain::getInstance()->SaveData();
}