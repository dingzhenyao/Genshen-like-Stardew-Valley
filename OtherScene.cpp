#include"cocos2d.h"
#include"OtherScene.h"
#include"HelloWorldScene.h"
#include"hero.h"
USING_NS_CC;

Scene* Desert::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    auto layer = Desert::create();
    scene->addChild(layer);
    return scene;
}

bool Desert::init()
{

    if (!Layer::init())
    {
        return false;
    }
    this->scheduleUpdate();
    auto director = Director::getInstance();

    auto origin = director->getVisibleOrigin();
    auto visibleSize = director->getVisibleSize();

    if(!map)
        map = TMXTiledMap::create("desert map/desert.tmx");

    
    map->setScale(director->getContentScaleFactor() * 2);              //������С��������Ļ
    this->addChild(map, 1);


    hero = Sprite::create("player.png");
    hero->setPosition(origin.x + 100.0f, visibleSize.height / 2 + origin.y);
    this->addChild(hero, 3);
    auto herobody = PhysicsBody::createBox(hero->getContentSize());
    herobody->setGravityEnable(false);
    herobody->setDynamic(false);
    hero->setPhysicsBody(herobody);
    
   
    auto listenerKeyboard = cocos2d::EventListenerKeyboard::create();
    listenerKeyboard->onKeyPressed = CC_CALLBACK_2(Desert::onKeyPressed, this);
    listenerKeyboard->onKeyReleased = CC_CALLBACK_2(Desert::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

    return true;
}

void Desert::update(float delta)      //����֡���º���
{
    auto ymax = Director::getInstance()->getVisibleSize().height;  //��Ļ��Ե
    auto xmax = Director::getInstance()->getVisibleSize().width;
    auto heroposition = hero->getPosition();
    //��Ļ��Ե���
    {
        
        if (ymax < heroposition.y + 10.f)
        {
            auto repeat = hero->getActionByTag((int)MyActionTag::MyGoUp);
            if (repeat)
                hero->stopAction(repeat);
        }
        if (xmax < heroposition.x + 10.f)
        {
            auto repeat = hero->getActionByTag((int)MyActionTag::MyGoRight);
            if (repeat)
                hero->stopAction(repeat);
        }
        if (heroposition.y - 10.0f < 0)
        {
            auto repeat = hero->getActionByTag((int)MyActionTag::MyGoDown);
            if (repeat)
                hero->stopAction(repeat);
        }
        if (heroposition.x - 10.0f < 0)
        {
            auto repeat = hero->getActionByTag((int)MyActionTag::MyGoLeft);
            if (repeat)
                hero->stopAction(repeat);
        }
    }
    if (abs(heroposition.x) < 10.0f && abs(heroposition.y - ymax / 2) < 100.0f)
    {
        hero->stopAllActions();
        Director::getInstance()->popScene();
    }
}

void Desert::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    switch (keyCode)
    {
        case EventKeyboard::KeyCode::KEY_W:
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
        {

            auto action = MoveBy::create(0.1f, Vec2(0, HERO_SPEED));
            auto repeat = RepeatForever::create(action);
            repeat->setTag(static_cast<int>(MyActionTag::MyGoUp));
            this->hero->runAction(repeat);
            break;
        }
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        case EventKeyboard::KeyCode::KEY_S:
        {
            auto action = MoveBy::create(0.1f, Vec2(0, -HERO_SPEED));
            auto repeat = RepeatForever::create(action);
            repeat->setTag(static_cast<int>(MyActionTag::MyGoDown));
            this->hero->runAction(repeat);

            break;
        }
        case EventKeyboard::KeyCode::KEY_A:
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        {

            auto action = MoveBy::create(0.1f, Vec2(-HERO_SPEED, 0));
            auto repeat = RepeatForever::create(action);
            repeat->setTag(static_cast<int>(MyActionTag::MyGoLeft));
            this->hero->runAction(repeat);
            break;
        }
        case EventKeyboard::KeyCode::KEY_D:
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        {

            auto action = MoveBy::create(0.1f, Vec2(HERO_SPEED, 0));
            auto repeat = RepeatForever::create(action);
            repeat->setTag(static_cast<int>(MyActionTag::MyGoRight));
            this->hero->runAction(repeat);
            break;
        }
        default:
            break;
    }
}

void Desert::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    switch (keyCode)
    {
        case EventKeyboard::KeyCode::KEY_W:
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
        {

            auto repeat = this->hero->getActionByTag(static_cast<int>(MyActionTag::MyGoUp));
            if (repeat)
                this->hero->stopAction(repeat);
            break;
        }
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        case EventKeyboard::KeyCode::KEY_S:
        {
            auto repeat = this->hero->getActionByTag(static_cast<int>(MyActionTag::MyGoDown));
            if (repeat)
                this->hero->stopAction(repeat);
            break;
        }
        case EventKeyboard::KeyCode::KEY_A:
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        {

            auto repeat = this->hero->getActionByTag(static_cast<int>(MyActionTag::MyGoLeft));
            if (repeat)
                this->hero->stopAction(repeat);
            break;
        }
        case EventKeyboard::KeyCode::KEY_D:
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        {


            auto repeat = this->hero->getActionByTag(static_cast<int>(MyActionTag::MyGoRight));
            if (repeat)
                this->hero->stopAction(repeat);
            break;
        }
        case EventKeyboard::KeyCode::KEY_ESCAPE:
        {
            Director::getInstance()->end();
        }
        default:
            break;
    }
}

void Desert::onExit()
{
   
    Layer::onExit();
}