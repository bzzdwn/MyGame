#ifndef MAIN_CPP_BATTLE_H
#define MAIN_CPP_BATTLE_H
#include <ctime>
#include <iostream>

///abstract classes
class Creature;

class Weapon {
public:
    Weapon();
    Weapon(std::string n, int a);
    void showWeaponInfo();
    friend class Creature;
    friend bool fightStage(Creature* c1, Creature* c2, Weapon* w1, Weapon* w2);
    friend void EnemyAttack(Creature* c1, Creature* c2, Weapon* w1, Weapon* w2);
    friend void HeroAttack(Creature* c1, Creature* c2, Weapon* w1, Weapon* w2);
protected:
    virtual int attackroll();
    int hitroll();
    const std::string name;
    int attack_modifier;
};

class Creature {
public:
    Creature();
    Creature(int a, int h, int i);
    virtual void showCreatureInfo();
    void Regen();
    friend void start();
    int GetScore();
    friend void EnemyAttack(Creature* c1, Creature* c2, Weapon* w1, Weapon* w2);
    friend void HeroAttack(Creature* c1, Creature* c2, Weapon* w1, Weapon* w2);
    friend bool fightStage(Creature* c1, Creature* c2, Weapon* w1, Weapon* w2);
    friend class Weapon;
protected:
    int InitiativeDrop();

    int score;

    int AC;
    int coins;
    int HP;
    int Max_HP;
    int Initiative_modifier; // модификатор инициативы (он прибавляется к броскам кубиков)
    int Initiative; // итоговая инициатива. высчитывается с помощью броска кубиков в InitiativeDrop.
    // изначально инициализируется нулем

};

/// Enemies

class Spider : public Creature { // паук. средне брони и хп. наносит урона выше среднего
public:
    Spider();
    void showCreatureInfo();
private:
    std::string name;
    int agility;
};

class Ogre : public Creature { // огр. много хп. средне брони. наносит мало урона
public:
    Ogre() ;
    void showCreatureInfo();
private:
    std::string name;
    int strength;
};

class Dwarf_Warlock : public Creature { // гном чернокнижник. мало хп и брони. наносит много урона
public:
    Dwarf_Warlock();
    void showCreatureInfo();
private:
    std::string name;
    int intellect;
};

///Classes


class Paladin : public Creature { // Паладин. Больше ХП и брони. наносит меньше урона
public:
    Paladin();
    void showCreatureInfo();
private:
    int strength;
};

class Rogue : public Creature { // Разбойник. Броня и хп средне. урона наносит средне.
public:
    Rogue();
    void showCreatureInfo();
private:
    int agility;
};

class Mage : public Creature { // маг. мало хп и брони. наносит больше урона
public:
    Mage();
    void showCreatureInfo();
private:
    int intellect;
};

///Heroes' Weapon

class Sword : public Weapon { // меч. двуручное. носить может паладин
public:
    Sword() ;
    Sword(std::string n, int a);
};

class MagicStaff : public Weapon { // посох. двуручное. носить может маг
public:
    MagicStaff();
    MagicStaff(std::string n, int a);
};

class Daggers : public Weapon { // клинки. одноручное. носить может разбойник
public:
    Daggers();
    Daggers(std::string n, int a);
};

///Enemies' weapon

class SpiderLegs : public Weapon { // у паука оружие - его лапы. наносят больше среднего урона
public:
    SpiderLegs();
};

class Cudgel : public Weapon { // дубинка наносит мало урона
public:
    Cudgel();
private:

};

class WarlockStaff : public Weapon { // посох чернокнижника. ебашит по полной программе
public:
    WarlockStaff();
private:

};

///Fight

void EnemyAttack(Creature* c1, Creature* c2, Weapon* w1, Weapon* w2);
void HeroAttack(Creature* c1, Creature* c2, Weapon* w1, Weapon* w2);
bool fightStage(Creature* c1, Creature* c2, Weapon* w1, Weapon* w2);

#endif //MAIN_CPP_BATTLE_H
