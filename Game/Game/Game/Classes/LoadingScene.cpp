#include "LoadingScene.h"

#include "../Header/BResource.h"

#include "../Export/Export_Lua_Scene.h"

using namespace cocos2d;

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

void LoadingScene::LoadingCallbackFunc()
{
}

bool LoadingScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());

		/************************************************************************/
		/* Show Loading                                                         */
		/************************************************************************/

		CCSize size = CCDirector::sharedDirector()->getWinSize();
		CCSprite * pLoadingSprite = CCSprite::spriteWithFile(BResource::getInstance()->getLoadingFileName());
		pLoadingSprite->setPosition(ccp(size.width/2, size.height/2));
		pLoadingSprite->setScaleX(size.width/pLoadingSprite->getContentSize().width);
		pLoadingSprite->setScaleY(size.height/pLoadingSprite->getContentSize().height);


		CCActionInterval* color_sub_action = CCFadeTo::actionWithDuration(0.5f, 0xaf);
		CCActionInterval* color_add_action = CCFadeTo::actionWithDuration(1.0f, 0xff);
		CCFiniteTimeAction* color_seq = CCSequence::actions(color_sub_action, color_add_action, NULL);		CCActionInterval* time_action = CCActionInterval::actionWithDuration(0.01f);		CCFiniteTimeAction* time_seq = CCSequence::actions(time_action, CCCallFunc::actionWithTarget(this, callfunc_selector(LoadingCallbackFunc)), NULL);

		this->addChild(pLoadingSprite, ZORDER_BG, 10);

		pLoadingSprite->runAction(CCRepeatForever::actionWithAction((CCActionInterval*)color_seq));

		runAction((CCActionInterval*)time_seq);

		BResource * pbres = BResource::getInstance();
		/************************************************************************/
		/*                                                                      */
		/************************************************************************/
		if (true)
		{
			pbres->ReadAllTable();
			pbres->ReadAllScript();
			pbres->PackData();
		}
		pbres->GainData();

		bRet = true;

	}while (0);

	return bRet;
}

void LoadingScene::onEnter()
{
	CCLayer::onEnter();

	Export_Lua_Scene::ExecuteIOLoadingScene(LUASCENE_IOFLAG_ONENTER);
}