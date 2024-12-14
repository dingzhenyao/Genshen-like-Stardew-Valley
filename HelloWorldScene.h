#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback

    virtual void update(float delta);              //重写的更新函数

    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    void ChangeSeason(float delta);                 //改变季节函数

    virtual void onExit();                  
    
    
    // implement the "static create()" method manually

    CREATE_FUNC(HelloWorld);
private:
    static cocos2d::TMXTiledMap* map;               //瓦片地图成员,以瓦片地图为成员，方便切换季节
   
    static cocos2d::Sprite* hero;
};

#endif // __HELLOWORLD_SCENE_H__