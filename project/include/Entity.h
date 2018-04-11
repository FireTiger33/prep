#ifndef PROJECT_INCLUDE_ENTITY_H_
#define PROJECT_INCLUDE_ENTITY_H_

#include <iostream>


class Entity {
 public:
    explicit Entity(const std::pair<int, int>& pos): pos(pos) {}
    virtual ~Entity() = default;

    void set_name(const std::string& str);
    std::string get_name();
    std::pair<int, int> get_pos();
    virtual std::string get_type() = 0;

 protected:
    std::pair<int, int> pos;

 private:
    std::string name;
};


#endif  // PROJECT_INCLUDE_ENTITY_H_
