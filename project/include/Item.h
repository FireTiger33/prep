#ifndef PROJECT_INCLUDE_ITEM_H_
#define PROJECT_INCLUDE_ITEM_H_

#include "Entity.h"


class Item : public Entity {
 public:
    explicit Item(const std::pair<int, int>& pos, int WGT, int ARM): Entity(pos), WGT(WGT), ARM(ARM) {}
    virtual ~Item() = default;

    int get_ARM();
    int get_WGT();
    int get_type();

 private:
    int WGT;
    int ARM;
};


#endif  // PROJECT_INCLUDE_ITEM_H_
