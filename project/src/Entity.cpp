#include "Entity.h"


void Entity::set_name(const std::string& str) {
    name = str;
}

std::string Entity::get_name() {
    return name;
}

std::pair<int, int> Entity::get_pos() {
    return pos;
}
