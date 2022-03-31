#include "battle.h"

///abstract classes


Creature::Creature() : AC(0), HP(0), Max_HP(0), Initiative_modifier(0),
Initiative(0), coins(0), score(0){}
Creature::Creature(int a, int h, int i) :AC(a), HP(h), Max_HP(h), Initiative_modifier(i),
Initiative(0), coins(0), score(0){}

void Creature::showCreatureInfo() {
    std::cout << "HP: " << HP << "/" << Max_HP << "\n";
    std::cout << "AC: " << AC << "\n";
    std::cout << "Initiative modifier: " << Initiative_modifier << "\n";
    std::cout << "Money: " << coins << "\n";
}

int Creature::GetScore() {
    return score;
}

int Creature::InitiativeDrop() { // пробрасывает инициативу. protected,
    // потому что не хочу, чтобы из main можно было вызвать это.
    Initiative = rand() % 20 + 1 + Initiative_modifier;
    return Initiative;
}

void Creature::Regen() {
    int tmp = Max_HP / 10;
    if (Max_HP - tmp <= HP) {
        HP = Max_HP;
    } else {
        HP += tmp;
    }
}

Weapon::Weapon() : name(""), attack_modifier(0) {}
Weapon::Weapon(std::string n, int a) : name(n), attack_modifier(a) {}

void Weapon::showWeaponInfo() { // метод для осмотра оружия. публичный
    std::cout << "There is a " << name << " with attack modifier " << attack_modifier << "\n";
}

int Weapon::attackroll() { // ролл на атаку 2 6-гранника + модификатор атаки оружия. protected, чтоб не вызывалось извне
    int cube1 = rand() % 6 + 1, cube2 = rand() % 6 + 1, result = 0;
    result += cube1 + cube2 + attack_modifier;
    std::cout << "\nROLL:\n-----------------------------------------------------\nCUBE D6: " << cube1 << "\nCUBE D6: " << cube2 << "\nAttack Modifier: " << attack_modifier << "\n-----------------------------------------------------\n";
    return result;
}

int Weapon::hitroll()  { // ролл на пробитие. 20-гранник + модификатор атаки оружия
    srand(time(nullptr));
    int cube = rand() % 20 + 1 + attack_modifier;
    std::cout << "\nROLL:\n-----------------------------------------------------\nCUBE D20: ";
    std::cout << cube - attack_modifier << "\nAttack Modifier: " << attack_modifier;
    std::cout << "\n-----------------------------------------------------\n";
    return cube;
}

///Enemies

Spider::Spider() : Creature((rand() % 10 + 8), rand() % 20 + 10,
                            rand() % 5), agility(rand() % 10 + 10),
                   name("Spider") {
}
void Spider::showCreatureInfo() {
    std::cout << "Name: " << name << "\n";
    Creature::showCreatureInfo();
}

Ogre::Ogre() : Creature((rand() % 13 + 8), rand() % 20 + 14,
                        rand() % 6), strength(rand() % 10 + 10),
               name("Ogre") {
}
void Ogre::showCreatureInfo() {
    std::cout << "Name: " << name << "\n";
    Creature::showCreatureInfo();
}

Dwarf_Warlock::Dwarf_Warlock() : Creature((rand() % 8 + 8),
                                          rand() % 20 + 7,
                                          rand() % 5),
                                 intellect(rand() % 10 + 10),
                                 name("Dwarf Warlock") {
}
void Dwarf_Warlock::showCreatureInfo() {
    std::cout << "Name: " << name << "\n";
    Creature::showCreatureInfo();
}

Paladin::Paladin() : Creature((rand() % 10 + 13), rand() % 20 + 14,
                              rand() % 5), strength(rand() % 10 + 10) {
}
void Paladin::showCreatureInfo() {
    Creature::showCreatureInfo();
    std::cout << "Your base strength is: " << strength << "\n";
}

Rogue::Rogue() : Creature((rand() % 10 + 10), rand() % 20 + 11,
                          rand() % 5), agility(rand() % 10 + 10) {
}
void Rogue::showCreatureInfo() {
    Creature::showCreatureInfo();
    std::cout << "Your base agility is: " << agility << "\n";
}

Mage::Mage() : Creature((rand() % 10 + 8), rand() % 20 + 10,
                        rand() % 5), intellect(rand() % 10 + 10) {
}
void Mage::showCreatureInfo() {
    Creature::showCreatureInfo();
    std::cout << "Your base intellect is: " << intellect << "\n";
}



///Heroes' weapon

Sword::Sword() : Weapon("", 0) {
}
Sword::Sword(std::string n, int a) : Weapon(n, a) {
}

MagicStaff::MagicStaff() : Weapon("", 0) {
}
MagicStaff::MagicStaff(std::string n, int a)  : Weapon(n, a) {
}

Daggers::Daggers() : Weapon("", 0) {
}
Daggers::Daggers(std::string n, int a) : Weapon(n, a) {
}

///Enemies' weapon

SpiderLegs::SpiderLegs() : Weapon("Spider Legs", rand() % 5) {
}
Cudgel::Cudgel() : Weapon("Cudgel", rand() % 3) {
}
WarlockStaff::WarlockStaff() : Weapon("Warlock Staff", rand() % 5 + 2) {
}

///Fight

