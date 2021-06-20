#include "safeScene.h"
#include"cocos2d.h"
#include"InitialScene.h"
#include"windows.h"

float volume2 = 0.2;
float volume3 = 0.5;
int id_2;
int id_3;

Scene* safe_scene::createWithPhysics()
{
	return safe_scene::create();
}

bool safe_scene::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}
	if (!Scene::init())
		return false;


	auto visibleSize1 = Director::getInstance()->getVisibleSize();       //可视区域尺寸
	Vec2 origin1 = Director::getInstance()->getVisibleOrigin();          //可视区域起点坐标
	auto* dispatcher = Director::getInstance()->getEventDispatcher();   //调度器
	auto* keyListener = EventListenerKeyboard::create();                //键盘监听器
	//创建一个事件监听器监听键盘事件
	keyListener->onKeyPressed = CC_CALLBACK_2(safe_scene::onKeyPressed_start, this);
	//键盘被按下时响应
	dispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	id_2 = AudioEngine::play2d("1bgm.mp3", true, volume2);

	auto safe_map = Sprite::create("windows//safemap1.jpg");
	auto layer = Layer::create();
	auto visibleSize = Director::getInstance()->getWinSize();       //可视区域尺寸
	Vec2 origin = Director::getInstance()->getVisibleOrigin();          //可视区域起点坐标


	if (safe_map == nullptr);
	else {
		safe_map->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		addChild(safe_map, 1, 0);
		safe_map->addChild(layer, 1, 122);
	}
	auto return_to_home = MenuItemImage::create("windows\\return initial.jpg", "windows\\return initial1.jpg", CC_CALLBACK_1(safe_scene::menuReturnCallback, this));


	if (return_to_home == nullptr ||return_to_home->getContentSize().width <= 0 ||return_to_home->getContentSize().height <= 0)
	{
		return false;
	}
	else
	{
		float x = origin.x + return_to_home->getContentSize().width / 2;
		float y = origin.y + return_to_home->getContentSize().height / 2;
		return_to_home->setPosition(Vec2(x, y));

	}
	auto menu = Menu::create(return_to_home, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	//血条，护甲，蓝条的刷新   马昕岳******************************************************************************************************************************
	UIBase = Sprite::create("PlayerBaseUI.png");
	UIBase->setPosition(Vec2(UIBase->getContentSize().width / 2, Director::getInstance()->getVisibleSize().height - UIBase->getContentSize().height / 2));
	addChild(UIBase,11);

	HP = Sprite::create("PlayerHpUI.png");
	ProgressTimer* HP_bar = ProgressTimer::create(HP);
	HP_bar->setType(ProgressTimer::Type::BAR);
	HP_bar->setPosition(Vec2(UIBase->getContentSize().width / 2 + 20, Director::getInstance()->getVisibleSize().height - UIBase->getContentSize().height / 2 + HP->getContentSize().height + 6));
	HP_bar->setMidpoint(Point(0, 0.5));
	HP_bar->setBarChangeRate(Point(1, 0));
	HP_bar->setName("HP_bar");
	this->addChild(HP_bar,11);
	schedule(CC_SCHEDULE_SELECTOR(safe_scene::schedule_HP), 0.1f);

	Sheild = Sprite::create("PlayerDefendeseUI.png");
	ProgressTimer* sheild_bar = ProgressTimer::create(Sheild);
	sheild_bar->setType(ProgressTimer::Type::BAR);
	sheild_bar->setPosition(Vec2(UIBase->getContentSize().width / 2 + 20, Director::getInstance()->getVisibleSize().height - UIBase->getContentSize().height / 2 + 6));
	sheild_bar->setMidpoint(Point(0, 0.5));
	sheild_bar->setBarChangeRate(Point(1, 0));
	sheild_bar->setName("sheild_bar");
	this->addChild(sheild_bar, 11);
	schedule(CC_SCHEDULE_SELECTOR(safe_scene::schedule_sheild, 0.1f));


	MP = Sprite::create("PlayerMpUI.png");
	ProgressTimer* MP_bar = ProgressTimer::create(MP);
	MP_bar->setType(ProgressTimer::Type::BAR);
	MP_bar->setPosition(Vec2(UIBase->getContentSize().width / 2 + 20, Director::getInstance()->getVisibleSize().height - UIBase->getContentSize().height / 2 - HP->getContentSize().height + 5));
	MP_bar->setMidpoint(Point(0, 0.5));
	MP_bar->setBarChangeRate(Point(1, 0));
	MP_bar->setName("MP_bar");
	this->addChild(MP_bar,11);
	schedule(CC_SCHEDULE_SELECTOR(safe_scene::schedule_MP),0.1);
	//*****************************************************************************************************************************************************************************************************************

	auto upItem = MenuItemImage::create("windows\\up.png", "windows\\up1.png", CC_CALLBACK_1(safe_scene::menuCloseCallback_up, this));

	if (upItem == nullptr ||
		upItem->getContentSize().width <= 0 ||
		upItem->getContentSize().height <= 0)
	{
		return false;
	}
	else
	{
		float x = origin.x + return_to_home->getContentSize().width / 2 + 100;
		float y = origin.y + return_to_home->getContentSize().height / 2;
		upItem->setPosition(Vec2(x, y));

	}
	auto menu4 = Menu::create(upItem, NULL);
	menu4->setPosition(Vec2::ZERO);
	this->addChild(menu4, 1);



	auto downItem = MenuItemImage::create("windows\\down.png", "windows\\down1.png", CC_CALLBACK_1(safe_scene::menuCloseCallback_down, this));

	if (downItem == nullptr ||
		downItem->getContentSize().width <= 0 ||
		downItem->getContentSize().height <= 0)
	{
		return false;
	}
	else
	{
		float x = origin.x + return_to_home->getContentSize().width / 2 + 200;
		float y = origin.y + return_to_home->getContentSize().height / 2;
		downItem->setPosition(Vec2(x, y));

	}
	auto menu5 = Menu::create(downItem, NULL);
	menu5->setPosition(Vec2::ZERO);
	this->addChild(menu5, 1);


	//暂停继续

	auto stopItem = MenuItemImage::create("windows\\pause1.png", "windows\\pause2.png", CC_CALLBACK_1(safe_scene::menuCloseCallback_stop, this));

	if (stopItem == nullptr ||
		stopItem->getContentSize().width <= 0 ||
		stopItem->getContentSize().height <= 0)
	{
		return false;
	}
	else
	{
		float x = origin.x + return_to_home->getContentSize().width / 2 + 300;
		float y = origin.y + return_to_home->getContentSize().height / 2;
		stopItem->setPosition(Vec2(x, y));

	}
	auto menu_stop = Menu::create(stopItem, NULL);
	menu_stop->setPosition(Vec2::ZERO);
	this->addChild(menu_stop, 1);


	auto goItem = MenuItemImage::create("windows\\go.png", "windows\\go1.png", CC_CALLBACK_1(safe_scene::menuCloseCallback_go, this));

	if (goItem == nullptr ||
		goItem->getContentSize().width <= 0 ||
		goItem->getContentSize().height <= 0)
	{
		return false;
	}
	else
	{
		float x = origin.x + return_to_home->getContentSize().width / 2 + 400;
		float y = origin.y + return_to_home->getContentSize().height / 2;
		goItem->setPosition(Vec2(x, y));

	}
	auto menu_go = Menu::create(goItem, NULL);
	menu_go->setPosition(Vec2::ZERO);
	this->addChild(menu_go, 1);



	/*黄远宏的传送门*/
	door = Sprite::create("door.png");
	door->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.1));
	layer->addChild(door, 1);


	/*骑士部分 by马昕岳*/
	Knight = knight::create("knight.png");
	Knight->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height / 2 ));
	Knight->init();
	layer->addChild(Knight, 2);
	Knight->weapon_init();
	/*计时器部分*/
	schedule(CC_SCHEDULE_SELECTOR(safe_scene::update),1/60);                   //骑士的一系列动作   怪物的移动
	return true;
}

