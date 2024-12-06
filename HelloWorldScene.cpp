#include "HelloWorldScene.h"
#include"hero.h"
USING_NS_CC;
Scene* HelloWorld::createScene()
{
    auto scene = HelloWorld::create();
    //scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool HelloWorld::init()
{
    using namespace cocos2d;
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //��ʼ��ͼ
    auto map = TMXTiledMap::create("home map/home.tmx");                  //������Ƭ��ͼ,��ʼ��ͼ 

    
    auto director = Director::getInstance();                       //��õ���
    map->setScale(director->getContentScaleFactor() * 2);              //������С��������Ļ
    this->addChild(map, 1);
    auto hero = Hero::GetHero();

    //��������
    hero->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height + origin.y);
    this->addChild(hero, 1);
    auto myhero = Hero::instance();

    //���̼���
    auto listenerKeyboard = cocos2d::EventListenerKeyboard::create();
    listenerKeyboard->onKeyPressed = CC_CALLBACK_2(Hero::OnKeyPressed, myhero);
    listenerKeyboard->onKeyReleased = CC_CALLBACK_2(Hero::OnKeyRelease, myhero);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}