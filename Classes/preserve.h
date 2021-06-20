#pragma once

#ifndef _preserve_H_
#define  _preserve_H_
#include "cocos2d.h"
#include"weapon.h"
class game_preserve :public Node
{
public:
	bool virtual init();
	void get_knight(int _hp_max,int _hp_,int _mp_max,int _mp_,int _armor_max, bool _buff_1, bool _buff_2, bool _buff_3, std::string _weapon_name);
	int get_hp_max();
	int get_hp();
	int get_mp_max();
	int get_mp();
	int get_armor_max();
	int get_buff_1();
	int get_buff_2();
	int get_buff_3();
	std::string get_weapon_name();

private:
	int hp_max;
	int hp_;
	int mp_max;
	int mp_;
	int armor_max;
	bool buff_1;
	bool buff_2;
	bool buff_3;
	std::string weapon_name;

};

#endif