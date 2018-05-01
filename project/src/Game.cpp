#include "Game.h"
#include <string>
#include <set>
#include "keypress.h"


enum actions {
    ATTACK = 0,
    GO_LEFT = 1,
    GO_RIGHT = 2,
    GO_DOWN = 3,
    GO_UP = 4,
    PICK_ITEM = 5,
    THROW_ITEM = 6
};

enum move_toward_return {
    NO_ACTIONS = 0,
    MOVEMENT = 1,
    THERE_IS_A_THING = 2,
    INPUT_ERROR = 3
};

enum character_progress {
    GAME_OVER = 0,
    ALIVE = 1
};

void Game::play() {
    if (cursor_control) {
        shadow_keypress();
    }

    if (get_possible_actions(&hero).empty()) {
        puts("Supported actions:");
        puts("");
        hero.print_info(armor);
        return;
    }

    do {
        print_possible_actions(get_possible_actions(&hero), &hero);
        hero.print_info(armor);
    } while (character_progress(&hero));

    if (cursor_control) {
        reset_keypress();
    }

    return;
}

std::vector<bool> Game::get_possible_actions(Hero *person) {
    std::vector<bool> actions(7, false);
    bool flag = false;

    if (map.is_entity_on_cell(person->get_pos())) {
        if (map.get_entity(person->get_pos())->get_type() == ENEMY) {
            actions[ATTACK] = true;
            return actions;
        }
        if (map.get_entity(person->get_pos())->get_type() == ITEM) {
            std::set<Item *, lexicographical_compare> *items = person->get_available_item();
            actions[PICK_ITEM] = true;
            for (auto i : *items) {
                if (i->get_name() == map.get_entity(person->get_pos())->get_name()) {
                    actions[PICK_ITEM] = false;
                    break;
                }
            }
            if (actions[PICK_ITEM]) {
                flag = true;
            }
            if (!person->available_item_is_empty()) {
                actions[THROW_ITEM] = true;
                flag = true;
            }
        }
    }
    if (person->get_pos().first > 0) {
        actions[GO_LEFT] = true;
        flag = true;
    }
    if (person->get_pos().first < map.get_size().first - 1) {
        actions[GO_RIGHT] = true;
        flag = true;
    }
    if (person->get_pos().second > 0) {
        actions[GO_DOWN] = true;
        flag = true;
    }
    if (person->get_pos().second < map.get_size().second - 1) {
        actions[GO_UP] = true;
        flag = true;
    }

    if (!flag) {
        return std::vector<bool>(0);
    }

    return actions;
}

void Game::print_possible_actions(std::vector<bool> possible_actions, Hero *person) {
    puts("Supported actions:");
    if (possible_actions[ATTACK]) {
        puts(" * kick enemy");
    } else {
        if (possible_actions[GO_LEFT]) {
            puts(" * move left");
        }
        if (possible_actions[GO_RIGHT]) {
            puts(" * move right");
        }
        if (possible_actions[GO_DOWN]) {
            puts(" * move down");
        }
        if (possible_actions[GO_UP]) {
            puts(" * move up");
        }
        if (possible_actions[PICK_ITEM]) {
            std::cout << " * pick " << map.get_entity(person->get_pos())->get_name() << std::endl;
        }
        if (possible_actions[THROW_ITEM]) {
            person->print_item_throw();
        }
    }
}

int Game::fight(Hero *person_1, Person *person_2) {
    while (person_2->get_hp() > 0 && person_1->get_hp() > 0) {
        std::string action;

        getline(std::cin, action);

        if (action == "kick enemy" || action == "") {
            person_1->attack(person_2);
            if (person_2->get_hp() > 0) {
                if (person_1->get_hp() > 0) {
                    std::cout << "\nenemy kicked. Enemy hp: " << person_2->get_hp() << std::endl;
                    print_possible_actions(get_possible_actions(person_1), person_1);
                    person_1->print_info(armor);
                } else {
                    std::cout << "\nplayer died\n";
                    map.delete_entity(person_1->get_pos());
                    return 1;
                }
            } else {
                map.delete_entity(person_1->get_pos());
                puts("\nenemy killed");
                return 0;
            }
        }
    }

    return 0;
}

