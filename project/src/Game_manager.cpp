#include "Game_manager.h"


void print_possible_actions(Person* person, Map* map) {
    puts("Supported actions:");
    if (map->is_enemy_on_cell(person->get_pos())) {
        puts(" * kick enemy");
    } else {
        if (person->get_pos().first > 0) {
            puts(" * move left");
        }
        if (person->get_pos().first < map->get_size().first - 1) {
            puts(" * move right");
        }
        if (person->get_pos().second > 0) {
            puts(" * move down");
        }
        if (person->get_pos().second < map->get_size().second - 1) {
            puts(" * move up");
        }
    }
}

int fight(Person* person_1, Person* person_2, Map* map) {
    bool correctly = false;
    while (person_2->get_hp() > 0 && person_1->get_hp() > 0) {
        std::string action;

        action[0] = getc(stdin);
        if (action[0] == 10) {
            correctly = true;
        } else {
            reset_keypress();
            if (action[0] == 'k') {
                std::getline(std::cin, action);
                if (action == "ick enemy") {
                    correctly = true;
                }
            }
            shadow_keypress();
        }
        if (correctly) {
            person_1->attack(person_2);
            if (person_2->get_hp() > 0) {
                if (person_1->get_hp() > 0) {
                    std::cout << "\nenemy kicked. Enemy hp: " << person_2->get_hp() << std::endl;
                    print_possible_actions(person_1, map);
                    person_1->print_info();
                } else {
                    std::cout << std::endl << "player died\n";
                    return 1;
                }
            } else {
                free(person_2);
                map->delete_enemy(person_1->get_pos());
                puts("\nenemy killed");
                return 0;
            }
        }
        correctly = false;
    }

    return 0;
}

void move_toward(int route, Person* person, Map* map) {
    switch (route) {
        case 65:  // std::cout << "move up\n";
        case 117:
            if (person->get_pos().second < map->get_size().second - 1) {
                person->go_up();
            } else {
                puts("");
            }
            break;
        case 66:  // std::cout << "move down\n";
        case 100:
            if (person->get_pos().second > 0) {
                person->go_down();
            } else {
                puts("");
            }
            break;
        case 67:  // std::cout << "move right\n";
        case 114:
            if (person->get_pos().first < map->get_size().first - 1) {
                person->go_right();
            } else {
                puts("");
            }
            break;
        case 68:  // std::cout << "move left\n";
        case 108:
            if (person->get_pos().first > 0) {
                person->go_left();
            } else {
                puts("");
            }
            break;
        default:
            break;
    }
    reset_keypress();
}

static void input_and_move(Person* person, Map* map) {
    char key[4] = {};
    std::string move_dir;

    shadow_keypress();
    key[0] = getc(stdin);
    if (key[0] == 27) {
        fgets(&key[1], 3, stdin);
        if (key[1] == '[') {
            move_toward(key[2], person, map);
        }
    } else {
        reset_keypress();
        std::cin >> move_dir >> move_dir;
        puts("");
        move_toward(move_dir[0], person, map);
        getc(stdin);
    }
    /* reset_keypress();
        if (key[0] == 'm') {
            std::cin >> move_dir >> move_dir;
            puts("");
            move_toward(move_dir[0], person, map);
            getc(stdin);
        } else {
            getline(std::cin, move_dir);
        }
    */
}

int character_progress(Person* person, Map* map) {
    input_and_move(person, map);

    if (map->is_enemy_on_cell(person->get_pos())) {
        std::cout << map->get_enemy(person->get_pos())->get_name() << " found, ";
        std::cout << map->get_enemy(person->get_pos())->get_hp() << " hp" << std::endl;
        print_possible_actions(person, map);
        person->print_info();
        if (fight(person, map->get_enemy(person->get_pos()), map)) {
            return 0;
        }
    } else {
        std::cout << "moved\n";
        char c = getc(stdin);;

        if (c == -1) {
            print_possible_actions(person, map);
            person->print_info();
            return 0;
        } else {
            fputc(c, stdin);
        }
    }

    return 1;
}
