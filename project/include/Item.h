#ifndef PROJECT_INCLUDE_ITEM_H_
#define PROJECT_INCLUDE_ITEM_H_

#include "Entity.h"


class Item : public Entity {
 public:
    explicit Item(const std::pair<int, int>& pos, int WGT, int ARM): Entity(pos), WGT(WGT), ARM(ARM) {}
    virtual ~Item() = default;

    int get_ARM();
    int get_WGT();
    std::string get_type();

 private:
    int WGT;
    int ARM;
};


class Armor : public Item {
 public:
    explicit Armor(const std::pair<int, int>& pos): Item(pos, 3, 3) {
        std::string name = "armor";
        set_name(name);
    }
    virtual ~Armor() = default;
};

class Helmet : public Item {
 public:
    explicit Helmet(const std::pair<int, int>& pos): Item(pos, 2, 3) {
        std::string name = "helmet";
        set_name(name);
    }
    virtual ~Helmet() = default;
};

class Shield : public Item {
 public:
    explicit Shield(const std::pair<int, int>& pos): Item(pos, 7, 5) {
        std::string name = "shield";
        set_name(name);
    }
    virtual ~Shield() = default;
};

class Pants : public Item {
 public:
    explicit Pants(const std::pair<int, int>& pos): Item(pos, 1, 1) {
        std::string name = "pants";
        set_name(name);
    }
    virtual ~Pants() = default;
};

class T_Shirt : public Item {
 public:
    explicit T_Shirt(const std::pair<int, int>& pos): Item(pos, 1, 1) {
        std::string name = "T-Shirt";
        set_name(name);
    }
    virtual ~T_Shirt() = default;
};



#endif  // PROJECT_INCLUDE_ITEM_H_
