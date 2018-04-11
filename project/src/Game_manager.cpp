#include <string>
#include "Game_manager.h"


std::vector<bool> get_possible_actions(Hero *person, Map *map) {
    std::vector<bool> possible_actions(7, false);
    bool flag = false;
    if (map->is_entity_on_cell(person->get_pos())) {
        if (map->get_entity(person->get_pos())->get_type() == "enemy") {
            possible_actions[0] = true;
            flag = true;
            return possible_actions;
        }
        if (map->get_entity(person->get_pos())->get_type() == "item") {
            std::set<Item*, lexicographical_compare>* available_item = person->get_available_item();
            possible_actions[5] = true;
            for (auto i : *available_item) {
                if (i->get_name() == map->get_entity(person->get_pos())->get_name()) {
                    possible_actions[5] = false;
                    break;
                }
            }
            if (possible_actions[5]) {
                flag = true;
            }
            if (!person->available_item_is_empty()) {
                possible_actions[6] = true;
                flag = true;
            }
        }
    }
    if (person->get_pos().first > 0) {
        possible_actions[1] = true;
        flag = true;
    }
    if (person->get_pos().first < map->get_size().first - 1) {
        possible_actions[2] = true;
        flag = true;
    }
    if (person->get_pos().second > 0) {
        possible_actions[3] = true;
        flag = true;
    }
    if (person->get_pos().second < map->get_size().second - 1) {
        possible_actions[4] = true;
        flag = true;
    }

    if (!flag) {
        return std::vector<bool>(0);
    }

    return possible_actions;
}

void print_possible_actions(std::vector<bool> possible_actions, Hero* person, Map* map) {
    puts("Supported actions:");
    if (possible_actions[0]) {
        puts(" * kick enemy");
    } else {
        if (possible_actions[1]) {
            puts(" * move left");
        }
        if (possible_actions[2]) {
            puts(" * move right");
        }
        if (possible_actions[3]) {
            puts(" * move down");
        }
        if (possible_actions[4]) {
            puts(" * move up");
        }
        if (possible_actions[5]) {
            std::cout << " * pick " << map->get_entity(person->get_pos())->get_name() << std::endl;
        }
        if (possible_actions[6]) {
            person->print_item_throw();
        }
    }
}

int fight(Hero *person_1, Person *person_2, Map *map, bool armor) {
    while (person_2->get_hp() > 0 && person_1->get_hp() > 0) {
        std::string action;

        getline(std::cin, action);

        if (action == "kick enemy" || action == "") {
            person_1->attack(person_2);
            if (person_2->get_hp() > 0) {
                if (person_1->get_hp() > 0) {
                    std::cout << "\nenemy kicked. Enemy hp: " << person_2->get_hp() << std::endl;
                    print_possible_actions(get_possible_actions(person_1, map), person_1, map);
                    person_1->print_info(armor);
                } else {
                    std::cout << "\nplayer died\n";
                    map->delete_entity(person_1->get_pos());
                    return 1;
                }
            } else {
                map->delete_entity(person_1->get_pos());
                puts("\nenemy killed");
                return 0;
            }
        }
    }

    return 0;
}

short int move_toward(const std::string &route, Hero *person, std::vector<bool> possible_actions, Map* map) {
    static std::string MOVE_UP = {27, '[', 'A'};
    static std::string MOVE_DOWN = {27, '[', 'B'};
    static std::string MOVE_RIGHT = {27, '[', 'C'};
    static std::string MOVE_LEFT = {27, '[', 'D'};
    static std::string PICK = "e";

    if (map->is_entity_on_cell(person->get_pos())) {
        Entity* entity_on_hero_pos = map->get_entity(person->get_pos());

        if (possible_actions[5]) {
            std::string action = "pick " + entity_on_hero_pos->get_name();
            if (route == action || route == PICK) {
                person->pick_item(static_cast<Item*>(entity_on_hero_pos));
                map->transfer_to_person(person->get_pos());
                std::cout << "\nclothes worn\n";
                return 2;
            } else {
                if (route.find("move") != std::string::npos) {
                    map->delete_entity(person->get_pos());
                }
            }
        } else {
            if (route.find("move") != std::string::npos) {
                map->delete_entity(person->get_pos());
            }
        }
    }
    if (route == "") {
        return 0;
    }
    if (possible_actions[1] && (route == "move left" || route == MOVE_LEFT)) {
        person->go_left();
        return 1;
    }
    if (possible_actions[2] && (route == "move right" || route == MOVE_RIGHT)) {
        person->go_right();
        return 1;
    }
    if (possible_actions[3] && (route == "move down" || route == MOVE_DOWN)) {
        person->go_down();
        return 1;
    }
    if (possible_actions[4] && (route == "move up" || route == MOVE_UP)) {
        person->go_up();
        return 1;
    }
    if (possible_actions[6] && route.find("throw") != std::string::npos) {
        const std::set <class Item*, lexicographical_compare>* available_item =
                person->get_available_item();
        for (auto i : *available_item) {
            std::string action = "throw " + i->get_name();
            if (route == action) {
                person->throw_item(i);
                std::cout << "\nthe " << route.substr(sizeof("throw")) << " is thrown out";
                break;
            }
        }
    }

    return 3;
}


static short int input_and_move(Hero *person, Map *map, bool cursor_control) {
    std::string move_dir;
    short int move = false;

    if (cursor_control) {
        char key[4] = {};
        key[0] = getc(stdin);
        if (key[0] == 27) {
            fgets(&key[1], 3, stdin);
        }
        move_dir = key;
    } else {
        getline(std::cin, move_dir);
    }
    move = move_toward(move_dir, person, get_possible_actions(person, map), map);

    return move;
}

int character_progress(Hero *person, Map *map, bool cursor_control, bool armor) {
    static std::pair<int, int> pos = person->get_pos();
    short int move = input_and_move(person, map, cursor_control);

    if (move) {
        if (map->is_entity_on_cell(person->get_pos())) {
            Entity* entity_on_hero_pos = map->get_entity(person->get_pos());

            if (pos != person->get_pos()) {
                std::cout << std::endl << entity_on_hero_pos->get_name() << " found";
                pos = person->get_pos();
            }
            if (entity_on_hero_pos->get_type() == "enemy") {
                std::cout << ", " << static_cast<Person*>(entity_on_hero_pos)->get_hp() << " hp\n";
                print_possible_actions(get_possible_actions(person, map), person, map);
                person->print_info(armor);
                if (fight(person, static_cast<Person*>(entity_on_hero_pos), map, armor)) {
                    return 0;
                }
            } else {
                if (entity_on_hero_pos->get_type() == "item") {
                    puts("");
                }
            }
        } else {
            if (move == 1) {
                pos = person->get_pos();
                std::cout << "\nmoved\n";
            }
        }
    } else {
        return 0;
    }

    return 1;
}
