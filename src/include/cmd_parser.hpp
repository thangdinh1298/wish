#include <iostream>
#include <lib/common/utils.hpp>

class CMD {
public:
    CMD(const std::string& line) {
        const auto tokens = Utils::split(line, ' ');
        if (tokens.empty()) {
            throw std::invalid_argument("Token list is empty");
        }
        cmd_ = tokens.at(0);
        arg_v_= {tokens.begin() + 1, tokens.end()};
    }

    const std::string& cmd() const {
        return cmd_;
    }

    const std::vector<std::string>& arg_v() const {
        return arg_v_;
    }

    const std::string to_string() const {
        std::string str = cmd_;
        for (const auto& arg : arg_v_) {
            str += " " + arg;
        }
        return str;
    }
private:
	std::string cmd_;
	std::vector<std::string> arg_v_;
};
