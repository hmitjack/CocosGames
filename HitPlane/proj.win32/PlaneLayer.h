#pragma once
#include "cocos2d.h"
const int AIRPLANE = 0;
USING_NS_CC;
class PlaneLayer : public cocos2d::Layer
{
public:
	PlaneLayer();
	~PlaneLayer();
	static PlaneLayer* create();
	virtual bool init();
	static PlaneLayer* sharedPlane;
	bool isAlive = true;
	void moveTo(cocos2d::CCPoint location);
};
