#include "safeScene.h"
#include"cocos2d.h"
#include"InitialScene.h"
#include"battlescene.h"
#include"knight.h"

int round_ = 0;           //第几小关
int map_num = 0;
int aaa = 0;
int enter_room[4] = { 0,0,0,0 };
float volume2_ = 0.2;
float volume3_ = 0.5;
int id_2_;
int id_3_;

int mp = 50;
int hp = 3;
int mhp = 5;
int mmp = 200;
int armor = 5;
std::string bullet_name, weapon_name;
int damage, mp_cost;
Scene* battle_scene::createWithPhysics()
{
	return battle_scene::create();
}


bool battle_scene::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}


	///////////////////////


	//by 黄远宏 **************************************************************************************************************************************************

	auto visibleSize1 = Director::getInstance()->getVisibleSize();       //可视区域尺寸
	Vec2 origin1 = Director::getInstance()->getVisibleOrigin();          //可视区域起点坐标
	auto* dispatcher = Director::getInstance()->getEventDispatcher();   //调度器
	auto* keyListener = EventListenerKeyboard::create();                //键盘监听器
	//创建一个事件监听器监听键盘事件
	keyListener->onKeyPressed = CC_CALLBACK_2(battle_scene::onKeyPressed_safe, this);
	//键盘被按下时响应
	dispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
	_bool = false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	//auto winsize = Director::getInstance()->getWinSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto size = Director::getInstance()->getWinSize();

	//场景中的按钮
	id_2_ = AudioEngine::play2d("1bgm.mp3", true, volume2_);


	auto return_to_home = MenuItemImage::create("windows\\return initial.jpg", "windows\\return initial1.jpg", CC_CALLBACK_1(battle_scene::menuReturnCallback, this));


	if (return_to_home == nullptr || return_to_home->getContentSize().width <= 0 || return_to_home->getContentSize().height <= 0)
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
	this->addChild(menu, 130);


	auto upItem = MenuItemImage::create("windows\\up.png", "windows\\up1.png", CC_CALLBACK_1(battle_scene::menuCloseCallback_up, this));

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
	this->addChild(menu4, 130);



	auto downItem = MenuItemImage::create("windows\\down.png", "windows\\down1.png", CC_CALLBACK_1(battle_scene::menuCloseCallback_down, this));

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
	this->addChild(menu5, 130);


	//暂停继续

	auto stopItem = MenuItemImage::create("windows\\pause1.png", "windows\\pause2.png", CC_CALLBACK_1(battle_scene::menuCloseCallback_stop, this));

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
	this->addChild(menu_stop, 130);


	auto goItem = MenuItemImage::create("windows\\go.png", "windows\\go1.png", CC_CALLBACK_1(battle_scene::menuCloseCallback_go, this));

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
	this->addChild(menu_go, 130);
	if(map_num==0)
		map = TMXTiledMap::create("forest_map.tmx");
	if(map_num==1)
		map = TMXTiledMap::create("ice_map5.tmx");

	wall = map->getLayer("meta");
	floor = map->getLayer("floor");
	
	TMXObjectGroup* objGroup1 = map->getObjectGroup("items");
	auto playerPointDic1 = objGroup1->getObject("born");
	float born_x = playerPointDic1["x"].asFloat();
	float born_y = playerPointDic1["y"].asFloat();

	auto layer = Layer::create();
	
	
	if (map != nullptr) {
		map->setPosition(map->getMapSize().width / 2, map->getMapSize().height / 2);
		addChild(map,1,10);
		map->addChild(layer,1,100);
	}


	TMXObjectGroup* objGroup = map->getObjectGroup("items");
	auto PointDic = objGroup->getObject("tutor");
	float tutor_x = PointDic["x"].asFloat();
	float tutor_y = PointDic["y"].asFloat();
	tutor = Sprite::create("tutor.png");
	tutor->setPosition(tutor_x, tutor_y);
	map->addChild(tutor, 10);

	auto dict1 = objGroup->getObject("wall1v1");
	auto dict2 = objGroup->getObject("wall1v2");
	auto dict3 = objGroup->getObject("wall1p1");
	auto dict4 = objGroup->getObject("wall1p2");
	auto dict5 = objGroup->getObject("wall2p1");
	auto dict6 = objGroup->getObject("wall2p2");
	auto dict7 = objGroup->getObject("wall3p1");
	auto dict8 = objGroup->getObject("wall3p2");
	auto dict9 = objGroup->getObject("wall3v1");
	auto dict10 = objGroup->getObject("wall3v2");

	float width1 = dict1["width"].asFloat();
	float height1 = dict1["height"].asFloat();
	float x_1 = dict1["x"].asFloat();
	float y_1 = dict1["y"].asFloat() + 0.5 * height1;
	PhysicsBody* phy1 = PhysicsBody::createBox(Size(width1, height1), PhysicsMaterial(0.1f, 1.0f, 0));
	phy1->setGravityEnable(false);
	phy1->setRotationEnable(false);
	phy1->setDynamic(false);
	Sprite* sp1 = Sprite::create("door.png");
	sp1->setVisible(false);
	sp1->setPosition(x_1, y_1);
	sp1->setContentSize(Size(width1, height1));
	sp1->addComponent(phy1);
	map->addChild(sp1);

	float width2 = dict2["width"].asFloat();
	float height2 = dict2["height"].asFloat();
	float x_2 = dict2["x"].asFloat();
	float y_2 = dict2["y"].asFloat() + 0.5 * height2;
	PhysicsBody* phy2 = PhysicsBody::createBox(Size(width2, height2), PhysicsMaterial(0.1f, 1.0f, 0));
	phy2->setGravityEnable(false);
	phy2->setRotationEnable(false);
	phy2->setDynamic(false);
	Sprite* sp2 = Sprite::create("door.png");
	sp2->setVisible(false);
	sp2->setPosition(x_2, y_2);
	sp2->setContentSize(Size(width2, height2));
	sp2->addComponent(phy2);
	map->addChild(sp2);

	float width3 = dict3["width"].asFloat();
	float height3 = dict3["height"].asFloat();
	float x_3 = dict3["x"].asFloat() + 0.5 * width3;
	float y_3 = dict3["y"].asFloat();
	PhysicsBody* phy3 = PhysicsBody::createBox(Size(width3, height3), PhysicsMaterial(0.1f, 1.0f, 0));
	phy3->setGravityEnable(false);
	phy3->setRotationEnable(false);
	phy3->setDynamic(false);
	Sprite* sp3 = Sprite::create("door.png");
	sp3->setVisible(false);
	sp3->setPosition(x_3, y_3);
	sp3->setContentSize(Size(width3, height3));
	sp3->addComponent(phy3);
	map->addChild(sp3);

	float width4 = dict4["width"].asFloat();
	float height4 = dict4["height"].asFloat();
	float x_4 = dict4["x"].asFloat() + 0.5 * width4;
	float y_4 = dict4["y"].asFloat();
	PhysicsBody* phy4 = PhysicsBody::createBox(Size(width4, height4), PhysicsMaterial(0.1f, 1.0f, 0));
	phy4->setGravityEnable(false);
	phy4->setRotationEnable(false);
	phy4->setDynamic(false);
	Sprite* sp4 = Sprite::create("door.png");
	sp4->setVisible(false);
	sp4->setPosition(x_4, y_4);
	sp4->setContentSize(Size(width4, height4));
	sp4->addComponent(phy4);
	map->addChild(sp4);

	float width5 = dict5["width"].asFloat();
	float height5 = dict5["height"].asFloat();
	float x_5 = dict5["x"].asFloat() + 0.5 * width5;
	float y_5 = dict5["y"].asFloat();
	PhysicsBody* phy5 = PhysicsBody::createBox(Size(width5, height5), PhysicsMaterial(0.1f, 1.0f, 0));
	phy5->setGravityEnable(false);
	phy5->setRotationEnable(false);
	phy5->setDynamic(false);
	Sprite* sp5 = Sprite::create("door.png");
	sp5->setVisible(false);
	sp5->setPosition(x_5, y_5);
	sp5->setContentSize(Size(width5, height5));
	sp5->addComponent(phy5);
	map->addChild(sp5);

	float width6 = dict6["width"].asFloat();
	float height6 = dict6["height"].asFloat();
	float x_6 = dict6["x"].asFloat() + 0.5 * width6;
	float y_6 = dict6["y"].asFloat();
	PhysicsBody* phy6 = PhysicsBody::createBox(Size(width6, height6), PhysicsMaterial(0.1f, 1.0f, 0));
	phy6->setGravityEnable(false);
	phy6->setRotationEnable(false);
	phy6->setDynamic(false);
	Sprite* sp6 = Sprite::create("door.png");
	sp6->setVisible(false);
	sp6->setPosition(x_6, y_6);
	sp6->setContentSize(Size(width6, height6));
	sp6->addComponent(phy6);
	map->addChild(sp6);

	float width7 = dict7["width"].asFloat();
	float height7 = dict7["height"].asFloat();
	float x_7 = dict7["x"].asFloat() + 0.5 * width7;
	float y_7 = dict7["y"].asFloat();
	PhysicsBody* phy7 = PhysicsBody::createBox(Size(width7, height7), PhysicsMaterial(0.1f, 1.0f, 0));
	phy7->setGravityEnable(false);
	phy7->setRotationEnable(false);
	phy7->setDynamic(false);
	Sprite* sp7 = Sprite::create("door.png");
	sp7->setVisible(false);
	sp7->setPosition(x_7, y_7);
	sp7->setContentSize(Size(width7, height7));
	sp7->addComponent(phy7);
	map->addChild(sp7);

	float width8 = dict8["width"].asFloat();
	float height8 = dict8["height"].asFloat();
	float x_8 = dict8["x"].asFloat() + 0.5 * width8;
	float y_8 = dict8["y"].asFloat();
	PhysicsBody* phy8 = PhysicsBody::createBox(Size(width8, height8), PhysicsMaterial(0.1f, 1.0f, 0));
	phy8->setGravityEnable(false);
	phy8->setRotationEnable(false);
	phy8->setDynamic(false);
	Sprite* sp8 = Sprite::create("door.png");
	sp8->setVisible(false);
	sp8->setPosition(x_8, y_8);
	sp8->setContentSize(Size(width8, height8));
	sp8->addComponent(phy8);
	map->addChild(sp8);

	float width9 = dict9["width"].asFloat();
	float height9 = dict9["height"].asFloat();
	float x_9 = dict9["x"].asFloat();
	float y_9 = dict9["y"].asFloat() + 0.5 * height9;
	PhysicsBody* phy9 = PhysicsBody::createBox(Size(width9, height9), PhysicsMaterial(0.1f, 1.0f, 0));
	phy9->setGravityEnable(false);
	phy9->setRotationEnable(false);
	phy9->setDynamic(false);
	Sprite* sp9 = Sprite::create("door.png");
	sp9->setVisible(false);
	sp9->setPosition(x_9, y_9);
	sp9->setContentSize(Size(width9, height9));
	sp9->addComponent(phy9);
	map->addChild(sp9);

	float width10 = dict10["width"].asFloat();
	float height10 = dict10["height"].asFloat();
	float x_10 = dict10["x"].asFloat();
	float y_10 = dict10["y"].asFloat() + 0.5 * height10;
	PhysicsBody* phy10 = PhysicsBody::createBox(Size(width10, height10), PhysicsMaterial(0.1f, 1.0f, 0));
	phy10->setGravityEnable(false);
	phy10->setRotationEnable(false);
	phy10->setDynamic(false);
	Sprite* sp10 = Sprite::create("door.png");
	sp10->setVisible(false);
	sp10->setPosition(x_10, y_10);
	sp10->setContentSize(Size(width10, height10));
	sp10->addComponent(phy10);
	map->addChild(sp10);

	auto playerPointDic2 = objGroup->getObject("guard1");
	float in_x1 = playerPointDic2["x"].asFloat();
	float in_y1 = playerPointDic2["y"].asFloat();
	guard1 = Sprite::create("door.png");
	guard1->setVisible(false);
	guard1->setPosition(in_x1, in_y1);
	map->addChild(guard1);

	auto playerPointDic3 = objGroup->getObject("guard2");
	float in_x2 = playerPointDic3["x"].asFloat();
	float in_y2 = playerPointDic3["y"].asFloat();
	guard2 = Sprite::create("door.png");
	guard2->setVisible(false);
	guard2->setPosition(in_x2, in_y2);
	map->addChild(guard2);

	auto playerPointDic4 = objGroup->getObject("guard3");
	float in_x3 = playerPointDic4["x"].asFloat();
	float in_y3 = playerPointDic4["y"].asFloat();
	guard3 = Sprite::create("door.png");
	guard3->setVisible(false);
	guard3->setPosition(in_x3, in_y3);
	map->addChild(guard3);

	auto playerPointDic5 = objGroup->getObject("guard4");
	float in_x4 = playerPointDic5["x"].asFloat();
	float in_y4 = playerPointDic5["y"].asFloat();
	guard4 = Sprite::create("door.png");
	guard4->setVisible(false);
	guard4->setPosition(in_x4, in_y4);
	map->addChild(guard4);

	auto playerPointDic6 = objGroup->getObject("guard5");
	float in_x5 = playerPointDic6["x"].asFloat();
	float in_y5 = playerPointDic6["y"].asFloat();
	guard5 = Sprite::create("door.png");
	guard5->setVisible(false);
	guard5->setPosition(in_x5, in_y5);
	map->addChild(guard5);

	auto playerPointDic = objGroup->getObject("door");
	float door_x = playerPointDic["x"].asFloat();
	float door_y = playerPointDic["y"].asFloat();
	
    door = Sprite::create("door.png");
	door->setPosition(door_x, door_y);
	door->setVisible(false);
	map->addChild(door,0);
	

	/*初始化骑士*/
	Knight = knight::create("knight.png");
	Knight->setPosition(Vec2(born_x, born_y));
	Knight->init();
	create_unpicked_weapon(Vec2(born_x, born_y), "M2.png", "M2 bullet.png");
	//create_unpicked_weapon(Vec2(born_x-100, born_y+100), "big_knife.png", "knife_bullet.png");
	layer->addChild(Knight, 0);
	Knight->weapon_init();
	if (!(round_ == 0 && map_num == 0)) {
		set_knight(mp, mmp, hp, mhp, armor);
		Knight->removeChild(Knight->Weapon,1);
		Knight->weapon_init(weapon_name, bullet_name, damage, mp_cost);
	}
	
	
	//血条，护甲，蓝条的刷新   马昕岳******************************************************************************************************************************
	UIBase = Sprite::create("PlayerBaseUI.png");
	UIBase->setPosition(Vec2(UIBase->getContentSize().width / 2, Director::getInstance()->getVisibleSize().height - UIBase->getContentSize().height / 2));
	addChild(UIBase, 11);

	HP = Sprite::create("PlayerHpUI.png");
	ProgressTimer* HP_bar = ProgressTimer::create(HP);
	HP_bar->setType(ProgressTimer::Type::BAR);
	HP_bar->setPosition(Vec2(UIBase->getContentSize().width / 2 + 20, Director::getInstance()->getVisibleSize().height - UIBase->getContentSize().height / 2 + HP->getContentSize().height + 6));
	HP_bar->setMidpoint(Point(0, 0.5));
	HP_bar->setBarChangeRate(Point(1, 0));
	HP_bar->setName("HP_bar");
	this->addChild(HP_bar, 11);
	schedule(CC_SCHEDULE_SELECTOR(battle_scene::schedule_HP), 0.1f);

	Sheild = Sprite::create("PlayerDefendeseUI.png");
	ProgressTimer* sheild_bar = ProgressTimer::create(Sheild);
	sheild_bar->setType(ProgressTimer::Type::BAR);
	sheild_bar->setPosition(Vec2(UIBase->getContentSize().width / 2 + 20, Director::getInstance()->getVisibleSize().height - UIBase->getContentSize().height / 2 + 6));
	sheild_bar->setMidpoint(Point(0, 0.5));
	sheild_bar->setBarChangeRate(Point(1, 0));
	sheild_bar->setName("sheild_bar");
	this->addChild(sheild_bar, 11);
	schedule(CC_SCHEDULE_SELECTOR(battle_scene::schedule_sheild),0.1);


	MP = Sprite::create("PlayerMpUI.png");
	ProgressTimer* MP_bar = ProgressTimer::create(MP);
	MP_bar->setType(ProgressTimer::Type::BAR);
	MP_bar->setPosition(Vec2(UIBase->getContentSize().width / 2 + 20, Director::getInstance()->getVisibleSize().height - UIBase->getContentSize().height / 2 - HP->getContentSize().height + 5));
	MP_bar->setMidpoint(Point(0, 0.5));
	MP_bar->setBarChangeRate(Point(1, 0));
	MP_bar->setName("MP_bar");
	this->addChild(MP_bar, 11);
	schedule(CC_SCHEDULE_SELECTOR(battle_scene::schedule_MP),0.1);
	//*****************************************************************************************************************************************************************************************************************
	/*计时器*/

	schedule(CC_SCHEDULE_SELECTOR(battle_scene::update_follow));                    //骑士的一系列动作
	schedule(CC_SCHEDULE_SELECTOR(battle_scene::update_if_battle));                    //骑士的一系列动作
	schedule(CC_SCHEDULE_SELECTOR(battle_scene::update_knight_fire), 0.4);
	schedule(CC_SCHEDULE_SELECTOR(battle_scene::update_if_recover_armor), 4);    //判断骑士是否恢复护甲的计时器
	return true;
}





