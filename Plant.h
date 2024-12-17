#pragma once
#ifndef _PLANT_H_
#define _PLANT_H_
#include<cocos2d.h>



class Plant : public cocos2d::Sprite
{
public:
	static Plant* create(const std::string& filename);
	bool init(const std::string& filename);
	virtual void update(float delta) override;


private:
};

#endif