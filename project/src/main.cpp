#include <cstddef>
#include "Map.h"
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
    bool cursor_control = (keys.find("--cursor_control") != keys.end())? true: false;
    bool armor = (keys.find("--view-armor") != keys.end())? true: false;

    if (keys.find("--map") != keys.end()) {
        for (auto i : keys) {
            if (i[0] != '-') {
                if (map.read_Map_from_file((i))) {
                    return -1;
                }
                break;
            }
        }
    } else {
        return -1;
    }

    if (cursor_control) {
        shadow_keypress();
    }

    if (get_possible_actions(&hero, &map).empty()) {
        puts("Supported actions:");
        puts("");
        hero.print_info(armor);
        return 0;
    }

    do {
        print_possible_actions(get_possible_actions(&hero, &map), &hero, &map);
        hero.print_info(armor);
    } while (character_progress(&hero, &map, cursor_control, armor));

    if (cursor_control) {
        reset_keypress();
    }

    return 0;
}
