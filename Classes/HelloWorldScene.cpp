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


	map = CCTMXTiledMap::create(TILEMAP_NAME);
	background = map->layerNamed(MAP_TYLENAME);
	CCTMXObjectGroup* objectGroup = map->getObjectGroup(MAP_OBJECTLAYER);
	//metaInfo = map->layerNamed("MetaInfo");
//	metaInfo->setVisible(false);
	
	map->setTag(2);
	mapSize = map->getMapSize();
	tileSize = map->getContentSize();
	this->addChild(map);


	

	auto objectStart = objectGroup->getObject(Start_Object);
	

	float x = objectStart["x"].asFloat();
	float y = objectStart["y"].asFloat();

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




	Sprite* sprite = Sprite::create(CHARACTER_NAME);



	sprite->setPosition(x, y);
	sprite->setTag(0);
	this->addChild(sprite);


	Rect rectSpr = sprite->getBoundingBox();

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
	Vec2 moveVec = Vec2(0,0);
	bool movable = false;

	std::string xPosition = "";
	std::string yPosition = "";
	char buffer[100];

	
	if (isLeft)
	{		
		moveVec.add(Vec2(-1, 0));
	}
	else if (isRight)
	{	
		moveVec.add(Vec2(1, 0));
	}
	
	if (isDown)
	{
		moveVec.add(Vec2(0, -1));
	}
	else if(isUp)
	{
		moveVec.add(Vec2(0, 1));
	}

	movable = IsWall(position + moveVec * 16);

	if (movable == true && moveVec != Vec2(0,0))
	{
		position = setCharacterPosition(position, moveVec);
	}

	/*
	

	if (isLeft)
	{
	position = position - Vec2(16, 0);
	movable = IsWall(position);
	if (movable == false)
	{
	map->setPosition(Vec2(backgroundX, backgroundY));
	pea->setPosition(Vec2(peaX, peaY));

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
	map->setPosition(Vec2(backgroundX, backgroundY));
	pea->setPosition(Vec2(peaX, peaY));
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
	map->setPosition(Vec2(backgroundX, backgroundY));
	pea->setPosition(Vec2(peaX, peaY));
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
	map->setPosition(Vec2(backgroundX, backgroundY));
	pea->setPosition(Vec2(peaX, peaY));
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
	*/

	
	map->setPosition(Vec2(backgroundX, backgroundY));
	pea->setPosition(position);

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

		String propertyValue = vmap[COLLIDABLE].asString();
		if (propertyValue.compare("True") == 0)
		{
			return false;
		}
	}
	return true;


}

