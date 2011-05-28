#include "LoadingScene.h"

#include "../Header/BResource.h"
#include "../Export/Export_Lua_Scene.h"

#include "../Header/SceneConst.h"

#include "../Header/SpriteItemManager.h"
#include "../Header/BIOInterface.h"

CCScene* LoadingScene::scene()
{
	CCScene * pScene = NULL;
	do 
	{
		pScene = CCScene::node();
		CC_BREAK_IF(! pScene);

		LoadingScene *pLayer = LoadingScene::node();
		CC_BREAK_IF(! pLayer);

		pScene->addChild(pLayer, ZORDER_BG, KTAG_LOADINGSCENELAYER);

		Export_Lua_Scene::ExecuteIOScene(LUASCENE_IOFLAG_ONINIT, pLayer, pLayer->getTag());

		pLayer->toenter = true;
		pLayer->toentertdf = true;

	} while (0);

	return pScene;
}

void LoadingScene::MenuCallbackFunc(CCObject * sender)
{
	CCNode * nSender = (CCNode *)sender;
	Export_Lua_Scene::ExecuteCBScene(nSender->getTag(), this);
}

void LoadingScene::NodeCallbackFunc(CCNode *sender, void *data)
{
	Export_Lua_Scene::ExecuteCBScene(sender->getTag(), this, (int)data);
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
		
		BResource * pbres = BResource::getInstance();
		BIOInterface * bio = BIOInterface::getInstance();
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		CCSprite * pLoadingSprite = CCSprite::spriteWithFile(bio->Resource_MakePath(pbres->getLoadingFileName()));
		
		if (pLoadingSprite) {
			pLoadingSprite->setPosition(ccp(size.width/2, size.height/2));
			pLoadingSprite->setScaleX(size.width/pLoadingSprite->getContentSize().width);
			pLoadingSprite->setScaleY(size.height/pLoadingSprite->getContentSize().height);
			CCActionInterval* color_sub_action = CCFadeTo::actionWithDuration(0.5f, 0xaf);
			CCActionInterval* color_add_action = CCFadeTo::actionWithDuration(1.0f, 0xff);
			CCFiniteTimeAction* color_seq = CCSequence::actions(color_sub_action, color_add_action, NULL);
			addChild(pLoadingSprite, ZORDER_BG);
			
			pLoadingSprite->runAction(CCRepeatForever::actionWithAction((CCActionInterval*)color_seq));
		}


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
	CCSprite * sp1 = SpriteItemManager::CreateSprite(11);
	sp1->setColor(ccc3(0xff, 0xff, 0xff));

	CCSprite * sp2 = SpriteItemManager::CreateSprite(12);
	sp2->setColor(ccc3(0x00, 0xff, 0xff));

	CCSprite * sp3 = SpriteItemManager::CreateSprite(11);
	sp3->setColor(ccc3(0xff, 0x00, 0xff));

	sp1->setScale(0.5f);
	sp2->setScale(0.5f);
	sp3->setScale(0.5f);

//	sp1->setOpacity(0);

	CCMenuItemSprite * item = CCMenuItemSprite::itemFromNormalSprite(sp1, sp2, sp3, this, menu_selector(LoadingScene::MenuCallbackFunc));
	item->setPosition(ccp(480, 120));

	CCMenu *menu = CCMenu::menuWithItems(item, NULL);
	menu->setPosition(ccp(0, 0));

	CCActionInterval * moveaction = CCMoveTo::actionWithDuration(1, ccp(400, 120));
//	CCActionInterval * moveeased = CCEaseIn::actionWithAction(moveaction, 0.5f);
	CCActionInterval * moveeased = CCEaseExponentialOut::actionWithAction(moveaction);

	CCActionInterval * movealpha = CCFadeIn::actionWithDuration(1);
	CCActionInterval * alphapre = CCFadeTo::actionWithDuration(0.3f, 0x7f);
	CCActionInterval * alphapost = CCFadeTo::actionWithDuration(0.7f, 0xff);
	CCActionInterval * alphaseq = CCSequence::actionOneTwo(alphapre, alphapost);
	CCActionInterval * alpharepeat = CCRepeat::actionWithAction(alphaseq, -1);
	CCActionInterval * totalseq = CCSequence::actionOneTwo(movealpha, alpharepeat);

	CCFiniteTimeAction * seq = CCSequence::actions(moveeased, NULL);
//	CCFiniteTimeAction * spawn = CCSpawn::actions(seq, movealpha, NULL);

	item->runAction(seq);
	sp1->runAction(totalseq);

	((CCNode*)this)->addChild(menu);
*/

	if (toenter)
	{
		Export_Lua_Scene::ExecuteIOScene(LUASCENE_IOFLAG_ONENTER, this, this->getTag());
		toenter = false;
	}
/*
	CCMutableArray<CCNode*> *pChildren = this->getChildren();

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