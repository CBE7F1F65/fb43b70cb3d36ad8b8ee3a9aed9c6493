#include "HelpScene.h"

#include "../Export/Export_Lua_Scene.h"
#include "../Header/SceneConst.h"

CCScene* HelpScene::scene()
{
	CCScene * pScene = NULL;
	do 
	{
		pScene = CCScene::node();
		CC_BREAK_IF(! pScene);

		HelpScene *pLayer = HelpScene::node();
		CC_BREAK_IF(! pLayer);

		pScene->addChild(pLayer, ZORDER_BG, KTAG_HELPSCENELAYER);

		Export_Lua_Scene::ExecuteIOScene(LUASCENE_IOFLAG_ONINIT, pLayer, pLayer->getTag());

		pLayer->toenter = true;
		pLayer->toentertdf = true;

	} while (0);

	return pScene;
}

void HelpScene::MenuCallbackFunc(CCObject * sender)
{
	CCNode * nSender = (CCNode *)sender;
	Export_Lua_Scene::ExecuteCBScene(nSender->getTag(), this);
}

void HelpScene::NodeCallbackFunc(CCNode *sender, void *data)
{
	Export_Lua_Scene::ExecuteCBScene(sender->getTag(), this, (int)data);
}

bool HelpScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
		bRet = true;

	}while (0);

	return bRet;
}

void HelpScene::onEnter()
{
	CCLayer::onEnter();

	if (toenter)
	{
		Export_Lua_Scene::ExecuteIOScene(LUASCENE_IOFLAG_ONENTER, this, this->getTag());
		toenter = false;
	}
}

void HelpScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();

	if (toentertdf)
	{
		Export_Lua_Scene::ExecuteIOScene(LUASCENE_IOFLAG_ONENTERTDF, this, this->getTag());
		toentertdf = false;
	}
}