void EnemyAttack(Creature* c1, Creature* c2, Weapon* w1, Weapon* w2) { // атака врага.
    int chosen_result;
    int tmp;
    std::cout << "\nYour enemy is attack now!\nPress any key...\n";
    std::cin >> chosen_result; // нам сообщили, что враг будет атаковать. просто тыкнуть на кнопку.
    tmp = w2->hitroll();// в tmp результат броска кубика на пробитие
    if (tmp - w2->attack_modifier >= 19) { // если кубик выбросил 19-20, то есть шанс нанести крит
        std::cout << "\nYour enemy has a chance to attack critically...\n";
        tmp = w2->hitroll();
        if (tmp >= c1->AC) { // если кубик выбросил больше, чем АС цели, то крит подтвержден
            std::cout << "\nYour enemy accepted critical strike!\n";
            tmp = w2->attackroll(); // бросаем кубики на получаемый урон
            std::cout << "You have lost " << tmp * 2 << " HP.\n"; // наносится x2 урон
            c1->HP -= tmp * 2; // изменяем количество хп
            std::cout << "Your HP are " << c1->HP << " HP.\n";
        }
        else { // иначе наносится обычный урон, если крит не потдтвержден
            std::cout << "\nYour enemy didn't accept critical strike!\n";
            tmp = w2->attackroll(); // бросаем кубики на получаемый урон
            std::cout << "You have lost " << tmp << " HP.\n";
            c1->HP -= tmp; // изменяем количество хп
            std::cout << "Your HP are " << c1->HP << " HP.\n";
        }
    }
    else if (tmp >= c1->AC) { // если кубик >= нашего AC, то враг наносит удар
        std::cout << "Your enemy has hit you!\n";
        tmp = w2->attackroll(); // бросаем кубики на получаемый урон
        std::cout << "You have lost " << tmp << " HP.\n";
        c1->HP -= tmp; // изменяем количество хп
        std::cout << "Your HP are " << c1->HP << " HP.\n"; // выводим наше ХП
    }
    else std::cout << "Enemy missed!\n"; // в ином случае, если кубики выбросили < AC, то враг промахивается
}

void HeroAttack(Creature* c1, Creature* c2, Weapon* w1, Weapon* w2) { // атака игрока
    int chosen_result;
    int tmp;
    std::cout << "You are attack now!\n";
    std::cout << "Press any key to shake Hit Roll cubes...\n"; // предупреждения, + пояснения, где, какой ролл
    std::cin >> chosen_result; // ни ху я
    tmp = w1->hitroll(); // бросаем кубики на пробитие брони
    if (tmp - w1->attack_modifier >= 19) { // если кубик выбросил 19-20, то есть шанс наести крит
        std::cout << "\nYou have a chance to attack critically...\n";
        std::cout << "Press any key to shake Critical Strike cubes...\n";
        std::cin >> chosen_result;
        tmp = w1->hitroll();
        if (tmp >= c2->AC) { // если кубик выбросил больше, чем АС цели, то крит подтвержден
            std::cout << "\nYou accepted critical strike!\n";
            tmp = w1->attackroll(); // бросаем кубики на получаемый урон
            std::cout << "Your enemy has lost " << tmp * 2 << " HP.\n"; // наносится x2 урон
            c2->HP -= tmp * 2; // изменяем количество хп
        }
        else { // иначе наносится обычный урон
            std::cout << "\nYou didn't accept critical strike!\n";
            tmp = w1->attackroll(); // бросаем кубики на получаемый урон
            std::cout << "Your enemy has lost " << tmp << " HP.\n"; // наносится x1 урон
            c2->HP -= tmp;
        }
    }
    else if (tmp >= c2->AC) { // если пробили броню, то...
        std::cout << "You hit your enemy!\n";
        std::cout << "Press any key to shake Attack Damage cubes...\n";
        std::cin >> chosen_result;
        tmp = w1->attackroll(); // выбрасываем урон
        std::cout << "The enemy has lost " << tmp << " HP.\n";
        c2->HP -= tmp;// меняем хп врага: отнимаем от его хп полученный урон
    }
    else std::cout << "You missed!\n"; // если не выбросили пробивание брони, то мисс
}

bool fightStage(Creature* c1, Creature* c2, Weapon* w1, Weapon* w2) {
    int chosen_result;
    int tmp;
    std::cout << "\nPress any key to shake Initiative cubes...\n";
    // выбрасываем кубики на инициативу. у кого больше - тот и бьёт первый
    std::cin >> chosen_result;
    do {
        std::cout << "\nYour initiative is: " << c1->InitiativeDrop() << "\n";
        std::cout << "\nYour enemy initiative is: " << c2->InitiativeDrop() << "\n";
        if (c1->Initiative == c2->Initiative) std::cout << "\n-----------------------------------------------------\nREROLL\n-----------------------------------------------------\n"; // если инициатива выпала одинаковая, то реролл
    } while (c1->Initiative == c2->Initiative); // если инициатива одинаковая, то цикл по-новой
    while (c1->HP > 0 || c2->HP > 0) { // пока у кого-то не кончатся хп...

        if (c1->Initiative < c2->Initiative) { // если инициатива врага больше, снала бьёт враг,
            // затем проверка, не убил ли он нас, потом бьем мы -> проверка,
            //не убили ли мы его
            EnemyAttack(c1, c2, w1, w2);
            if (c1->HP <= 0) {
                std::cout << "\nGAME OVER!\nGAME OVER!\nGAME OVER!\n";
                return false;
            }
            HeroAttack(c1, c2, w1, w2);
            if (c2->HP <= 0) {
                std::cout << "\nYOU WON THIS FIGHT! WEEEEEEEEEE!!!\n";
                return true;
            }

        }
        if (c1->Initiative > c2->Initiative) { // если инициатива героя больше, то то же самое, но наоборот
            HeroAttack(c1, c2, w1, w2);
            if (c2->HP <= 0) {
                std::cout << "\nYOU WON THIS FIGHT! WEEEEEEEEEE!!!\n";
                return true;
            }
            EnemyAttack(c1, c2, w1, w2);
            if (c1->HP <= 0) {
                std::cout << "\nGAME OVER!\nGAME OVER!\nGAME OVER!\n";
                return false;
            }
        }
    }
}
