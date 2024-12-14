#pragma once
#ifndef _OTHERSCENE_H_
#define _OTHERSCENE_H_
#include"cocos2d.h"
#include"HelloWorldScene.h"
class Desert : public HelloWorld 
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void update(float delta) override;              //��д�ĸ��º���

	//void ChangeSeason(float delta);                 //�ı伾�ں���
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	virtual void onExit();

	CREATE_FUNC(Desert);
private:
	cocos2d::TMXTiledMap* map = nullptr;
	cocos2d::Sprite* hero = nullptr;
};
#endif