Vec2 HelloWorld::setCharacterPosition(Vec2 position, Vec2 moveVec)
{
	bool backMoveX = false;
	bool backMoveY = false;
	
	if (moveVec.x < 0)
	{
		if (backgroundX < 0 && position.x <= winSize.width / 2)
		{
			backgroundX += MAP_MOVE_SPEED;
			backMoveX = true;
		}
		else
		{
			if (backgroundX > 0)
			{
				backgroundX = 0;
			}
			moveVec.add(Vec2(-TAG_MOVE_SPEED, 0));
			if (position.x - TAG_MOVE_SPEED < 32)
			{
				moveVec.x = 0;
			}
		}

	}
	else if (moveVec.x > 0)
	{
		if (backgroundX > -(mapSize.width * 32 - winSize.width) && position.x >= winSize.width / 2)
		{
			backgroundX -= MAP_MOVE_SPEED;
			backMoveX = true;
		}
		else
		{
			if (backgroundX <= -(mapSize.width * 32 - winSize.width))
			{
				backgroundX = -(mapSize.width * 32 - winSize.width);
			}
			moveVec.add(Vec2(TAG_MOVE_SPEED, 0));
			if (position.x+ TAG_MOVE_SPEED > winSize.width - 32)
			{
				moveVec.x = 0;
			}
		}
	}

	if (moveVec.y < 0)
	{
		if (backgroundY < 0 && position.y <= winSize.height / 2)
		{
			backgroundY += MAP_MOVE_SPEED;
			backMoveY = true;
		}
		else
		{
			if (backgroundY >= 0)
			{
				backgroundY = 0;
			}
			moveVec.add(Vec2(0,-TAG_MOVE_SPEED));
			if (position.y - TAG_MOVE_SPEED < 32)
			{
				moveVec.y = 0;
			}
		}
	}
	else if(moveVec.y > 0)
	{
		if (backgroundY > -(mapSize.height * 32 - winSize.height) && position.y >= winSize.height / 2)
		{
			backgroundY -= MAP_MOVE_SPEED;
			backMoveY = true;
		}
		else
		{
			if (backgroundY <= -(mapSize.height * 32 - winSize.height))
			{
				backgroundY = -(mapSize.height * 32 - winSize.height);
			}
			moveVec.add(Vec2(0, TAG_MOVE_SPEED));
			if (position.y + TAG_MOVE_SPEED > winSize.height - 32)
			{
				moveVec.y=0;
			}
		}
	}
	/*
	if (moveVec.x < 0)
	{
		if (backgroundMove() && position.x <= winSize.width / 2)
		{
			backgroundX += MAP_MOVE_SPEED;
			backMoveX = true;
			if (backgroundX > 0)
			{
				backgroundX = 0;


			}
		}
		else
		{
			
			moveVec.add(Vec2(-TAG_MOVE_SPEED, 0));
			if (position.x - TAG_MOVE_SPEED < 32)
			{
				moveVec.x = 0;
			}
		}

	}
	else if (moveVec.x > 0)
	{
		if (backgroundMove() && position.x >= winSize.width / 2)
		{
			backgroundX -= MAP_MOVE_SPEED;
			backMoveX = true;
			if (backgroundX <= -(mapSize.width * 32 - winSize.width))
			{
				backgroundX = -(mapSize.width * 32 - winSize.width);
	
			}
		}
		else
		{
			
			moveVec.add(Vec2(TAG_MOVE_SPEED, 0));
			if (position.x+ TAG_MOVE_SPEED > winSize.width - 32)
			{
				moveVec.x = 0;
			}
		}
	}

	if (moveVec.y < 0)
	{
		if (backgroundMove() && position.y <= winSize.height / 2)
		{
			backgroundY += MAP_MOVE_SPEED;
			backMoveY = true;

			if (backgroundY >= 0)
			{
				backgroundY = 0;
			}
		}
		else
		{
			moveVec.add(Vec2(0,-TAG_MOVE_SPEED));
			if (position.y - TAG_MOVE_SPEED < 32)
			{
				moveVec.y = 0;
			}
		}
	}
	else if(moveVec.y > 0)
	{
		if (backgroundMove() && position.y >= winSize.height / 2)
		{
			backgroundY -= MAP_MOVE_SPEED;
			backMoveY = true;

			if (backgroundY <= -(mapSize.height * 32 - winSize.height))
			{
				backgroundY = -(mapSize.height * 32 - winSize.height);
	
			}
		}
		else
		{
			moveVec.add(Vec2(0, TAG_MOVE_SPEED));
			if (position.y + TAG_MOVE_SPEED > winSize.height - 32)
			{
				moveVec.y=0;
			}
		}
	}*/



	if (backMoveX && backMoveY )
	{
		return position;
	}
	return position + moveVec;
}

bool HelloWorld::backgroundMove()
{
	if ((backgroundX <= 0 &&	backgroundX  >= -(mapSize.width * 32 - winSize.width)) &&
		(backgroundY <= 0 &&	backgroundY  >= -(mapSize.height * 32 - winSize.height))
		)
	{
		return true;
	}
	return false;

}
bool HelloWorld::characterMove(Vec2 position)
{
	if (position.x != winSize.width / 2 ||
		position.y != winSize.height / 2)
	{
		return true;
	}
	return false;
}