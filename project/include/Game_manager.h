#ifndef PROJECT_INCLUDE_GAME_MANAGER_H_
#define PROJECT_INCLUDE_GAME_MANAGER_H_

#include "Person.h"
#include "Hero.h"
#include "Map.h"
#include <vector>
#include <set>


std::vector<bool> get_possible_actions(Hero* person, Map* map);
void print_possible_actions(std::vector<bool> possible_actions, Hero* person, Map* map);
int fight(const Hero* person_1, Person* person_2, const Map* map, bool armor);
short int move_toward(const std::string& route, Person* person, std::vector<bool> possible_actions, Map* map);
int character_progress(Hero* person, Map* map, bool cursor_control, bool armor);


#endif  // PROJECT_INCLUDE_GAME_MANAGER_H_
