#pragma once
#ifndef _PLANT_H_
#define _PLANT_H_
#include<cocos2d.h>



class Plant : public cocos2d::Sprite
{
public:
	enum class State
	{
		None,
		Planted
	};

	static Plant* create(const std::string& filename);
	void IsPlanted();
	bool init(const std::string& filename);
	virtual void update(float delta) override;
private:
	State _plantstate;
	float _deathtime = 0;


	static float _todeathtime;
};

#endif