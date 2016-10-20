#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include "cocos2d.h"

class Drawable
{
	public:
    Drawable() : _sprite() { }
    Drawable(const std::string& path) :
      _sprite(cocos2d::Sprite::create(path))
    { }
    Drawable(const Drawable& draw) :
      _sprite(draw._sprite)
    { }

    //virtual void update(float dt) { CCLOG("%s", "DRAW"); }
    virtual void update(float dt) = 0;
    virtual bool collidesWith(const Drawable* drawable) const;

    const cocos2d::Node* getNode() const;
    cocos2d::Sprite* getSprite() const { return _sprite; }
    //cocos2d::Vec2 getVelo() const { return _velocity; }

    void createSprite(const std::string& path) { _sprite = cocos2d::Sprite::create(path); }

    void retain();
    void release();

		void setPosition(const cocos2d::Point& pt) { _sprite->setPosition(pt); }
		//cocos2d::Point	getPosition();

		cocos2d::Rect	getBoundingBox() const { return _sprite->getTextureRect(); }
    cocos2d::Point getPosition() const { return _sprite->getPosition(); }
		//cocos2d::Size	getContentSize();

		//Now for the fun methods
		//cocos2d::Point	moveFrom(cocos2d::Point);
		//cocos2d::Point	moveToward(cocos2d::Point);
		//cocos2d::Point	moveLeft();
		//cocos2d::Point	moveRight();
		//cocos2d::Point	moveUp();
		//cocos2d::Point	moveDown();


	private:
		cocos2d::Sprite* _sprite;
};

#endif
