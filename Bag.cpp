/*
* ���������ľ���ʵ��
*/

#include"Bag.h"
USING_NS_CC;

float Bag::BeginX = 0;
float Bag::EndX = 0;
float Bag::BeginY = 0;
float Bag::EndY = 0;
int Bag::BagTag = 111;

Layer* Bag::createLayer()
{
	return Bag::create();
}

bool Bag::init()
{
	if (!Layer::init())
		return false;
	auto director = Director::getInstance();
	auto origin = director->getVisibleOrigin();
	auto viSize = director->getVisibleSize();

	//���س�ʼѡ�еĸ���
    select_cell = Sprite::create("bag/Inventory_select.png");
	select_cell->setContentSize(select_cell->getContentSize() * 4);

	//��ʼ�����ӵı߽�
	BeginX = viSize.width / 2 - 5 * select_cell->getContentSize().width;
	EndX = viSize.width / 2 + 5 * select_cell->getContentSize().width;
	BeginY = viSize.height / 2 - 5 * select_cell->getContentSize().height;
	EndY = viSize.height / 2 + 5 * select_cell->getContentSize().height;

	//����ʼ��ѡ�и��ӷ���Layer��
	select_cell->setPosition(BeginX, BeginY);

	for (float X = BeginX; X <= EndX; X += select_cell->getContentSize().width)   //��Ӹ���
		for(float Y = BeginY;Y <= EndY;Y += select_cell->getContentSize().height)
		    AddCell(Vec2(X, Y));
	
	this->addChild(select_cell,3);


	//���������ļ�����Ӧ

	auto bagKey = EventListenerKeyboard::create();

	bagKey->onKeyPressed = CC_CALLBACK_2(Bag::onKeyPressed, this);

	director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(bagKey, this);
	return true;
}

void Bag::AddCell(Vec2 Pos)
{
	auto sprite = Sprite::create("bag/Inventory_Slot.png");
	sprite->setScale(4.0);
	sprite->setPosition(Pos);
	this->addChild(sprite, 3);
}

void Bag::onKeyPressed(EventKeyboard::KeyCode keycode,Event* event)
{
	auto position = select_cell->getPosition();
	//�ƶ�ѡ�еĸ���
	switch (keycode)
	{
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		{
			if (position.y >= EndY)
				;
			else
			{
				auto moveto = MoveTo::create(1e-6, Vec2(position.x, position.y + select_cell->getContentSize().height));

				select_cell->runAction(moveto);
			}
			break;
		}
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		{
			if (position.y <= BeginY)
				;
			else
			{
				auto moveto = MoveTo::create(1e-6, Vec2(position.x, position.y - select_cell->getContentSize().height));

				select_cell->runAction(moveto);
			}
			break;
		}
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		{
			if (position.x <= BeginX)
				;
			else
			{
				auto moveto = MoveTo::create(1e-6, Vec2(position.x - select_cell->getContentSize().width, position.y));

				select_cell->runAction(moveto);
			}
			break;
		}
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		{
			if (position.x >= EndX)
				;
			else
			{
				auto moveto = MoveTo::create(1e-6, Vec2(position.x + select_cell->getContentSize().width, position.y));

				select_cell->runAction(moveto);
			}
			break;
		}
		case EventKeyboard::KeyCode::KEY_B:
		{
			break;
		}
		default:
			break;
	}
}