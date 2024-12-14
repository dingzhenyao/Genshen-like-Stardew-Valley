#include "HelloWorldScene.h"
#include"hero.h"
#include"OtherScene.h"
USING_NS_CC;

cocos2d::TMXTiledMap* HelloWorld::map = nullptr;
Sprite* HelloWorld::hero = nullptr;
Scene* HelloWorld::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
   
    auto layer = HelloWorld::create();
    
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    
    using namespace cocos2d;
   
    this->scheduleUpdate();
    //this->schedule(SEL_SCHEDULE(&HelloWorld::ChangeSeason),6.0f,kRepeatForever,0.0f);
    
    if (!Layer::init())
    {
        return false;
    }
   

    
  
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //初始地图
    if (!map)
        map = TMXTiledMap::create("home map/home.tmx");                  //加载瓦片地图,初始地图 
  

    

    auto director = Director::getInstance();                       //获得导演
    map->setScale(director->getContentScaleFactor() * 2);              //调整大小，适配屏幕
    
    //加载地图
    
    this->addChild(map, 1);
    

    //添加NPC
    auto enemy = Sprite::create("monster.png");
    enemy->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 100);
    auto enemybody = PhysicsBody::createBox(enemy->getContentSize());
    enemybody->setGravityEnable(false);
    enemybody->setDynamic(false);
    enemy->setPhysicsBody(enemybody);
    this->addChild(enemy, 3);
    auto sequence = Sequence::create(MoveBy::create(10.0f, Vec2(-500, 0)),MoveBy::create(10.0f,Vec2(500,0)), nullptr);
    auto reAction = RepeatForever::create(sequence);
    enemy->runAction(reAction);

    //放置主角
    hero = Sprite::create("player.png");
    hero->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    this->addChild(hero, 3);
    auto herobody = PhysicsBody::createBox(hero->getContentSize());
    herobody->setGravityEnable(false);
    herobody->setDynamic(true);
    hero->setPhysicsBody(herobody);

    //键盘监听
    auto listenerKeyboard = cocos2d::EventListenerKeyboard::create();
    listenerKeyboard->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
    listenerKeyboard->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

    
    return true;
}

void HelloWorld::update(float delta)      //场景帧更新函数
{
    auto director = Director::getInstance();
   
    auto ymax = Director::getInstance()->getVisibleSize().height;  //屏幕边缘
    auto xmax = Director::getInstance()->getVisibleSize().width;
    auto heroposition = this->hero->getPosition();
    //屏幕边缘检测
    {
        if (ymax < heroposition.y + 10.f)
        {
            auto repeat = this->hero->getActionByTag(static_cast<int>(MyActionTag::MyGoUp));
            if (repeat)
                this->hero->stopAction(repeat);
        }
        if (xmax < heroposition.x + 10.f)
        {
            auto repeat = this->hero->getActionByTag(static_cast<int>(MyActionTag::MyGoRight));
            if (repeat)
                this->hero->stopAction(repeat);
        }
        if (heroposition.y - 10.0f < 0)
        {
            auto repeat = this->hero->getActionByTag(static_cast<int>(MyActionTag::MyGoDown));
            if (repeat)
                this->hero->stopAction(repeat);
        }
        if (heroposition.x - 10.0f < 0)
        {
            auto repeat = hero->getActionByTag(static_cast<int>(MyActionTag::MyGoLeft));
            if (repeat)
                this->hero->stopAction(repeat);
        }
    }
    if(abs(heroposition.x - xmax) < 10.0f && abs(heroposition.y - ymax / 2) < 100.0f)
    {
        hero->setPosition(heroposition.x - 100.0f, heroposition.y);
        auto desert = Desert::createScene();//下一个场景
        Director::getInstance()->pushScene(desert);
    }
}

void HelloWorld::ChangeSeason(float delta)
{
    static int Time = 0;
    Time++;
    if(Time % 2 == 1)
    {
        auto zorder = map->getLocalZOrder();
        auto newmap = TMXTiledMap::create("desert map/desert.tmx");
        auto director = Director::getInstance();                       //获得导演
        newmap->setScale(director->getContentScaleFactor() * 2);              //调整大小，适配屏幕
        this->removeChild(map, true);
        this->addChild(newmap, zorder);
        map = newmap;
    }
    else if (Time % 2 == 0)
    {
        auto zorder = map->getLocalZOrder();
        auto newmap = TMXTiledMap::create("home map/home.tmx");
        auto director = Director::getInstance();                       //获得导演
        newmap->setScale(director->getContentScaleFactor() * 2);              //调整大小，适配屏幕
        this->removeChild(map, true);
        this->addChild(newmap, zorder);
        map = newmap;
    }
}

void HelloWorld::onExit()
{
    //for (auto child : this->getChildren())
    //{
     //   child->pause();
    //}
    //this->removeAllChildren();
    //if(this->isRunning())
     //   Director::getInstance()->getTextureCache()->removeUnusedTextures();
    Layer::onExit();
}

void HelloWorld::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
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

void HelloWorld::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
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
        default:
            break;
    }
}

