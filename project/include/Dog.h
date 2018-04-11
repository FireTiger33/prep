#ifndef PROJECT_INCLUDE_DOG_H_
#define PROJECT_INCLUDE_DOG_H_

#include "Enemy.h"


class Dog : public Enemy {
 public:
    explicit Dog(const std::pair<int, int>& pos): Enemy::Enemy(3, 5, pos) {
        std::string name = "dog";
        set_name(name);
    }
    virtual ~Dog() = default;
};


#endif  // PROJECT_INCLUDE_DOG_H_
