#include"cocos2d.h"
#include"hero.h"
/*
* ���ã�ʵ��Hero��ĳ�Ա����
*/
using namespace cocos2d;
cocos2d::Sprite* Hero::MyHero = nullptr;

cocos2d::Sprite* Hero::GetHero()                                                     //��ȡ��̬Sprite Hero
{
	if (!MyHero)
		MyHero = cocos2d::Sprite::create("player.png");

	return MyHero;
}

void Hero::OnKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) //�������������
{
	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_W: 
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
	    {
			
			auto action = MoveBy::create(0.1f, Vec2(0, HERO_SPEED));
			MyHero->runAction(RepeatForever::create(action));
			
			break;
		}
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S: 
		{
			auto action = MoveBy::create(0.1f, Vec2(0, -HERO_SPEED));
			MyHero->runAction(RepeatForever::create(action));
			
			break;
		}
		case EventKeyboard::KeyCode::KEY_A:
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		{
	
			auto action = MoveBy::create(0.1f, Vec2(-HERO_SPEED, 0));
			MyHero->runAction(RepeatForever::create(action));
			
			break;
		}
		case EventKeyboard::KeyCode::KEY_D:
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		{

			auto action = MoveBy::create(0.1f, Vec2(HERO_SPEED, 0));
			MyHero->runAction(RepeatForever::create(action));
			break;
		}
		default:
			break;
	}
}

void Hero::OnKeyRelease(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_W:
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		{

			auto action = MoveBy::create(0.1f, Vec2(0, HERO_SPEED));
			MyHero->runAction(RepeatForever::create(action->reverse()));

			break;
		}
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S:
		{
			auto action = MoveBy::create(0.1f, Vec2(0, -HERO_SPEED));
			MyHero->runAction(RepeatForever::create(action->reverse()));

			break;
		}
		case EventKeyboard::KeyCode::KEY_A:
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		{

			auto action = MoveBy::create(0.1f, Vec2(-HERO_SPEED, 0));
			MyHero->runAction(RepeatForever::create(action->reverse()));

			break;
		}
		case EventKeyboard::KeyCode::KEY_D:
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		{


			auto action = MoveBy::create(0.1f, Vec2(HERO_SPEED, 0));
			MyHero->runAction(RepeatForever::create(action->reverse()));
			
			break;
		}
		default:
			break;
	}
}

Hero* Hero::instance()
{
	static Hero hero;
	return &hero;
}
