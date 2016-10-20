#ifndef TPLAYER_H
#define TPLAYER_H

#include <string>

#include "cocos2d.h"
#include "TiledCharacter.h"
#include "TileMap.h"

class TiledPlayer : public TiledCharacter {
  public:
    TiledPlayer(const std::string& path, TileMap* map) :
      TiledCharacter(path, map),
      _moveLeft(false),
      _moveRight(false),
      _moveUp(false),
      _moveDown(false)
    { init(); }

    void update(float dt);

  private:
    bool _moveLeft,
         _moveRight,
         _moveUp,
         _moveDown;

    void init();
};

#endif
