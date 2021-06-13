#pragma once

#ifndef _sprite_H_
#define _sprite_H_


#include"cocos2d.h"
USING_NS_CC;
//#include"Actor.h"
//#include"Map.h"
//#include"obstruction.h"

class sprite_living :public cocos2d::Sprite//活物基类
{

public:
	
	//virtual bool init();
	CREATE_FUNC(sprite_living);
	void bind_sprite(Sprite* sprite);                           //绑定精灵,初始化精灵的接口
	void set_positon(Vec2 pos);                                 //设置精灵坐标,初始化精灵的接口
	Sprite* get_sprite();                                       //获取精灵,调用精灵的接口
	int get_hp();                                               //获取精灵的血量的接口
	int get_speed();                                            //获取精灵的速度的接口
	int get_attack();                                           //获取精灵的攻击力的接口
	void set_hp(int hp);                                        //设置血量
	void set_speed(float speed);                                //设置速度
	void set_attack(int attack);                                //设置攻击力
	bool if_dead();                                             //是否死亡
	void deduct_hp(int attack);                                 //精灵扣血
	void set_if_is_attacked(bool if_is_attacked);               //设置是否被攻击的状态
	bool get_if_is_attacked();                                  //获取是否被攻击的状态
	//bool if_collided_with_border(map* map);//是否与边界碰撞
	//bool if_collided_with_obstruction(obstruction* obstruction);//是否与障碍物碰撞
	//virtual void death_animation();//播放死亡动画


	//后续如果用刚体和物理引擎，可能还要再加一些成员。

private:
	int hp;                                                      //当前生命值
	float speed;                                                 //移速
	int attack;                                                  //攻击力
	Sprite* sprite;                                              //精灵
	bool if_is_attacked;                                         //判断是否被攻击
};

class sprite_dead//死物基类
{
public:

private:

};

#endif;