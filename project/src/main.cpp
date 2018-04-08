#include <cstddef>
#include "Map.h"
#include "Hero.h"
#include "Game_manager.h"
#include "keypress.h"
#include <set>


std::set<std::string> key_parser(const std::vector<std::string>& keys) {
    std::set<std::string> parsed;
    for (auto& i : keys) {
        parsed.insert(i);
    }
    return parsed;
}

int main(int argc, const char** argv) {
    if (argc < 3) {
        return -1;
    }
    std::vector<std::string> values;
    for (int i = 1; i < argc; ++i) {
        values.push_back(argv[i]);
    }

    Map map;
    Hero hero("Hero_1");
    auto keys = key_parser(values);
    auto z = keys.find("--map");

    if (z != keys.end()) {
        if (map.read_Map_from_file((*++z))) {
            return -1;
        }
    } else {
        return -1;
    }

    bool cursor_control = (keys.find("--cursor_control") != keys.end())? true: false;
    if (cursor_control) {
        shadow_keypress();
    }

    if (get_possible_actions(&hero, &map).empty()) {
        print_possible_actions(get_possible_actions(&hero, &map));
        puts("");
        hero.print_info();
        return 0;
    }

    do {
        print_possible_actions(get_possible_actions(&hero, &map));
        hero.print_info();
    } while (character_progress(&hero, &map, cursor_control));

    if (cursor_control) {
        reset_keypress();
    }

    return 0;
}
