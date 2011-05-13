#include "LoadingScene.h"

#include "../Header/BResource.h"

using namespace cocos2d;

LoadingScene::LoadingScene(void)
{
	nCallBackCount = 0;
}

LoadingScene::~LoadingScene(void)
{
}

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

void LoadingScene::LoadingCallBackFunc()
{
	nCallBackCount++;
	if (nCallBackCount == 1)
	{
		BResource::getInstance()->ReadAllTable();
		BResource::getInstance()->ReadAllScript();
	}
	else
	{
		BResource::getInstance()->LoadTexture(nCallBackCount-1);
	}
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
		CCFiniteTimeAction* color_seq = CCSequence::actions(color_sub_action, color_add_action, NULL);		CCActionInterval* time_action = CCActionInterval::actionWithDuration(0.01f);		CCFiniteTimeAction* time_seq = CCSequence::actions(time_action, CCCallFunc::actionWithTarget(this, callfunc_selector(LoadingCallBackFunc)), NULL);

		this->addChild(pLoadingSprite, ZORDER_BG, 10);

		pLoadingSprite->runAction(CCRepeatForever::actionWithAction((CCActionInterval*)color_seq));

		runAction(CCRepeatForever::actionWithAction((CCActionInterval*)time_seq));

		bRet = true;

	}while (0);

	return bRet;
}

void LoadingScene::onEnter()
{
	CCLayer::onEnter();
}