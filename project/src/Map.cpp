#include "Map.h"


std::pair<int, int> Map::get_size() {
    return size;
};

int Map::add_enemy_on_map(const std::string name) {
    if (name == "wolf") {
        return 3;
    }
    if (name == "dog") {
        return 2;
    }
    if (name == "rat") {
        return 1;
    }
    return 0;
}

int Map::add_enemy(const std::string name, std::pair<int, int> pos) {
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

int Map::is_enemy_on_cell(std::pair<int, int> pos) {
    if (location_person.find(pos) != location_person.end()) {
        return 1;
    }
    return 0;
}

Person* Map::get_enemy(std::pair<int, int> pos) {
    return location_person[pos];
}

void Map::delete_enemy(std::pair<int, int> pos) {
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
    map = new int* [size.first];
    for (int i = 0; i < size.second; ++i) {
        map[i] = new int [size.second];
    }
    while (in) {
        in >> x >> y >> name_enemy;
        // map[x][y] = add_enemy_on_map(name_enemy);
        add_enemy(name_enemy, {x, y});
        // std::cout << x << " x " << y << name_enemy << std::endl;
    }

    in.close();

    return 0;
}

void Map::print() {
    for (int y = size.second - 1; y >= 0; --y) {
        for (int x = 0; x < size.first; ++x) {
            std::cout << map[x][y] << ' ';
        }
        puts("");
    }
}