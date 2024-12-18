#include"Plant.h"
USING_NS_CC;

float Plant::_todeathtime = 120.0f;

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

	this->scheduleUpdate();
	_plantstate = State::None;
	return true;
}

void Plant::update(float delta)
{
	if(_plantstate == State::Planted)
	{
		_deathtime += 1;
		if(_deathtime > _todeathtime)
			this->removeFromParent();
	}
}

void Plant::IsPlanted()
{
	if(_plantstate == State::None)
	    _plantstate = State::Planted;
}

void Plant::ResetDeathtime()
{
	_deathtime = 0;
}