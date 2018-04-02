#ifndef PROJECT_WOLF_H
#define PROJECT_WOLF_H

#include "Enemy.h"

class Wolf : public Enemy {
public:
    Wolf (std::pair<int, int> pos) : Enemy::Enemy(6, 10, pos, "wolf") {}
};


#endif //PROJECT_WOLF_H
