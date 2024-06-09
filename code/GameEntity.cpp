#include"GameEntity.h"

GameEntity::GameEntity(){}

GameEntity::GameEntity(unsigned int m, float f, float d, float t)
{
    this->m=m;
    this->f=f;
    this->d=d;
    this->t=t;
}

GameEntity::~GameEntity(){};