#include <iostream>

#define INVALID_ARGS_COUNT -1


int main(int argc, const char** /*argv*/) {
    if (argc != 2) {
        return INVALID_ARGS_COUNT;
    }

	std::cout << "Hi, Hw-4" << std::endl;

    return 0;
}
