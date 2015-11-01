#include "PlaneLayer.h"
USING_NS_CC;
PlaneLayer* PlaneLayer::sharedPlane = NULL;
PlaneLayer::PlaneLayer()
{
}


PlaneLayer::~PlaneLayer()
{
}

PlaneLayer* PlaneLayer::create()
{
	PlaneLayer* pRet = new PlaneLayer();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		sharedPlane = pRet;
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

bool PlaneLayer::init()
{
	//没默认是活的
	isAlive = true;
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shoot.plist");
	auto hero = Sprite::create("hero1.png");
	Size contentSize = Director::sharedDirector()->getWinSize();
	hero->setPosition(Point(contentSize.width / 2, hero->getContentSize().height / 2));//把飞机放在中间
	hero->setAnchorPoint(Point(0.5,0.5));
	this->addChild(hero,0,AIRPLANE);

	//给飞机添加闪烁动画
	Blink* blink = Blink::create(1, 3);
	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero1.png"));
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero2.png"));
	//帧动画
	Animate* animate = Animate::create(animation);
	hero->runAction(blink);
	hero->runAction(CCRepeatForever::create(animate));

	auto onTouchListener = EventListenerTouchOneByOne::create();
	onTouchListener->setSwallowTouches(true);
	onTouchListener->onTouchBegan = [](Touch* touch, Event* event)
	{
		log("touched");
		return true;
	};
	onTouchListener->onTouchMoved = [](Touch* touch, Event* event)
	{
		//// 获取事件所绑定的 target 
		auto target = static_cast<PlaneLayer*>(event->getCurrentTarget());

		//获取当前屏幕宽高
		auto winSize = CCDirector::getInstance()->getWinSize();

		//获取当前点击点所在相对按钮的位置坐标
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		//获得当前滑动触摸的坐标值
		auto touchLocation = touch->getLocation();

		//判断触摸位置是否超出屏幕
		auto locationX = touchLocation.x;
		auto locationY = touchLocation.y;

		if (locationX <= s.width /2)
		{
			locationX = s.width / 2;
		}

		if (locationX >= winSize.width - s.width / 2)
		{
			locationX = winSize.width - s.width / 2;
		}

		if (locationY <= s.height / 2)
		{
			locationY = s.height / 2;
		}

		if (locationY >= winSize.height - s.height / 2)
		{
			locationY = winSize.height - s.height / 2;
		}
		
		// 点击范围判断检测
		if (rect.containsPoint(locationInNode))
		{
			log("touchX = %f, touchY = %f.", locationX, locationY);
			target->setPosition(Point(locationX, locationY));
			//target->moveTo(touchLocation);
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(onTouchListener,hero);
	return true;
}

