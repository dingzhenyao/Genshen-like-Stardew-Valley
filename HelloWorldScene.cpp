#include "HelloWorldScene.h"
#include"hero.h"
#include"OtherScene.h"
#include"NPC.h"
#include"menu.h"
#include"Plant.h"
#include"bag.h"
USING_NS_CC;
cocos2d::TMXTiledMap* HelloWorld::map = nullptr;
Sprite* HelloWorld::hero = nullptr;
Sprite* HelloWorld::collidedSprite = nullptr;
bool HelloWorld::IsCollide = false;

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
    //��ʼ��ͼ
    if (!map)
        map = TMXTiledMap::create("home map/home.tmx");                  //������Ƭ��ͼ,��ʼ��ͼ 
  
    auto director = Director::getInstance();                       //��õ���
    map->setScale(director->getContentScaleFactor() * 2);              //������С��������Ļ
    
    //���ص�ͼ
    this->addChild(map, 1);

    //��������
    hero = Sprite::create("player.png");
    hero->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    this->addChild(hero, 3);
    auto herobody = PhysicsBody::createBox(hero->getContentSize());
    herobody->setGravityEnable(false);
    herobody->setDynamic(false);

    //����λ����
    herobody->setCategoryBitmask((int)PhysicsCategory::Hero);
    herobody->setContactTestBitmask(0xfffffff);
    herobody->setCollisionBitmask(0);
    hero->setPhysicsBody(herobody);
    hero->stopAllActions();

    //���̼���
    auto listenerKeyboard = cocos2d::EventListenerKeyboard::create();
    listenerKeyboard->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
    listenerKeyboard->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

    //��ײ���
    auto physicalcontact = cocos2d::EventListenerPhysicsContact::create();
    physicalcontact->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
    physicalcontact->onContactSeparate = CC_CALLBACK_1(HelloWorld::onContactSeparate, this);

    director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(physicalcontact, this);

    return true;
}

void HelloWorld::update(float delta)      //����֡���º���
{
    auto director = Director::getInstance();
   
    auto ymax = Director::getInstance()->getVisibleSize().height;  //��Ļ��Ե
    auto xmax = Director::getInstance()->getVisibleSize().width;
    auto heroposition = this->hero->getPosition();
    //��Ļ��Ե���
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
        auto desert = Desert::createScene();//��һ������
        Director::getInstance()->pushScene(desert);
        hero->stopAllActions();
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
        auto director = Director::getInstance();                       //��õ���
        newmap->setScale(director->getContentScaleFactor() * 2);              //������С��������Ļ
        this->removeChild(map, true);
        this->addChild(newmap, zorder);
        map = newmap;
    }
    else if (Time % 2 == 0)
    {
        auto zorder = map->getLocalZOrder();
        auto newmap = TMXTiledMap::create("home map/home.tmx");
        auto director = Director::getInstance();                       //��õ���
        newmap->setScale(director->getContentScaleFactor() * 2);              //������С��������Ļ
        this->removeChild(map, true);
        this->addChild(newmap, zorder);
        map = newmap;
    }
}

void HelloWorld::onExit()
{
    Layer::onExit();
}

