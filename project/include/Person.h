#ifndef PROJECT_INCLUDE_PERSON_H_
#define PROJECT_INCLUDE_PERSON_H_

#include "Entity.h"


class Person : public Entity {
 public:
    Person(int hp, const std::pair<int, int>& pos):
            Entity(pos), hp(hp), damage(1), armor(0) {}
    virtual ~Person() = default;

    void attack(Person* enemy);
    void go_up();
    void go_down();
    void go_right();
    void go_left();

    int get_hp() {
        return hp;
    }
    int get_armor() {
        return armor;
    }
    void up_armor(int arm) {
        armor += arm;
    }
    std::string get_type() {
        return "person";
    }

 protected:
    void up_damage(int val) {
        damage += val;
    }

 private:
    int hp;
    int damage;
    int armor;
};


#endif  // PROJECT_INCLUDE_PERSON_H_
