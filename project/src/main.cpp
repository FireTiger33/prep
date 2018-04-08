#include "Map.h"
#include "Hero.h"
#include "Game_manager.h"


int main(int argc, const char** argv) {
    if (argc != 3) {
        return -1;
    }

    Map map;
    Hero hero("Hero_1");

    if (map.read_Map_from_file(argv[2])) {
        return -1;
    }
    if (map.blank_map()) {
        print_possible_actions(&hero, &map);
        puts("");
        hero.print_info();
        return 0;
    }

    do {
        print_possible_actions(&hero, &map);
        hero.print_info();
    } while (character_progress(&hero, &map));

    return 0;
}
