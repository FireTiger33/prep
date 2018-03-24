#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

#define INVALID_ARGS_COUNT -1
#define FILE_READ_FAIL -2


int read_DB_from_file_and_fix(std::map<std::string, int>* str_DB, const char** path_to_file) {
    if (!str_DB || !path_to_file) {
        return 1;
    }

    std::string key = "";
    int value = 0;
    int number = 0;

    std::ifstream DB(*path_to_file);
    if (!DB.is_open()) {
        return FILE_READ_FAIL;
    }

    while (DB >> number >> key >> value) {
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        if (str_DB->find(key) == str_DB->end()) {
            str_DB->insert(std::pair<std::string, int>(key, value));
        } else {
            str_DB[0][key] += value;
        }
    }

    DB.close();

    return 0;
}

int print_data_base(std::map<std::string, int>* str_DB) {
    if (!str_DB) {
        return 1;
    }

    unsigned int number = 0;

    for (std::map<std::string, int>::iterator it = str_DB->begin(); it != str_DB->end(); ++it, ++number) {
        std::cout << number << '|' << (*it).first << '|' << (*it).second << std::endl;
    }

    return 0;
}


int main(int argc, const char** argv) {
    if (argc != 2) {
        return INVALID_ARGS_COUNT;
    }

    std::map <std::string, int> str_DB;

    if (read_DB_from_file_and_fix(&str_DB, &argv[1])) {
        return FILE_READ_FAIL;
    }
    print_data_base(&str_DB);

    return 0;
}
