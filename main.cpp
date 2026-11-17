#include "inc/app.hpp"
#include <iostream>

int main() {
    App app;
    try {
        app.run();
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
