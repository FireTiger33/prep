#include <cstddef>
#include "Map.h"
#include "Hero.h"
#include "Game_manager.h"
#include "keypress.h"
#include <map>


std::map<std::string, bool> key_parser(const std::vector<std::string>& keys) {
    std::map<std::string, bool> parsed;
    for (auto& i : keys) {
        parsed.insert({i, true});
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

    Map map_f;
    Hero hero("Hero_1");
    auto keys = key_parser(values);
    auto z = keys.find("--map");
    if (z != keys.end()) {
        if (map_f.read_Map_from_file((*++z).first)) {
            return -1;
        }
    } else {
        return -1;
    }

    bool cursor_control = (keys.find("--cursor_control") != keys.end())? true: false;
    if (cursor_control) {
        shadow_keypress();
    }

    if (map_f.blank_map()) {
        print_possible_actions(get_possible_actions(&hero, &map_f));
        puts("");
        hero.print_info();
        return 0;
    }

    do {
        print_possible_actions(get_possible_actions(&hero, &map_f));
        hero.print_info();
    } while (character_progress(&hero, &map_f, cursor_control));

    if (cursor_control) {
        reset_keypress();
    }

    return 0;
}
