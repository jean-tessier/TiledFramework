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
    cocos2d::Layer* _worldLayer;
    cocos2d::Layer* _uiLayer;
    std::list<Drawable*> _drawables;
    std::list<Drawable*> _freeables;
    int score;
    cocos2d::Label* _scorelabel;
    CocosDenshion::SimpleAudioEngine* audio;
    unsigned int soundID[15];
    unsigned int soundIDIdx = 0;
    unsigned int soundCount = 0;
    //Drawable* _drawables[2];

    void update(float dt);
};

#endif // __HELLOWORLD_SCENE_H__
