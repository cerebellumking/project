#include"InitialScene.h"
#include"enemy.h"
#include"safeScene.h"
#include<iostream>

int id_1;
float volume = 0.5;

Scene* initial_scene::createScene()
{
	return initial_scene::create();
}

/*错误处理*/
void initial_scene::problemLoading(const char* filename)
{
	std::cout << "Error while loading:" << filename<<std::endl;
	std::cout << "Depending on how you compiled you might have to add 'Resources/' in front of filenames "<<std::endl;
}

bool initial_scene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();       //可视区域尺寸
	Vec2 origin = Director::getInstance()->getVisibleOrigin();          //可视区域起点坐标
	auto* dispatcher = Director::getInstance()->getEventDispatcher();   //调度器
	auto* keyListener = EventListenerKeyboard::create();                //键盘监听器
	//创建一个事件监听器监听键盘事件
	keyListener->onKeyPressed = CC_CALLBACK_2(initial_scene::onKeyPressed, this);
	//键盘被按下时响应
	keyListener->onKeyReleased = CC_CALLBACK_2(initial_scene::onKeyReleased, this);
	//键盘按键被弹回时响应
	dispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
	auto scene_sprite = Sprite::create("windows\\initial scene1.png");
	if (scene_sprite == nullptr)
	{
		problemLoading("'initial scene1.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		scene_sprite->setScaleX(visibleSize.width / scene_sprite->getContentSize().width);
		scene_sprite->setScaleY(visibleSize.height / scene_sprite->getContentSize().height);
		scene_sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		// add the sprite as a child to this layer
		this->addChild(scene_sprite, 1, 121);
	}


	/*背景音乐*/
	id_1 = AudioEngine::play2d("home.mp3", true, volume);//////////////////////////////////////////////

	/////////// 各种按钮↓

	/*关闭按钮*/
	auto closeItem = MenuItemImage::create("windows\\close.png", "windows\\close1.png", CC_CALLBACK_1(initial_scene::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'windows\\close.png' and 'windows\\close.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + visibleSize.height - closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));

	}
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);



	//音量增大按钮
	auto upItem = MenuItemImage::create("windows\\up.png", "windows\\up1.png", CC_CALLBACK_1(initial_scene::menuCloseCallback2, this));

	if (upItem == nullptr ||
		upItem->getContentSize().width <= 0 ||
		upItem->getContentSize().height <= 0)
	{
		problemLoading("'windows\\up.png' and 'windows\\up1.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2 - 100;
		float y = origin.y + visibleSize.height - closeItem->getContentSize().height / 2;
		upItem->setPosition(Vec2(x, y));

	}
	auto menu2 = Menu::create(upItem, NULL);
	menu2->setPosition(Vec2::ZERO);
	this->addChild(menu2, 1);


	//音量减小按钮
	auto downItem = MenuItemImage::create("windows\\down.png", "windows\\down1.png", CC_CALLBACK_1(initial_scene::menuCloseCallback3, this));

	if (downItem == nullptr ||
		downItem->getContentSize().width <= 0 ||
		downItem->getContentSize().height <= 0)
	{
		problemLoading("'windows\\down.png' and 'windows\\down1.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2 - 200;
		float y = origin.y + visibleSize.height - closeItem->getContentSize().height / 2;
		downItem->setPosition(Vec2(x, y));

	}
	auto menu3 = Menu::create(downItem, NULL);
	menu3->setPosition(Vec2::ZERO);
	this->addChild(menu3, 1);


	return true;
}



void initial_scene::menuCloseCallback2(cocos2d::Ref* pSender)
{
	if (volume < 1.f) {
		volume = volume + 0.1;
		AudioEngine::setVolume(id_1, volume);
	}
}

void initial_scene::menuCloseCallback3(cocos2d::Ref* pSender)
{
	if (volume > 0.f) {
		volume = volume - 0.1;
		AudioEngine::setVolume(id_1, volume);
	}
}

void initial_scene::menuCloseCallback(cocos2d::Ref* pSender)
{
	
	Director::getInstance()->end();
}


void initial_scene::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	if (keycode == EventKeyboard::KeyCode::KEY_SPACE) {
		Scene* scene = Scene::create();
		//enemy_action sprite(Sprite::create("enemy\\melee1.png"), Vec2(540, 300), 200,Vec2(600,200));
		auto safe_map = Sprite::create("windows\\safemap1.jpg");
		auto layer = Layer::create();
		scene->addChild(layer, 0);

		if (safe_map == nullptr)
		{
			problemLoading("'initial scene1.png'");
		}
		else
		{
			// position the sprite on the center of the screen
			safe_map->setScaleX(visibleSize.width / safe_map->getContentSize().width);
			safe_map->setScaleY(visibleSize.height / safe_map->getContentSize().height);
			safe_map->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
			// add the sprite as a child to this layer
			layer->addChild(safe_map, 0);
		}
		//layer->addChild(sprite.enemy_ ,1);

		AudioEngine::stop(id_1);
		auto safeScene = safe_scene::createWithPhysics();
		//Director::getInstance()->replaceScene(safeScene);
		Director::getInstance()->pushScene(safeScene);

		//Director::getInstance()->replaceScene(scene);
		

		//enemy::init();
		//Director::getInstance()->replaceScene(enemy::createScene());
		//Director::getInstance()->end();
	}
}

void initial_scene::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
}

void initial_scene::push_button() {

	auto visibleSize = Director::getInstance()->getVisibleSize();
	RenderTexture* renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();          //给当前屏幕截图


}


Scene* pause_scene(RenderTexture* sqr) {

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Scene* myscene = Scene::create();
	initial_scene* mylayer = initial_scene::create();
	myscene->addChild(mylayer);

	//增加部分：使用截图的sqr纹理图片创建Sprite
	//并将Sprite添加到暂停场景层中
	Sprite* _spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	_spr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	_spr->setFlippedY(true);
	//FlipY(_spr);
	//_spr->Flip
	//_spr->FlipY(true);            
	_spr->setColor(cocos2d::Color3B::GRAY);  //背景变灰暗
	myscene->addChild(_spr);


	return  myscene;
}