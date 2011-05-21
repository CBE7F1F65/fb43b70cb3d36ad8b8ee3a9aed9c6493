#include "../Header/Const.h"
#include "HelloWorldScene.h"

#include "../Header/BResource.h"
#include "../Header/GameMain.h"

#include "LoadingScene.h"

using namespace cocos2d;

CCScene* HelloWorldScene::scene()
{
    CCScene * pScene = NULL;
    do 
    {
        pScene = CCScene::node();
        CC_BREAK_IF(! pScene);

        HelloWorldScene *pLayer = HelloWorldScene::node();
        CC_BREAK_IF(! pLayer);

        pScene->addChild(pLayer);
    } while (0);

    return pScene;
}

bool HelloWorldScene::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());

		/************************************************************************/
		/* Init Only                                                            */
		/************************************************************************/
		BResource::getInstance()->Init();
		GameMain::getInstance()->Init();

        bRet = true;

    } while (0);

    return bRet;
}

void HelloWorldScene::onEnter()
{
	CCLayer::onEnter();

	CCScene *pScene = LoadingScene::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}
