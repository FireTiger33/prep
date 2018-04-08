#ifndef PROJECT_INCLUDE_GAME_MANAGER_H_
#define PROJECT_INCLUDE_GAME_MANAGER_H_

#include "Person.h"
#include "Map.h"
#include <vector>


std::vector<bool> get_possible_actions(Person* person, Map* map);
void print_possible_actions(std::vector<bool> possible_actions);
int fight(const Person* person_1, Person* person_2, const Map* map);
bool move_toward(const std::string& route, Person* person, std::vector<bool> possible_actions);
int character_progress(Person* person, Map* map, bool cursor_control);


#endif  // PROJECT_INCLUDE_GAME_MANAGER_H_
