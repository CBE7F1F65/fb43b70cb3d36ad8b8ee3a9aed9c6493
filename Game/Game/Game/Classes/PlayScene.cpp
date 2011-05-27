#include "PlayScene.h"

#include "../Export/Export_Lua_Scene.h"
#include "../Header/SceneConst.h"

CCScene* PlayScene::scene()
{
	CCScene * pScene = NULL;
	do 
	{
		pScene = CCScene::node();
		CC_BREAK_IF(! pScene);

		PlayScene *pLayer = PlayScene::node();
		CC_BREAK_IF(! pLayer);

		pScene->addChild(pLayer, ZORDER_BG, KTAG_PLAYSCENELAYER);

		Export_Lua_Scene::ExecuteIOScene(LUASCENE_IOFLAG_ONINIT, pLayer, pLayer->getTag());
		
		pLayer->toenter = true;
		pLayer->toentertdf = true;

	} while (0);

	return pScene;
}

void PlayScene::MenuCallbackFunc(CCObject * sender)
{
	CCNode * nSender = (CCNode *)sender;
	Export_Lua_Scene::ExecuteCBScene(nSender->getTag(), this);
}

void PlayScene::NodeCallbackFunc(CCNode *sender, void *data)
{
	Export_Lua_Scene::ExecuteCBScene(sender->getTag(), this);
}

bool PlayScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());

		scheduleUpdate();

		bRet = true;

	}while (0);

	return bRet;
}

void PlayScene::onEnter()
{
	CCLayer::onEnter();

	if (toenter)
	{
		Export_Lua_Scene::ExecuteIOScene(LUASCENE_IOFLAG_ONENTER, this, this->getTag());
		toenter = false;
	}
	Export_Lua_Scene::ExecuteIOScene(LUASCENE_IOFLAG_ONENTERA, this, this->getTag());
}

void PlayScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();

	if (toentertdf)
	{
		Export_Lua_Scene::ExecuteIOScene(LUASCENE_IOFLAG_ONENTERTDF, this, this->getTag());
		toentertdf = false;
	}
	Export_Lua_Scene::ExecuteIOScene(LUASCENE_IOFLAG_ONENTERTDFA, this, this->getTag());
}

void PlayScene::update(ccTime dt)
{
	CCLayer::update(dt);

	Export_Lua_Scene::ExecuteIOScene(LUASCENE_IOFLAG_ONUPDATE, this, this->getTag());
}

void PlayScene::onExit()
{
	CCLayer::onExit();

	Export_Lua_Scene::ExecuteIOScene(LUASCENE_IOFLAG_ONEXIT, this, this->getTag());
}