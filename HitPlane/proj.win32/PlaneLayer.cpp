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
	//ûĬ���ǻ��
	isAlive = true;
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shoot.plist");
	auto hero = Sprite::create("hero1.png");
	Size contentSize = Director::sharedDirector()->getWinSize();
	hero->setPosition(Point(contentSize.width / 2, hero->getContentSize().height / 2));//�ѷɻ������м�
	hero->setAnchorPoint(Point(0.5,0.5));
	this->addChild(hero,0,AIRPLANE);

	//���ɻ������˸����
	Blink* blink = Blink::create(1, 3);
	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero1.png"));
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero2.png"));
	//֡����
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
		//// ��ȡ�¼����󶨵� target 
		auto target = static_cast<PlaneLayer*>(event->getCurrentTarget());

		//��ȡ��ǰ��Ļ���
		auto winSize = CCDirector::getInstance()->getWinSize();

		//��ȡ��ǰ�����������԰�ť��λ������
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		//��õ�ǰ��������������ֵ
		auto touchLocation = touch->getLocation();

		//�жϴ���λ���Ƿ񳬳���Ļ
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
		
		// �����Χ�жϼ��
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

