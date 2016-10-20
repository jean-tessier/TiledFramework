#include "Drawable.h"

bool Drawable::collidesWith(const Drawable* drawable) const {
  int width = _sprite->getContentSize().width;
  int height = _sprite->getContentSize().height;
  int oWidth = drawable->getSprite()->getContentSize().width;
  int oHeight = drawable->getSprite()->getContentSize().height;

  cocos2d::Point pos = _sprite->getPosition();
  cocos2d::Point oPos = drawable->getPosition();

  if( pos.x+width/2 < oPos.x-oWidth/2) return false;
  if( pos.x-width/2 > oPos.x+oWidth/2) return false;
  if( pos.y-height/2 > oPos.y+oHeight/2) return false;
  if( pos.y+height/2 < oPos.y-oHeight/2) return false;

  return true;
}

const cocos2d::Node* Drawable::getNode() const {
  return _sprite;
}

void Drawable::retain() {
  _sprite->retain();
}

void Drawable::release() {
  _sprite->release();
}