//  判定是否首次进入某个房间，若是，则关上门，再获取刷怪点坐标，并传入刷怪函数  by 黄远宏********************************************************************************


void battle_scene::update_if_battle(float dt)
{
	float V_sight = 56;
	float P_sight = 168;
	TMXObjectGroup* objGroup = map->getObjectGroup("items");

	float dx1 = static_cast<float>((Knight->getPosition().x - guard1->getPositionX()));
	float dy1 = static_cast<float>((Knight->getPosition().y - guard1->getPositionY()));
	if ((sqrt(dx1 * dx1 + dy1 * dy1) < 60) && enter_room[0] == 0) {
		enter_room[0]++;
		room_num = 0;
		room_type = 0;
		max_melee = 4;
		max_remote = 2;
		auto room_1v1 = objGroup->getObject("1v1");
		auto room_1p1 = objGroup->getObject("1p1");
		float room_1v1_x = room_1v1["x"].asFloat();
		float room_1v1_y = room_1v1["y"].asFloat();
		float room_1p1_x = room_1p1["x"].asFloat();
		float room_1p1_y = room_1p1["y"].asFloat();


		Sprite* room_1v1_1 = Sprite::create("close.png");
		room_1v1_1->setPosition(room_1v1_x, room_1v1_y + 112);
		map->getChildByTag(100)->addChild(room_1v1_1, 5,1);
		Sprite* room_1v1_2 = Sprite::create("close.png");
		room_1v1_2->setPosition(room_1v1_x, room_1v1_y + 56);
		map->getChildByTag(100)->addChild(room_1v1_2, 5,2);
		Sprite* room_1v1_3 = Sprite::create("close.png");
		room_1v1_3->setPosition(room_1v1_x, room_1v1_y);
		map->getChildByTag(100)->addChild(room_1v1_3, 5,3);


		Sprite* room_1p1_1 = Sprite::create("close.png");
		room_1p1_1->setPosition(room_1p1_x, room_1p1_y);
		map->getChildByTag(100)->addChild(room_1p1_1, 5,4);
		Sprite* room_1p1_2 = Sprite::create("close.png");
		room_1p1_2->setPosition(room_1p1_x + 56, room_1p1_y);
		map->getChildByTag(100)->addChild(room_1p1_2, 5,5);
		Sprite* room_1p1_3 = Sprite::create("close.png");
		room_1p1_3->setPosition(room_1p1_x + 112, room_1p1_y);
		map->getChildByTag(100)->addChild(room_1p1_3, 5,6);
		_bool = true;
	}
	if (_bool && room_num == 0 && wave[0] < 2) {
		auto b1 = objGroup->getObject("enemy11");
		float b1_x = b1["x"].asFloat();
		float b1_y = b1["y"].asFloat();

		auto c1 = objGroup->getObject("enemy12");
		float c1_x = c1["x"].asFloat();
		float c1_y = c1["y"].asFloat();

		auto d1 = objGroup->getObject("enemy13");
		float d1_x = d1["x"].asFloat();
		float d1_y = d1["y"].asFloat();

		auto e1 = objGroup->getObject("enemy14");
		float e1_x = e1["x"].asFloat();
		float e1_y = e1["y"].asFloat();

		auto f1 = objGroup->getObject("enemy15");
		float f1_x = f1["x"].asFloat();
		float f1_y = f1["y"].asFloat();

		auto g1 = objGroup->getObject("enemy16");
		float g1_x = g1["x"].asFloat();
		float g1_y = g1["y"].asFloat();

		Vec2 v1 = Vec2(b1_x, b1_y);
		Vec2 v2 = Vec2(c1_x, c1_y);
		Vec2 v3 = Vec2(d1_x, d1_y);
		Vec2 v4 = Vec2(e1_x, e1_y);
		Vec2 v5 = Vec2(f1_x, f1_y);
		Vec2 v6 = Vec2(g1_x, g1_y);
		if (wave[0] == 0) {
			enemy_born(v1, v2, v3, v4, v5, v6, _bool);
			wave[0]++;
		}
		if (wave[0] == 1 && if_all_enemy_dead()) {
			unschedule(CC_SCHEDULE_SELECTOR(battle_scene::update_remote));
			unschedule(CC_SCHEDULE_SELECTOR(battle_scene::update));
			unschedule(CC_SCHEDULE_SELECTOR(battle_scene::update_bullet));
			set_all_enemy_unvisible();
			enemy_born(v1, v2, v3, v4, v5, v6, _bool);
			wave[0]++;
		}
	}
	if (!_bool && enter_room[0] > 0) {
		map->getChildByTag(100)->getChildByTag(1)->setVisible(false);
		map->getChildByTag(100)->getChildByTag(2)->setVisible(false);
		map->getChildByTag(100)->getChildByTag(3)->setVisible(false);
		map->getChildByTag(100)->getChildByTag(4)->setVisible(false);
		map->getChildByTag(100)->getChildByTag(5)->setVisible(false);
		map->getChildByTag(100)->getChildByTag(6)->setVisible(false);
	}
	


	float dx2 = static_cast<float>((Knight->getPosition().x - guard2->getPositionX()));
	float dy2 = static_cast<float>((Knight->getPosition().y - guard2->getPositionY()));
	if (fabs(dx2) < P_sight && fabs(dy2) < V_sight && enter_room[1] == 0) {
		enter_room[1]++;
		room_num = 1;
		room_type = 0;
		if (map_num == 0) {
			max_melee = 5;
			max_remote = 3;
		}
		else {
			max_melee = 4;
			max_remote = 2;
		}
		auto room_2v1 = objGroup->getObject("2v1");
		auto room_2p1 = objGroup->getObject("2p1");
		auto room_2v2 = objGroup->getObject("2v2");
		auto room_2p2 = objGroup->getObject("2p2");
		float room_2v1_x = room_2v1["x"].asFloat();
		float room_2v1_y = room_2v1["y"].asFloat();
		float room_2p1_x = room_2p1["x"].asFloat();
		float room_2p1_y = room_2p1["y"].asFloat();
		float room_2v2_x = room_2v2["x"].asFloat();
		float room_2v2_y = room_2v2["y"].asFloat();
		float room_2p2_x = room_2p2["x"].asFloat();
		float room_2p2_y = room_2p2["y"].asFloat();


		Sprite* room_2v1_1 = Sprite::create("close.png");
		room_2v1_1->setPosition(room_2v1_x, room_2v1_y + 112);
		map->getChildByTag(100)->addChild(room_2v1_1, 5,13);
		Sprite* room_2v1_2 = Sprite::create("close.png");
		room_2v1_2->setPosition(room_2v1_x, room_2v1_y + 56);
		map->getChildByTag(100)->addChild(room_2v1_2, 5,14);
		Sprite* room_2v1_3 = Sprite::create("close.png");
		room_2v1_3->setPosition(room_2v1_x, room_2v1_y);
		map->getChildByTag(100)->addChild(room_2v1_3, 5,15);


		Sprite* room_2p1_1 = Sprite::create("close.png");
		room_2p1_1->setPosition(room_2p1_x, room_2p1_y);
		map->getChildByTag(100)->addChild(room_2p1_1, 5,16);
		Sprite* room_2p1_2 = Sprite::create("close.png");
		room_2p1_2->setPosition(room_2p1_x + 56, room_2p1_y);
		map->getChildByTag(100)->addChild(room_2p1_2, 5,17);
		Sprite* room_2p1_3 = Sprite::create("close.png");
		room_2p1_3->setPosition(room_2p1_x + 112, room_2p1_y);
		map->getChildByTag(100)->addChild(room_2p1_3, 5,18);

		Sprite* room_2v2_1 = Sprite::create("close.png");
		room_2v2_1->setPosition(room_2v2_x, room_2v2_y + 112);
		map->getChildByTag(100)->addChild(room_2v2_1, 5,7);
		Sprite* room_2v2_2 = Sprite::create("close.png");
		room_2v2_2->setPosition(room_2v2_x, room_2v2_y + 56);
		map->getChildByTag(100)->addChild(room_2v2_2, 5,8);
		Sprite* room_2v2_3 = Sprite::create("close.png");
		room_2v2_3->setPosition(room_2v2_x, room_2v2_y);
		map->getChildByTag(100)->addChild(room_2v2_3, 5,9);


		Sprite* room_2p2_1 = Sprite::create("close.png");
		room_2p2_1->setPosition(room_2p2_x, room_2p2_y);
		map->getChildByTag(100)->addChild(room_2p2_1, 5,10);
		Sprite* room_2p2_2 = Sprite::create("close.png");
		room_2p2_2->setPosition(room_2p2_x + 56, room_2p2_y);
		map->getChildByTag(100)->addChild(room_2p2_2, 5,11);
		Sprite* room_2p2_3 = Sprite::create("close.png");
		room_2p2_3->setPosition(room_2p2_x + 112, room_2p2_y);
		map->getChildByTag(100)->addChild(room_2p2_3, 5,12);

		_bool = true;
	}
	if(_bool&&room_num==1&&wave[1]<2){
		auto b1 = objGroup->getObject("enemy21");
		float b1_x = b1["x"].asFloat();
		float b1_y = b1["y"].asFloat();

		auto c1 = objGroup->getObject("enemy22");
		float c1_x = c1["x"].asFloat();
		float c1_y = c1["y"].asFloat();

		auto d1 = objGroup->getObject("enemy23");
		float d1_x = d1["x"].asFloat();
		float d1_y = d1["y"].asFloat();

		auto e1 = objGroup->getObject("enemy24");
		float e1_x = e1["x"].asFloat();
		float e1_y = e1["y"].asFloat();

		auto f1 = objGroup->getObject("enemy25");
		float f1_x = f1["x"].asFloat();
		float f1_y = f1["y"].asFloat();

		auto g1 = objGroup->getObject("enemy26");
		float g1_x = g1["x"].asFloat();
		float g1_y = g1["y"].asFloat();
		Vec2 v1 = Vec2(b1_x, b1_y);
		Vec2 v2 = Vec2(c1_x, c1_y);
		Vec2 v3 = Vec2(d1_x, d1_y);
		Vec2 v4 = Vec2(e1_x, e1_y);
		Vec2 v5 = Vec2(f1_x, f1_y);
		Vec2 v6 = Vec2(g1_x, g1_y);
		if (map_num == 0) {
			auto h1 = objGroup->getObject("enemy27");
			float h1_x = h1["x"].asFloat();
			float h1_y = h1["y"].asFloat();

			auto i1 = objGroup->getObject("enemy28");
			float i1_x = i1["x"].asFloat();
			float i1_y = i1["y"].asFloat();
			Vec2 v7 = Vec2(h1_x, h1_y);
			Vec2 v8 = Vec2(i1_x, i1_y);
			if (wave[1] == 0) {
				enemy_born(v1, v2, v3, v4, v5, v6, v7, v8, _bool);
				wave[1]++;
			}
			if (wave[1] == 1 && if_all_enemy_dead()) {
				unschedule(CC_SCHEDULE_SELECTOR(battle_scene::update_remote));
				unschedule(CC_SCHEDULE_SELECTOR(battle_scene::update));
				unschedule(CC_SCHEDULE_SELECTOR(battle_scene::update_bullet));
				set_all_enemy_unvisible();
				enemy_born(v1, v2, v3, v4, v5, v6, v7, v8, _bool);
				wave[1]++;
			}
		}
		
		if (map_num == 1) {
			if (wave[1] == 0) {
				enemy_born(v1, v2, v3, v4, v5, v6, _bool);
				wave[1]++;
			}
			if (wave[1] == 1 && if_all_enemy_dead()) {
				unschedule(CC_SCHEDULE_SELECTOR(battle_scene::update_remote));
				unschedule(CC_SCHEDULE_SELECTOR(battle_scene::update));
				unschedule(CC_SCHEDULE_SELECTOR(battle_scene::update_bullet));
				set_all_enemy_unvisible();
				enemy_born(v1, v2, v3, v4, v5, v6, _bool);
				wave[1]++;
			}
		}
	}
	if (!_bool && enter_room[1] > 0) {
		
		map->getChildByTag(100)->getChildByTag(13)->setVisible(false);
		map->getChildByTag(100)->getChildByTag(14)->setVisible(false);
		map->getChildByTag(100)->getChildByTag(15)->setVisible(false);
		map->getChildByTag(100)->getChildByTag(16)->setVisible(false);
		map->getChildByTag(100)->getChildByTag(17)->setVisible(false);
		map->getChildByTag(100)->getChildByTag(18)->setVisible(false);
		map->getChildByTag(100)->getChildByTag(7)->setVisible(false);
		map->getChildByTag(100)->getChildByTag(8)->setVisible(false);
		map->getChildByTag(100)->getChildByTag(9)->setVisible(false);
		map->getChildByTag(100)->getChildByTag(10)->setVisible(false);
		map->getChildByTag(100)->getChildByTag(11)->setVisible(false);
		map->getChildByTag(100)->getChildByTag(12)->setVisible(false);

	}

	float dx3 = static_cast<float>((Knight->getPosition().x - guard3->getPositionX()));
	float dy3 = static_cast<float>((Knight->getPosition().y - guard3->getPositionY()));
	if (fabs(dx3) < V_sight && fabs(dy3) < P_sight && enter_room[2] == 0) {
		enter_room[2]++;
		room_num = 2;
		room_type = 0;
		max_melee = 4;
		max_remote = 2;
		auto room_3v1 = objGroup->getObject("3v1");

		float room_3v1_x = room_3v1["x"].asFloat();
		float room_3v1_y = room_3v1["y"].asFloat();

		Sprite* room_3v1_1 = Sprite::create("close.png");
		room_3v1_1->setPosition(room_3v1_x, room_3v1_y + 112);
		map->getChildByTag(100)->addChild(room_3v1_1, 5,19);
		Sprite* room_3v1_2 = Sprite::create("close.png");
		room_3v1_2->setPosition(room_3v1_x, room_3v1_y + 56);
		map->getChildByTag(100)->addChild(room_3v1_2, 5,20);
		Sprite* room_3v1_3 = Sprite::create("close.png");
		room_3v1_3->setPosition(room_3v1_x, room_3v1_y);
		map->getChildByTag(100)->addChild(room_3v1_3, 5,21);

		_bool = 1;
	}
	if (_bool && room_num == 2 && wave[2] < 2) {
		auto b1 = objGroup->getObject("enemy31");
		float b1_x = b1["x"].asFloat();
		float b1_y = b1["y"].asFloat();

		auto c1 = objGroup->getObject("enemy32");
		float c1_x = c1["x"].asFloat();
		float c1_y = c1["y"].asFloat();

		auto d1 = objGroup->getObject("enemy33");
		float d1_x = d1["x"].asFloat();
		float d1_y = d1["y"].asFloat();

		auto e1 = objGroup->getObject("enemy34");
		float e1_x = e1["x"].asFloat();
		float e1_y = e1["y"].asFloat();

		auto f1 = objGroup->getObject("enemy35");
		float f1_x = f1["x"].asFloat();
		float f1_y = f1["y"].asFloat();

		auto g1 = objGroup->getObject("enemy36");
		float g1_x = g1["x"].asFloat();
		float g1_y = g1["y"].asFloat();

		Vec2 v1 = Vec2(b1_x, b1_y);
		Vec2 v2 = Vec2(c1_x, c1_y);
		Vec2 v3 = Vec2(d1_x, d1_y);
		Vec2 v4 = Vec2(e1_x, e1_y);
		Vec2 v5 = Vec2(f1_x, f1_y);
		Vec2 v6 = Vec2(g1_x, g1_y);
		if (wave[2] == 0) {
			enemy_born(v1, v2, v3, v4, v5, v6, _bool);
			wave[2]++;
		}
		if (wave[2] == 1 && if_all_enemy_dead()) {
			unschedule(CC_SCHEDULE_SELECTOR(battle_scene::update_remote));
			unschedule(CC_SCHEDULE_SELECTOR(battle_scene::update));
			unschedule(CC_SCHEDULE_SELECTOR(battle_scene::update_bullet));
			set_all_enemy_unvisible();
			enemy_born(v1, v2, v3, v4, v5, v6, _bool);
			wave[2]++;
		}
	}
	if (!_bool && enter_room[2] > 0) {

		map->getChildByTag(100)->getChildByTag(19)->setVisible(false);
		map->getChildByTag(100)->getChildByTag(20)->setVisible(false);
		map->getChildByTag(100)->getChildByTag(21)->setVisible(false);

	}
	float dx4 = static_cast<float>((Knight->getPosition().x - guard4->getPositionX()));
	float dy4 = static_cast<float>((Knight->getPosition().y - guard4->getPositionY()));
	float dx5 = static_cast<float>((Knight->getPosition().x - guard5->getPositionX()));
	float dy5 = static_cast<float>((Knight->getPosition().y - guard5->getPositionY()));
	if ((fabs(dx4) < P_sight && fabs(dy4) < V_sight || fabs(dx5) < V_sight && fabs(dy5) < P_sight) && enter_room[3] == 0) {
		enter_room[3]++;
		room_num = 3;
		room_type = 1;
		max_melee = 0;
		max_remote = 0;
		auto room_4v1 = objGroup->getObject("4v1");
		auto room_4p1 = objGroup->getObject("4p1");
		float room_4v1_x = room_4v1["x"].asFloat();
		float room_4v1_y = room_4v1["y"].asFloat();
		float room_4p1_x = room_4p1["x"].asFloat();
		float room_4p1_y = room_4p1["y"].asFloat();


		Sprite* room_4v1_1 = Sprite::create("close.png");
		room_4v1_1->setPosition(room_4v1_x, room_4v1_y + 112);
		map->getChildByTag(100)->addChild(room_4v1_1, 5,22);
		Sprite* room_4v1_2 = Sprite::create("close.png");
		room_4v1_2->setPosition(room_4v1_x, room_4v1_y + 56);
		map->getChildByTag(100)->addChild(room_4v1_2, 5,23);
		Sprite* room_4v1_3 = Sprite::create("close.png");
		room_4v1_3->setPosition(room_4v1_x, room_4v1_y);
		map->getChildByTag(100)->addChild(room_4v1_3, 5,24);

		Sprite* room_4p1_1 = Sprite::create("close.png");
		room_4p1_1->setPosition(room_4p1_x, room_4p1_y);
		map->getChildByTag(100)->addChild(room_4p1_1, 5,25);
		Sprite* room_4p1_2 = Sprite::create("close.png");
		room_4p1_2->setPosition(room_4p1_x + 56, room_4p1_y);
		map->getChildByTag(100)->addChild(room_4p1_2, 5,26);
		Sprite* room_4p1_3 = Sprite::create("close.png");
		room_4p1_3->setPosition(room_4p1_x + 112, room_4p1_y);
		map->getChildByTag(100)->addChild(room_4p1_3, 5,27);
		_bool = true;
	}
	if ( _bool && room_num == 3 && aaa == 0&&round_==1 ) {
		aaa++;
		auto b1 = objGroup->getObject("boss");
		float b1_x = b1["x"].asFloat();
		float b1_y = b1["y"].asFloat();
		boss_born(Vec2(b1_x, b1_y));
		create_boss_HP_bar();
	}
	if (!_bool && enter_room[3] > 0) {

		map->getChildByTag(100)->getChildByTag(22)->setVisible(false);
		map->getChildByTag(100)->getChildByTag(23)->setVisible(false);
		map->getChildByTag(100)->getChildByTag(24)->setVisible(false);
		map->getChildByTag(100)->getChildByTag(25)->setVisible(false);
		map->getChildByTag(100)->getChildByTag(26)->setVisible(false);
		map->getChildByTag(100)->getChildByTag(27)->setVisible(false);

	}
	if (room_type == 1 && if_all_enemy_dead()&&round_==1 ) {
		door->setVisible(true);
	}
	else if(room_type==1&&round_==0)
		door->setVisible(true);
	if ((wave[room_num] == 2 || room_type == 1) && if_all_enemy_dead()) {
		_bool = false;
	}
}


