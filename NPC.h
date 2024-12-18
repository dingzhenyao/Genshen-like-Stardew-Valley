#pragma once
#include<cocos2d.h>
/*
* 作用: 重写NPC
*/

//物理体掩码
enum class PhysicsCategory 
{
	None = 0,
	Hero = (1 << 0),
	NPC = (1 << 1),
	Animal = (1 << 2)
};

