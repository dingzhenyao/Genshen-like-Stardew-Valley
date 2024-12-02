#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool HelloWorld::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto map = TMXTiledMap::create("desert map/desert.tmx");                  //加载瓦片地图
   
    auto director = Director::getInstance();                       //获得导演

    map->setScale(director->getContentScaleFactor());              //调整大小，适配屏幕
    
    this->addChild(map, -1);

    //auto poly = AutoPolygon::generatePolygon("Player.png");        
    //auto sprite = Sprite::create(poly);

    //sprite->setPosition(Vec2(0.5f * visibleSize.width , 0.5f * visibleSize.width));
    
    //this->addChild(sprite);
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}