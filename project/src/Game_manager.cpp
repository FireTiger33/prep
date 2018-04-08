#include <string>
#include "Game_manager.h"


std::vector<bool> get_possible_actions(Person* person, Map* map) {
    std::vector<bool> possible_actions(5, false);
    bool flag = false;
    if (map->is_enemy_on_cell(person->get_pos())) {
        possible_actions[0] = true;
        flag = true;
    } else {
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
    }

    if (!flag) {
        return std::vector<bool> (0);
    }

    return possible_actions;
}

void print_possible_actions(std::vector<bool> possible_actions) {
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
    }
}

int fight(Person* person_1, Person* person_2, Map* map) {
    while (person_2->get_hp() > 0 && person_1->get_hp() > 0) {
        std::string action;
        getline(std::cin, action);

        if (action == "kick enemy" || action == "") {
            person_1->attack(person_2);
            if (person_2->get_hp() > 0) {
                if (person_1->get_hp() > 0) {
                    std::cout << "\nenemy kicked. Enemy hp: " << person_2->get_hp() << std::endl;
                    print_possible_actions(get_possible_actions(person_1, map));
                    person_1->print_info();
                } else {
                    std::cout << "\nplayer died\n";
                    return 1;
                }
            } else {
                free(person_2);
                map->delete_enemy(person_1->get_pos());
                puts("\nenemy killed");
                return 0;
            }
        }
    }

    return 0;
}

bool move_toward(const std::string& route, Person* person, std::vector<bool> possible_actions) {
    static std::string MOVE_UP = {27, '[', 'A'};
    static std::string MOVE_DOWN = {27, '[', 'B'};
    static std::string MOVE_RIGHT = {27, '[', 'C'};
    static std::string MOVE_LEFT = {27, '[', 'D'};

    if (route == "") {
        return false;
    }
    if (possible_actions[1] && (route == "move left" || route == MOVE_LEFT)) {
        person->go_left();
        return true;
    }
    if (possible_actions[2] && (route == "move right" || route == MOVE_RIGHT)) {
        person->go_right();
        return true;
    }
    if (possible_actions[3] && (route == "move down" || route == MOVE_DOWN)) {
        person->go_down();
        return true;
    }
    if (possible_actions[4] && (route == "move up" || route == MOVE_UP)) {
        person->go_up();
        return true;
    }

    return true;
}


static bool input_and_move(Person* person, Map* map, bool cursor_control) {
    std::string move_dir;
    bool move = false;

    if (cursor_control) {
        char key[4] = {};

        fgets(key, 4, stdin);
        move_dir = key;
    } else {
        getline(std::cin, move_dir);
    }
    move = move_toward(move_dir, person, get_possible_actions(person, map));

    return move;
}

int character_progress(Person* person, Map* map, bool cursor_control) {
    bool move = input_and_move(person, map, cursor_control);
    if (move) {
        if (map->is_enemy_on_cell(person->get_pos())) {
            std::cout << std::endl << map->get_enemy(person->get_pos())->get_name() << " found, ";
            std::cout << map->get_enemy(person->get_pos())->get_hp() << " hp" << std::endl;
            print_possible_actions(get_possible_actions(person, map));
            person->print_info();
            if (fight(person, map->get_enemy(person->get_pos()), map)) {
                return 0;
            }
        } else {
            std::cout << "\nmoved\n";
        }
    } else {
        return 0;
    }

    return 1;
}
