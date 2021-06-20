#pragma once

#ifndef _Enemy_H_
#define _Enemy_H_

#include"knight.h"
#include"sprite.h"
#include"cocos2d.h"

USING_NS_CC;

//怪物基类

class enemy:public sprite_living
{
	
private:
	int map_num;
	float sight_distance;                                     //怪物视野
	float attack_distance;                                    //怪物攻击范围
	Vec2 enemy_pos;                                           //怪物坐标（用于巡逻边界的判定，并非实时更新）
	Vec2 knight_pos;                                          //attack动作发生瞬间骑士坐标，每一次攻击时重新获取
public:
	enemy() = default;

	virtual ~enemy()=default;
    //virtual bool init();
	CREATE_FUNC(enemy);
	void set_sight_distance(float sight_distance);              //设置视野
	void set_attack_distance(float attack_distance);            //设置攻击范围
	float get_distance(knight* Knight);                         //获取怪物与骑士之间的直线距离
	float get_distancex(knight* Knight);                        //获取怪物与骑士之间的x轴方向距离
	float get_distancey(knight* Knight);                        //获取怪物与骑士之间的y轴方向距离
	//virtual void death_animation();                           //播放死亡动画
	virtual bool if_close_to_actor(knight* Knight) ;            //是否距离人物足够近,近战远程判断判定标准不同
	virtual bool if_attack(knight* Knight);                     //是否攻击人物
	//bool if_collided_with_actor(knight* Knight) ;               //是否与人物碰撞
	Vec2 get_enemy_pos();                                       //获取怪物坐标
	void set_enemy_pos();                                       //设置怪物坐标
	virtual void move(knight* Knight);                          //移动方式,传入骑士对象
	virtual void wander(int seed);                                      //未发现敌人时徘徊 
	bool if_collide(knight* Knight,Sprite* bullet);             //检查子弹是否与骑士碰撞，怪物的子弹和骑士
	bool if_collide(Sprite* enemy_, Sprite* bullet);            //检查子弹是否与骑士碰撞，骑士的子弹和怪
	void set_map_num(int map_num);
	int get_map_num();
	//

};

//两个近战怪物派生类
class enemy_melee1 :public enemy{
public:
	//virtual void death_animation()override;
	CREATE_FUNC(enemy_melee1);
	virtual bool init();
	virtual void attack(knight* Knight);
private:
};

class enemy_melee2 :public enemy{

public:
	virtual bool init();
	CREATE_FUNC(enemy_melee2);
	virtual void attack(knight* Knight);
	//virtual void death_animation()override;
private:
	
};

//两个远程怪物派生类
class enemy_remote1 :public enemy{
public:
	virtual bool init();
	Sprite* get_bullet();
	virtual void attack(knight* Knight); 
	void remove_bullet();
	//virtual void death_animation()override;
private:
	Sprite* bullet;
	
};

class enemy_remote2 :public enemy {
public:
	virtual bool init();
	//virtual void death_animation()override;
	Sprite* get_bullet();
	virtual void attack(knight* Knight);
private:
	Sprite* bullet;
};

class boss :public enemy{
public:
	//virtual void death_animation()override;
	CREATE_FUNC(boss);
	virtual bool init();
	//Sprite* get_bullet();
	Sprite* bullet[12];
	virtual void attack(knight* Knight);
private:
	MoveBy* move_[12];
};

#endif;