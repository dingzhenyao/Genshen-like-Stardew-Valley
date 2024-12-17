#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    //������������
    static cocos2d::Scene* createScene();

    //��ʼ������
    virtual bool init();

    // a selector callback

    virtual void update(float delta);              //��д�ĸ��º���

    //���̼�������
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    //��ײ����
    virtual bool onContactBegin(cocos2d::PhysicsContact& contact);
    virtual bool onContactSeparate(cocos2d::PhysicsContact& contact);

    //��������
    void ChangeSeason(float delta);              
    virtual void onExit();                  
    
    void AddPlant(const std::string& filepath);                               //���ֲ��
    void AddAnimal();                              //��Ӷ���
    // implement the "static create()" method manually

    //����HelloWorld::create()
    CREATE_FUNC(HelloWorld);
private:
    static cocos2d::TMXTiledMap* map;               //��Ƭ��ͼ��Ա,����Ƭ��ͼΪ��Ա�������л�����
   
    //����
    static cocos2d::Sprite* hero;

    //����ײ������
    static cocos2d::Sprite* collidedSprite;

    //�Ƿ���ײ���
    static bool IsCollide;
};

#endif // __HELLOWORLD_SCENE_H__