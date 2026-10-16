#include "Application.h"
#include <iostream>

int main(int argc, char* argv[]) {

    Application& app = Application::GetInstance();

    if (!app.Initialize(argc, argv)) {
        std::cerr << "Failed to initialize application." << std::endl;
        return EXIT_FAILURE;
    }

    app.Run();

    return EXIT_SUCCESS;
}