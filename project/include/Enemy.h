#ifndef PROJECT_INCLUDE_ENEMY_H_
#define PROJECT_INCLUDE_ENEMY_H_

#include "Person.h"


class Enemy : public Person {
 public:
    Enemy(int hp, int damage, const std::pair<int, int>& pos) : Person::Person(hp, pos) {
        up_damage(damage);
    }
    virtual ~Enemy() = default;

    std::string get_type() {
        return "enemy";
    }
};


#endif  // PROJECT_INCLUDE_ENEMY_H_