void safe_scene::update(float dt)
{
	/*骑士移动的部分 by马昕岳*/
	Knight->keyboard_event();
	if (Knight->get_speed_x() < 0)
	{
		Knight->runAction(FlipX::create(true));
		Knight->Weapon->runAction(FlipX::create(true));
	}
	if (Knight->get_speed_x() > 0)
	{
		Knight->runAction(FlipX::create(false));
		Knight->Weapon->runAction(FlipX::create(false));
	}
	auto move = MoveBy::create(0.2, Vec2(10 * Knight->get_speed_x(), 10 * Knight->get_speed_y()));
	Knight->runAction(move);
	
}

//和当前场景的交互与响应↓ by黄远宏

void safe_scene::onKeyPressed_start(EventKeyboard::KeyCode keycode, Event* event)
{
	float dx = static_cast<float>((Knight->getPosition().x - door->getPositionX()));
	float dy = static_cast<float>((Knight->getPosition().y - door->getPositionY()));

	if (sqrt(dx * dx + dy * dy) < 80) {
		if (keycode == EventKeyboard::KeyCode::KEY_F)
		{
			//auto battlescene = battle_scene::createWithPhysics();
			AudioEngine::stop(id_2);
			auto battlescene = battle_scene::createWithPhysics();

			Director::getInstance()->pushScene(battlescene);
		}
	}
}


