#include "StageSelectScene.h"

#include "../Export/Export_Lua_Scene.h"
#include "../Header/SceneConst.h"

CCScene* StageSelectScene::scene()
{
	CCScene * pScene = NULL;
	do 
	{
		pScene = CCScene::node();
		CC_BREAK_IF(! pScene);

		StageSelectScene *pLayer = StageSelectScene::node();
		CC_BREAK_IF(! pLayer);

		pScene->addChild(pLayer, ZORDER_BG, KTAG_STAGESELECTSCENELAYER);

		Export_Lua_Scene::ExecuteIOScene(LUASCENE_IOFLAG_ONINIT, pLayer, pLayer->getTag());
		
		pLayer->toenter = true;
		pLayer->toentertdf = true;

	} while (0);

	return pScene;
}

void StageSelectScene::MenuCallbackFunc(CCObject * sender)
{
	CCNode * nSender = (CCNode *)sender;
	Export_Lua_Scene::ExecuteCBScene(nSender->getTag(), this);
}

void StageSelectScene::NodeCallbackFunc(CCNode *sender, void *data)
{
	Export_Lua_Scene::ExecuteCBScene(sender->getTag(), this);
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
		Export_Lua_Scene::ExecuteIOScene(LUASCENE_IOFLAG_ONENTER, this, this->getTag());
		toenter = false;
	}
}

void StageSelectScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();

	if (toentertdf)
	{
		Export_Lua_Scene::ExecuteIOScene(LUASCENE_IOFLAG_ONENTERTDF, this, this->getTag());
		toentertdf = false;
	}
}
