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
	//ȷ���ӵ��ĳ�ʼ��λ��
	auto planeLayer = PlaneLayer::sharedPlane;
	auto plane = PlaneLayer::sharedPlane->getChildByTag(AIRPLANE);
	CCPoint planePosition = PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->getPosition();
	CCPoint bulletPosition = ccp(planePosition.x, planePosition.y + PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->getContentSize().height / 2);
	bullet->setPosition(bulletPosition);

	float length = CCDirector::sharedDirector()->getWinSize().height + bullet->getContentSize().height / 2 - bulletPosition.y;//���о��룬������Ļ������  
	float velocity = 420 / 1;//�����ٶȣ�420pixel/sec  
	float realMoveDuration = length / velocity;//����ʱ��  

	CCFiniteTimeAction* actionMove = CCMoveTo::create(realMoveDuration, ccp(bulletPosition.x, CCDirector::sharedDirector()->getWinSize().height + bullet->getContentSize().height / 2));
	CCFiniteTimeAction* actionDone = CCCallFuncN::create(this, callfuncN_selector(BulletLayer::bulletMoveFinished));//�ص�һ���ӵ�����������  

	CCSequence* sequence = CCSequence::createWithTwoActions(actionMove, actionDone);
	bullet->runAction(sequence);

	bulletBatchNode->addChild(bullet);
}

void BulletLayer::bulletMoveFinished(CCNode* pSender)
{
	CCSprite* bullet = (CCSprite*)pSender;
	m_pAllBullet->removeObject(bullet);//�Ƴ�CCArray  
	this->bulletBatchNode->removeChild(bullet, true);//�Ƴ���Ļ  
}

/*
	�����ӵ��ķ���
*/
void BulletLayer::StartShoot(float delay)
{
	this->schedule(schedule_selector(BulletLayer::AddBullet),0.3f,kRepeatForever,delay);
}

/*ֹͣ�����ӵ��ķ���*/
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