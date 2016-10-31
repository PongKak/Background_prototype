#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

#define TAG_MOVE_SPEED	  5
#define MAP_MOVE_SPEED  5
#define WALL			32

#define TILEMAP_NAME "untitled.tmx"
#define MAP_TYLENAME "Tile Layer 1"
#define MAP_OBJECTLAYER "Object Layer 1"
#define Start_Object "Start"
#define CHARACTER_NAME "pea.png"
#define COLLIDABLE "Collidable"


class HelloWorld : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();


	CREATE_FUNC(HelloWorld);

	Size winSize;
	Size mapSize;
	Size tileSize;

	bool isLeft = false;
	bool isRight = false;
	bool isDown = false;
	bool isUp = false;
	float backgroundX = 0.0f;
	float backgroundY = 0.0f;
	//Vec2 background = Vec2(backgroundX, backgroundY);

	EventListenerKeyboard* listener;
	

	CCTMXTiledMap* map = nullptr;
	CCTMXLayer* background = nullptr;
	CCTMXLayer* metaInfo = nullptr;
	



	CCLabelTTF* xNowLabel = CCLabelTTF::create(" ", "Thonburi", 32);
	CCLabelTTF* yNowLabel = CCLabelTTF::create(" ", "Thonburi", 32);



	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void update(float fDelta);
	bool IsWall(CCPoint position);
	CCPoint tileCoordForPosition(CCPoint position);
	Vec2 setCharacterPosition(Vec2 Position, Vec2 moveVec);
	bool backgroundMove(void);
	bool characterMove(Vec2 position);
};

#endif  __HELLOWORLD_SCENE_H__