//******************************************************************************************************************************************



//  by黄远宏****************************************************************************************************

void battle_scene::onKeyPressed_safe(EventKeyboard::KeyCode keycode, Event* event)
{
	float dx = static_cast<float>((Knight->getPosition().x - door->getPositionX()));
	float dy = static_cast<float>((Knight->getPosition().y - door->getPositionY()));

	if (sqrt(dx * dx + dy * dy) < 80) {
		if (door->isVisible()) {
			if (keycode == EventKeyboard::KeyCode::KEY_F)
			{
				unscheduleAllCallbacks();
				hp = Knight->get_hp();
				mhp = Knight->get_max_hp();
				mmp = Knight->get_max_mp();
				mp = Knight->get_mp();
				armor = Knight->get_max_sheild();
				weapon_name = Knight->Weapon->get_weapon_name();
				bullet_name = Knight->Weapon->get_bullet_name();
				damage = Knight->Weapon->get_original_demage();
				mp_cost == Knight->Weapon->get_bullet_cost();
				for (int i = 0; i < 4; i++) {
					enter_room[i] = 0;
				}
				if (round_ == 0 && map_num == 0) {
					round_ = 1;
					AudioEngine::stop(id_2_);
					auto scene = battle_scene::createWithPhysics();
					Director::getInstance()->replaceScene(scene);
					return;
				}
				else if (round_ == 1 && map_num == 0) {
					round_ = 0;
					map_num = 1;
					AudioEngine::stop(id_2_);
					auto scene = battle_scene::createWithPhysics();
					Director::getInstance()->replaceScene(scene);
					return;
				}
				else if (round_ == 0 && map_num == 1) {
					aaa = 0;
					round_ = 1;
					AudioEngine::stop(id_2_);
					auto scene = battle_scene::createWithPhysics();
					Director::getInstance()->replaceScene(scene);
					return;
				}
				else if (round_ == 1 && map_num == 1) {
					map_num = 0;
					round_ = 0;
					AudioEngine::stop(id_2_);
					Director::getInstance()->popScene();
				}
				//Director::getInstance()->popScene();
			}
		}
	}
}
/*导师系统*/
void battle_scene::onKeyPressed_tutor(EventKeyboard::KeyCode keycode, Event* event)
{
	float sight_tutor = 80;
	float dx_tutor = static_cast<float>((Knight->getPosition().x - tutor->getPositionX()));
	float dy_tutor = static_cast<float>((Knight->getPosition().y - tutor->getPositionY()));

	if (sqrt(dx_tutor * dx_tutor + dy_tutor * dy_tutor) < sight_tutor) {
		if (keycode == EventKeyboard::KeyCode::KEY_E)
		{
			//createbuff

		}
	}
}








