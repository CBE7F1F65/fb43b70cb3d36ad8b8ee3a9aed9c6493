#include "TitleScene.h"

#include "../Export/Export_Lua_Scene.h"
#include "../Header/SceneConst.h"

CCScene * TitleScene::thisScene = NULL;
CCLayer * TitleScene::thisLayer = NULL;

CCScene* TitleScene::scene()
{
	CCScene * pScene = NULL;
	do 
	{
		pScene = CCScene::node();
		CC_BREAK_IF(! pScene);
		thisScene = pScene;

		TitleScene *pLayer = TitleScene::node();
		CC_BREAK_IF(! pLayer);
		thisLayer = pLayer;

		pScene->addChild(pLayer, ZORDER_BG, KTAG_TITLESCENELAYER);

		Export_Lua_Scene::ExecuteIOScene(LUASCENE_IOFLAG_ONINIT, thisLayer, thisLayer->getTag());

	} while (0);

	return pScene;
}

void TitleScene::MenuCallbackFunc(CCObject * sender)
{
	CCNode * nSender = (CCNode *)sender;
	Export_Lua_Scene::ExecuteCBScene(nSender->getTag(), 0);
}

bool TitleScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
		bRet = true;

	}while (0);

	return bRet;
}

void TitleScene::onEnter()
{
	CCLayer::onEnter();

	Export_Lua_Scene::ExecuteIOScene(LUASCENE_IOFLAG_ONENTER, thisLayer, thisLayer->getTag());
}