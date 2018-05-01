#ifndef PROJECT_INCLUDE_RAT_H_
#define PROJECT_INCLUDE_RAT_H_

#include "Enemy.h"


enum {
    RAT_DEFAULT_HP = 2,
    RAT_DEFAULT_DMG = 3
};

class Rat :public Enemy {
 public:
    explicit Rat(const std::pair<int, int>& pos) : Enemy::Enemy(RAT_DEFAULT_HP, RAT_DEFAULT_DMG, pos) {
        std::string name = "rat";
        set_name(name);
    }
    virtual ~Rat() = default;
};


#endif  // PROJECT_INCLUDE_RAT_H_
