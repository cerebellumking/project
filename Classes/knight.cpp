#include "knight.h"
USING_NS_CC;
float knight::get_speed_x()
{
	return this->knight_speed_x;
}
float knight::get_speed_y()
{
	return this->knight_speed_y;
}
bool knight::get_E_check()
{
    return E_pressed_check;
}

void knight::set_speed_x(float speed)
{
	knight_speed_x = speed;
}
void knight::set_speed_y(float speed)
{
	knight_speed_y = speed;
}
void knight::set_E_check(bool check)
{
    E_pressed_check = check;
}

int knight::get_hp()
{
    return HP;
}

void knight::deduct_hp(int attack)
{
    if (armor > 0) {
        if ((armor - attack) < 0) {
            armor = 0;
            HP += armor - attack;
        }
        else
            armor -= attack;
    }
    else
        HP = HP-attack;
}

bool knight::if_dead()
{
    if (HP <= 0)
        return true;
    return false;
}

void knight::set_if_is_attacked(bool if_is_attacked)
{
    this->if_is_attacked = if_is_attacked;
}

bool knight::get_if_is_attacked()
{
    return if_is_attacked;
}

void knight::recover_armor(int delta_armor)
{
    if (armor + delta_armor >= max_armor)
        armor = max_armor;
    else
        armor += delta_armor;
}

bool knight::if_armor_max()
{
    if (armor == max_armor)
        return true;
    return false;
}

int knight::get_armor()
{
    return armor;
}

bool knight::init()
{
	this->HP = this->max_HP = 5;
	this->armor = this->max_armor = 5;
	this->MP = this->max_MP = 200;
	this->gold = 0;
	this->knight_speed_x = 0, this->knight_speed_y = 0;
    this->if_is_attacked = false;
	return true;
}

bool knight::weapon_init()
{
    this->Weapon = weapon::create("OldPistal.png");
    Weapon->setPosition(Vec2(40,10));
    Weapon->set_bullet_name("old pistal bullet.png");
    Weapon->set_weapon_name("OldPistal.png");
    Weapon->set_demage(5);
    Weapon->set_original_demage(5);
    Weapon->set_speed(0.5);
    Weapon->set_pos(Vec2(0,0));
    Weapon->set_bullet_amount(1);
    addChild(Weapon);
    return true;
}



knight* knight::create(const char* picFileName) {

	knight* sprite = new knight();

	if (sprite && sprite->initWithFile(picFileName))

	{
		sprite->autorelease(); return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;

}

void knight::keyboard_event()
{

    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [&](EventKeyboard::KeyCode code, Event*)
    {
     
        
          
        switch (code)
        {
        case EventKeyboard::KeyCode::KEY_D:
         
          
            knight::set_speed_x(1);
            break;

        case EventKeyboard::KeyCode::KEY_A:
          
           
            knight::set_speed_x(-1);
            break;
        case EventKeyboard::KeyCode::KEY_W:
         
          
            knight::set_speed_y(1);
            break;
        case EventKeyboard::KeyCode::KEY_S:
         
          
            knight::set_speed_y(-1);
            break;
        case EventKeyboard::KeyCode::KEY_E:


            E_pressed_check = 1;
            break;
        }

    };

    listener->onKeyReleased = [&](EventKeyboard::KeyCode code, Event*)
    {
      
       

        switch (code)
        {
        case EventKeyboard::KeyCode::KEY_D:
          
         
            knight::set_speed_x(0);
            break;

        case EventKeyboard::KeyCode::KEY_A:
          
         
            knight::set_speed_x(0);
            break;
        case EventKeyboard::KeyCode::KEY_W:
           
         
            knight::set_speed_y(0);
            break;
        case EventKeyboard::KeyCode::KEY_S:
            
          
            knight::set_speed_y(0);
            break;
        }
        
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


bool knight::picked_weapon_init(std::string name, std::string bulllet_name, int demage, int cost)
{
    const char* c1 = name.c_str();
    const char* c2 = bulllet_name.c_str();
    this->Weapon = weapon::create(c1);
    Weapon->setPosition(Vec2(40, 10));
    Weapon->set_bullet_name(c2);
    Weapon->set_weapon_name(c1);
    Weapon->set_speed(0.5);
    Weapon->set_pos(Vec2(0, 0));
    Weapon->set_demage(demage);
    Weapon->set_original_demage(demage);
    Weapon->set_bullet_cost(cost);
    addChild(Weapon);
    return true;
}


