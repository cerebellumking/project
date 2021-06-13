#include "..\Classes\sprite.h"

void sprite_living::bind_sprite(Sprite* sprite)
{

	float w = sprite->getContentSize().width;
	float h = sprite->getContentSize().height;
	auto physicsBody1 = PhysicsBody::createBox(Size(w, h), PhysicsMaterial(0.1f, 1.0f, 0.0f));/////////////
	physicsBody1->setGravityEnable(false);
	physicsBody1->setRotationEnable(false);
	sprite->addComponent(physicsBody1);
	this->sprite = sprite;
}

void sprite_living::set_positon(Vec2 pos)
{
	this->sprite->setPosition(pos);
}

Sprite* sprite_living::get_sprite()
{
	return this->sprite;
}

int sprite_living::get_hp()
{
	return hp;
}

int sprite_living::get_speed()
{
	return speed;
}

int sprite_living::get_attack()
{
	return attack;
}

void sprite_living::set_hp(int hp)
{
	this->hp = hp;
}

void sprite_living::set_speed(float speed)
{
	this->speed = speed;
}

void sprite_living::set_attack(int attack)
{
	this->attack = attack;
}

bool sprite_living::if_dead()
{
	if (hp <= 0)
		return true;
	return false;
}

void sprite_living::deduct_hp(int attack)
{
	hp -= attack;
}

void sprite_living::set_if_is_attacked(bool if_is_attacked)
{
	this->if_is_attacked = if_is_attacked;
}

bool sprite_living::get_if_is_attacked()
{
	return if_is_attacked;
}
