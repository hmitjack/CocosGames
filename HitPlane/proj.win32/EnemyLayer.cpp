#include "EnemyLayer.h"
#include "proj.win32\Enemy.h"
#define schedule_selector(_SELECTOR) (SEL_SCHEDULE)(&_SELECTOR)

EnemyLayer::EnemyLayer()
{

}
EnemyLayer::~EnemyLayer()
{
}
bool EnemyLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());
		CCTexture2D *texture = CCTextureCache::sharedTextureCache()->textureForKey("shoot.png");
		enemyBatchNode = CCSpriteBatchNode::createWithTexture(texture);
		this->addChild(enemyBatchNode);
		bRet = true;
		//schedule(schedule_selector(BulletLayer::AddBullet), 0.01f, kRepeatForever, 0);
	} while (0);
	return bRet;
}
 void EnemyLayer::addEnemy1(float dt)
{
	//���ð󶨵л�1  
	Enemy* enemy1 = Enemy::create();
	enemy1->bindSprite(CCSprite::create("enermy1.png"), 100);

	//�����ʼλ��  
	CCSize enemy1Size = enemy1->getSprite()->getContentSize();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int minX = enemy1Size.width / 2;
	int maxX = winSize.width - enemy1Size.width / 2;
	int rangeX = maxX - minX;
	int actualX = (rand() % rangeX) + minX;

	enemy1->setPosition(ccp(actualX, winSize.height + enemy1Size.height / 2));
	this->addChild(enemy1);
	this->m_pAllEnemy1->addObject(enemy1);

	//��������ٶ�  
	float minDuration, maxDuration;

	//������Ϸ�Ѷȸ�minDuration,maxDuration��ֵ  

	int rangeDuration = maxDuration - minDuration;
	int actualDuration = (rand() % rangeDuration) + minDuration;

	CCFiniteTimeAction* actionMove = CCMoveTo::create(actualDuration, ccp(actualX, 0 - enemy1->getSprite()->getContentSize().height / 2));
	CCFiniteTimeAction* actionDone = CCCallFuncN::create(this, callfuncN_selector(EnemyLayer::enemy1MoveFinished));//�ص�һ���ӵ����������� 

	CCSequence* sequence = CCSequence::create(actionMove, actionDone);
	enemy1->runAction(sequence);
}

void EnemyLayer::enemy1MoveFinished(CCNode* pSender)
{
	CCSprite* bullet = (CCSprite*)pSender;
	m_pAllEnemy1->removeObject(bullet);//�Ƴ�CCArray  
}

/*
�����ӵ��ķ���
*/
void EnemyLayer::startShoot(float delay)
{
	this->schedule(schedule_selector(EnemyLayer::addEnemy1), 0.3f, kRepeatForever, delay);
}