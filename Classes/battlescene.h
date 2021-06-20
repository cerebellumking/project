#pragma once

#ifndef _battlescene_H_
#define  _battlescene_H_
#include"cocos2d.h"
#include"Enemy.h"
#include"knight.h"
#include"preserve.h"
USING_NS_CC;

class battle_scene :public Scene
{

public:

	TMXTiledMap* map;
	TMXLayer* wall;
	TMXLayer* wall_;
	TMXLayer* floor;
	bool isTileBlocked(Point position);
	Point tileToWin(Point position);
	Vec2 tileCoordForPosition(Vec2 point);
	//static Scene* create_buff_scene();        //生成buff的场景
	
	static Scene* createWithPhysics();
	void update_follow(float dt);
	virtual bool init();

	//by 黄远宏


	//virtual void onKeyPressed_start(EventKeyboard::KeyCode keycode, Event* event);
	void menuCloseCallback_up(cocos2d::Ref* pSender);
	void menuCloseCallback_down(cocos2d::Ref* pSender);
	void menuCloseCallback_stop(cocos2d::Ref* pSender);
	void menuCloseCallback_go(cocos2d::Ref* pSender);
	void menuReturnCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(battle_scene);
	Sprite* door;
	Sprite* guard1;
	Sprite* guard2;
	Sprite* guard3;
	Sprite* guard4;
	Sprite* guard5;
	Sprite* tutor;
	virtual void onKeyPressed_safe(EventKeyboard::KeyCode keycode, Event* event);
	void battle_scene::onKeyPressed_tutor(EventKeyboard::KeyCode keycode, Event* event);
	/*施朱博*/
	void update(float dt) override;
	void update_knight_fire(float dt);
	void update_remote(float dt);
	void update_bullet(float dt);
	void update_if_recover_armor(float dt);
	void update_recover_armor(float dt);
	void update_bullet_to_enemy(float dt);
	void update_if_battle(float dt);
	void set_all_enemy_unvisible();
	void update_check_bullet(float dt);
	void enemy_born(Vec2 v1, Vec2 v2, Vec2 v3, Vec2 v4, Vec2 v5, Vec2 v6, Vec2 v7, Vec2 v8, bool if_battle);    //怪物生成函数
	void enemy_born(Vec2 v1, Vec2 v2, Vec2 v3, Vec2 v4,Vec2 v5,Vec2 v6, bool if_battle);    //怪物生成函数
	void boss_born(Vec2 v1);
	bool if_all_enemy_dead(); //判断当前的怪是否全部消灭

	void set_knight(int mp, int mp_max, int hp, int max_hp, int armor);

	/*创作者：马昕岳*/
	void create_unpicked_weapon(Vec2 pos, std::string name, std::string bulllet_name);
	void delete_picked_weapon(Vec2 pos);
	void gun_switch();
	void fire_bullet();
	void delete_bullet();
	std::map<Vec2, weapon*> get_weapon_map();
	void schedule_HP(float delta);
	void schedule_sheild(float delta);
	void schedule_MP(float delta);
	//buff系统 马昕岳*********************************************************************************************************************
	void create_buff_add_max_hp(Vec2 pos);
	void create_buff_add_max_mp(Vec2 pos);
	void create_buff_add_attack_speed(Vec2 pos);
	void create_buff_arrmor(Vec2 pos);
	void create_buff_recover_mp(Vec2 pos);

	void create_buff_add_max_hp_callback(cocos2d::Ref* pSender);
	void create_buff_add_max_mp_callback(cocos2d::Ref* pSender);
	void create_buff_add_attack_speed_callback(cocos2d::Ref* pSender);
	void create_buff_arrmor_callback(cocos2d::Ref* pSender);
	void create_buff_recover_mp_callback(cocos2d::Ref* pSender);

	void create_supply(Vec2 pos);
	void pick_up_supply();
	//buff系统 马昕岳*********************************************************************************************************************
	void  battle_scene::create_boss_HP_bar();
	void  battle_scene::schedule_boss_HP(float delta);
private:
	knight* Knight;
	std::map<Vec2, weapon*> weapon_map;
	Sprite* HP;
	Sprite* MP;
	Sprite* Sheild;
	Sprite* UIBase;
	bool _bool;
	//创造补给和捡起补给 马昕岳***********************************************************************************************************
	Sprite* HP_bottle;
	Sprite* MP_bottle;
	bool HP_bottle_exist;
	bool MP_bottle_exist;
	//创造补给和捡起补给 马昕岳***********************************************************************************************************
	/*怪物*/
	enemy_melee1 enemy_1;
	enemy_melee2 enemy_2;
	enemy_remote1 enemy_3;
	enemy_remote2 enemy_4;
	/*怪物数组*/
	enemy_melee1 melee1[5];
	enemy_remote1 remote1[3];
	int mark_melee[5] = {};
	int mark_remote[3] = {};
	int mark_boss=0;
	boss enemy_boss;
	int wave[5] = {};           //存放战斗房刷怪的波数
	int room_num=4;
	int max_melee=0;
	int max_remote=0;
	int room_type = 0;
};

#endif