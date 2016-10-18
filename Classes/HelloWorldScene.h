#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

#define TAG_MOVE_SPEED	5
#define MAP_MOVE_SPEED  16


class HelloWorld : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();


	CREATE_FUNC(HelloWorld);

	Size winSize;
	Size mapSize;
	Size tileSize;

	bool isLeft;
	bool isRight;
	bool isDown;
	bool isUp;
	float backgroundX = 0.0f;
	float backgroundY = 0.0f;

	EventListenerKeyboard* listener;
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	void update(float fDelta);

	TMXTiledMap* map;
	TMXLayer *wall;

	CCPoint tileCoordForPosition(CCPoint position);
};

#endif  __HELLOWORLD_SCENE_H__
