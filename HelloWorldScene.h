#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback

    void update(float delta) override;              //��д�ĸ��º���

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;

    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;

    void ChangeSeason(float delta);                 //�ı伾�ں���

    void onExit() override;                  
    
    
    // implement the "static create()" method manually

    CREATE_FUNC(HelloWorld);
private:
    static cocos2d::TMXTiledMap* map;               //��Ƭ��ͼ��Ա,����Ƭ��ͼΪ��Ա�������л�����
   
    static cocos2d::Sprite* hero;
};

#endif // __HELLOWORLD_SCENE_H__