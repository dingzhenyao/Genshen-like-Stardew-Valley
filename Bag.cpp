/*
* 背包函数的具体实现
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

	//加载初始选中的格子
    select_cell = Sprite::create("bag/Inventory_select.png");
	select_cell->setContentSize(select_cell->getContentSize() * 4);

	//初始化格子的边界
	BeginX = viSize.width / 2 - 5 * select_cell->getContentSize().width;
	EndX = viSize.width / 2 + 5 * select_cell->getContentSize().width;
	BeginY = viSize.height / 2 - 5 * select_cell->getContentSize().height;
	EndY = viSize.height / 2 + 5 * select_cell->getContentSize().height;

	//将初始的选中格子放入Layer中
	select_cell->setPosition(BeginX, BeginY);

	for (float X = BeginX; X <= EndX; X += select_cell->getContentSize().width)   //添加格子
		for(float Y = BeginY;Y <= EndY;Y += select_cell->getContentSize().height)
		    AddCell(Vec2(X, Y));
	
	this->addChild(select_cell,3);


	//创建背包的键盘响应

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
	//移动选中的格子
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