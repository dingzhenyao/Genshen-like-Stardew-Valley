#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    //创建场景函数
    static cocos2d::Scene* createScene();

    //初始化函数
    virtual bool init();

    // a selector callback

    virtual void update(float delta);              //重写的更新函数

    //键盘监听函数
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    //碰撞函数
    virtual bool onContactBegin(cocos2d::PhysicsContact& contact);
    virtual bool onContactSeparate(cocos2d::PhysicsContact& contact);

    //换季函数
    void ChangeSeason(float delta);              
    virtual void onExit();                  
    
    void AddPlant(const std::string& filepath);                               //添加植物
    void AddAnimal();                              //添加动物
    // implement the "static create()" method manually

    //生成HelloWorld::create()
    CREATE_FUNC(HelloWorld);
private:
    static cocos2d::TMXTiledMap* map;               //瓦片地图成员,以瓦片地图为成员，方便切换季节
   
    //主角
    static cocos2d::Sprite* hero;

    //被碰撞的物体
    static cocos2d::Sprite* collidedSprite;

    //是否碰撞检测
    static bool IsCollide;
};

#endif // __HELLOWORLD_SCENE_H__