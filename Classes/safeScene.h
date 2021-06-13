#pragma once
#ifndef _SAFE_SCENE_H_
#define  _SAFE_SCENE_H_
#include"cocos2d.h"
#include"Enemy.h"
#include"knight.h"
USING_NS_CC;

class safe_scene :public Scene {
public:

	static Scene* createWithPhysics();



	void menuCloseCallback4(cocos2d::Ref* pSender);
	void menuCloseCallback5(cocos2d::Ref* pSender);
	void menuCloseCallback_stop(cocos2d::Ref* pSender);
	void menuCloseCallback_go(cocos2d::Ref* pSender);
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
	// a selector callback
	std::map<Vec2, weapon*> get_weapon_map();


private:
	knight* Knight;
	enemy_melee1 enemy_1;
	enemy_melee2 enemy_2;
	enemy_remote1 enemy_3;
	enemy_remote2 enemy_4;
	std::map<Vec2, weapon*> weapon_map;
	Sprite* HP;
	Sprite* MP;
	Sprite* Sheild;
	Sprite* UIBase;
};


#endif