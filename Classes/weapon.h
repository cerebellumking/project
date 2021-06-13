#include "cocos2d.h"
#ifndef _WEAPON_H_
#define  _WEAPON_H_

USING_NS_CC;

class weapon : public Sprite
{


public:
	static	weapon* weapon::create(const char* picFileName);

	void weapon::fire();

	void weapon::set_bullet_name(std::string name);
	void weapon::set_weapon_name(std::string name);
	void weapon::set_demage(int Demage);
	void weapon::set_speed(float Speed);
	void weapon::set_pos(Vec2 Pos);
	void weapon::set_bullet(Sprite* Bullet);
	void weapon::set_click_check(bool check);
	void weapon::set_bullet_amount(int amount);
	void weapon::set_bullet_cost(int cost);
	void weapon::set_original_demage(int demage);

	int weapon::get_original_demage();
	Vec2 weapon::get_pos();
	float weapon::get_bullet_speed();
	Sprite* get_bullet();
	std::string weapon::get_bullet_name();
	std::string weapon::get_weapon_name();
	bool weapon::get_click_check();
	int weapon::get_bullet_amount();
	int weapon::get_bullet_cost();
	int weapon::get_bullet_demage();
	std::vector<Sprite*> bullet_vector;
private:
	int demage,original_demage, bullet_number, bullet_cost;
	float bullet_speed, tan_x;
	std::string bullet_name;
	std::string weapon_name;
	Sprite* bullet;
	Vec2 pos;
	bool click_check;
	int bullet_amount;
};
#endif