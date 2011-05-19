#include "StageSelectScene.h"

#include "../Export/Export_Lua_Scene.h"
#include "../Header/SceneConst.h"

CCScene * StageSelectScene::thisScene = NULL;
CCLayer * StageSelectScene::thisLayer = NULL;

CCScene* StageSelectScene::scene()
{
	CCScene * pScene = NULL;
	do 
	{
		pScene = CCScene::node();
		CC_BREAK_IF(! pScene);
		thisScene = pScene;

		StageSelectScene *pLayer = StageSelectScene::node();
		CC_BREAK_IF(! pLayer);
		thisLayer = pLayer;

		pScene->addChild(pLayer, ZORDER_BG, KTAG_STAGESELECTSCENELAYER);

		Export_Lua_Scene::ExecuteIOScene(LUASCENE_IOFLAG_ONINIT, thisLayer, thisLayer->getTag());
		
		pLayer->toenter = true;
		pLayer->toentertdf = true;

	} while (0);

	return pScene;
}

void StageSelectScene::MenuCallbackFunc(CCObject * sender)
{
	CCNode * nSender = (CCNode *)sender;
	Export_Lua_Scene::ExecuteCBScene(nSender->getTag(), 0);
}

void StageSelectScene::NodeCallbackFunc(CCNode *sender, void *data)
{
	Export_Lua_Scene::ExecuteCBScene(sender->getTag(), 0);
}

bool StageSelectScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
		bRet = true;

	}while (0);

	return bRet;
}

void StageSelectScene::onEnter()
{
	CCLayer::onEnter();

	if (toenter)
	{
		Export_Lua_Scene::ExecuteIOScene(LUASCENE_IOFLAG_ONENTER, thisLayer, thisLayer->getTag());
		toenter = false;
	}
}