void safe_scene::menuReturnCallback(cocos2d::Ref* pSender)
{
	AudioEngine::stop(id_2);
	Director::getInstance()->popScene();
}

void safe_scene::menuCloseCallback_up(cocos2d::Ref* pSender)
{
	if (volume2 < 0.4f) {
		volume2 = volume2 + 0.1;
		AudioEngine::setVolume(id_2, volume2);
	}
	if (volume3 < 1.0f) {
		volume3 = volume3 + 0.25;
		AudioEngine::setVolume(id_3, volume3);
	}
}

void safe_scene::menuCloseCallback_down(cocos2d::Ref* pSender)
{
	if (volume2 > 0.f) {
		volume2 = volume2 - 0.1;
		AudioEngine::setVolume(id_2, volume2);
	}
	if (volume3 > 0.f) {
		volume3 = volume3 - 0.25;
		AudioEngine::setVolume(id_3, volume3);
	}

}



void safe_scene::menuCloseCallback_stop(cocos2d::Ref* psender)
{

	auto size = Director::getInstance()->getWinSize();
	Director::getInstance()->stopAnimation();

}

void safe_scene::menuCloseCallback_go(cocos2d::Ref* psender)
{
	Director::getInstance()->startAnimation();
}




//血量 蓝条 护甲的计时器 马昕岳***************************************************************************************************************************************************************

void safe_scene::schedule_HP(float delta)
{
	auto progress = (ProgressTimer*)this->getChildByName("HP_bar");
	progress->setPercentage((((float)Knight->get_hp()) / Knight->get_max_hp()) * 100);  //这里是百分制显示
	if (progress->getPercentage() < 0)
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(safe_scene::schedule_HP));
	}
}

void safe_scene::schedule_sheild(float delta)
{
	auto progress = (ProgressTimer*)this->getChildByName("sheild_bar");
	progress->setPercentage((((float)Knight->get_sheild()) / Knight->get_max_sheild()) * 100);  //这里是百分制显示
	if (progress->getPercentage() < 0)
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(safe_scene::schedule_sheild));
	}
}

void safe_scene::schedule_MP(float delta)
{
	auto progress = (ProgressTimer*)this->getChildByName("MP_bar");
	progress->setPercentage((((float)Knight->get_mp()) / Knight->get_max_mp()) * 100);  //这里是百分制显示
	if (progress->getPercentage() < 0)
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(safe_scene::schedule_MP));
	}
}
