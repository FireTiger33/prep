#ifndef PROJECT_RAT_H
#define PROJECT_RAT_H

#include "Enemy.h"


class Rat :public Enemy {
public:
    Rat (std::pair<int, int> pos) : Enemy::Enemy(1, 3, pos, "rat") {}
};


#endif //PROJECT_RAT_H
