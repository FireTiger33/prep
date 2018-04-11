#ifndef PROJECT_INCLUDE_RAT_H_
#define PROJECT_INCLUDE_RAT_H_

#include "Enemy.h"


class Rat :public Enemy {
 public:
    explicit Rat(const std::pair<int, int>& pos) : Enemy::Enemy(2, 3, pos) {
        std::string name = "rat";
        set_name(name);
    }
    virtual ~Rat() = default;
};


#endif  // PROJECT_INCLUDE_RAT_H_
