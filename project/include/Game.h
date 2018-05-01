#ifndef PROJECT_INCLUDE_GAME_H_
#define PROJECT_INCLUDE_GAME_H_

#include "Hero.h"
#include "Map.h"
#include <vector>
#include <getopt.h>


class Game {
 public:
    Game(int argc, char* const* argv): cursor_control(false), armor(false) {
        while (1) {
            int opt = 0;
            static struct option long_opt[] = {
                    {"map",            1, NULL, 'm'},
                    {"view-armor",     0, NULL, 'a'},
                    {"cursor_control", 0, NULL, 'c'}
            };

            if ((opt = getopt_long(argc, argv, "m:ca", long_opt, NULL)) == -1) {
                break;
            }

            switch (opt) {
                case 'm':
                    if (map.read_from_file((optarg))) {
                        return;
                    }
                    break;
                case 'a': armor = true;
                    break;
                case 'c': cursor_control = true;
                    break;
                default:
                    break;
            }
        }
    }

    void play();
    std::vector<bool> get_possible_actions(Hero *person);
    void print_possible_actions(std::vector<bool> possible_actions, Hero *person);
    int fight(Hero *person_1, Person *person_2);
    short int move_toward(const std::string &route, Hero *person, std::vector<bool> possible_actions);
    short int input_and_move(Hero *person);
    int character_progress(Hero *person);

 private:
    Map map;
    Hero hero;
    bool cursor_control;
    bool armor;
};

#endif  // PROJECT_INCLUDE_GAME_H_
