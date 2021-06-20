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

	//

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
	HP_bottle = Sprite::create("HP_bottle.png");
	MP_bottle = Sprite::create("MP_bottle.png");
	create_unpicked_weapon(Vec2(400, 400), "M2.png", "M2 bullet.png");
	create_unpicked_weapon(Vec2(400, 400), "big_knife.png", "knife_bullet.png");
	create_supply(Vec2(390, 230));
	/*计时器部分*/
	schedule(CC_SCHEDULE_SELECTOR(safe_scene::update),1/60);                   //骑士的一系列动作   怪物的移动

	//schedule(CC_SCHEDULE_SELECTOR(safe_scene::update_knight_fire), 0.4);
	return true;
}

void safe_scene::update(float dt)
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
	



	auto move = MoveBy::create(0.2, Vec2(10 * Knight->get_speed_x(), 10 * Knight->get_speed_y()));
	Knight->runAction(move);
	if (Knight->get_E_check())
	{
		gun_switch();
	}
	//创造补给和捡起补给 马昕岳***********************************************************************************************************
	pick_up_supply();
	//创造补给和捡起补给 马昕岳***********************************************************************************************************
	//delete_bullet();

	/*怪物移动的部分 by施朱博
	操作思路：1、判定怪物是否死亡
	          2、未死亡则判定是否接近骑士
			  3、若不接近则随机游荡 若需要接近骑士 近战怪调用move函数并在完成移动后刷新坐标，作为游荡的起始位置
	*/

	
}
/*骑士开火 单独放在计时器里避免子弹连发间隔过短*/
void safe_scene::update_knight_fire(float dt)
{
	Knight->Weapon->fire();
	if (Knight->Weapon->get_click_check())
	{
		fire_bullet();
		Knight->Weapon->set_click_check(false);
	}
}
/*判定骑士是否恢复护甲*/
void safe_scene::update_if_recover_armor(float dt)
{
	if (!Knight->get_if_is_attacked() && !Knight->if_armor_max()) {
		schedule(CC_SCHEDULE_SELECTOR(safe_scene::update_recover_armor), 1);
	}
	else
		unschedule(CC_SCHEDULE_SELECTOR(safe_scene::update_recover_armor));
	Knight->set_if_is_attacked(false);
}

/*骑士恢复护甲*/
void safe_scene::update_recover_armor(float dt)
{
	Knight->recover_armor(1);
}

void safe_scene::delete_bullet()
{
	if (Knight->Weapon->get_pos().x < -1 * Director::getInstance()->getVisibleSize().width / 2 || Knight->Weapon->get_pos().x < -1 * Director::getInstance()->getVisibleSize().height / 2
		|| Knight->Weapon->get_pos().x > 1 * Director::getInstance()->getVisibleSize().width / 2 || Knight->Weapon->get_pos().x > 1 * Director::getInstance()->getVisibleSize().height / 2)
	{
		this->removeChild(Knight->Weapon->get_bullet(), 1);
	}
}

void safe_scene::fire_bullet()
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
		if (Knight->isFlippedX())
		{
			Knight->Weapon->get_bullet()->setPosition(Knight->getPosition().x - 40, Knight->getPosition().y - 10);
		}
		else
		{
			Knight->Weapon->get_bullet()->setPosition(Knight->getPosition().x + 40, Knight->getPosition().y - 10);
		}
		this->addChild(Knight->Weapon->get_bullet(), 2);
		float rad = atan2(Knight->Weapon->get_pos().x, Knight->Weapon->get_pos().y);
		float degree = CC_RADIANS_TO_DEGREES(rad);
		auto rotate = RotateTo::create(0.001, degree - 90);
		float delta = sqrt(Knight->Weapon->get_pos().x * Knight->Weapon->get_pos().x + Knight->Weapon->get_pos().y * Knight->Weapon->get_pos().y);
		auto bullet_move = MoveBy::create(100 / Knight->Weapon->get_bullet_speed(), Vec2(600000 * Knight->Weapon->get_pos().x / delta, 600000 * Knight->Weapon->get_pos().y / delta));
		auto action = Sequence::create(rotate, bullet_move, NULL);
		Knight->Weapon->get_bullet()->runAction(action);
		Knight->set_mp(Knight->get_mp() - Knight->Weapon->get_bullet_cost());
		id_3 = AudioEngine::play2d("fire1.mp3", false, volume3);
	}
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

	//  auto size = Director::getInstance()->getWinSize();

	//   auto layer_stop = LayerColor::create(Color4B(0, 255, 0, 120), 200, 200);
	//   this->addChild(layer_stop, 2);
	Director::getInstance()->startAnimation();

	//   this->removeChild(layer_stop, 2);
}



void safe_scene::create_unpicked_weapon(Vec2 pos, std::string name, std::string bulllet_name)
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
	else if (name == "big_knife.png")
	{
		weapon_map[pos]->set_demage(20);
		weapon_map[pos]->set_bullet_cost(10);
	}
	//*************************************************************************************************************************
	addChild(weapon_map[pos],10);
}

