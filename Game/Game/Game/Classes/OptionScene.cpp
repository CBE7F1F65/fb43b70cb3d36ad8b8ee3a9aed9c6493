#include "OptionScene.h"

#include "../Export/Export_Lua_Scene.h"
#include "../Header/SceneConst.h"

CCScene * OptionScene::thisScene = NULL;
CCLayer * OptionScene::thisLayer = NULL;

CCScene* OptionScene::scene()
{
	CCScene * pScene = NULL;
	do 
	{
		pScene = CCScene::node();
		CC_BREAK_IF(! pScene);
		thisScene = pScene;

		OptionScene *pLayer = OptionScene::node();
		CC_BREAK_IF(! pLayer);
		thisLayer = pLayer;

		pScene->addChild(pLayer, ZORDER_BG, KTAG_OPTIONSCENELAYER);

		Export_Lua_Scene::ExecuteIOScene(LUASCENE_IOFLAG_ONINIT, thisLayer, thisLayer->getTag());

		pLayer->toenter = true;
		pLayer->toentertdf = true;

	} while (0);

	return pScene;
}

void OptionScene::MenuCallbackFunc(CCObject * sender)
{
	CCNode * nSender = (CCNode *)sender;
	Export_Lua_Scene::ExecuteCBScene(nSender->getTag(), 0);
}

void OptionScene::NodeCallbackFunc(CCNode *sender, void *data)
{
	Export_Lua_Scene::ExecuteCBScene(sender->getTag(), 0);
}

bool OptionScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
		bRet = true;

	}while (0);

	return bRet;
}

void OptionScene::onEnter()
{
	CCLayer::onEnter();

	if (toenter)
	{
		Export_Lua_Scene::ExecuteIOScene(LUASCENE_IOFLAG_ONENTER, thisLayer, thisLayer->getTag());
		toenter = false;
	}
}
