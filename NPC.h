#pragma once
#include<cocos2d.h>
/*
* ����: ��дNPC
*/

//����������
enum class PhysicsCategory 
{
	None = 0,
	Hero = (1 << 0),
	NPC = (1 << 1),
	Animal = (1 << 2)
};

