#include<cocos2d.h>
#include"NPC.h"


Object::ObjectType Object::getType()
{
	return _type;
}

void Object::setType(ObjectType type)
{
	_type = type;
}

Object* Object::create(const std::string& filepath)
{
	Object* object = new (std::nothrow) Object;
	if (object && object->initWithFile(filepath))
	{
		object->autorelease();
		return object;
	}
	else
	{
		CC_SAFE_DELETE(object);
	}
}