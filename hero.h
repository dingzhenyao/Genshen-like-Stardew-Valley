#pragma once
#include"cocos2d.h"
/*
* ���ƣ�������
* ���ã�ʵ�����ǵĴ����Լ��ƶ��������ȵĹ���
*/
#define HERO_SPEED 50


class Hero       //����ģʽ
{
public:
	static Hero* instance();          

	static cocos2d::Sprite* GetHero();

	void OnKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void OnKeyRelease(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

private:
	static cocos2d::Sprite* MyHero;        //Ӣ�۽�ɫ
	Hero(){}
	Hero(const Hero&) = delete;
	Hero(const Hero&&) = delete;
	Hero& operator=(const Hero&) = delete;
}; 