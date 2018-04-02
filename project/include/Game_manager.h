#ifndef PROJECT_GAME_MANAGER_H
#define PROJECT_GAME_MANAGER_H

#include "Person.h"
#include "Map.h"


void print_possible_actions(Person& person, Map& map);
int fight (Person& person_1, Person* person_2, Map& map);
void move (int route, Person& person, Map& map);
int character_progress (Person& person, Map& map);


#endif //PROJECT_GAME_MANAGER_H
