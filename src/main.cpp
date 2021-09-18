#include <string.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <sys/wait.h>

#include <lib/common/strings.hpp>

static const std::string prompt = "wish> ";
static const std::string error_msg = "An error has occurred\n";

void print_error() {
    std::cerr << error_msg;
}

void handle_non_built_in(std::vector<char*> args) {
    int rc = fork();
    if (rc < 0) {
        print_error();
    } else if (rc == 0) {
        execvp(args[0], args.data());
        print_error();
        exit(1);
    } else {
        int rc = wait(NULL); //TODO: Check return code ?
        if (rc < 0) {
            print_error();
        }
    }
}

void handle_line(const std::string& line) {
    std::vector<char*> args = Utils::split_to_c_strings(line, ' ');
    if (args.empty()) {
        return;
    }

    if (strcmp(args[0], "exit") == 0) {
        exit(0);
    } else if (strcmp(args[0], "cd") == 0) {
        if (args.size() != 2) {
            print_error();
            goto free_resource;
        }
        int rc = chdir(args[1]);
        if (rc != 0) {
            print_error();
            goto free_resource;
        }
    }
    else {
        handle_non_built_in(args);
    }
free_resource:
    for (const auto p : args) {
        delete p;
    }
}

void handle_interactive_mode() {
    std::string line;
    std::cout << prompt;
    while(std::getline(std::cin, line)) {
        handle_line(line);
        std::cout << prompt;
    }
}

int main(int argc, char** /*argv*/) {
    if (argc > 1) {
//       handle_batch_mode(argc, argv);
    } else {
        handle_interactive_mode();
    }
}
