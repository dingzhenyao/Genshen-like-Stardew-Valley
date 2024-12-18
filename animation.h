#pragma once
#include "cocos2d.h"

cocos2d::Animate* getanimation(std::string who,std::string animationname,std::string direction, int Framenum);
cocos2d::Sprite* initframe(std::string who, std::string animationname, std::string direction);
