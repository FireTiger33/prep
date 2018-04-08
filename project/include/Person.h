#ifndef PROJECT_INCLUDE_PERSON_H_
#define PROJECT_INCLUDE_PERSON_H_

#include <iostream>
#include "keypress.h"


class Person {
 public:
    Person(int hp, const std::pair<int, int>& pos): hp(hp), damage(1), pos(pos) {}
    void attack(Person* enemy);
    void print_info();
    void go_up();
    void go_down();
    void go_right();
    void go_left();
    std::pair<int, int> get_pos() {
        return pos;
    }
    std::string get_name() {
        return name;
    }
    int get_hp() {
        return hp;
    }
    void set_name(const std::string& str) {
        name = str;
    }


 protected:
    void up_damage(int val) {
        damage += val;
    }

 private:
    int hp;
    int damage;
    std::pair<int, int> pos;
    std::string name;
};


#endif  // PROJECT_INCLUDE_PERSON_H_
