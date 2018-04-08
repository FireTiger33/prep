#include "Map.h"


std::pair<int, int> Map::get_size() {
    return size;
}

int Map::add_enemy(const std::string& name, const std::pair<int, int>& pos) {
    if (name == "wolf") {
        location_person.insert({pos, new Wolf(pos)});
    }
    if (name == "dog") {
        location_person.insert({pos, new Dog(pos)});
    }
    if (name == "rat") {
        location_person.insert({pos, new Rat(pos)});
    }

    return 0;
}

int Map::is_enemy_on_cell(const std::pair<int, int>& pos) {
    if (location_person.find(pos) != location_person.end()) {
        return 1;
    }

    return 0;
}

Person* Map::get_enemy(const std::pair<int, int>& pos) {
    return location_person[pos];
}

void Map::delete_enemy(const std::pair<int, int>& pos) {
    this->location_person.erase(pos);
}

int Map::blank_map() {
    if (location_person.begin() == location_person.end()) {
        return 1;
    }

    return 0;
}

int Map::read_Map_from_file(const char* path_to_file) {
    std::string name_enemy;
    std::ifstream in(path_to_file);
    int x = 0;
    int y = 0;

    if (in.bad()) {
        return -1;
    }
    in >> size.first >> size.second;
    while (in) {
        in >> x >> y >> name_enemy;
        add_enemy(name_enemy, {x, y});
    }

    in.close();

    return 0;
}
