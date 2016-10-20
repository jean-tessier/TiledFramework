#ifndef TCHAR_H
#define TCHAR_H

#include "cocos2d.h"
#include "Drawable.h"
#include "TileMap.h"

class TiledCharacter : public Drawable {
  public:
    TiledCharacter(const std::string& path, TileMap* map);

    virtual void update(float dt);

    void setVelocity(const cocos2d::Vec2& velo) { _velocity = velo; }
    void setVelocityX(float x) { _velocity.x = x; }
    void setVelocityY(float y) { _velocity.y = y; }

  private:
    TileMap* _collisionTileMap;
    cocos2d::Vec2 _velocity;

    TiledCharacter() { }
};

#endif
