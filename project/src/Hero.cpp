#include "Hero.h"


void Hero::print_info(bool view_armor) {
    std::cout << get_pos().first << " x " << get_pos().second << ", hp: " << this->get_hp();
    if (view_armor) {
        std::cout << ", armor: " << get_armor();
    }
    std::cout << " > ";
}

void Hero::pick_item(Item* item) {
    available_weight -= item->get_WGT();
    up_armor(item->get_ARM());
    items.insert(item);
}

bool Hero::available_item_is_empty() {
    if (items.size()) {
        return false;
    }

    return true;
}

void Hero::print_item_throw() {
    for (auto i : items) {
        std::cout << " * throw " << i->get_name() << std::endl;
    }
}

std::set<class Item*, lexicographical_compare>* Hero::get_available_item() {
    return &items;
}

void Hero::throw_item(Item* i) {
    available_weight += i->get_WGT();
    up_armor(-i->get_ARM());
    items.erase(i);
    delete(i);
}
