#ifndef PROJECT_INCLUDE_PANTS_H_
#define PROJECT_INCLUDE_PANTS_H_

#include "Item.h"


enum {
    PANTS_DEFAULT_WGT = 1,
    PANTS_DEFAULT_ARM = 1
};

class Pants : public Item {
 public:
    explicit Pants(const std::pair<int, int>& pos): Item(pos, PANTS_DEFAULT_WGT, PANTS_DEFAULT_ARM) {
        std::string name = "pants";
        set_name(name);
    }
    virtual ~Pants() = default;
};


#endif  // PROJECT_INCLUDE_PANTS_H_
