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

		//��õ�ǰ��������������ֵ
		auto touchLocation = touch->getLocation();
		
		//��ȡ��ǰ�����������԰�ť��λ������
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		CCPoint beginPoint = touch->getLocationInView();
		// �����Χ�жϼ��
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
	//�ɻ�����Ϸ״̬�ж�  
	if (!CCDirector::sharedDirector()->isPaused())
	{
		this->setPosition(Point(toPoint.x, toPoint.y));
		//���б߽��ж�,���ɳ�����Ļ  
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


