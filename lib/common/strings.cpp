#include <lib/common/strings.hpp>

template <typename Operator>
void iterate_token(const std::string& input, const char delim, Operator&& op) {
    int token_length = 0;
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == delim) {
            if (token_length) {
                op(input, i - token_length, i - 1);
            }
            token_length = 0;
        } else {
            token_length++;
        }
    }
    if (token_length) {
        op(input, input.size() - token_length, input.size() - 1);
    }
}

/*
 * Split string list of strings using a char delimeter
 * Skips empty tokens
 */
std::vector<std::string> Utils::split(const std::string& input, const char delim) {
    struct TokenAggregator {
        std::vector<std::string> tokens_;
        void operator()(const std::string& input, int token_begin, int token_end) {
            tokens_.push_back(std::string(input.begin() + token_begin,
                              input.begin() + token_end + 1));
        }
    };
    TokenAggregator aggr;
    iterate_token(input, delim, aggr);
    return aggr.tokens_;
}

/*
 * Split string list of c-strings using a char delimeter
 * Skips empty tokens
 */
std::vector<char*> Utils::split_to_c_strings(const std::string& input, const char delim) {
    struct TokenAggregator {
        std::vector<char*> tokens_;
        void operator()(const std::string& input, int token_begin, int token_end) {
            char* token = new char[(token_end - token_begin + 2 )];
            int j = 0;
            for (int i = token_begin; i <= token_end; i++, j++) {
                token[j] = input[i];
            }
            token[j] = '\0';
            tokens_.push_back(token);
        }
    };
    TokenAggregator aggr;
    iterate_token(input, delim, aggr);
    return aggr.tokens_;
} 

/*
 * Split strings by string delimeter.
 * Skips empty tokens
 */
std::vector<std::string> Utils::split(std::string s, const std::string& delim) {
    size_t pos = 0;
    std::string token;
    std::vector<std::string> tokens;
    while ((pos = s.find(delim)) != std::string::npos) {
        token = s.substr(0, pos);
        if (!token.empty()) {
            tokens.push_back(token);
        }
        s.erase(0, pos + delim.length());
    }
    tokens.push_back(s);
    return tokens;
}

/*
 *  Trim whitespaces characters from string
 */
std::string Utils::trim(const std::string& str) {
    std::string whitespaces = " \t\f\v\n\r";
    size_t start = str.find_first_not_of(whitespaces);
    size_t end = str.find_last_not_of(whitespaces);
    if (start == std::string::npos || end == std::string::npos) {
        return "";
    }
    return str.substr(start, end - start + 1);
}
