#include"weapon.h"
USING_NS_CC;


void weapon::set_bullet_name(std::string name)
{
	bullet_name = name;
}

void weapon::set_weapon_name(std::string name)
{
	weapon_name = name;
}

void weapon::set_bullet_cost(int cost)
{
	bullet_cost = cost;
}

void weapon::set_bullet_amount(int amount)
{
	bullet_amount = amount;
}
void weapon::set_demage(int Demage)
{
	demage = Demage;
}

void weapon::set_speed(float Speed)
{
	bullet_speed = Speed;
}

void weapon::set_pos(Vec2 Pos)
{
	pos = this->convertToNodeSpace(Pos);
}

void weapon::set_original_demage(int demage)
{
	original_demage = demage;
}

void weapon::set_bullet(Sprite* Bullet)
{
	bullet = Bullet;
}

void weapon::set_click_check(bool check)
{
	click_check = check;
}

Vec2 weapon::get_pos()
{
	return pos;
}

std::string weapon::get_bullet_name()
{
	return bullet_name;
}

std::string weapon::get_weapon_name()
{
	return weapon_name;
}

float weapon::get_bullet_speed()
{
	return bullet_speed;
}

int weapon::get_original_demage()
{
	return original_demage;
}

bool weapon::get_click_check()
{
	return click_check;
}

Sprite* weapon::get_bullet()
{
	return bullet;
}

int weapon::get_bullet_amount()
{
	return bullet_amount;
}

int weapon::get_bullet_demage()
{
	return demage;
}
int weapon::get_bullet_cost()
{
	return bullet_cost;
}

weapon* weapon::create(const char* picFileName) {

	weapon* sprite = new weapon();

	if (sprite && sprite->initWithFile(picFileName))

	{
		sprite->autorelease();
		return sprite;
	}
	else
	{
		CC_SAFE_DELETE(sprite);
		return nullptr;

	}
}


void weapon::fire()
{
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = [&](Event* event)
	{
		EventMouse* click;
		click = dynamic_cast<EventMouse*>(event);
		set_pos(click->getLocationInView());
		click_check = true;

	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

