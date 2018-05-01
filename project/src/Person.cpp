#include "Person.h"
#include "Game.h"


void Person::got_damage(int damage) {
    hp -= damage;
}

void Person::attack(Person* enemy) {
    enemy->got_damage(damage);
    if (enemy->get_hp() > 0) {
        int damage = enemy->damage;
        if (armor >= damage) {
            got_damage(1);
        } else {
            got_damage(damage - armor);
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
