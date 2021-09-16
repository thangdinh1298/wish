#include <unistd.h>
#include <iostream>
#include <vector>
#include <sys/wait.h>

#include <lib/common/strings.hpp>

static const std::string prompt = "shelly> ";
static std::vector<std::string> paths = {"/bin/"};

//void handle_batch_mode();
//void handle_interactive_mode();

void handle_interactive_mode() {
    std::string line;
    while(true) {
        std::cout << prompt;
        std::getline(std::cin, line);
        std::vector<char*> args = Utils::split_to_c_strings(line, ' ');
        if (args.empty()) {
            continue;
        }

        int rc = fork();
        if (rc < 0) {
            std::cerr << "Error creating child process\n";
        } else if (rc == 0) {
            execvp(args[0], args.data());
            exit(1);
        } else {
            /*int rc = */wait(NULL); //TODO: Check return code ?
            for (const auto p : args) {
                delete p;
            }
        }
    }
}

int main(int argc, char** /*argv*/) {
    if (argc > 1) {
//       handle_batch_mode(argc, argv);
    } else {
        handle_interactive_mode();
    }
}
