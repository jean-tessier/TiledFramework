#ifndef TILEMAP_H
#define TILEMAP_H

#include "cocos2d.h"
#include <string>

class TileMap
{

	public:
		//CONSTRUCTOR -- loads tilemap, sets meta layer not visible
		//TileMap(std::string mapPath, cocos2d::Layer* parent);
    TileMap(const std::string& mapPath);

		//Tile Methods
		bool tileIsCollidableAt (const cocos2d::Point& pos) const;
		bool collidable (cocos2d::Point pos) const;
		cocos2d::Point tileCoordAt(const cocos2d::Point& pos) const;
		
    cocos2d::TMXTiledMap* getMap() const;
		cocos2d::TMXLayer* getMetaLayer() const;
		const cocos2d::TMXObjectGroup* getObjects() const;

    void setPosition(const cocos2d::Point& pos);

  private:
		cocos2d::TMXTiledMap* _tileMap;
		cocos2d::TMXLayer* _meta;
    cocos2d::TMXObjectGroup* _objects;
};

		
#endif // TILEMAP_H