void battle_scene::menuReturnCallback(cocos2d::Ref* pSender)
{
	AudioEngine::stop(id_2_);
	Director::getInstance()->popScene();
}

void battle_scene::menuCloseCallback_up(cocos2d::Ref* pSender)
{
	if (volume2_ < 0.4f) {
		volume2_ = volume2_ + 0.1;
		AudioEngine::setVolume(id_2_, volume2_);
	}
	if (volume3_ < 1.0f) {
		volume3_ = volume3_ + 0.25;
		AudioEngine::setVolume(id_3_, volume3_);
	}
}

void battle_scene::menuCloseCallback_down(cocos2d::Ref* pSender)
{
	if (volume2_ > 0.f) {
		volume2_ = volume2_ - 0.1;
		AudioEngine::setVolume(id_2_, volume2_);
	}
	if (volume3_ > 0.f) {
		volume3_ = volume3_ - 0.25;
		AudioEngine::setVolume(id_3_, volume3_);
	}

}

void battle_scene::menuCloseCallback_stop(cocos2d::Ref* psender)
{

	auto size = Director::getInstance()->getWinSize();
	Director::getInstance()->stopAnimation();

}

void battle_scene::menuCloseCallback_go(cocos2d::Ref* psender)
{
	Director::getInstance()->startAnimation();
}



