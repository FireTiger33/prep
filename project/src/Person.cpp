#include "Person.h"
#include "Game_manager.h"


void Person::attack(Person* enemy) {
    enemy->hp -= damage;
    if (enemy->get_hp() > 0) {
        int damage = enemy->damage;
        if (armor >= damage) {
            hp -= 1;
        } else {
            hp -= (damage - armor);
        }
    }
}

void Person::go_up() {
    pos.second++;
}

void Person::go_down() {
    pos.second--;
}

void Person::go_right() {
    pos.first++;
}

void Person::go_left() {
    pos.first--;
}