void HelloWorld::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    static bool IsBag = false;        //����Ƿ�Ϊ�������棬���Ϊ�������棬������޷��ƶ�
    static int BagNumber = 0;         //��BagNumberΪ����ʱ�����뱳������BagNumberΪż��ʱ���뿪����
    static EventKeyboard::KeyCode lastKeycode = EventKeyboard::KeyCode::KEY_0;
    switch (keyCode)
    {
        case EventKeyboard::KeyCode::KEY_W:
        case EventKeyboard::KeyCode::KEY_UP_ARROW:   //���������ƶ�
        {
            if(!IsBag)
            {
                auto action = MoveBy::create(0.1f, Vec2(0, HERO_SPEED));
                auto repeat = RepeatForever::create(action);
                repeat->setTag(static_cast<int>(MyActionTag::MyGoUp));
                this->hero->runAction(repeat);
            }
            break;
        }
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW: //���������ƶ�
        case EventKeyboard::KeyCode::KEY_S:
        {
            if(!IsBag)
            {
                auto action = MoveBy::create(0.1f, Vec2(0, -HERO_SPEED));
                auto repeat = RepeatForever::create(action);
                repeat->setTag(static_cast<int>(MyActionTag::MyGoDown));
                this->hero->runAction(repeat);
            }

            break;
        }
        case EventKeyboard::KeyCode::KEY_A:
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW: //���������ƶ�
        {
            if(!IsBag)
            {
                auto action = MoveBy::create(0.1f, Vec2(-HERO_SPEED, 0));
                auto repeat = RepeatForever::create(action);
                repeat->setTag(static_cast<int>(MyActionTag::MyGoLeft));
                this->hero->runAction(repeat);
            }
            break;
        }
        case EventKeyboard::KeyCode::KEY_D:
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: //���������ƶ�
        {
            if(!IsBag)
            {
                auto action = MoveBy::create(0.1f, Vec2(HERO_SPEED, 0));
                auto repeat = RepeatForever::create(action);
                repeat->setTag(static_cast<int>(MyActionTag::MyGoRight));
                this->hero->runAction(repeat);
            }
            break;
        }
        case EventKeyboard::KeyCode::KEY_ESCAPE:       //�˳�����
        {
            Director::getInstance()->end();
            break;
        }
        case EventKeyboard::KeyCode::KEY_TAB:          //���뼼����ҳ��
        {
            Scene* menu = GameMenu::createScene();
            Director::getInstance()->pushScene(menu);
            break;
        }
        case EventKeyboard::KeyCode::KEY_P:            //��ֲֲ��
        {
            if(!IsBag)
            {
                lastKeycode = EventKeyboard::KeyCode::KEY_P;
            }
            break;
        }
        case EventKeyboard::KeyCode::KEY_K:            //���׶���
        {
            if (IsCollide && !IsBag)
            {
                if(collidedSprite)
                    this->removeChild(collidedSprite, true);
            }
            break;
        }
        case EventKeyboard::KeyCode::KEY_B:            //���뱳��
        {
            if (BagNumber & 1)
            {
                auto bag = this->getChildByTag(Bag::BagTag);
               
                this->removeChildByTag(Bag::BagTag,true);
                IsBag = false;
            }
            else
            {
                auto bag = Bag::createLayer();
                bag->setTag(Bag::BagTag);
                this->addChild(bag, INT_MAX);
                IsBag = true;
            }
            BagNumber++;
            break;
        }
        case EventKeyboard::KeyCode::KEY_Q:           //������
        {
            AddAnimal();
            break;
        }
        case EventKeyboard::KeyCode::KEY_1:          //�����
        {
            if (lastKeycode == EventKeyboard::KeyCode::KEY_P)  //����P�Ժ�
            {
                AddPlant("monster.png");
            }
            break;
        }
        case EventKeyboard::KeyCode::KEY_2:
        {
            if (lastKeycode == EventKeyboard::KeyCode::KEY_P)  //����P�Ժ�
            {
                AddPlant("player.png");
            }
            break;
        }
        case EventKeyboard::KeyCode::KEY_E:                    //ʩ����
        {
            if (!IsBag && IsCollide)
            {
                if (collidedSprite)
                {

                }
            }
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

bool HelloWorld::onContactBegin(PhysicsContact& contact)
{
    auto ShapeA = contact.getShapeA()->getBody();
    auto ShapeB = contact.getShapeB()->getBody();
    switch (ShapeB->getCategoryBitmask())
    {
        case (int)PhysicsCategory::Animal:
        {
            IsCollide = true;
            collidedSprite = (Sprite*)ShapeB->getNode();
            break;
        }
        case (int)PhysicsCategory::Plant:
        {
            IsCollide = true;
            collidedSprite = (Sprite*)ShapeB->getNode();
            break;
        }
        break;
    }
    return true;
}

bool HelloWorld::onContactSeparate(PhysicsContact& contact)
{
    auto ShapeA = contact.getShapeA()->getBody();
    auto ShapeB = contact.getShapeB()->getBody();
    switch (ShapeB->getCategoryBitmask())
    {
        case (int)PhysicsCategory::Animal:
        {
            IsCollide = false;
            collidedSprite = nullptr;
        }
        break;
    }
    return true;
}
//��ֲֲ��
void HelloWorld::AddPlant(const std::string & filepath)
{
    auto position = hero->getPosition();
    auto plant = Plant::create(filepath);
    plant->setPosition(position);

    //���������
    auto plantbody = PhysicsBody::createBox(plant->getContentSize());

    plantbody->setCategoryBitmask((int)PhysicsCategory::Plant);
    plantbody->setContactTestBitmask((int)PhysicsCategory::Hero);

    plant->setPhysicsBody(plantbody);
    this->addChild(plant, 2);
    plant->scheduleUpdate();
    plant->IsPlanted();
}

void HelloWorld::AddAnimal()
{
    //auto visblieSize = Director::getInstance()->getVisibleSize();
    //auto origin = Director::getInstance()->getVisibleOrigin();


    auto animal = Sprite::create("monster.png");
    animal->setPosition(hero->getPosition());
    auto animalbody = PhysicsBody::createBox(animal->getContentSize());
    animalbody->setGravityEnable(false);
    animalbody->setDynamic(false);
    animalbody->setCategoryBitmask((int)PhysicsCategory::Animal);
    animalbody->setContactTestBitmask((int)PhysicsCategory::Hero);
    animal->setPhysicsBody(animalbody);
    this->addChild(animal, 3);


    //auto sequence = Sequence::create(MoveBy::create(10.0f, Vec2(-500, 0)),MoveBy::create(10.0f,Vec2(500,0)), nullptr);
    //auto reAction = RepeatForever::create(sequence);
    //animal->runAction(reAction);
}




