#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorldScene : public cocos2d::CCLayer
{
public:
    virtual bool init();  

    static cocos2d::CCScene* scene();

	virtual void onEnter();
    
    LAYER_NODE_FUNC(HelloWorldScene);
};

#endif  // __HELLOWORLD_SCENE_H__