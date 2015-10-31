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

		//获得当前滑动触摸的坐标值
		auto touchLocation = touch->getLocation();
		
		//获取当前点击点所在相对按钮的位置坐标
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		CCPoint beginPoint = touch->getLocationInView();
		// 点击范围判断检测
		if (rect.containsPoint(locationInNode))
		{
			log("touchX = %f, touchY = %f.", touchLocation.x, touchLocation.y);
			target->setPosition(Point(touchLocation.x, touchLocation.y));
			//target->moveTo(touchLocation);
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(onTouchListener,hero);
	return true;
}


void PlaneLayer::moveTo(CCPoint toPoint)
{
	//飞机及游戏状态判断  
	if (!CCDirector::sharedDirector()->isPaused())
	{
		this->setPosition(Point(toPoint.x, toPoint.y));
		//进行边界判断,不可超出屏幕  
		CCPoint actualPoint;
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSize planeSize = this->getChildByTag(AIRPLANE)->getContentSize();
		if (toPoint.x<planeSize.width / 2)
		{
			toPoint.x = planeSize.width / 2;
		}
		if (toPoint.x>winSize.width - planeSize.width / 2)
		{
			toPoint.x = winSize.width - planeSize.width / 2;
		}
		if (toPoint.y<planeSize.height / 2)
		{
			toPoint.y = planeSize.height / 2;
		}
		if (toPoint.y>winSize.height - planeSize.height / 2)
		{
			toPoint.y = winSize.height - planeSize.height / 2;
		}
		//this->getChildByTag(AIRPLANE)->setPosition(toPoint);
	}
}


