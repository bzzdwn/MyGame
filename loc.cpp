#include "loc.h"
#include <iostream>
///Base class

Location::Location () {
    }

void Location::info() {}

///inheriting classes

Mobe_Room::Mobe_Room(){
    name = "Room with Monster";
    number = 1;
    }
void Mobe_Room::info() {
    std::cout << "There is some strange noise ahead. Hope the worst is over...";
}
std::string Mobe_Room::GetName() {
    return this->name;
}


Elite_Room::Elite_Room(){
    name = "Room with Elite Monster";
    number = 2;
    }
std::string Elite_Room::GetName() {
    return this->name;
}
void Elite_Room::info() {
    std::cout << "There is something scary. So... What's about joke?" << '\n';
    std::cout << "Will glass coffins be a success? Remains to be seen." << '\n';
    std::cout << "Heh. At least I've tried..." << '\n';
}

Secret_Room::Secret_Room(){
    name = "Strange room";
    number = 3;
    }
std::string Secret_Room::GetName() {
    return this->name;
}
void Secret_Room::info() {
    std::cout << "What do you want to hear? This room is called strange for a reason."<<'\n';
}

Empty_Room::Empty_Room(){
    name = "Empty room";
    number = 4;
    }
std::string Empty_Room::GetName() {
    return this->name;
}
void Empty_Room::info() {
    std::cout << "Finally, Some Good Room"<<'\n';
}

Trader::Trader(){
    name = "Trader";
    number = 5;
    }
std::string Trader::GetName() {
    return this->name;
}
void Trader::info() {
    std::cout << "Maybe this time he will make a discount..."<<'\n';
}