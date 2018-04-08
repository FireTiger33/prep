#ifndef PROJECT_INCLUDE_ENEMY_H_
#define PROJECT_INCLUDE_ENEMY_H_

#include "Person.h"


class Enemy : public Person {
 public:
    Enemy(int hp, int damage, const std::pair<int, int>& pos) : Person::Person(hp, pos) {
        up_damage(damage);
    }
};


#endif  // PROJECT_INCLUDE_ENEMY_H_
