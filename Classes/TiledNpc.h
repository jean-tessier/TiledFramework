#ifndef TILED_NPC_H
#define TILED_NPC_H

#include <string>

#include "cocos2d.h"
#include "TileMap.h"
#include "Drawable.h"
#include "TiledCharacter.h"

class TiledNpc : public TiledCharacter {
  public:
    TiledNpc(const std::string& path, TileMap* map);
    void update(float dt);
    void track(Drawable* tc) { _trackedDrawable = tc; }
    void setMode(unsigned int m) { _mode = m; }

  private:
    Drawable* _trackedDrawable;
    // mode 0: wander, mode 1: toward, mode 2: from
    unsigned int _mode;

    void wander(float dt);
    void moveLeft(float dt);
    void moveRight(float dt);
    void moveUp(float dt);
    void moveDown(float dt);
    void moveTowardTracked(float dt);
    void moveFromTracked(float dt);
};

#endif
