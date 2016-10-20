#include "TileMap.h"

TileMap::TileMap(const std::string& path) {
	_tileMap = cocos2d::TMXTiledMap::create(path);

  _meta = _tileMap->getLayer("meta");
	_meta->setVisible(false);

  _objects = _tileMap->getObjectGroup("Objects");
}

cocos2d::TMXTiledMap* TileMap::getMap() const {
  return _tileMap;
}

cocos2d::TMXLayer* TileMap::getMetaLayer() const {
	return _meta;
}

const cocos2d::TMXObjectGroup* TileMap::getObjects() const {
	return _objects;
}

cocos2d::Point TileMap::tileCoordAt(const cocos2d::Point& pos) const{
  int x = pos.x / _tileMap->getTileSize().width;
  int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().height;

  cocos2d::Point coord = cocos2d::Point((float)x, (float)y);

  return coord;
}

// void TileMap::setViewPointCenter(cocos2d::Point newCenter){
// 	cocos2d::Size winSize = cocos2d::Director::sharedDirector()->getWinSize();
// 
//   int x = MAX(newCenter.x, winSize.width/2);
//   int y = MAX(newCenter.y, winSize.height/2);
//   x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
//   y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height/2);
//   cocos2d::Point actualPosition = cocos2d::ccp(x, y);
// 
//   cocos2d::Point centerOfView = cocos2d::ccp(winSize.width/2, winSize.height/2);
//   cocos2d::Point viewPoint = cocos2d::ccpSub(centerOfView, actualPosition);
//   _parent->setPosition(viewPoint);
// }

bool TileMap::collidable(cocos2d::Point pos) const {
  cocos2d::Point tileCoord = tileCoordAt(pos);
  unsigned int gid = _meta->getTileGIDAt(tileCoord);

  if(gid) {
    cocos2d::ValueMap properties = _tileMap->getPropertiesForGID(gid).asValueMap();

    if(!properties.empty()) {
      std::string collision = properties["Collidable"].asString();

      if("True" == collision) {
          return true;
      }
    }
  }

  return false;
}

void TileMap::setPosition(const cocos2d::Point& pos) {
  _tileMap->setPosition(pos);
}
