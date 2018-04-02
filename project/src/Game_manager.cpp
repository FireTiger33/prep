#include "Game_manager.h"


void print_possible_actions(Person& person, Map& map) {
    puts("Supported actions:");
    if (map.is_enemy_on_cell(person.get_pos())) {
        puts(" * kick enemy");
    } else {
        if (person.get_pos().first > 0) {
            puts(" * move left");
        }
        if (person.get_pos().first < map.get_size().first - 1) {
            puts(" * move right");
        }
        if (person.get_pos().second > 0) {
            puts(" * move down");
        }
        if (person.get_pos().second < map.get_size().second - 1) {
            puts(" * move up");
        }
    }
}

int fight (Person& person_1, Person* person_2, Map& map) {
    bool correctly = false;
    while (person_2->get_hp() > 0 && person_1.get_hp() > 0) {
        std::string action;

        action[0] = getc(stdin);
        if (action[0] == 10) {
            correctly = true;
        } else {
            reset_keypress();
            // putchar(action[0]);
            if (action[0] == 'k') {
                std::getline(std::cin, action);
                if (action == "ick enemy") {
                    correctly = true;
                }
            }
            set_keypress();
        }
        if (correctly) {
            person_1.attack(person_2);
            if (person_2->get_hp() > 0) {
                if (person_1.get_hp() > 0) {
                    std::cout << "\nenemy kicked. Enemy hp: " << person_2->get_hp() << std::endl;
                    print_possible_actions(person_1, map);
                    person_1.print_info();
                } else {
                    std::cout << std::endl << "player died\n";
                    // puts("\nplayer died");
                    // std::cout << std::endl;
                    return 1;
                }
            } else {
                free(person_2);
                map.delete_enemy(person_1.get_pos());
                puts("\nenemy killed");
                return 0;
            }
        }
        correctly = false;
    }

    return 0;
}

void move (int route, Person& person, Map& map) {
    // std::cout << route << std::endl;
    switch (route) {
        case 65:  // std::cout << "move up\n";
        case 117:
            if (person.get_pos().second < map.get_size().second - 1) {
                person.go_up();
            } else {
                puts("");
            }
            reset_keypress();
            break;
        case 66:  // std::cout << "move down\n";
        case 100:
            if (person.get_pos().second > 0) {
                person.go_down();
            } else {
                puts("");
            }
            reset_keypress();
            break;
        case 67:  // std::cout << "move right\n";
        case 114:
            if (person.get_pos().first < map.get_size().first - 1) {
                person.go_right();
            } else {
                puts("");
            }
            reset_keypress();
            break;
        case 68:  // std::cout << "move left\n";
        case 108:
            if (person.get_pos().first > 0) {
                person.go_left();
            } else {
                puts("");
            }
            reset_keypress();
            break;
        default:
            break;
    }
}

int character_progress (Person& person, Map& map) {
    char key[3] = {};
    std::string move_dir;

    set_keypress();
    key[0] = getc(stdin);
    if (key[0] == 27) {
        fgets(&key[1], 3, stdin);
        if (key[1] == '[') {
            move(key[2], person, map);
        }
    } else {
        reset_keypress();
        // std::cout << key[0];
        std::cin >> move_dir >> move_dir;
        puts("");
        move(move_dir[0], person, map);
        getc(stdin);
    }

    if (map.is_enemy_on_cell(person.get_pos())) {
        std::cout << map.get_enemy(person.get_pos())->get_name() << " found, ";
        std::cout << map.get_enemy(person.get_pos())->get_hp() << " hp" << std::endl;
        print_possible_actions(person, map);
        person.print_info();
        if (fight(person, map.get_enemy(person.get_pos()), map)) {
            return 0;
        }
        /*if (map.blank_map()) {
            return 0;
        }*/
    } else {
        char c = '\0';
        if ((c = getc(stdin)) == EOF) {
            return 0;
        } else {
            fputc(c, stdin);
            std::cout << "moved\n";
        }
    }

    return 1;
}