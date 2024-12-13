#pragma once
#include<cocos2d.h>

enum class PhysicsCategory {
	None = 0,
	Hero = (1 << 0),
	NPC = (1 << 1)
};

class NPC : public cocos2d::Sprite
{
public:
	
private:
};

