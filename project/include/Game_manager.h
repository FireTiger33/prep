#ifndef PROJECT_INCLUDE_GAME_MANAGER_H_
#define PROJECT_INCLUDE_GAME_MANAGER_H_

#include "Person.h"
#include "Map.h"


void print_possible_actions(Person* person, Map* map);
int fight(const Person* person_1, Person* person_2, const Map* map);
void move_toward(int route, Person* person, Map* map);
int character_progress(Person* person, Map* map);


#endif  // PROJECT_INCLUDE_GAME_MANAGER_H_
