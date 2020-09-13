#include <sstream>

#include "MyFramework.h"

static int getSize(const std::string& str) {
    try {
        return std::stoi(str) > 1 ? std::stoi(str) : throw("error");
    } catch (...) {
        std::cerr << "[hight_window] [width_window] [hight_map] [width_map] [num_enemies] [num_ammo]\n";
        return -1;
    }
}

int main(int argc, char* argv[]) {
    srand(time(0));
    if (argc == 7) {
        int hight_window = getSize(argv[1]), width_window = getSize(argv[2]), hight_map = getSize(argv[3]), width_map = getSize(argv[4]), num_enemies = getSize(argv[5]), num_ammo = getSize(argv[6]);
        if (hight_map < 0 || hight_window < 0 || width_map < 0 || width_window < 0 || num_enemies < 0 || num_ammo < 0)
            return 0;
        return run(new MyFramework(width_map, hight_map, width_window, hight_window, num_enemies, num_ammo));
    }
    std::cerr << "[hight_window] [width_window] [hight_map] [width_map] [num_enemies] [num_ammo]\n";
    return 0;
}
