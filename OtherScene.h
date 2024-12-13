#pragma once
#ifndef _OTHERSCENE_H_
#define _OTHERSCENE_H_
#include"cocos2d.h"

class Desert : public cocos2d::Layer 
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void update(float delta) override;              //重写的更新函数

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;

	//void ChangeSeason(float delta);                 //改变季节函数

	CREATE_FUNC(Desert);
private:
	static cocos2d::TMXTiledMap* map;
	static cocos2d::Sprite* hero;
};
#endif