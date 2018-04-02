#ifndef PROJECT_ENEMY_H
#define PROJECT_ENEMY_H

#include "Person.h"


class Enemy : public Person {
public:
    Enemy (int hp, int damage, std::pair<int, int> pos, std::string name) : Person::Person(hp, pos, name) {
        up_damage(damage);
    }
};


#endif //PROJECT_ENEMY_H