//马昕岳 16:34 : 52
void  battle_scene::create_boss_HP_bar()
{
	auto boss_HP = Sprite::create("BOSSHpUI.png");
	ProgressTimer* boss_HP_bar = ProgressTimer::create(boss_HP);
	boss_HP_bar->setType(ProgressTimer::Type::BAR);
	boss_HP_bar->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height - boss_HP->getContentSize().height - 10));
	boss_HP_bar->setMidpoint(Point(0, 0.5));
	boss_HP_bar->setBarChangeRate(Point(1, 0));
	boss_HP_bar->setName("boss_HP_bar");
	this->addChild(boss_HP_bar,10);
	schedule(CC_SCHEDULE_SELECTOR(battle_scene::schedule_boss_HP), 0.1f);
}

//马昕岳 
void  battle_scene::schedule_boss_HP(float delta)
{
	auto progress = (ProgressTimer*)this->getChildByName("boss_HP_bar");
	progress->setPercentage((((float)enemy_boss.get_hp()) / enemy_boss.get_max_hp()) * 100); 
	if (progress->getPercentage() < 0)
	{
		unschedule(CC_SCHEDULE_SELECTOR(battle_scene::schedule_boss_HP));
	}
}




void battle_scene::update_follow(float dt)
{

	/*骑士移动、开火、切枪的部分 by马昕岳*/
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
	if (Knight->get_E_check())
	{
		gun_switch();
	}
	/*骑士与墙碰撞*/
	auto up = EventKeyboard::KeyCode::KEY_W;
	auto left = EventKeyboard::KeyCode::KEY_A;
	auto down = EventKeyboard::KeyCode::KEY_S;
	auto right = EventKeyboard::KeyCode::KEY_D;
	Point p = Knight->getPosition();

	float x0 = p.x / map->getTileSize().width;
	float y0 = ((map->getMapSize().height * map->getTileSize().height) - p.y) / map->getTileSize().height;
	int tilegid = wall->getTileGIDAt(Point(x0, y0));
	auto value = map->getPropertiesForGID(tilegid);
	auto op = Knight->getContentSize();
	float X = 0, Y = 0;
	float width = op.width;//骑士宽
	float height = op.height;//骑士高
	Vec2 tiledPos_up = tileCoordForPosition(Vec2(p.x, p.y + height));
	Vec2 tiledPos_down = tileCoordForPosition(Vec2(p.x, p.y - height));
	Vec2 tiledPos_left = tileCoordForPosition(Vec2(p.x - width, p.y));
	Vec2 tiledPos_right = tileCoordForPosition(Vec2(p.x + width, p.y));
	
	int tiledGid_up = wall->getTileGIDAt(tiledPos_up);
	int tiledGid_down = wall->getTileGIDAt(tiledPos_down);
	int tiledGid_left = wall->getTileGIDAt(tiledPos_left);
	int tiledGid_right = wall->getTileGIDAt(tiledPos_right);


	int floorGid_up = floor->getTileGIDAt(tiledPos_up);
	int floorGid_down = floor->getTileGIDAt(tiledPos_down);
	int floorGid_left = floor->getTileGIDAt(tiledPos_left);
	int floorGid_right = floor->getTileGIDAt(tiledPos_right);

	int tiled_sign;//墙3的id
	if (map_num == 0)
		tiled_sign = 52;
	else
		tiled_sign = 51;
	int barrier_sign = 47;//门的id


	if (Knight->get_speed_y() > 0 && (tiledGid_up == tiled_sign)) {
		Knight->set_speed_y(0);

	}
	else if (Knight->get_speed_x() > 0 && (tiledGid_right == tiled_sign)) {

		Knight->set_speed_x(0);
	}
	else if (Knight->get_speed_y() < 0 && (tiledGid_down == tiled_sign)) {
		Knight->set_speed_y(0);
	}
	else if (Knight->get_speed_x() < 0 && (tiledGid_left == tiled_sign)) {

		Knight->set_speed_x(0);
	}

	//对门的碰撞检测
	if (Knight->get_speed_y() > 0 && (floorGid_up == barrier_sign && _bool)) {
		/*Y -= Speed;*/
		Knight->set_speed_y(0);

	}
	else if (Knight->get_speed_x() > 0 && (floorGid_right == barrier_sign && _bool)) {

		Knight->set_speed_x(0);
		/*X -= Speed;*/
	}
	else if (Knight->get_speed_y() < 0 && (floorGid_down == barrier_sign && _bool)) {
		/*Y += Speed;*/
		Knight->set_speed_y(0);
	}
	else if (Knight->get_speed_x() < 0 && (floorGid_left == barrier_sign && _bool)) {

		//X += Speed;
		Knight->set_speed_x(0);
	}


	auto move = MoveBy::create(0.06, Vec2(10 * Knight->get_speed_x(), 10 * Knight->get_speed_y()));//运动持续0.2秒
	Knight->runAction(move);

	/*地图跟随骑士移动 by吴皖腾*/

	Point position = Knight->getPosition();
	auto winSize = Director::getInstance()->getWinSize();
	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);

	auto mapSize = map->getMapSize();

	auto tileSize = map->getTileSize();

	x = MIN(x, mapSize.width * tileSize.width - winSize.width / 2);
	y = MIN(y, mapSize.height * tileSize.height - winSize.height / 2);

	auto centerPoint = Point(winSize.width / 2, winSize.height / 2);
	auto actualPoint = Point(x, y);
	auto viewPoint = (centerPoint - actualPoint);

	TMXLayer* meta = map->getLayer("meta");
	map->setPosition(viewPoint);
}

