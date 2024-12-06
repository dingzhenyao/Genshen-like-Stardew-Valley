#pragma once
#include"cocos2d.h"
/*
* 名称：主角类
* 作用：实现主角的创建以及移动，交互等的功能
*/
#define HERO_SPEED 50


class Hero       //单例模式
{
public:
	static Hero* instance();          

	static cocos2d::Sprite* GetHero();

	void OnKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void OnKeyRelease(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

private:
	static cocos2d::Sprite* MyHero;        //英雄角色
	Hero(){}
	Hero(const Hero&) = delete;
	Hero(const Hero&&) = delete;
	Hero& operator=(const Hero&) = delete;
}; 