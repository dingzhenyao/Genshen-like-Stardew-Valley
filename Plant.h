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
	void IsPlanted();                           //�ɹ����º����
	void ResetDeathtime();                      //ʩ�ʻ�ˮ��������������ʱ��
	bool init(const std::string& filename);     //��ʼ������
	virtual void update(float delta) override;  //���Ҹ��º���

private:
	State _plantstate;                          //Ŀǰ״̬
	float _deathtime = 0;                       //��������ʱ
	static float _todeathtime;                  //����ʱ��
};

#endif