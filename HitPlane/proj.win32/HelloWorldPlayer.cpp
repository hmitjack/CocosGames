#include "HelloWorldPlayer.h"
#include "cocos2d.h"
#include "proj.win32\PlaneLayer.h"
#include "proj.win32\BulletLayer.h"
#define schedule_selector(_SELECTOR) (SEL_SCHEDULE)(&_SELECTOR)
USING_NS_CC;
Layer* HelloWorldPlayer::createLayer()
{
	auto layer = HelloWorldPlayer::create();
	return layer;
}

bool HelloWorldPlayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		////png加入全局cache中  
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shoot_background.plist");

		////加载background1，background1和background2是CCSprite*型成员变量  
		////auto background1 = CCSprite::create(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
		background1 = Sprite::create("background.png");
		background1->setAnchorPoint(ccp(0, 0));
		background1->setPosition(ccp(0, 0));
		this->addChild(background1);

		//加载background2  
		//background2 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("HelloWorld.png"));
		background2 = Sprite::create("background.png");
		background2->setAnchorPoint(ccp(0, 0));
		background2->setPosition(ccp(0, background2->getContentSize().height - 2));//这里减2的目的是为了防止图片交界的黑线  

		this->addChild(background2);

		this->addChild(PlaneLayer::create());
		auto bullet = BulletLayer::create();
		bullet->StartShoot(2.0);
		this->addChild(bullet);
		////执行任务计划，实现背景滚动  
		//
		schedule(schedule_selector(HelloWorldPlayer::backgroundMove), 0.01f, kRepeatForever, 0);
		//schedule_selector();
		this->setTouchEnabled(true);
		bRet = true;
	} while (0);
	return bRet;
}
 
void HelloWorldPlayer::backgroundMove(float dt)
{
	background1->setPositionY(background1->getPositionY() - 2);
	background2->setPositionY(background1->getPositionY() + background1->getContentSize().height - 2);
	if (background2->getPositionY() == 0)//要注意因为背景图高度是842，所以每次减去2最后可以到达0，假如背景高度是841，那么这个条件永远达不到，滚动失败  
	{
		background1->setPositionY(0);
	}
}
HelloWorldPlayer::HelloWorldPlayer()
{
}


HelloWorldPlayer::~HelloWorldPlayer()
{
}
