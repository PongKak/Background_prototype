#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	winSize = Director::getInstance()->getWinSize();


	listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	map = TMXTiledMap::create("untitled.tmx");
	CCTMXObjectGroup* objectGroup = map->getObjectGroup("Object Layer 1");
	
	


	map->setTag(2);
	mapSize = map->getMapSize();
	tileSize = map->getContentSize();
	this->addChild(map);

	

	auto objectStart = objectGroup->getObject("Start");
	

	float x = objectStart["x"].asFloat();
	float y = objectStart["y"].asFloat();

	Sprite* sprite = Sprite::create("Pea.png");

	sprite->setPosition(x, y);
	sprite->setTag(0);
	this->addChild(sprite);


	isLeft = false;
	isRight = false;
	isUp = false;
	isDown = false;


	this->scheduleUpdate();


	return true;
}



void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	
	CCLOG("onKeyPressed : %d", keyCode);

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		isLeft = true;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		isRight = true;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		isDown = true;
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		isUp = true;
		break;
	default:
		break;
	}




}
void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		isLeft = false;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		isRight = false;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		isDown = false;
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		isUp = false;
		break;
	default:
		break;
	}
}

void HelloWorld::update(float fDelta)
{
	Node* pea = this->getChildByTag(0);
	Sprite* sprite = (Sprite*)this->getChildByTag(1);
	Vec2 position = pea->getPosition();
	map = (TMXTiledMap*)this->getChildByTag(2);

	float peaX, peaY;
	peaX = pea->getPosition().x;
	peaY = pea->getPosition().y;

	float backX, backY;
	backX = backgroundX;
	backY = backgroundY;

	wall = map->layerNamed("Wall");

	int tileGid;

	CCPoint tileCoord;
	



	if (isLeft)
	{
		if (backX < 0 && peaX <= winSize.width / 2)
		{

			backX += MAP_MOVE_SPEED;
			
		}
		else
		{
			if(backX > 0)
			{
				backX = 0;
			}
			
			peaX -= TAG_MOVE_SPEED;
			if (peaX < 32)
			{
				peaX += TAG_MOVE_SPEED;
			}

		}

	}

	if (isRight)
	{
		if (backX > -(mapSize.width * 32 - winSize.width)  && peaX >= winSize.width / 2)
		{
			backX -= MAP_MOVE_SPEED;
		}
		else
		{
			if(backX <= -(mapSize.width*32 - winSize.width))
			{
				backX = -(mapSize.width * 32 - winSize.width);
			}
			
			peaX += TAG_MOVE_SPEED;

			if (peaX > winSize.width - 32)
			{
				peaX -= TAG_MOVE_SPEED;
			}
			
		}

	}

	if (isDown)
	{
		if (backY <  0 && peaY <= winSize.height / 2)
		{
			backY += MAP_MOVE_SPEED;
		}
		else
		{
			if(backY >= 0 )
			{
				backY = 0;
			}

			peaY -= TAG_MOVE_SPEED;
			if (peaY < 32)
			{
				peaY += TAG_MOVE_SPEED;
			}


		}
	}

	if(isUp)
	{
		if (backY > -(mapSize.height * 32 - winSize.height) && peaY >= winSize.height /2)
		{
			backY -= MAP_MOVE_SPEED;
		}
		else
		{
			if(backY <= -(mapSize.height * 32 - winSize.height))
			{
				backY = -(mapSize.height * 32 - winSize.height);
			}

			peaY += TAG_MOVE_SPEED;
			if (peaY > winSize.height - 32)
			{
				peaY -= TAG_MOVE_SPEED;
			}


		}
		

		
	}

	/*
	
	if (isLeft)
	{
		if (backgroundX < 0 && pea->getPositionX() <= winSize.width / 2)
		{

			backgroundX += MAP_MOVE_SPEED;
			
		}
		else
		{
			if(backgroundX>0)
			{
				backgroundX = 0;
			}
			pea->setPosition(pea->getPosition() + Vec2(-TAG_MOVE_SPEED, 0));

			if (pea->getPositionX() < 32)
			{
				pea->setPosition(pea->getPosition() + Vec2(TAG_MOVE_SPEED, 0));
			}

		}

	}
	
	if (isRight)
	{
		if (backgroundX > -(mapSize.width * 32 - winSize.width)  && pea->getPositionX() >= winSize.width / 2)
		{
			backgroundX -= MAP_MOVE_SPEED;
		}
		else
		{
			if(backgroundX <= -(mapSize.width*32 - winSize.width))
			{
				backgroundX = -(mapSize.width * 32 - winSize.width);
			}
			pea->setPosition(pea->getPosition() + Vec2(TAG_MOVE_SPEED, 0));

			if (pea->getPositionX() > winSize.width - 32)
			{
				pea->setPosition(pea->getPosition() + Vec2(-TAG_MOVE_SPEED, 0));
			}

		}

	}
	
	if (isDown)
	{
		if (backgroundY <  0 && pea->getPositionY() <= winSize.height / 2)
		{
			backgroundY += MAP_MOVE_SPEED;
		}
		else
		{
			if(backgroundY >= 0 )
			{
				backgroundY = 0;
			}
			pea->setPosition(pea->getPosition() + Vec2(0, -TAG_MOVE_SPEED));
			if (pea->getPositionY() < 32)
			{
				pea->setPosition(pea->getPosition() + Vec2(0, +TAG_MOVE_SPEED));

			}


		}
	}

	if(isUp)
	{
		if (backgroundY > -(mapSize.height * 32 - winSize.height) && pea->getPositionY() >= winSize.height /2)
		{
			backgroundY -= MAP_MOVE_SPEED;
		}
		else
		{
			if(backgroundY <= -(mapSize.height * 32 - winSize.height))
			{
				backgroundY = -(mapSize.height * 32 - winSize.height);
			}
			pea->setPosition(pea->getPosition() + Vec2(0, +TAG_MOVE_SPEED));
			if (pea->getPositionY() > winSize.height - 32)
			{
				pea->setPosition(pea->getPosition() + Vec2(0, -TAG_MOVE_SPEED));
			}


		}
		

		
	}*/

	map->setPosition(Vec2(backX, backY));
	pea->setPosition(Vec2(peaX, peaY));


}

CCPoint HelloWorld::tileCoordForPosition(CCPoint position)
{
	int x = position.x / map->getTileSize().width;
	int y = ((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height;

	return ccp(x, y);

}