#include <algorithm>
#include <vector>
#include <fcntl.h>

#include <lib/common/strings.hpp>

class CMD {
public:
    CMD(const std::string& line,
        bool need_redirect=false,
        std::string output="") :
        need_redirect_(need_redirect), output_(output)
    {
        args_ = Utils::split(line, ' '); // args_ might be empty since split skips empty tokens
        std::for_each(args_.begin(), args_.end(), Utils::trim);
    }

    void execute() const {
        if (args_.empty()) {
            return;
        }

        if (args_[0] =="exit") {
            exit(0);
        } else if (args_[0] == "cd") {
            if (args_.size() != 2) {
                print_error();
                return;
            }
            int rc = chdir(args_[1].c_str());
            if (rc != 0) {
                print_error();
            }
        } else {
            handle_non_built_in();
        }
    }

    static std::vector<CMD> parse_cmds(const std::string& line) {
        auto cmd_strings = Utils::split(line, "&&");
        std::vector<CMD> cmds;
        for (const auto& cmd_string : cmd_strings) {
            auto tokens = Utils::split(cmd_string, '>');
            switch(tokens.size()) {
                case 0:
                    break;
                case 1:
                    cmds.emplace_back(tokens[0]);
                    break;
                default:
                    cmds.emplace_back(tokens[0], true, Utils::trim(tokens[1]));
                    break;
            }
        }
        return cmds;
    }
private:
    void handle_non_built_in() const {
        int rc = fork();
        if (rc < 0) {
            print_error();
        } else if (rc == 0) {
            if (need_redirect_) {
                int close_rc = close(STDOUT_FILENO);
                if (close_rc < 0) {
                    print_error();
                    exit(1);
                }
                int open_rc = open(output_.c_str(),  O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
                if (open_rc < 0) {
                    print_error();
                    exit(1);
                }
            }
            std::vector<char*> argv;
            for (const auto& p : args_) {
                argv.push_back(const_cast<char*>(p.c_str()));
            }
            argv.push_back(nullptr);

            execvp(argv[0], argv.data());
            print_error();
            exit(1);
        } else {
            int rc = wait(NULL);
            if (rc < 0) {
                print_error();
            }
        }
    }
private:
    std::vector<std::string> args_;
    bool need_redirect_;
    std::string output_;
};
