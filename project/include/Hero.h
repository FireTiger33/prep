#ifndef PROJECT_INCLUDE_HERO_H_
#define PROJECT_INCLUDE_HERO_H_

#include "Person.h"
#include "Item.h"
#include <set>


struct lexicographical_compare {
    bool operator()(Entity* x, Entity* y) {
        return x->get_name() < y->get_name();
    }
};

class Hero : public Person {
 public:
    explicit Hero(const std::string& name): Person(100, std::make_pair(0, 0)), left_place(20) {
        set_name(name);
    }
    ~Hero() {
        for (auto i = available_item.begin(); i != available_item.end(); i = available_item.begin()) {
            auto iterator = *i;
            available_item.erase(i);
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
    int left_place;
    std::set <class Item*, lexicographical_compare> available_item;
};


#endif  // PROJECT_INCLUDE_HERO_H_
