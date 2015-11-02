#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Enemy : public CCNode
{
public:
	Enemy();
	~Enemy();
	CCSprite * m_sprite;//°ó¶¨µÐ»ú
	int m_life;
	static Enemy* create();
	void bindSprite(CCSprite* sprite,int life);
	CCSprite* getSprite();
	int getLife();
	void loseLife();
	CCRect getBoundingBox();
};

