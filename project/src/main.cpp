#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

#define INVALID_ARGS_COUNT -1
#define FILE_OPEN_FAIL -2


int main(int argc, const char** argv) {
    if (argc != 2) {
        return INVALID_ARGS_COUNT;
    }

    std::map <std::string, int> str_DB;
	std::string key = "";
    int value = 0;
    int number = 0;

    std::ifstream DB(argv[1]);
    if (!DB.is_open()) {
        return FILE_OPEN_FAIL;
    }

    while (DB >> number >> key >> value) {
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        if (str_DB.find(key) == str_DB.end()) {
            str_DB.insert(std::pair<std::string, int>(key, value));
        } else {
            str_DB[key] += value;
        }
    }

    DB.close();

    number = 0;
    for (std::map<std::string, int>::iterator it = str_DB.begin(); it != str_DB.end(); ++it, ++number) {
        std::cout << number << '|' << (*it).first << '|' << (*it).second << std::endl;
    }

    return 0;
}
