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


	map = CCTMXTiledMap::create("untitled.tmx");
	background = map->layerNamed("Tile Layer 1");
	CCTMXObjectGroup* objectGroup = map->getObjectGroup("Object Layer 1");
	//metaInfo = map->layerNamed("MetaInfo");
//	metaInfo->setVisible(false);
	
	map->setTag(2);
	mapSize = map->getMapSize();
	tileSize = map->getContentSize();
	this->addChild(map);


	

	auto objectStart = objectGroup->getObject("Start");
	

	float x = objectStart["x"].asFloat();
	float y = objectStart["y"].asFloat() +4;

	char pointX[]  = "X:";
	char pointY[] = "Y:";
	CCLabelTTF* xLabel = CCLabelTTF::create(pointX, "Thonburi", 32);

	xLabel->setPosition(100, 150);
	xLabel->setColor(ccc3(0, 0, 0));
	xLabel->setOpacity(100.0);
	this->addChild(xLabel);

	xNowLabel->setPosition(200, 150);
	xNowLabel->setColor(ccc3(0, 0, 0));
	xNowLabel->setOpacity(100.0);
	this->addChild(xNowLabel);


	CCLabelTTF* yLabel = CCLabelTTF::create(pointY, "Thonburi", 32);
	yLabel->setPosition(100, 100);
	yLabel->setColor(ccc3(0, 0, 0));
	yLabel->setOpacity(100.0);
	this->addChild(yLabel);
	

	yNowLabel->setPosition(200, 100);
	yNowLabel->setColor(ccc3(0, 0, 0));
	yNowLabel->setOpacity(100.0);
	this->addChild(yNowLabel);




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
	bool movable = true;

	std::string xPosition = "";
	std::string yPosition = "";
	char buffer[100];

	float peaX = pea->getPosition().x;
	float peaY = pea->getPosition().y;


	
	map->setPosition(Vec2(backgroundX, backgroundY));
	pea->setPosition(Vec2(peaX, peaY));



	xPosition += itoa((int)(-backgroundX + pea->getPositionX()), buffer, 10);
	xNowLabel->setString(xPosition);

	yPosition += itoa((int)(-backgroundY + pea->getPositionY()), buffer, 10);
	yNowLabel->setString(yPosition);
	
	
	
	if (isLeft)
	{
		position = position - Vec2(16, 0);
		movable = IsWall(position);
		if (movable == false)
		{
			return;
		}

		if (backgroundX < 0 && peaX <= winSize.width / 2)
		{

			backgroundX += MAP_MOVE_SPEED;
			
		}
		else
		{
			if(backgroundX>0)
			{
				backgroundX = 0;
			}
			peaX -=TAG_MOVE_SPEED;

			if (peaX < 32)
			{
				peaX += TAG_MOVE_SPEED;
			}

		}

	}
	
	if (isRight)
	{
		position = position + Vec2(16, 0);
		movable = IsWall(position);
		if (movable == false)
		{
			return;
		}

		if (backgroundX > -(mapSize.width * 32 - winSize.width)  && peaX >= winSize.width / 2)
		{
			backgroundX -= MAP_MOVE_SPEED;
		}
		else
		{
			if(backgroundX <= -(mapSize.width*32 - winSize.width))
			{
				backgroundX = -(mapSize.width * 32 - winSize.width);
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
		position = position + Vec2(0, -16);
		movable = IsWall(position);
		if (movable == false)
		{
			return;
		}
		if (backgroundY <  0 && peaY <= winSize.height / 2)
		{
			backgroundY += MAP_MOVE_SPEED;
		}
		else
		{
			if(backgroundY >= 0 )
			{
				backgroundY = 0;
			}
			peaY -= TAG_MOVE_SPEED;
			if (peaY < 32)
			{
				peaY += TAG_MOVE_SPEED;;

			}


		}
	}

	if(isUp)
	{
		position = position + Vec2(0, 16);
		movable = IsWall(position);
		if (movable == false)
		{
			return;
		}

		if (backgroundY > -(mapSize.height * 32 - winSize.height) && peaY >= winSize.height /2)
		{
			backgroundY -= MAP_MOVE_SPEED;
		}
		else
		{
			if(backgroundY <= -(mapSize.height * 32 - winSize.height))
			{
				backgroundY = -(mapSize.height * 32 - winSize.height);
			}
			peaY += TAG_MOVE_SPEED;
			if (peaY > winSize.height - 32)
			{
				peaY -= TAG_MOVE_SPEED;;
			}


		}
		

		
	}

	/*
	
	if (isLeft)
	{
		position = position - Vec2(5, 0);
		movable = IsWall(position);
		if (movable == false)
		{
			return;
		}

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
		position = position + Vec2(5, 0);
		movable = IsWall(position);
		if (movable == false)
		{
			return;
		}

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
		position = position + Vec2(0, -5);
		movable = IsWall(position);
		if (movable == false)
		{
			return;
		}
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
		position = position + Vec2(0, 5);
		movable = IsWall(position);
		if (movable == false)
		{
			return;
		}

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
		

		
	}
	
	map->setPosition(Vec2(backgroundX, backgroundY));
	*/


	
	map->setPosition(Vec2(backgroundX, backgroundY));
	pea->setPosition(Vec2(peaX, peaY));

	xPosition = "";
	xPosition += itoa((int)(-backgroundX + pea->getPositionX()), buffer , 10);
	xNowLabel->setString(xPosition);
	
	yPosition = "";
	yPosition += itoa((int)(-backgroundY + pea->getPositionY()), buffer, 10);
	yNowLabel->setString(yPosition);	

	

}

CCPoint HelloWorld::tileCoordForPosition(CCPoint position)
{
	int x = position.x / map->getTileSize().width;
	int y = ((map->getMapSize().height*map->getTileSize().height) - position.y) / map->getTileSize().height;

	return ccp(x, y);

}

bool HelloWorld::IsWall(CCPoint position)
{
	position -= Vec2(backgroundX,backgroundY);
	CCPoint tileCoord = tileCoordForPosition(position);
	unsigned int tileGid = background->tileGIDAt(tileCoord);
	
	if (tileGid == WALL)
	{
		auto properties = map->propertiesForGID(tileGid);

		ValueMap vmap = properties.asValueMap();

		String propertyValue = vmap["Collidable"].asString();
		if (propertyValue.compare("True") == 0)
		{
			return false;
		}
	}
	return true;


}

Vec2 HelloWorld::setCharacterPosition(Vec2 position, Vec2 moveVec)
{
	return position;
}



/*
if (isRight)
{
	position = position + Vec2(5, 0);
	movable = IsWall(position);
	if (movable == false)
	{
		return;
	}

	if (backgroundX > -(mapSize.width * 32 - winSize.width) && peaX >= winSize.width / 2)
	{
		backgroundX -= MAP_MOVE_SPEED;
	}
	else
	{
		if (backgroundX <= -(mapSize.width * 32 - winSize.width))
		{
			backgroundX = -(mapSize.width * 32 - winSize.width);
		}
		peaX += TAG_MOVE_SPEED;

		if (peaX > winSize.width - 32)
		{
			peaX -= TAG_MOVE_SPEED;
		}

	}

}
*/