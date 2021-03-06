#ifndef HELLOWORLD_SCENE_H
#define HELLOWORLD_SCENE_H

#include <list>
#include "cocos2d.h"
#include "Drawable.h"
#include "SimpleAudioEngine.h"

class Game : public cocos2d::Layer
{
  public:
    Game();
    static Game* create();
    static cocos2d::Scene* createScene();

    virtual bool init();
      
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

  private:
    // Fix constructors for additions here...
    CocosDenshion::SimpleAudioEngine* _audio;
    cocos2d::Layer* _worldLayer;
    cocos2d::Layer* _uiLayer;
    cocos2d::Label* _scorelabel;
    std::list<Drawable*> _drawables;
    std::list<Drawable*> _freeables;
    int _score;
    unsigned int _soundID[15];
    unsigned int _soundIDIdx = 0;
    unsigned int _soundCount = 0;
    //Drawable* _drawables[2];

    void update(float dt);
};

#endif // __HELLOWORLD_SCENE_H__
