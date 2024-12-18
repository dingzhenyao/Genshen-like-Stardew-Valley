#pragma once
#ifndef _PLANT_H_
#define _PLANT_H_
#include<cocos2d.h>
#include"NPC.h"


class Plant : public Object
{
public:
	enum class State
	{
		None,
		Planted,
		Growth
	};

	static Plant* create(const std::string& filename);
	void IsPlanted();                           //成功种下后调用
	void ResetDeathtime();                      //施肥或浇水后，重新设置死亡时间
	bool init(const std::string& filename);     //初始化函数
	virtual void update(float delta) override;  //自我更新函数
	void setState(State);
	State getState();
private:
	State _plantstate;                          //目前状态
	float _deathtime = 0;                       //死亡倒计时
	static float _todeathtime;                  //死亡时间
};

#endif