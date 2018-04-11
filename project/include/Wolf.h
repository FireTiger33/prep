#ifndef PROJECT_INCLUDE_WOLF_H_
#define PROJECT_INCLUDE_WOLF_H_

#include "Enemy.h"


class Wolf : public Enemy {
 public:
    explicit Wolf(const std::pair<int, int>& pos) : Enemy::Enemy(6, 10, pos) {
        std::string name = "wolf";
        set_name(name);
    }
    virtual ~Wolf() = default;
};


#endif  // PROJECT_INCLUDE_WOLF_H_
