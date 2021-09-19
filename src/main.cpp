#include <fstream>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <sys/wait.h>

static const std::string prompt = "wish> ";
static const std::string error_msg = "An error has occurred\n";

void print_error() {
    std::cerr << error_msg;
}

void print_usage() {
    std::cerr << "Usage: ./wish [batch_file]\n";
}

#include "cmd.hpp"

void handle_line(const std::string& line) {
    auto cmds = CMD::parse_cmds(line);
    for (const auto& cmd : cmds) {
        cmd.execute();
    }
}

void handle_interactive_mode() {
    std::string line;
    std::cout << prompt;
    while (std::getline(std::cin, line)) {
        handle_line(line);
        std::cout << prompt;
    }
}

void handle_batch_mode(int argc, char** argv) {
    if (argc != 2) {
        print_usage();
        return;
    }

    std::fstream f(argv[1], std::ios_base::in);
    std::string line;
    while (std::getline(f, line)) {
        handle_line(line);
    }
}

int main(int argc, char** argv) {
    if (argc > 1) {
        handle_batch_mode(argc, argv);
    } else {
        handle_interactive_mode();
    }
}
