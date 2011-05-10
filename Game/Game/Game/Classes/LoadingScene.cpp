#include "LoadingScene.h"

using namespace cocos2d;

LoadingScene::LoadingScene(void)
{
}

LoadingScene::~LoadingScene(void)
{
}

CCScene* LoadingScene::scene()
{
	CCScene * pScene = NULL;
	do 
	{
		pScene = CCScene::node();
		CC_BREAK_IF(! pScene);

		LoadingScene *pLayer = LoadingScene::node();
		CC_BREAK_IF(! pLayer);

		pScene->addChild(pLayer);
	} while (0);

	return pScene;
}


bool LoadingScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
		bRet = true;
	}while (0);
	return bRet;
}