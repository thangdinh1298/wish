#include <vector>
#include <string>

namespace Utils {
    std::vector<std::string> split(const std::string& input, const char delim); 
    std::vector<char*> split_to_c_strings(const std::string& input, const char delim); 
}

