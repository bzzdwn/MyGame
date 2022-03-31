#ifndef Loc
#define Loc
#include <iostream>
class Location {
public:
    Location();
    std::string GetName();
    virtual void info();
    std::string name;
    size_t number;
};

class Mobe_Room: public Location {
public:
    Mobe_Room();
    void info() override;
    std::string GetName();
};

class Elite_Room: public Location {
public:
    Elite_Room();
    void info() override;
    std::string GetName();
};

class Secret_Room: public Location {
public:
    Secret_Room();
    void info() override;
    std::string GetName();
};

class Empty_Room: public Location {
public:
    Empty_Room();
    void info() override;
    std::string GetName();
};

class Trader: public Location {
public:
    Trader();
    void info() override;
    std::string GetName();
};
#endif