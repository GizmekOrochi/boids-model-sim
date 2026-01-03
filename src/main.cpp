#include "include/Application.hpp"
#include "include/config/Settings.hpp"

int main() {
    bd::Settings settings;

    bd::Application app(settings);
    app.run();

    return 0;
}
