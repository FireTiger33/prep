#ifndef PROJECT_HERO_H
#define PROJECT_HERO_H

#include "Hero.h"
#include "Person.h"


class Hero : public Person {
public:
    Hero(std::string name): Person::Person(100, {0, 0}, name) {}
};


#endif //PROJECT_HERO_H
