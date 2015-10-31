#ifndef HELLOWWORLDPLAYER_H_
#define HELLOWWORLDPLAYER_H_
#pragma once
#include "cocos2d.h"
class HelloWorldPlayer : public cocos2d::Layer
{
public:
	cocos2d::Sprite* background1;
	cocos2d::Sprite* background2;
	static cocos2d::Layer* createLayer();
	virtual bool init();
	HelloWorldPlayer();
	~HelloWorldPlayer();
	CREATE_FUNC(HelloWorldPlayer);
	void backgroundMove(float dt);
};
#endif
