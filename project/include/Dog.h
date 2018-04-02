#ifndef PROJECT_DOG_H
#define PROJECT_DOG_H

#include "Enemy.h"

class Dog : public Enemy {
public:
    Dog (std::pair<int, int> pos) : Enemy::Enemy(3, 5, pos, "dog") {}
};


#endif //PROJECT_DOG_H