/*生成怪物函数*/

void battle_scene::enemy_born(Vec2 v1, Vec2 v2, Vec2 v3, Vec2 v4, Vec2 v5, Vec2 v6, Vec2 v7, Vec2 v8, bool if_battle) {
	for (int i = 0; i < 5; i++) {
		Vec2 pos;
		melee1[i].set_map_num(map_num);
		melee1[i].init();
		mark_melee[i] = 0;
		if (i == 0)
			pos = v1;
		else if (i == 1)
			pos = v2;
		else if (i == 2)
			pos = v5;
		else if (i == 3)
			pos = v6;
		else
			pos = v7;
		melee1[i].get_sprite()->setPosition(pos);
		map->getChildByTag(100)->addChild(melee1[i].get_sprite(), 2);
		melee1[i].set_enemy_pos();
	}
	for (int i = 0; i < 3; i++) {
		Vec2 pos;
		remote1[i].set_map_num(map_num);
		remote1[i].init();
		mark_remote[i] = 0;
		if (i == 0)
			pos = v3;
		else if (i == 1)
			pos = v4;
		else
			pos = v8;
		remote1[i].get_sprite()->setPosition(pos);
		map->getChildByTag(100)->addChild(remote1[i].get_sprite(), 2);
		remote1[i].set_enemy_pos();
	}
	schedule(CC_SCHEDULE_SELECTOR(battle_scene::update_remote), 1.3);              //远程怪攻击的计时器    
	schedule(CC_SCHEDULE_SELECTOR(battle_scene::update), 1 / 60);                   //怪物的移动	
}
void battle_scene::enemy_born(Vec2 v1, Vec2 v2, Vec2 v3, Vec2 v4, Vec2 v5, Vec2 v6, bool if_battle)
{
	for (int i = 0; i < 4; i++) {
		Vec2 pos;
		melee1[i].set_map_num(map_num);
		melee1[i].init();
		mark_melee[i] = 0;
		if (i == 0)
			pos = v1;
		else if (i == 1)
			pos = v2;
		else if (i == 3)
			pos = v3;
		else
			pos = v4;
		melee1[i].get_sprite()->setPosition(pos);
		map->getChildByTag(100)->addChild(melee1[i].get_sprite(), 2);
		melee1[i].set_enemy_pos();
	}
	for (int i = 0; i < 2; i++) {
		Vec2 pos;
		remote1[i].set_map_num(map_num);
		remote1[i].init();
		mark_remote[i] = 0;
		if (i == 0)
			pos = v5;
		else
			pos = v6;
		remote1[i].get_sprite()->setPosition(pos);
		map->getChildByTag(100)->addChild(remote1[i].get_sprite(), 2);
		remote1[i].set_enemy_pos();
	}
	schedule(CC_SCHEDULE_SELECTOR(battle_scene::update_remote), 1.3);              //远程怪攻击的计时器    
	schedule(CC_SCHEDULE_SELECTOR(battle_scene::update), 1 / 60);                   //怪物的移动	
}
bool battle_scene::if_all_enemy_dead() {
	for (int i = 0; i < max_melee; i++) {
		if (!melee1[i].if_dead())
			return false;
	}
	for (int i = 0; i < max_remote; i++) {
		if (!remote1[i].if_dead())
			return false;
	}
	if (room_type == 1&&round_==1)
		if (!enemy_boss.if_dead())
			return false;
	return true;
}

void battle_scene::boss_born(Vec2 v1)
{
	enemy_boss.set_map_num(map_num);
	enemy_boss.init();
	mark_boss = 0;
	enemy_boss.get_sprite()->setPosition(v1);
	map->getChildByTag(100)->addChild(enemy_boss.get_sprite(), 2);
	schedule(CC_SCHEDULE_SELECTOR(battle_scene::update_remote), 1.3);              //远程怪攻击的计时器    
	schedule(CC_SCHEDULE_SELECTOR(battle_scene::update), 1 / 60);                   //怪物的移动	
}

void battle_scene::set_all_enemy_unvisible() {
	for (int i = 0; i < max_melee; i++) {
		melee1[i].get_sprite()->setVisible(false);
	}
	for (int i = 0; i < max_remote; i++) {
		remote1[i].get_sprite()->setVisible(false);
	}
	if (room_type == 1&&round_==1) {
		enemy_boss.setVisible(false);
	}
}
void battle_scene::update(float dt)
{
	/*怪物移动的部分 by施朱博
	操作思路：1、判定怪物是否死亡
			  2、未死亡则判定是否接近骑士
			  3、若不接近则随机游荡 若需要接近骑士 近战怪调用move函数并在完成移动后刷新坐标，作为游荡的起始位置
	*/
	
	srand(time(NULL));
	int seed = rand() % 3 + 1;
	for (int i = 0; i < max_melee; i++) {
		if (!melee1[i].if_dead()) {
			if (melee1[i].if_close_to_actor(Knight))
			{
				melee1[i].move(Knight);
				melee1[i].set_enemy_pos();
			}
			else
				melee1[i].wander(seed);
		}
	}
	for (int i = 0; i < max_remote; i++) {
		if (!remote1[i].if_dead()) {
			remote1[i].wander(seed);
		}
	}
	if(room_type==1&&round_==1)
		if (!enemy_boss.if_dead()) {
			enemy_boss.move(Knight);
		}

}
/*骑士开火 单独放在计时器里避免子弹连发间隔过短*/
void battle_scene::update_knight_fire(float dt)
{
	Knight->Weapon->fire();
	if (Knight->Weapon->get_click_check())
	{
		fire_bullet();
		Knight->Weapon->set_click_check(false);
	}
	schedule(CC_SCHEDULE_SELECTOR(battle_scene::update_check_bullet), 1 / 6);
}
/*检测子弹是否出墙*/
void battle_scene::update_check_bullet(float dt)
{
	if (Knight->Weapon->get_bullet() != nullptr)
	{
		Point p = Knight->Weapon->get_bullet()->getPosition();
		float x0 = p.x / map->getTileSize().width;
		float y0 = ((map->getMapSize().height * map->getTileSize().height) - p.y) / map->getTileSize().height;

		int tilegid = wall->getTileGIDAt(Point(x0, y0));
		if (map_num == 0) {
			if (tilegid == 52||(_bool&&tilegid==47))
			{
				Knight->Weapon->get_bullet()->setVisible(false);
				Knight->Weapon->get_bullet()->stopAllActions();
			}
		}
		if (map_num == 1) {
			if (tilegid == 51 || (_bool && tilegid == 47))
			{
				Knight->Weapon->get_bullet()->setVisible(false);
				Knight->Weapon->get_bullet()->stopAllActions();
			}
		}
	}
}

/*怪物攻击 计时器*/
void battle_scene::update_remote(float dt)
{
	for (int i = 0; i < max_melee; i++) {
		if (!melee1[i].if_dead()) {
			melee1[i].attack(Knight);
			schedule(CC_SCHEDULE_SELECTOR(battle_scene::update_bullet), 1 / 60);
		}
		else
			;//unschedule(CC_SCHEDULE_SELECTOR(battle_scene::update_bullet));
	}
	for (int i = 0; i < max_remote; i++) {
		if (!remote1[i].if_dead()) {
			remote1[i].attack(Knight);
			map->getChildByTag(100)->addChild(remote1[i].get_bullet(), 5);
			schedule(CC_SCHEDULE_SELECTOR(battle_scene::update_bullet), 1 / 60);
		}
		else
			;//unschedule(CC_SCHEDULE_SELECTOR(battle_scene::update_bullet));
	}
	if (room_type == 1&&round_==1) {
		unschedule(CC_SCHEDULE_SELECTOR(battle_scene::update_bullet));
		if (!enemy_boss.if_dead()) {
			enemy_boss.attack(Knight);
			for (int i = 0; i < 12; i++) {
				map->getChildByTag(100)->addChild(enemy_boss.bullet[i], 5);
			}
			schedule(CC_SCHEDULE_SELECTOR(battle_scene::update_bullet), 1 / 60);
		}
		else
			;// unschedule(CC_SCHEDULE_SELECTOR(battle_scene::update_bullet));
	}
	
}

