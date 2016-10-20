#include "cocos2d.h"
#include "Game.h"
#include "TileMap.h"
#include "TiledPlayer.h"
#include "TiledNpc.h"

Game::Game() :
  _worldLayer(cocos2d::Layer::create()),
  _uiLayer(cocos2d::Layer::create()),
  _drawables(),
  score(0)
{ }

//Game::Game() :
//  _worldLayer(cocos2d::Layer::create()),
//  _uiLayer(cocos2d::Layer::create()),
//  _drawables(std::list<Drawable*>())

Game* Game::create() {
  Game* game = new Game();

  if(game && game->init()) {
    game->autorelease();
    return game;
  }

  CC_SAFE_DELETE(game);
  return NULL;
}

cocos2d::Scene* Game::createScene()
{
  cocos2d::Scene* scene = cocos2d::Scene::create();
  cocos2d::Layer* layer = Game::create();

  scene->addChild(layer);

  return scene;
}

// on "init" you need to initialize your instance
bool Game::init()
{
  if ( !Layer::init() )
  {
      return false;
  }

  audio = CocosDenshion::SimpleAudioEngine::getInstance();
  audio->preloadEffect("sounds/pop.wav");
  
  cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
  cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

  cocos2d::MenuItemImage* closeItem = cocos2d::MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(Game::menuCloseCallback, this));
    
	closeItem->setPosition(cocos2d::Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

  // create menu, it's an autorelease object
  cocos2d::Menu* menu = cocos2d::Menu::create(closeItem, NULL);
  menu->setPosition(cocos2d::Vec2::ZERO);
  _uiLayer->addChild(menu, 1);

  /////////////////////////////
  // 3. add your codes below...
  cocos2d::Label* _label = cocos2d::Label::createWithTTF("Pop the Jigglybits! -- Jean Tessier", "fonts/Marker Felt.ttf", 24);
    
  // position the label on the center of the screen
  _label->setPosition(cocos2d::Vec2(origin.x + visibleSize.width/2,
                          origin.y + visibleSize.height - _label->getContentSize().height));

  _scorelabel = cocos2d::Label::createWithTTF(std::to_string(score), "fonts/Marker Felt.ttf", 24);
  _scorelabel->setPosition(cocos2d::Vec2(925,24));

  _uiLayer->addChild(_label, 1);
  _uiLayer->addChild(_scorelabel,1);

  //This TileMap currently leaks...
  TileMap* tm = new TileMap("tilemaps/map.tmx");
  TiledPlayer* tc = new TiledPlayer("sprites/cootiedjigglybit.png", tm);
  tc->setPosition(cocos2d::Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
  // player will (for now) always be first
  _drawables.push_back(tc);
  // add to layers
  _worldLayer->addChild(tm->getMap(), 0);
  _worldLayer->addChild(tc->getSprite(), 0);

  for(int i=0;i<250;++i) {
    TiledNpc* npc = new TiledNpc("sprites/jigglybit.png", tm);
    npc->setPosition(cocos2d::Vec2(rand()%824+100, rand()%568+100));
    npc->setMode(2);
    npc->track(tc);
    _drawables.push_back(npc);
    _worldLayer->addChild(npc->getSprite(), 0);
  }

  // add layers to game
  addChild(_worldLayer, 0);
  addChild(_uiLayer, 1);

  schedule(schedule_selector(Game::update));
    
  return true;
}

void Game::update(float dt) {
  std::list<Drawable*>::iterator iter;
  std::list<Drawable*>::iterator player;

  player = _drawables.begin();
  (*player)->update(dt);
  iter = player;
  ++iter;

  while(iter != _drawables.end()) {
    (*iter)->update(dt);
    if((*iter)->collidesWith((*player))) {

      cocos2d::ParticleExplosion* emitter = cocos2d::ParticleExplosion::create();
      emitter->retain();
      _worldLayer->addChild(emitter,10);
      emitter->setTexture( cocos2d::Director::getInstance()->getTextureCache()->addImage("sprites/jigglybit.png"));
      emitter->setAutoRemoveOnFinish(true);
      emitter->setPosition((*iter)->getSprite()->getPosition());
      emitter->setLife(1.5);
      emitter->setLifeVar(0.75);
      
      if(soundCount < 15) {
        soundID[soundIDIdx++] = audio->playEffect("sounds/pop.wav");
        ++soundCount;
      }
      else {
        soundIDIdx = (soundIDIdx+1)%15;
        soundID[soundIDIdx] = audio->playEffect("sounds/pop.wav");
        audio->stopEffect(soundID[soundIDIdx+1]);
      }

      (*iter)->getSprite()->retain();
      _worldLayer->removeChild((*iter)->getSprite());
      iter = _drawables.erase(iter);
      score+=100;
    }
    else ++iter;
  }
  _scorelabel->setString(std::to_string(score));
}

void Game::menuCloseCallback(Ref* pSender)
{
  //std::list<Drawable*>::iterator iter;
  //
  //for(iter = _drawables.begin(); iter != _drawables.end(); ++iter) { 
  //  delete (*iter);
  //}
  cocos2d::Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  exit(0);
#endif
}
