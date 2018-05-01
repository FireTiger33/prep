#ifndef PROJECT_INCLUDE_HELMET_H_
#define PROJECT_INCLUDE_HELMET_H_

#include "Item.h"


enum {
    HELMET_DEFAULT_WGT = 2,
    HELMET_DEFAULT_ARM = 3
};

class Helmet : public Item {
 public:
    explicit Helmet(const std::pair<int, int>& pos): Item(pos, HELMET_DEFAULT_WGT, HELMET_DEFAULT_ARM) {
        std::string name = "helmet";
        set_name(name);
    }
    virtual ~Helmet() = default;
};


#endif  // PROJECT_INCLUDE_HELMET_H_
