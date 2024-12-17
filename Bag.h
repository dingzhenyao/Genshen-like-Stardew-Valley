#pragma once
/*
* ���ã�����
* 
* ������Ʒ��������Ʒ��ͼ��������Ϣ
*/
#ifndef _BAG_H_
#define _BAG_H_
#include<cocos2d.h>

class Bag :public cocos2d::Layer
{
public:
	static cocos2d::Layer* createLayer();    //bag�Ĵ���㺯��

	virtual bool init();                     //bag�ĳ�ʼ������

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	                                         //���̼�������
	void AddCell(cocos2d::Vec2 Pos);         //���ɱ������ӵĺ���
	CREATE_FUNC(Bag);

	//Tag
	static int BagTag;

private:
	cocos2d::Sprite* select_cell = nullptr;  //��ѡ�еĸ���

	static float BeginX;
	static float EndX;
	static float BeginY;
	static float EndY;
};
#endif // !_BAG_H_
