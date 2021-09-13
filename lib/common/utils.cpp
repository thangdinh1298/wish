#include <lib/common/utils.hpp>

std::vector<std::string> Utils::split(const std::string& input, const char delim) {
    std::string token;
    std::vector<std::string> tokens;
    for (const auto& c: input) {
        if (c == delim) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            } else { //token empty
                continue;
            }
        } else {
            token += c;
        }
    }
}
