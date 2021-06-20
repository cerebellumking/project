
#include"preserve.h"


bool game_preserve::init()
{
	if (!game_preserve::init())
		return false;
}

void game_preserve::get_knight(int _hp_max, int _hp_, int _mp_max, int _mp_, int _armor_max,bool _buff_1,bool _buff_2,bool _buff_3, std::string _weapon_name)
{
	 this->hp_max=_hp_max;
	 this->hp_=_hp_;
	 this->mp_max=_mp_max;
	 this->mp_=_mp_;
	 this->armor_max=_armor_max;
	 this->buff_1 = _buff_1;
	 this->buff_2 = _buff_2;
	 this->buff_3 = _buff_3;
	 this->weapon_name=_weapon_name;
}
int game_preserve::get_hp_max()
{
	return hp_max;
}
int game_preserve::get_hp()
{
	return hp_;
}

int game_preserve::get_mp_max() 
{
	return mp_max;
}

int game_preserve::get_mp() 
{
	return mp_;
}

int game_preserve::get_armor_max()
{
	return armor_max;
}

int game_preserve::get_buff_1()
{
	return buff_1;
}

int game_preserve::get_buff_2()
{
	return buff_2;
}

int game_preserve::get_buff_3()
{
	return buff_3;
}

std::string game_preserve::get_weapon_name()
{
	return weapon_name;
}
