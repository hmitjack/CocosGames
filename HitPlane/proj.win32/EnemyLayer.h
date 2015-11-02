#pragma once
#include "cocos2d.h"
USING_NS_CC;
class EnemyLayer : public Layer
{
public:
	EnemyLayer();
	~EnemyLayer();
	cocos2d::CCSpriteBatchNode* enemyBatchNode;
	void addEnemy1(float dt);
	CCArray * m_pAllEnemy1;
	void enemy1MoveFinished(cocos2d::CCNode* bullet);//É¾³ý×Óµ¯ 
	virtual bool init();
	void startShoot(float dt);
	CREATE_FUNC(EnemyLayer);
};

