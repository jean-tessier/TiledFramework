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
  float baseSpeed = 300; // this should be a constant somewhere...
  float xVelo = 0;
  float yVelo = 0;

  if( !(_moveLeft && _moveRight) && (_moveLeft || _moveRight) ) {
    xVelo = _moveLeft ? -1 : 1;
  }
  if( !(_moveUp && _moveDown) && (_moveUp || _moveDown) ) {
    yVelo = _moveDown ? -1 : 1;
  }

  if(xVelo != 0 && yVelo != 0) {
    baseSpeed = baseSpeed/2.0;
  }

  setVelocityX(xVelo * baseSpeed);
  setVelocityY(yVelo * baseSpeed);

  TiledCharacter::update(dt);
}
