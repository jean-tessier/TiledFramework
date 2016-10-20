#include "TiledPlayer.h"

void TiledPlayer::init() {
  cocos2d::EventListenerKeyboard* kbListener = cocos2d::EventListenerKeyboard::create();

  kbListener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch(keyCode) {
      case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
      case cocos2d::EventKeyboard::KeyCode::KEY_A:
        _moveLeft = true;
        break;
      case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
      case cocos2d::EventKeyboard::KeyCode::KEY_D:
        _moveRight = true;
        break;
      case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
      case cocos2d::EventKeyboard::KeyCode::KEY_W:
        _moveUp = true;
        break;
      case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
      case cocos2d::EventKeyboard::KeyCode::KEY_S:
        _moveDown = true;
        break;
      default:
       break;
    }
  };

  kbListener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch(keyCode) {
      case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	    case cocos2d::EventKeyboard::KeyCode::KEY_A:
	      _moveLeft = false;
	      break;
      case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	    case cocos2d::EventKeyboard::KeyCode::KEY_D:
	      _moveRight = false;
	      break;
      case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
	    case cocos2d::EventKeyboard::KeyCode::KEY_W:
	      _moveUp = false;
	      break;
      case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
      case cocos2d::EventKeyboard::KeyCode::KEY_S:
        _moveDown = false;
        break;
	    default:
	      break;
    }
  };

  cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(kbListener, 1);
}

void TiledPlayer::update(float dt) {
  if(!_moveLeft && !_moveRight) {
    setVelocityX(0);
  }
  if(_moveLeft && !_moveRight) {
    setVelocityX(-300);
  }
  if(!_moveLeft && _moveRight) {
    setVelocityX(300);
  }
  if(!_moveUp && ! _moveDown) {
    setVelocityY(0);
  }
  if(_moveUp && ! _moveDown) {
    setVelocityY(300);
  }
  if(!_moveUp &&  _moveDown) {
    setVelocityY(-300);
  }

  TiledCharacter::update(dt);
}
