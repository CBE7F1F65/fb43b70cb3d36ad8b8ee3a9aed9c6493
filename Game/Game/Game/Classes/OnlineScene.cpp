#include "OnlineScene.h"

#include "../Export/Export_Lua_Scene.h"
#include "../Header/SceneConst.h"

CCScene * OnlineScene::thisScene = NULL;
CCLayer * OnlineScene::thisLayer = NULL;

CCScene* OnlineScene::scene()
{
	CCScene * pScene = NULL;
	do 
	{
		pScene = CCScene::node();
		CC_BREAK_IF(! pScene);
		thisScene = pScene;

		OnlineScene *pLayer = OnlineScene::node();
		CC_BREAK_IF(! pLayer);
		thisLayer = pLayer;

		pScene->addChild(pLayer, ZORDER_BG, KTAG_ONLINESCENELAYER);

		Export_Lua_Scene::ExecuteIOScene(LUASCENE_IOFLAG_ONINIT, thisLayer, thisLayer->getTag());

		pLayer->toenter = true;
		pLayer->toentertdf = true;

	} while (0);

	return pScene;
}

void OnlineScene::MenuCallbackFunc(CCObject * sender)
{
	CCNode * nSender = (CCNode *)sender;
	Export_Lua_Scene::ExecuteCBScene(nSender->getTag(), 0);
}

void OnlineScene::NodeCallbackFunc(CCNode *sender, void *data)
{
	Export_Lua_Scene::ExecuteCBScene(sender->getTag(), 0);
}

bool OnlineScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
		bRet = true;

	}while (0);

	return bRet;
}

void OnlineScene::onEnter()
{
	CCLayer::onEnter();

	if (toenter)
	{
		Export_Lua_Scene::ExecuteIOScene(LUASCENE_IOFLAG_ONENTER, thisLayer, thisLayer->getTag());
		toenter = false;
	}
}
