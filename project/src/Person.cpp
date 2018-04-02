#include "Person.h"
#include "Game_manager.h"


void Person::print_info () {
    std::cout << pos.first << " x " << pos.second << ", hp: " << hp << " > ";
}

void Person::attack(Person* enemy) {
    enemy->hp -= this->damage;
    if (enemy->get_hp() > 0) {
        this->hp -= enemy->damage;
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