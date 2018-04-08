#ifndef PROJECT_INCLUDE_HERO_H_
#define PROJECT_INCLUDE_HERO_H_

#include "Hero.h"
#include "Person.h"


class Hero : public Person {
 public:
    explicit Hero(const std::string& name): Person(100, std::make_pair(0, 0)) {
        set_name(name);
    }
};


#endif  // PROJECT_INCLUDE_HERO_H_
