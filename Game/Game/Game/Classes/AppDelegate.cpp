#include "AppDelegate.h"

#include "cocos2d.h"
//#include "SimpleAudioEngine.h"

#include "HelloWorldScene.h"

#include "../Header/Const.h"
#include "../Header/SimpleAudioEngineExpand.h"
using namespace CocosDenshion;

using namespace cocos2d;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
	SimpleAudioEngineExpand::end();
}

bool AppDelegate::initInstance()
{
    bool bRet = false;
    do 
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        // Initialize OpenGLView instance, that release by CCDirector when application terminate.
        // The HelloWorld is designed as HVGA.
        CCEGLView * pMainWnd = new CCEGLView();
        CC_BREAK_IF(! pMainWnd
            || ! pMainWnd->Create(TEXT("Game"), 320, 480));
#endif  // CC_PLATFORM_WIN32

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

        // OpenGLView initialized in testsAppDelegate.mm on ios platform, nothing need to do here.

#endif  // CC_PLATFORM_IOS

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

        // Android doesn't need to do anything.

#endif  // CC_PLATFORM_ANDROID

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WOPHONE)
        // Initialize OpenGLView instance, that release by CCDirector when application terminate.
        // The HelloWorld is designed as HVGA.
        // Use GetScreenWidth() and GetScreenHeight() get screen width and height.
        CCEGLView * pMainWnd = new CCEGLView(this);
        CC_BREAK_IF(! pMainWnd
            || ! pMainWnd->Create(320, 480));

#if !defined(_TRANZDA_VM_)
        // set the resource zip file
        // on wophone emulator, we copy resources files to Work7/TG3/APP/ folder instead of zip file
        CCFileUtils::setResource("Game.zip");
#endif

#endif  // CC_PLATFORM_WOPHONE

        bRet = true;
    } while (0);
    return bRet;
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());

    // sets landscape mode
#if defined __WIN32
    pDirector->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);
#endif

    // turn on display FPS
    pDirector->setDisplayFPS(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / M_FPS);

    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorldScene::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

    SimpleAudioEngineExpand::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();

    SimpleAudioEngineExpand::sharedEngine()->resumeBackgroundMusic();
}
