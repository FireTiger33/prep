#ifndef PROJECT_PERSON_H
#define PROJECT_PERSON_H

#include <iostream>
#include "keypress.h"


class Person {
public:
    Person (int hp, std::pair<int, int> pos, std::string name): hp(hp), damage(1), pos(pos), name(name) {}
    void attack (Person* enemy);
    void print_info ();
    std::pair<int, int> get_pos () {
        return pos;
    }
    void go_up();
    void go_down();
    void go_right();
    void go_left();
    std::string get_name() {
        return name;
    }
    int get_hp() {
        return hp;
    }

protected:
    void up_damage (int val) {
        damage += val;
    }

private:
    int hp;
    int damage;
    std::pair<int, int> pos;
    std::string name;
};


#endif //PROJECT_PERSON_H
