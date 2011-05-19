#include "../Header/BGlobal.h"
#include "../Header/Const.h"

int BGlobal::pushedscenecount = 0;

CCPoint BGlobal::TranslatePosition(float x, float y)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	x = x * size.width / M_SCREEN_WIDTH;
	y = y * size.height / M_SCREEN_HEIGHT;
	return ccp(x, y);
}

float BGlobal::ScalerX(float val)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	return val * size.width / M_SCREEN_WIDTH;
}

float BGlobal::ScalerY(float val)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	return val * size.height / M_SCREEN_HEIGHT;
}