void safe_scene::delete_picked_weapon(Vec2 pos)
{
	if (weapon_map[pos] != nullptr)
	{
		removeChild(weapon_map[pos]);
	}
}

std::map<Vec2, weapon*> safe_scene::get_weapon_map()
{
	return weapon_map;
}

void safe_scene::gun_switch()
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
			//CCLOG("%d", weapon_map.size());
			break;

		}
	}
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

//*****************************************************************************************************************************************************************************************


//创造补给和捡起补给 马昕岳***********************************************************************************************************
void safe_scene::create_supply(Vec2 pos)
{

	int judge;

	srand(time(NULL));
	judge = rand() % 2;
	if (judge == 1)
	{

		HP_bottle->setPosition(pos);
		this->addChild(HP_bottle,3);
		HP_bottle_exist = 1;
	}
	else
	{

		MP_bottle->setPosition(pos);
		this->addChild(MP_bottle,3);
		MP_bottle_exist = 1;
	}
}

void safe_scene::pick_up_supply()
{

	if (Knight->get_Q_check())
	{
		if (HP_bottle_exist && sqrt((Knight->getPosition().x - HP_bottle->getPosition().x) * (Knight->getPosition().x - HP_bottle->getPosition().x) + (Knight->getPosition().y - HP_bottle->getPosition().y) * (Knight->getPosition().y - HP_bottle->getPosition().y)) <= 80)
		{


			if (Knight->get_hp() + 2 > Knight->get_max_hp())
			{
				Knight->set_hp(Knight->get_max_hp());
			}
			else
			{
				Knight->set_hp(Knight->get_hp() + 2);
			}
			removeChild(HP_bottle);
		}
		else if (MP_bottle_exist && sqrt((Knight->getPosition().x - MP_bottle->getPosition().x) * (Knight->getPosition().x - MP_bottle->getPosition().x) + (Knight->getPosition().y - MP_bottle->getPosition().y) * (Knight->getPosition().y - MP_bottle->getPosition().y)) <= 80)
		{
			if (Knight->get_mp() + 80 > Knight->get_max_mp())
			{
				Knight->set_mp(Knight->get_max_mp());
			}
			else
			{
				Knight->set_mp(Knight->get_mp() + 80);
			}
			removeChild(MP_bottle);
		}
		Knight->set_Q_check(false);
	}
}
//创造补给和捡起补给 马昕岳***********************************************************************************************************


//buff系统 马昕岳*********************************************************************************************************************
void safe_scene::create_buff_add_max_hp(Vec2 pos)
{
	auto buff_image = MenuItemImage::create(
		"add_max_hp_buff.png", "add_max_hp_buff.png",
		CC_CALLBACK_1(safe_scene::create_buff_add_max_hp_callback, this));

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
void safe_scene::create_buff_add_max_hp_callback(cocos2d::Ref* pSender)
{
	Knight->set_max_hp(Knight->get_max_hp() + 1);
	//之后在此加入场景切换函数
}

void safe_scene::create_buff_add_max_mp(Vec2 pos)
{
	auto buff_image = MenuItemImage::create(
		"increase_max_mp_buff.jpg", "increase_max_mp_buff.jpg",
		CC_CALLBACK_1(safe_scene::create_buff_add_max_mp_callback, this));

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
void safe_scene::create_buff_add_max_mp_callback(cocos2d::Ref* pSender)
{
	Knight->set_max_mp(Knight->get_max_mp() + 40);
	//之后在此加入场景切换函数
}

void safe_scene::create_buff_add_attack_speed(Vec2 pos)
{
	auto buff_image = MenuItemImage::create(
		"add_attack_speed_buff.png", "add_attack_speed_buff.png",
		CC_CALLBACK_1(safe_scene::create_buff_add_attack_speed_callback, this));

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
void safe_scene::create_buff_add_attack_speed_callback(cocos2d::Ref* pSender)
{
	Knight->set_if_get_add_attack_speed_buff(1);
	//之后在此加入场景切换函数
}



void safe_scene::create_buff_arrmor(Vec2 pos)
{
	auto buff_image = MenuItemImage::create(
		"armor_buff.jpg", "armor_buff.jpg",
		CC_CALLBACK_1(safe_scene::create_buff_arrmor_callback, this));

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
void safe_scene::create_buff_arrmor_callback(cocos2d::Ref* pSender)
{
	Knight->set_if_get_arrmor_buff(1);
	//之后在此加入场景切换函数
}

void safe_scene::create_buff_recover_mp(Vec2 pos)
{
	auto buff_image = MenuItemImage::create(
		"recover_mp_buff.jpg", "recover_mp_buff.jpg",
		CC_CALLBACK_1(safe_scene::create_buff_recover_mp_callback, this));

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
void safe_scene::create_buff_recover_mp_callback(cocos2d::Ref* pSender)
{
	Knight->set_if_get_recover_mp_buff(1);
	//之后在此加入场景切换函数
}
//buff系统 马昕岳*********************************************************************************************************************