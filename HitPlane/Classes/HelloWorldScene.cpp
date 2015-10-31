#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
	auto scene = HelloWorld::create();
    // 'layer' is an autorelease object
    //auto layer = HelloWorld::create();
	auto layer = HelloWorldPlayer::createLayer();
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCScene::init());
		game_layer = HelloWorldPlayer::create();//在这里获取GameLayer实例  
		game_layer->init();
		CC_BREAK_IF(game_layer);
		this->addChild(game_layer);//add _gameLayer到场景中  
		bRet = true;
	} while (0);

	return bRet;
}
