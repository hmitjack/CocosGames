#include "BulletLayer.h"
#include "proj.win32\PlaneLayer.h"
#define schedule_selector(_SELECTOR) (SEL_SCHEDULE)(&_SELECTOR)
USING_NS_CC;
BulletLayer::BulletLayer()
{
	m_pAllBullet = CCArray::create();
	m_pAllBullet->retain();
}


BulletLayer::~BulletLayer()
{
	m_pAllBullet->release();
	m_pAllBullet = NULL;
}

bool BulletLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());
		CCTexture2D *texture = CCTextureCache::sharedTextureCache()->textureForKey("shoot.png");
		bulletBatchNode = CCSpriteBatchNode::createWithTexture(texture);
		this->addChild(bulletBatchNode);
		bRet = true;
		//schedule(schedule_selector(BulletLayer::AddBullet), 0.01f, kRepeatForever, 0);
	} while (0);
	return bRet;
}

void BulletLayer::AddBullet(float dt)
{
	CCSprite* bullet = CCSprite::createWithSpriteFrameName("bullet1.png");
	//确定子弹的初始化位置
	auto planeLayer = PlaneLayer::sharedPlane;
	auto plane = PlaneLayer::sharedPlane->getChildByTag(AIRPLANE);
	CCPoint planePosition = PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->getPosition();
	CCPoint bulletPosition = ccp(planePosition.x, planePosition.y + PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->getContentSize().height / 2);
	bullet->setPosition(bulletPosition);

	float length = CCDirector::sharedDirector()->getWinSize().height + bullet->getContentSize().height / 2 - bulletPosition.y;//飞行距离，超出屏幕即结束  
	float velocity = 420 / 1;//飞行速度：420pixel/sec  
	float realMoveDuration = length / velocity;//飞行时间  

	CCFiniteTimeAction* actionMove = CCMoveTo::create(realMoveDuration, ccp(bulletPosition.x, CCDirector::sharedDirector()->getWinSize().height + bullet->getContentSize().height / 2));
	CCFiniteTimeAction* actionDone = CCCallFuncN::create(this, callfuncN_selector(BulletLayer::bulletMoveFinished));//回调一个子弹结束处理函数  

	CCSequence* sequence = CCSequence::createWithTwoActions(actionMove, actionDone);
	bullet->runAction(sequence);

	bulletBatchNode->addChild(bullet);
}

void BulletLayer::bulletMoveFinished(CCNode* pSender)
{
	CCSprite* bullet = (CCSprite*)pSender;
	m_pAllBullet->removeObject(bullet);//移除CCArray  
	this->bulletBatchNode->removeChild(bullet, true);//移除屏幕  
}

/*
	发射子弹的方法
*/
void BulletLayer::StartShoot(float delay)
{
	this->schedule(schedule_selector(BulletLayer::AddBullet),0.3f,kRepeatForever,delay);
}

/*停止发射子弹的方法*/
void BulletLayer::StopShoot()
{
	this->unschedule(schedule_selector(BulletLayer::AddBullet));
}

void BulletLayer::RemoveBullet(CCSprite* bullet)
{
	if (bullet != NULL)
	{
		this->m_pAllBullet->removeObject(bullet);
		this->bulletBatchNode->removeChild(bullet,true);
	}
}