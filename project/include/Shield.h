#ifndef PROJECT_INCLUDE_SHIELD_H_
#define PROJECT_INCLUDE_SHIELD_H_

#include "Item.h"


enum {
    SHIELD_DEFAULT_WGT = 7,
    SHIELD_DEFAULT_ARM = 5
};

class Shield : public Item {
 public:
    explicit Shield(const std::pair<int, int>& pos): Item(pos, SHIELD_DEFAULT_WGT, SHIELD_DEFAULT_ARM) {
        std::string name = "shield";
        set_name(name);
    }
    virtual ~Shield() = default;
};


#endif  // PROJECT_INCLUDE_SHIELD_H_
