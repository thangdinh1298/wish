#include <iostream>
#include <vector>

#include "include/cmd_parser.hpp"

//static const std::string prompt = "shelly> ";
//static std::vector<std::string> paths = {"/bin/"};

//void handle_batch_mode();
//void handle_interactive_mode();

void handle_interactive_mode() {
    std::string line;
    while(true) {
        std::getline(std::cin, line);
        CMD cmd(line);
        std::cout << cmd.to_string();
    }
}

int main(int argc, char** argv) {
    if (argc > 1) {
//       handle_batch_mode(argc, argv);
    } else {
        handle_interactive_mode();
    }
}
