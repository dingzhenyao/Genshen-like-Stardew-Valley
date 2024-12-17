#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback

    virtual void update(float delta);              //��д�ĸ��º���

    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    virtual bool onContactBegin(cocos2d::PhysicsContact& contact);

    virtual bool onContactSeparate(cocos2d::PhysicsContact& contact);

    void ChangeSeason(float delta);                 //�ı伾�ں���

    virtual void onExit();                  
    
    void AddPlant();                               //���ֲ��

    //void KeyBoardKill(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    
    // implement the "static create()" method manually

    CREATE_FUNC(HelloWorld);
private:
    static cocos2d::TMXTiledMap* map;               //��Ƭ��ͼ��Ա,����Ƭ��ͼΪ��Ա�������л�����
   
    static cocos2d::Sprite* hero;

    static cocos2d::Sprite* collidedSprite;

    static bool IsCollide;
};

#endif // __HELLOWORLD_SCENE_H__