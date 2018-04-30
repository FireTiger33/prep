#ifndef PROJECT_INCLUDE_ARMOR_H_
#define PROJECT_INCLUDE_ARMOR_H_

#include "Item.h"


enum {
    ARMOR_DEFAULT_WGT = 3,
    ARMOR_DEFAULT_ARM = 3
};

class Armor : public Item {
 public:
    explicit Armor(const std::pair<int, int>& pos): Item(pos, ARMOR_DEFAULT_WGT, ARMOR_DEFAULT_ARM) {
        std::string name = "armor";
        set_name(name);
    }
    virtual ~Armor() = default;
};


#endif  // PROJECT_INCLUDE_ARMOR_H_
