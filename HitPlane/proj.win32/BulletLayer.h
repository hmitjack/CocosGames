#pragma once
#include "cocos2d.h"
class BulletLayer : public cocos2d::Layer
{
public:
	BulletLayer();
	~BulletLayer();
	virtual bool init();
	cocos2d::CCSpriteBatchNode* bulletBatchNode;
	void AddBullet(float dt);
	void bulletMoveFinished(cocos2d::CCNode* pSender);
	cocos2d::CCArray* m_pAllBullet;
	void StartShoot(float delay);//·¢Éä×Óµ¯
	void StopShoot();//Í£Ö¹·¢Éä×Óµ¯
	void RemoveBullet(cocos2d::CCSprite* bullet);//É¾³ý×Óµ¯ 
	CREATE_FUNC(BulletLayer);
};

