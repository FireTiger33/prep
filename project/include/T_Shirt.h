#ifndef PROJECT_INCLUDE_T_SHIRT_H_
#define PROJECT_INCLUDE_T_SHIRT_H_

#include "Item.h"


enum {
    T_SHIRT_DEFAULT_WGT = 1,
    T_SHIRT_DEFAULT_ARM = 1
};

class T_Shirt : public Item {
 public:
    explicit T_Shirt(const std::pair<int, int>& pos): Item(pos, T_SHIRT_DEFAULT_WGT, T_SHIRT_DEFAULT_ARM) {
        std::string name = "T-Shirt";
        set_name(name);
    }
    virtual ~T_Shirt() = default;
};


#endif  // PROJECT_INCLUDE_T_SHIRT_H_
