#include "Hero.h"


void Hero::print_info(bool view_armor) {
    std::cout << get_pos().first << " x " << get_pos().second << ", hp: " << this->get_hp();
    if (view_armor) {
        std::cout << ", armor: " << get_armor();
    }
    std::cout << " > ";
}

void Hero::pick_item(Item* item) {
    left_place -= item->get_WGT();
    up_armor(item->get_ARM());
    available_item.insert(item);
}

bool Hero::available_item_is_empty() {
    if (available_item.size()) {
        return false;
    }

    return true;
}

void Hero::print_item_throw() {
    for (auto i : available_item) {
        std::cout << " * throw " << i->get_name() << std::endl;
    }
}

std::set<class Item*, lexicographical_compare>* Hero::get_available_item() {
    return &available_item;
}

void Hero::throw_item(Item* i) {
    left_place += i->get_WGT();
    up_armor(-i->get_ARM());
    available_item.erase(i);
    delete(i);
}
