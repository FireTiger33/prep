#ifndef PROJECT_INCLUDE_WOLF_H_
#define PROJECT_INCLUDE_WOLF_H_

#include "Enemy.h"


enum {
    WOLF_DEFAULT_HP = 6,
    WOLF_DEFAULT_DMG = 10
};

class Wolf : public Enemy {
 public:
    explicit Wolf(const std::pair<int, int>& pos) : Enemy::Enemy(WOLF_DEFAULT_HP, WOLF_DEFAULT_DMG, pos) {
        std::string name = "wolf";
        set_name(name);
    }
    virtual ~Wolf() = default;
};


#endif  // PROJECT_INCLUDE_WOLF_H_
