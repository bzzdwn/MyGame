#include <ctime>
#include <vector>
#include <windows.h>
#include "game_func.h"

std::vector<Location*> room_generation() {
    std::vector<Location*> result;
    srand(time(nullptr));
    for (size_t i = 0; i < 3; ++i){
        int temp = rand()%5;
        switch (temp) {
            case 0:{
                auto * tmp = new Mobe_Room;
                result.push_back(tmp);
                break;
            }
            case 1:{
                auto * tmp = new Elite_Room;
                result.push_back(tmp);
                break;
            }
            case 2:{
                auto * tmp = new Empty_Room;
                result.push_back(tmp);
                break;
            }
            case 3:{
                auto * tmp = new Secret_Room;
                result.push_back(tmp);
                break;
            }
            case 4:{
                auto * tmp = new Trader;
                result.push_back(tmp);
                break;
            }

        }
    }
    return result;
}


void start(){
    srand(time(nullptr));

    std::cout <<"Monsters destroyed my house..."<<'\n'<<"Well it's time for revenge"<<'\n';
    system("pause");
    system("cls");

    Creature* character;
    Weapon* item;
    std::cout << "Choose your class:\n1. Paladin.\n2. Rogue.\n3. Mage.\n";
    int chosen_result;
    std::cin >> chosen_result;
    system("cls");
    std::cout << "Info about your character: \n";

    //выбор класса. заметь, что выбор закидывается в указатель!
    // создание героев и выдача им оружий.
    while(true) {
        if (chosen_result == 1) {
            Paladin p1;
            character = &p1;
            p1.showCreatureInfo();
            Sword s1("Paladin Sword", 3);
            item = &s1;
            std::cout << "\nYou have base weapon.\n";
            s1.showWeaponInfo();
            break;
        } else if (chosen_result == 2) {
            Rogue r1;
            character = &r1;
            r1.showCreatureInfo();
            Daggers dg1("Daggers", 4);
            item = &dg1;
            std::cout << "\nYou have base weapon.\n";
            dg1.showWeaponInfo();
            break;
        } else if (chosen_result == 3) {
            Mage m1;
            character = &m1;
            m1.showCreatureInfo();
            MagicStaff st1("Mage Staff", 5);
            item = &st1;
            std::cout << "\nYou have base weapon.\n";
            st1.showWeaponInfo();
            break;
        } else {
            std::cout << "\nIncorrect value! Try again!!!\n";
            system("pause");
        }
        std::cin >> chosen_result;
    }
    //game
for(size_t i = 0; i < 25; ++i) {
    size_t breaker = 0;
    std::vector<Location*> rooms = room_generation();
    std::cout<< "I have to choose again..."<<'\n';
    system("pause");
    system("cls");
    std::cout << "Choose the path."<<'\n';
    for(auto j : rooms) {
        std::cout << "*" <<j->name<<'\n';
    }
    std::cout << "*Stats" << '\n';
    std::cout << '\n';
    std::cout << "P.s. To choose first room enter number 1 and etc.";
    std::cout << '\n';
    int ch;
    int numb;
    while (true) {
        std::cin >> ch;
        if (ch == 1) {
            numb = rooms[0]->number;
            break;
        } else if (ch == 2) {
            numb = rooms[1]->number;
            break;
        } else if (ch == 3) {
            numb = rooms[2]->number;
            break;
        } else if(ch == 4) {
            system("cls");
            std::cout << "Info about your character: \n";
            character->showCreatureInfo();
            std::cout << "\nYour weapon: \n";
            item->showWeaponInfo();
            std::cout << "\n";
            system("pause");
            system("cls");
            std::cout << "Choose the path."<<'\n';
            for(auto j : rooms) {
                std::cout << "*" <<j->name<<'\n';
            }
            std::cout << "*Stats" << '\n';
            std::cout << '\n';
            std::cout << "P.s. To choose first room enter number 1 and etc.";
            std::cout << '\n';
        } else {
            system("cls");
            std::cout << "It's not that hard, you can do it" << '\n';
            system("pause");
            system("cls");
            std::cout << "Choose the path."<<'\n';
            for(auto j : rooms) {
                std::cout << "*" <<j->name<<'\n';
            }
            std::cout << "*Stats" << '\n';
            std::cout << '\n';
            std::cout << "P.s. To choose first room enter number 1 and etc.";
            std::cout << '\n';
        }
    }
    system("cls");
    rooms[ch - 1]->info();
    switch(numb){
        //1 fight
        case 1 : {
            Creature* enemy;
            enemy = new Creature();
            Weapon* en_weapon;
            en_weapon = new Weapon();
            int tmp = rand() % 3;
            if (tmp == 0) {
                enemy = new Spider();
                en_weapon = new SpiderLegs();
            }
            if (tmp == 1) {
                enemy = new Ogre();
                en_weapon = new Cudgel();
            }
            if (tmp == 2) {
                enemy = new Dwarf_Warlock();
                en_weapon = new WarlockStaff();
            }
            std::cout << "Info about enemy: \n";
            enemy->showCreatureInfo();
            if (!fightStage(character, enemy, item, en_weapon)){
                breaker++;
            } else{
                character->coins++;
                character->score++;
            }
            break;
        }
        //2 fights in a row
        case 2 : {
            Creature* enemy;
            Weapon* en_weapon;
            enemy = new Creature();
            en_weapon = new Weapon();
            Creature* enemy1;
            Weapon* en_weapon1;
            enemy1 = new Creature();
            en_weapon1 = new Weapon();
            int tmp = rand() % 3;
            if (tmp == 0) {
                enemy1 = new Spider();
                en_weapon1 = new SpiderLegs();
            }
            if (tmp == 1) {
                enemy1 = new Ogre();
                en_weapon1 = new Cudgel();
            }
            if (tmp == 2) {
                enemy1 = new Dwarf_Warlock();
                en_weapon1 = new WarlockStaff();
            }
            int tmp1 = rand() % 3;
            if (tmp1 == 0) {
                enemy = new Spider();
                en_weapon = new SpiderLegs();
            }
            if (tmp1 == 1) {
                enemy = new Ogre();
                en_weapon = new Cudgel();
            }
            if (tmp1 == 2) {
                enemy = new Dwarf_Warlock();
                en_weapon = new WarlockStaff();
            }

            std::cout << "Info about enemy: \n";
            enemy->showCreatureInfo();
            if (!fightStage(character, enemy, item, en_weapon)){
                breaker++;
                system("pause");
            } else{
                std::cout << "Info about enemy: \n";
                enemy1->showCreatureInfo();
                if (!fightStage(character, enemy1, item, en_weapon1)){
                    breaker++;
                } else {
                    character->score++;
                    character->score++;
                    character->coins++;
                    character->coins++;
                }
            }
            break;
        }
        //buffs(or nor)
        case 3 : {
            std::cout << "I hope this elixir is not dangerous..." << '\n';
            int tmp = rand()%4;
            switch (tmp) {
                case 0: {
                    std::cout << "Success"<<'\n';
                    character->AC +=2;
                    std::cout << "Your current AC:" << character->AC <<'\n';
                    break;
                }
                case 1: {
                    std::cout <<"That was poison..."<<'\n';
                    character->AC -=2;
                    std::cout << "Your current AC:" << character->AC <<'\n';
                    break;
                }
                case 2: {
                    std::cout << "Success"<<'\n';
                    character->HP +=2;
                    character->Max_HP +=2;
                    std::cout << "Your current HP:" << character->HP << '\n';
                    std::cout << "Your current Max_HP:" << character->Max_HP << '\n';
                    break;
                }
                case 3: {
                    std::cout <<"That was poison..."<<'\n';
                    character->HP -=2;
                    character->Max_HP -=2;
                    std::cout << "Your current HP:" << character->HP << '\n';
                    std::cout << "Your current Max_HP:" << character->Max_HP << '\n';
                    break;
                }
            }
            break;
        }
        //heal
        case 4 : {
            character->Regen();
            break;
        }
        //trader
        case 5 : {
            if (character->coins < 5) {
                std::cout << "I have not enough money" <<'\n';
                break;
            }
            std::cout << "He-he-he"<<'\n';
            std::cout << "Choose wisely..."<<'\n';
            std::cout << "Upgrade costs 5 coins. You have " << character->coins << " now." << '\n';
            std::cout << "What do you want to upgrade?"<<'\n';
            std::cout << "* AC"<<'\n';
            std::cout << "* HP"<<'\n';
            int num;
            while (true) {
                std::cin >> num;
                if (num == 1) {
                    character->AC++;
                    std::cout << "Your current AC:" << character->AC <<'\n';
                    character->coins -= 5;
                    break;
                } else if (num == 2) {
                    character->Max_HP++;
                    character->HP++;
                    std::cout << "Your current HP:" << character->HP << '\n';
                    std::cout << "Your current Max_HP:" << character->Max_HP << '\n';
                    character->coins -= 5;
                    break;
                } else {
                    std::cout << "It's not that hard, you can do it" << '\n';
                }
            }
            break;
        }
    }
    if(breaker == 1) {
        for (size_t i = 0; i < 27; i++)
            std::cout << (char)254;
        std::cout << "\n\tYOU DIED \n";
        std::cout << "  Your score is: " << character->GetScore() << "\n";
        for (size_t i = 0; i < 27; i++)
            std::cout << (char)254;
        std::cout << "\n";
        system("pause");
        break;
    } else{
        character->Regen();
    }
}
}