short int Game::move_toward(const std::string &route, Hero *person, std::vector<bool> possible_actions) {
    static std::string MOVE_UP = {27, '[', 'A'};
    static std::string MOVE_DOWN = {27, '[', 'B'};
    static std::string MOVE_RIGHT = {27, '[', 'C'};
    static std::string MOVE_LEFT = {27, '[', 'D'};
    static std::string PICK = "e";

    if (map.is_entity_on_cell(person->get_pos())) {
        Entity *entity_on_hero_pos = map.get_entity(person->get_pos());

        if (possible_actions[PICK_ITEM]) {
            std::string action = "pick " + entity_on_hero_pos->get_name();
            if (route == action || route == PICK) {
                person->pick_item(static_cast<Item *>(entity_on_hero_pos));
                map.transfer_to_person(person->get_pos());
                std::cout << "\nclothes worn\n";
                return THERE_IS_A_THING;
            } else {
                if (route.find("move") != std::string::npos) {
                    map.delete_entity(person->get_pos());
                }
            }
        } else {
            if (route.find("move") != std::string::npos) {
                map.delete_entity(person->get_pos());
            }
        }
    }
    if (route == "") {
        return NO_ACTIONS;
    }
    if (possible_actions[GO_LEFT] && (route == "move left" || route == MOVE_LEFT)) {
        person->go_left();
        return MOVEMENT;
    }
    if (possible_actions[GO_RIGHT] && (route == "move right" || route == MOVE_RIGHT)) {
        person->go_right();
        return MOVEMENT;
    }
    if (possible_actions[GO_DOWN] && (route == "move down" || route == MOVE_DOWN)) {
        person->go_down();
        return MOVEMENT;
    }
    if (possible_actions[GO_UP] && (route == "move up" || route == MOVE_UP)) {
        person->go_up();
        return MOVEMENT;
    }
    if (possible_actions[THROW_ITEM] && route.find("throw") != std::string::npos) {
        const std::set<class Item *, lexicographical_compare> *items =
                person->get_available_item();
        for (auto i : *items) {
            std::string action = "throw " + i->get_name();
            if (route == action) {
                person->throw_item(i);
                std::cout << "\nthe " << route.substr(sizeof("throw")) << " is thrown out";
                break;
            }
        }
    }

    return INPUT_ERROR;
}


short int Game::input_and_move(Hero *person) {
    std::string move_dir;
    short int move = 0;

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
    move = move_toward(move_dir, person, get_possible_actions(person));

    return move;
}

int Game::character_progress(Hero *person) {
    static std::pair<int, int> pos = person->get_pos();
    short int move = input_and_move(person);

    if (!move) {
        return GAME_OVER;
    }
    if (map.is_entity_on_cell(person->get_pos())) {
        Entity *entity_on_hero_pos = map.get_entity(person->get_pos());

        if (pos != person->get_pos()) {
            std::cout << std::endl << entity_on_hero_pos->get_name() << " found";
            pos = person->get_pos();
        }
        if (entity_on_hero_pos->get_type() == ENEMY) {
            std::cout << ", " << static_cast<Person *>(entity_on_hero_pos)->get_hp() << " hp\n";
            print_possible_actions(get_possible_actions(person), person);
            person->print_info(armor);
            if (fight(person, static_cast<Person *>(entity_on_hero_pos))) {
                return GAME_OVER;
            }
        } else {
            if (entity_on_hero_pos->get_type() == ITEM) {
                puts("");
            }
        }
    } else {
        if (move == 1) {
            pos = person->get_pos();
            std::cout << "\nmoved\n";
        }
    }

    return ALIVE;
}
