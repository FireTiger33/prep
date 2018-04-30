#ifndef PROJECT_INCLUDE_HERO_H_
#define PROJECT_INCLUDE_HERO_H_

#include "Person.h"
#include "Item.h"
#include <set>


enum {
    HERO_DEFAULT_HP = 100
};

struct lexicographical_compare {
    bool operator()(Entity* x, Entity* y) {
        return x->get_name() < y->get_name();
    }
};

class Hero : public Person {
 public:
    explicit Hero(const std::string& name = "Hero"): Person(HERO_DEFAULT_HP, std::make_pair(0, 0)), available_weight(20) {
        set_name(name);
    }
    ~Hero() {
        for (auto i = items.begin(); i != items.end(); i = items.begin()) {
            auto iterator = *i;
            items.erase(i);
            delete(iterator);
        }
    }

    void print_info(bool view_armor);
    void pick_item(Item* item);
    bool available_item_is_empty();
    void print_item_throw();
    std::set <class Item*, lexicographical_compare>* get_available_item();
    void throw_item(Item* i);

 private:
    int available_weight;
    std::set <class Item*, lexicographical_compare> items;
};


#endif  // PROJECT_INCLUDE_HERO_H_
