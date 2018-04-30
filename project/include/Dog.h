#ifndef PROJECT_INCLUDE_DOG_H_
#define PROJECT_INCLUDE_DOG_H_

#include "Enemy.h"


enum {
    DOG_DEFAULT_HP = 3,
    DOG_DEFAULT_DMG = 5
};

class Dog : public Enemy {
 public:
    explicit Dog(const std::pair<int, int>& pos): Enemy::Enemy(DOG_DEFAULT_HP, DOG_DEFAULT_DMG, pos) {
        std::string name = "dog";
        set_name(name);
    }
    virtual ~Dog() = default;
};


#endif  // PROJECT_INCLUDE_DOG_H_
