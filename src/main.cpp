#include "include/controller/Controller.hpp"
#include "include/config/Settings.hpp"

int main() {
    bd::Settings settings;

    bd::Controller cont = bd::Controller(settings);
    cont.run();

    return 0;
}