/*
		  被update_remote调用
		  远程怪攻击 与骑士交互
*/
void battle_scene::update_bullet(float dt)
{
	for (int i = 0; i < max_melee; i++) {
		if (!melee1[i].if_dead() ) {
			if (melee1[i].if_collide(Knight, melee1[i].get_sprite())) {
				Knight->deduct_hp(melee1[i].get_attack());
				Knight->set_if_is_attacked(true);
				melee1[i].set_attack(0);
			}
		}
	}
	for (int i = 0; i < max_remote; i++) {
		Point p = remote1[i].get_bullet()->getPosition();
		float x0 = p.x / map->getTileSize().width;
		float y0 = ((map->getMapSize().height * map->getTileSize().height) - p.y) / map->getTileSize().height;
		int tilegid = wall->getTileGIDAt(Point(x0, y0));
		if (map_num == 0) {
			if (tilegid == 52 || (_bool && tilegid == 47))
			{
				remote1[i].get_bullet()->setVisible(false);
				remote1[i].get_bullet()->stopAllActions();
			}
		}
		if (map_num == 1) {
			if (tilegid == 51 || (_bool && tilegid == 47))
			{
				remote1[i].get_bullet()->setVisible(false);
				remote1[i].get_bullet()->stopAllActions();
			}
		}
		if (remote1[i].if_collide(Knight, remote1[i].get_bullet())) {
			remote1[i].get_bullet()->setVisible(false);
			Knight->deduct_hp(remote1[i].get_attack());
			Knight->set_if_is_attacked(true);
			remote1[i].set_attack(0);
		}
	}
	if (room_type == 1&&round_==1) {
		if (enemy_boss.get_sprite() == nullptr)
			return;
		if (!enemy_boss.if_dead()) {
			for (int i = 0; i < 12; i++) {
				Point p = enemy_boss.bullet[i]->getPosition();
				float x0 = p.x / map->getTileSize().width;
				float y0 = ((map->getMapSize().height * map->getTileSize().height) - p.y) / map->getTileSize().height;
				if (x0 < 0||y0<0)
					return;
				
				//int tilegid = wall->getTileGIDAt(Point(x0, y0));
				if (map_num == 0) {
					/*
					if (tilegid == 52 || (_bool && tilegid == 47))
					{
						enemy_boss.bullet[i]->setVisible(false);
						enemy_boss.bullet[i]->stopAllActions();
					}*/
				}
				if (map_num == 1) {
					/*if (tilegid == 51 || (_bool && tilegid == 47))
					{
						enemy_boss.bullet[i]->setVisible(false);
						enemy_boss.bullet[i]->stopAllActions();
					}*/
				}
				if (enemy_boss.if_collide(Knight, enemy_boss.bullet[i])) {
					enemy_boss.bullet[i]->setVisible(false);
					Knight->deduct_hp(enemy_boss.get_attack());
					Knight->set_if_is_attacked(true);
					enemy_boss.set_attack(0);
				}
			}
		}
	}
	/*判定骑士是否死亡*/
	if (Knight->if_dead()) {
		Knight->setVisible(false);
		for (int i = 0; i < 4; i++) {
			enter_room[i] = 0;
		}
		hp = Knight->get_max_hp();
		mhp = Knight->get_max_hp();
		mmp = Knight->get_max_mp();
		mp = Knight->get_max_mp();
		armor = Knight->get_max_sheild();
		weapon_name = "OldPistal.png";
		bullet_name = "old pistal bullet.png";
		damage = 5;
		mp_cost == 0;
		Director::getInstance()->replaceScene(safe_scene::createWithPhysics());
		//Director::getInstance()->popScene();
	}
}
/*判定骑士是否恢复护甲*/
void battle_scene::update_if_recover_armor(float dt)
{
	if (!Knight->get_if_is_attacked() && !Knight->if_armor_max()) {
		schedule(CC_SCHEDULE_SELECTOR(battle_scene::update_recover_armor), 1);
	}
	else
		unschedule(CC_SCHEDULE_SELECTOR(battle_scene::update_recover_armor));
	Knight->set_if_is_attacked(false);
}

/*骑士恢复护甲*/
void battle_scene::update_recover_armor(float dt)
{
	Knight->recover_armor(1);
}
/*骑士的子弹对怪的效果，在firebullet中被调用*/
void battle_scene::update_bullet_to_enemy(float dt)
{
	for (int i = 0; i < max_melee; i++) {
		if (!melee1[i].if_dead()) {
			if (melee1[i].if_collide(Knight->Weapon->get_bullet(), melee1[i].get_sprite())) {
				Knight->Weapon->get_bullet()->setVisible(false);
				melee1[i].deduct_hp(Knight->Weapon->get_bullet_demage());
				Knight->Weapon->set_demage(0);
			}
		}
		else if(mark_melee[i]==0){
			melee1[i].get_sprite()->setVisible(false);
			mark_melee[i]++;
		}
	}
	for (int i = 0; i < max_remote; i++) {
		if (!remote1[i].if_dead()) {
			if (remote1[i].if_collide(Knight->Weapon->get_bullet(), remote1[i].get_sprite())) {
				Knight->Weapon->get_bullet()->setVisible(false);
				remote1[i].deduct_hp(Knight->Weapon->get_bullet_demage());
				Knight->Weapon->set_demage(0);
			}
		}
		else if(mark_remote[i]==0){
			if (Knight->get_if_get_recover_mp_buff())
			{
				if (Knight->get_mp() + 2 < Knight->get_max_mp())
				{
					Knight->set_mp(Knight->get_mp() + 2);
				}
				else
				{
					Knight->set_mp(Knight->get_max_mp());
				}
			}
			remote1[i].get_sprite()->setVisible(false);
			mark_remote[i]++;
		}
	}
	if (room_type == 1&&round_==1) {
		if (!enemy_boss.if_dead()) {
			if (enemy_boss.if_collide(Knight->Weapon->get_bullet(), enemy_boss.get_sprite())) {
				Knight->Weapon->get_bullet()->setVisible(false);
				enemy_boss.deduct_hp(Knight->Weapon->get_bullet_demage());
				Knight->Weapon->set_demage(0);
			}
		}
		else if(mark_boss==0){
			enemy_boss.get_sprite()->setVisible(false);
			mark_boss++;
		}
	}
}


void battle_scene::delete_bullet()
{
	if (Knight->Weapon->get_pos().x < -1 * Director::getInstance()->getVisibleSize().width / 2 || Knight->Weapon->get_pos().x < -1 * Director::getInstance()->getVisibleSize().height / 2
		|| Knight->Weapon->get_pos().x > 1 * Director::getInstance()->getVisibleSize().width / 2 || Knight->Weapon->get_pos().x > 1 * Director::getInstance()->getVisibleSize().height / 2)
	{
		this->removeChild(Knight->Weapon->get_bullet(), 1);
	}
}

void battle_scene::fire_bullet()
{
	std::string a = "big_knife.png";
	if (Knight->Weapon->get_weapon_name().c_str() == a)
	{
		auto rotate = RotateBy::create(0.5, 360);
		Knight->Weapon->runAction(rotate);
		//抡人的函数
	}
	if (Knight->get_mp() >= Knight->Weapon->get_bullet_cost())
	{
		Knight->Weapon->set_bullet(Sprite::create(Knight->Weapon->get_bullet_name()));
		Knight->Weapon->set_demage(Knight->Weapon->get_original_demage());
		/*施朱博对于骑士子弹与怪碰撞的修改
		* 进入战斗状态后再检测子弹是否与怪碰撞
		*/
		if (_bool)
			schedule(CC_SCHEDULE_SELECTOR(battle_scene::update_bullet_to_enemy), 1 / 60);
		else
			unschedule(CC_SCHEDULE_SELECTOR(battle_scene::update_bullet_to_enemy));
		if (Knight->isFlippedX())
		{
			Knight->Weapon->get_bullet()->setPosition(Knight->getPosition().x - 40, Knight->getPosition().y - 10);
		}
		else
		{
			Knight->Weapon->get_bullet()->setPosition(Knight->getPosition().x + 40, Knight->getPosition().y - 10);
		}
		map->getChildByTag(100)->addChild(Knight->Weapon->get_bullet(), 2);
		float rad = atan2(Knight->Weapon->get_pos().x, Knight->Weapon->get_pos().y);
		float degree = CC_RADIANS_TO_DEGREES(rad);
		auto rotate = RotateTo::create(0.001, degree - 90);
		float delta = sqrt(Knight->Weapon->get_pos().x * Knight->Weapon->get_pos().x + Knight->Weapon->get_pos().y * Knight->Weapon->get_pos().y);
		auto bullet_move = MoveBy::create(100 / Knight->Weapon->get_bullet_speed(), Vec2(600000 * Knight->Weapon->get_pos().x / delta, 600000 * Knight->Weapon->get_pos().y / delta));
		auto action = Sequence::create(rotate, bullet_move, NULL);
		Knight->Weapon->get_bullet()->runAction(action);
		Knight->set_mp(Knight->get_mp() - Knight->Weapon->get_bullet_cost());
		id_3_ = AudioEngine::play2d("fire1.mp3", false, volume3_);
	}
}

void battle_scene::set_knight(int mp, int mp_max, int hp, int max_hp, int armor)
{
	Knight->set_hp(hp);
	Knight->set_mp(mp);
	Knight->set_max_hp(max_hp);
	Knight->set_max_mp(mp_max);
	Knight->set_max_armor(armor);
}

