#include "LoadingScene.h"

#include "../Header/BResource.h"
#include "../Export/Export_Lua_Scene.h"

#include "../Header/SceneConst.h"

#include "../Header/SpriteItemManager.h"

CCScene * LoadingScene::thisScene = NULL;
CCLayer * LoadingScene::thisLayer = NULL;

CCScene* LoadingScene::scene()
{
	CCScene * pScene = NULL;
	do 
	{
		pScene = CCScene::node();
		CC_BREAK_IF(! pScene);
		thisScene = pScene;

		LoadingScene *pLayer = LoadingScene::node();
		CC_BREAK_IF(! pLayer);
		thisLayer = pLayer;

		pScene->addChild(pLayer, ZORDER_BG, KTAG_LOADINGSCENELAYER);

		Export_Lua_Scene::ExecuteIOScene(LUASCENE_IOFLAG_ONINIT, thisLayer, thisLayer->getTag());

	} while (0);

	return pScene;
}

void LoadingScene::MenuCallbackFunc(CCObject * sender)
{
	CCNode * nSender = (CCNode *)sender;
	Export_Lua_Scene::ExecuteCBScene(nSender->getTag(), 0);
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
//		pLoadingSprite->setContentSize(CCSizeMake(size.width, size.height));


		CCActionInterval* color_sub_action = CCFadeTo::actionWithDuration(0.5f, 0xaf);
		CCActionInterval* color_add_action = CCFadeTo::actionWithDuration(1.0f, 0xff);
		CCFiniteTimeAction* color_seq = CCSequence::actions(color_sub_action, color_add_action, NULL);
		addChild(pLoadingSprite, ZORDER_BG);

		pLoadingSprite->runAction(CCRepeatForever::actionWithAction((CCActionInterval*)color_seq));


		BResource * pbres = BResource::getInstance();
		/************************************************************************/
		/*                                                                      */
		/************************************************************************/
		if (true)
		{
#ifdef __WIN32
			pbres->ReadAllTable();
			pbres->PackData();
#endif
		}
		pbres->GainData();
		pbres->ReadAllScript();

		pbres->InitTexinfo();
		
/*
//		CCActionInterval* time_action = CCActionInterval::actionWithDuration(0.01f);
//		CCFiniteTimeAction* time_seq = CCSequence::actions(time_action, CCCallFunc::actionWithTarget(this, callfunc_selector(LoadingCallbackFunc)), NULL);
//		runAction((CCActionInterval*)time_seq);
*/
		bRet = true;

	}while (0);

	return bRet;
}

void LoadingScene::onEnter()
{
	CCLayer::onEnter();

	/*
	CCSprite * sp1 = SpriteItemManager::CreateSprite(10);
	sp1->setColor(ccc3(0xff, 0xff, 0xff));

	CCSprite * sp2 = SpriteItemManager::CreateSprite(11);
	sp2->setColor(ccc3(0x00, 0xff, 0xff));

	CCSprite * sp3 = SpriteItemManager::CreateSprite(10);
	sp3->setColor(ccc3(0xff, 0x00, 0xff));

	sp1->setScale(0.5f);
	sp2->setScale(0.5f);
	sp3->setScale(0.5f);


	CCMenuItemSprite * item = CCMenuItemSprite::itemFromNormalSprite(sp1, sp2, sp3, thisLayer, menu_selector(LoadingScene::LoadingCallbackFunc));
	item->setPosition(ccp(120, 120));

	CCMenu *menu = CCMenu::menuWithItems(item, NULL);
	menu->setPosition(ccp(0, 0));

	((CCNode*)thisLayer)->addChild(menu);
	*/
	

	Export_Lua_Scene::ExecuteIOScene(LUASCENE_IOFLAG_ONENTER, thisLayer, thisLayer->getTag());
/*
	CCMutableArray<CCNode*> *pChildren = thisLayer->getChildren();

	CCNode * item = NULL;
	if (pChildren && pChildren->count() > 0)
	{
		CCMutableArray<CCNode*>::CCMutableArrayIterator iter;
		for (iter = pChildren->begin(); iter != pChildren->end(); ++iter)
		{
			item = (CCNode*)(*iter);

			if (! item)
			{
				break;
			}

			item->setPosition(ccp(item->getPosition().x, CCDirector::sharedDirector()->getWinSize().height-item->getPosition().y));
		}
	}	
*/	
}