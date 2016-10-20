#include <cstdlib>

#include "TiledNpc.h"

TiledNpc::TiledNpc(const std::string& path, TileMap* map) :
  TiledCharacter(path, map),
  _trackedDrawable(),
  _mode(0)
{ }

void TiledNpc::update(float dt) {
  switch(_mode) {
    case 0:
      wander(dt);
      break;
    case 1:
      moveTowardTracked(dt);
      break;
    case 2:
      moveFromTracked(dt);
      break;
  }
  TiledCharacter::update(dt);
}

void TiledNpc::moveTowardTracked(float dt) {
  if(!_trackedDrawable) {
    wander(dt);
    return;
  }

	cocos2d::Point pos = getPosition();
  cocos2d::Vec2 mvmtVec = pos - _trackedDrawable->getPosition();
  if(mvmtVec.length() > 100) {
    wander(dt);
    return;
  }
  mvmtVec.normalize();
  mvmtVec *= -150;
  setVelocity(mvmtVec);
}

void TiledNpc::moveFromTracked(float dt) {
  if(!_trackedDrawable) {
    wander(dt);
    return;
  }

	cocos2d::Point pos = getPosition();
  cocos2d::Vec2 mvmtVec = pos - _trackedDrawable->getPosition();
  if(mvmtVec.length() > 100) {
    wander(dt);
    return;
  }
  mvmtVec.normalize();
  mvmtVec *= 150;
  setVelocity(mvmtVec);
}

void TiledNpc::wander(float dt) {
  unsigned int randMode = std::rand()%4;
  
  switch(randMode) {
    case 0:
      moveLeft(dt);
      break;
    case 1:
      moveRight(dt);
      break;
    case 2:
      moveUp(dt);
      break;
    case 3:
      moveDown(dt);
      break;
    default:
      break;
  }
}

void TiledNpc::moveLeft(float dt) {
  setVelocity(cocos2d::Vec2(-100,0));
}

void TiledNpc::moveRight(float dt) {
  setVelocity(cocos2d::Vec2(100,0));
}

void TiledNpc::moveUp(float dt) {
  setVelocity(cocos2d::Vec2(0,100));
}

void TiledNpc::moveDown(float dt) {
  setVelocity(cocos2d::Vec2(0,-100));
}