void battle_scene::create_unpicked_weapon(Vec2 pos, std::string name, std::string bulllet_name)
{
	const char* c1 = name.c_str();
	const char* c2 = bulllet_name.c_str();

	weapon_map[pos] = weapon::create(c1);
	weapon_map[pos]->setPosition(pos);
	weapon_map[pos]->set_bullet_name(c2);
	weapon_map[pos]->set_weapon_name(c1);
	//************************************************************************************************************************
	if (name == "M2.png")
	{
		weapon_map[pos]->set_demage(7);
		weapon_map[pos]->set_bullet_cost(1);

	}
	else if (name == "OldPistal.png")
	{
		weapon_map[pos]->set_demage(5);
		weapon_map[pos]->set_bullet_cost(0);
	}
	//*************************************************************************************************************************
	map->getChildByTag(100)->addChild(weapon_map[pos], 10);
}

void battle_scene::delete_picked_weapon(Vec2 pos)
{
	if (weapon_map[pos] != nullptr)
	{
		map->getChildByTag(100)->removeChild(weapon_map[pos]);
	}
}

std::map<Vec2, weapon*> battle_scene::get_weapon_map()
{
	return weapon_map;
}

void battle_scene::gun_switch()
{

	Knight->set_E_check(false);
	Vec2 Knight_pos = Knight->getPosition();
	std::map<Vec2, weapon*>::iterator iter;
	for (iter = weapon_map.begin(); iter != weapon_map.end(); iter++)
	{
		if (sqrt(pow((iter->first.x - Knight_pos.x), 2) + pow((iter->first.y - Knight_pos.y), 2)) <= 200)
		{
			weapon* Knight_weapon = Knight->Weapon;
			create_unpicked_weapon(Knight_pos, Knight_weapon->get_weapon_name(), Knight_weapon->get_bullet_name());
			Knight->removeChild(Knight->Weapon, 1);
			// Knight->weapon_init();
			Knight->picked_weapon_init(iter->second->get_weapon_name(), iter->second->get_bullet_name(), iter->second->get_bullet_demage(), iter->second->get_bullet_cost());
			delete_picked_weapon(iter->first);
			weapon_map.erase(iter);
			break;
		}
	}
}

//血量 蓝条 护甲的计时器 马昕岳***************************************************************************************************************************************************************

void battle_scene::schedule_HP(float delta)
{
	auto progress = (ProgressTimer*)this->getChildByName("HP_bar");
	progress->setPercentage((((float)Knight->get_hp()) / Knight->get_max_hp()) * 100);  //这里是百分制显示
	if (progress->getPercentage() < 0)
	{
		unschedule(CC_SCHEDULE_SELECTOR(battle_scene::schedule_HP));
	}
}

void battle_scene::schedule_sheild(float delta)
{
	auto progress = (ProgressTimer*)this->getChildByName("sheild_bar");
	progress->setPercentage((((float)Knight->get_sheild()) / Knight->get_max_sheild()) * 100);  //这里是百分制显示
	if (progress->getPercentage() < 0)
	{
		unschedule(CC_SCHEDULE_SELECTOR(battle_scene::schedule_sheild));
	}
}

void battle_scene::schedule_MP(float delta)
{
	auto progress = (ProgressTimer*)this->getChildByName("MP_bar");
	progress->setPercentage((((float)Knight->get_mp()) / Knight->get_max_mp()) * 100);  //这里是百分制显示
	if (progress->getPercentage() < 0)
	{
		unschedule(CC_SCHEDULE_SELECTOR(battle_scene::schedule_MP));
	}
}

//*****************************************************************************************************************************************************************************************
//buff系统 马昕岳*********************************************************************************************************************
void battle_scene::create_buff_add_max_hp(Vec2 pos)
{
	auto buff_image = MenuItemImage::create(
		"add_max_hp_buff.png", "add_max_hp_buff.png",
		CC_CALLBACK_1(battle_scene::create_buff_add_max_hp_callback, this));

	if (buff_image == nullptr ||
		buff_image->getContentSize().width <= 0 ||
		buff_image->getContentSize().height <= 0)
	{
		//problemLoading("add_max_hp_buff.png");
	}
	else
	{
		float x = pos.x;
		float y = pos.y;
		buff_image->setPosition(Vec2(x, y));
	}
	auto menu = Menu::create(buff_image, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}
void battle_scene::create_buff_add_max_hp_callback(cocos2d::Ref* pSender)
{
	Knight->set_max_hp(Knight->get_max_hp() + 1);
	//之后在此加入场景切换函数
}

void battle_scene::create_buff_add_max_mp(Vec2 pos)
{
	auto buff_image = MenuItemImage::create(
		"increase_max_mp_buff.jpg", "increase_max_mp_buff.jpg",
		CC_CALLBACK_1(battle_scene::create_buff_add_max_mp_callback, this));

	if (buff_image == nullptr ||
		buff_image->getContentSize().width <= 0 ||
		buff_image->getContentSize().height <= 0)
	{
		//problemLoading("increase_max_mp_buff.jpg");
	}
	else
	{
		float x = pos.x;
		float y = pos.y;
		buff_image->setPosition(Vec2(x, y));
	}


	auto menu = Menu::create(buff_image, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}
void battle_scene::create_buff_add_max_mp_callback(cocos2d::Ref* pSender)
{
	Knight->set_max_mp(Knight->get_max_mp() + 40);
	//之后在此加入场景切换函数
}

void battle_scene::create_buff_add_attack_speed(Vec2 pos)
{
	auto buff_image = MenuItemImage::create(
		"add_attack_speed_buff.png", "add_attack_speed_buff.png",
		CC_CALLBACK_1(battle_scene::create_buff_add_attack_speed_callback, this));

	if (buff_image == nullptr ||
		buff_image->getContentSize().width <= 0 ||
		buff_image->getContentSize().height <= 0)
	{
		//problemLoading("add_attack_speed_buff.png");
	}
	else
	{
		float x = pos.x;
		float y = pos.y;
		buff_image->setPosition(Vec2(x, y));
	}


	auto menu = Menu::create(buff_image, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}
void battle_scene::create_buff_add_attack_speed_callback(cocos2d::Ref* pSender)
{
	Knight->set_if_get_add_attack_speed_buff(1);
	//之后在此加入场景切换函数
}



void battle_scene::create_buff_arrmor(Vec2 pos)
{
	auto buff_image = MenuItemImage::create(
		"armor_buff.jpg", "armor_buff.jpg",
		CC_CALLBACK_1(battle_scene::create_buff_arrmor_callback, this));

	if (buff_image == nullptr ||
		buff_image->getContentSize().width <= 0 ||
		buff_image->getContentSize().height <= 0)
	{
		//problemLoading("armor_buff.jpg");
	}
	else
	{
		float x = pos.x;
		float y = pos.y;
		buff_image->setPosition(Vec2(x, y));
	}


	auto menu = Menu::create(buff_image, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}
void battle_scene::create_buff_arrmor_callback(cocos2d::Ref* pSender)
{
	Knight->set_if_get_arrmor_buff(1);
	//之后在此加入场景切换函数
}

void battle_scene::create_buff_recover_mp(Vec2 pos)
{
	auto buff_image = MenuItemImage::create(
		"recover_mp_buff.jpg", "recover_mp_buff.jpg",
		CC_CALLBACK_1(battle_scene::create_buff_recover_mp_callback, this));

	if (buff_image == nullptr ||
		buff_image->getContentSize().width <= 0 ||
		buff_image->getContentSize().height <= 0)
	{
		//problemLoading("recover_mp_buff.jpg");
	}
	else
	{
		float x = pos.x;
		float y = pos.y;
		buff_image->setPosition(Vec2(x, y));
	}


	auto menu = Menu::create(buff_image, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}
void battle_scene::create_buff_recover_mp_callback(cocos2d::Ref* pSender)
{
	Knight->set_if_get_recover_mp_buff(1);
	//之后在此加入场景切换函数
}
//buff系统 马昕岳*********************************************************************************************************************

bool battle_scene::isTileBlocked(Point position)
{
	Point tilePos = tileToWin(position);
	int tileGID = wall->getTileGIDAt(tilePos);

	if (tileGID != 0)
	{
		auto properties = map->getPropertiesForGID(tileGID).asValueMap();
		if (!properties.empty())
		{
			auto canMove = properties["unblocked"].asString();
			if ("true" == canMove)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}
Point battle_scene::tileToWin(Point position)
{
	int x = position.x / map->getTileSize().width;
	int y = (map->getTileSize().height * map->getMapSize().height - position.y) / map->getTileSize().height;
	return Point(x, y);
}
Vec2 battle_scene::tileCoordForPosition(Vec2 p) {
	//获取屏幕显示大小
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// 获取瓦片地图的尺寸(瓦片数量)
	auto mapTiledNum = map->getMapSize();
	///获取单个瓦片的尺寸(pixel)
	auto tiledSize = map->getTileSize();

	//x表示瓦片地图上第几个瓦片
	int x0 = p.x / map->getTileSize().width;
	int y0 = ((map->getMapSize().height * map->getTileSize().height) - p.y) / map->getTileSize().height;

	//cocos2dx与tiledmap坐标不同

	//格子坐标从零开始
	return Vec2(x0, y0);
}
//获取格子坐标
/*
Scene* battle_scene::create_buff_scene()
{
	auto scene = Scene::create();

	return scene;
}*/

