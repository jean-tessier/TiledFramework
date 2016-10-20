#include "TiledCharacter.h"

TiledCharacter::TiledCharacter(const std::string& path, TileMap* map) :
  Drawable(path),
  _collisionTileMap(map),
  _velocity(0.0f,0.0f)
{
}

void TiledCharacter::update(float dt) {
  cocos2d::Vec2 incr = _velocity * dt;
  cocos2d::Point incrPt = cocos2d::Point(incr.x, incr.y);
  cocos2d::Point tileCoord = _collisionTileMap->tileCoordAt(getPosition()+incrPt);
  unsigned int gid = _collisionTileMap->getMetaLayer()->getTileGIDAt(tileCoord);

  if(gid) {
    cocos2d::ValueMap properties = _collisionTileMap->getMap()->getPropertiesForGID(gid).asValueMap(); 
    if(!properties.empty()) {
      std::string collision = properties.at("Collidable").asString();
      if(!collision.empty() && collision.compare("True") == 0) {
        _velocity.x = 0;
        _velocity.y = 0;
        incr = _velocity * dt;
      }
    }
  }

  setPosition(getPosition() + incr);
}
