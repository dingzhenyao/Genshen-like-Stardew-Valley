#include"Plant.h"
USING_NS_CC;


Plant* Plant::create(const std::string& filename)
{
	Plant* plant = new Plant;
	if (plant->init(filename))
	{
		plant->autorelease();
	}
	else
	{
		delete plant;
		plant = nullptr;
		return nullptr;
	}
	return plant;
}

bool Plant::init(const std::string& filename)
{
	if (!Sprite::initWithFile(filename))
		return false;
	return true;
}

void Plant::update(float delta)
{
	this->removeFromParent();
}