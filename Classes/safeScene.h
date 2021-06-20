#pragma once
#ifndef _SAFE_SCENE_H_
#define  _SAFE_SCENE_H_
#include"cocos2d.h"
#include"Enemy.h"
#include"knight.h"
#include"battlescene.h"
USING_NS_CC;

class safe_scene :public Scene {
public:

	static Scene* createWithPhysics();
	/*黄远宏修改部分*/
	virtual void onKeyPressed_start(EventKeyboard::KeyCode keycode, Event* event);

	void menuCloseCallback_up(cocos2d::Ref* pSender);
	void menuCloseCallback_down(cocos2d::Ref* pSender);
	void menuCloseCallback_stop(cocos2d::Ref* pSender);
	void menuCloseCallback_go(cocos2d::Ref* pSender);

	/*黄远宏的初版
	void menuCloseCallback4(cocos2d::Ref* pSender);
	void menuCloseCallback5(cocos2d::Ref* pSender);
	void menuCloseCallback_stop(cocos2d::Ref* pSender);
	void menuCloseCallback_go(cocos2d::Ref* pSender);
*/

	virtual bool init();
	void update(float dt) override;
	void update_knight_fire(float dt);
	void update_remote(float dt);
	void update_bullet(float dt);
	void update_if_recover_armor(float dt);
	void update_recover_armor(float dt);
	void update_bullet_to_enemy(float dt);
	void menuReturnCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(safe_scene);

	
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
private:
	knight* Knight;
	enemy_melee1 enemy_1;
	enemy_melee2 enemy_2;
	enemy_remote1 enemy_3;
	enemy_remote2 enemy_4;
	/*怪物数组*/
	enemy_melee1 melee[4];
	
	std::map<Vec2, weapon*> weapon_map;
	Sprite* HP;
	Sprite* MP;
	Sprite* Sheild;
	Sprite* UIBase;
	Sprite* door;

	//创造补给和捡起补给 马昕岳***********************************************************************************************************
	Sprite* HP_bottle;
	Sprite* MP_bottle;
	bool HP_bottle_exist;
	bool MP_bottle_exist;
	//创造补给和捡起补给 马昕岳***********************************************************************************************************
};


#endif