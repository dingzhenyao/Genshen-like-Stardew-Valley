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
	Animal = (1 << 2),
	Plant = (1 << 3)
};

class Object : public cocos2d::Sprite 
{
public:
	enum class ObjectType
	{
		Plant,
		Animal
	};
	static Object* create(const std::string& filepath);

	ObjectType getType();

	void setType(ObjectType type);
protected:
	ObjectType _type;
};

