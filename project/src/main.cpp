#include <cstddef>
#include "Game.h"


int main(int argc, char* const* argv) {
    if (argc < 3) {
        return -1;
    }

    Game game(argc, argv);

    game.play();

    return 0;
}
