#include <iostream>
#include <gtest/gtest.h>
#include <vector>

#include <lib/common/strings.hpp>

bool validate_result(const std::vector<std::string>& lhs,
                     const std::vector<std::string>& rhs) 
{
    std::cout << lhs.size() << "_" << rhs.size() << '\n';
    return (lhs.size() == rhs.size()) &&
           [&]() -> bool {
               for (int i = 0; i < lhs.size(); i++) {
                   std::cerr << (lhs[i]) << "_" << (rhs[i]) << "\n";
                   if(lhs[i] != rhs[i]) {
                       return false;
                   }
               }
               return true;
           }();
}

TEST(Strings, Strings) {
    {
        auto result = Utils::split("This is a   line ", ' ');
        std::vector<std::string> expect = {
            "This", "is", "a", "line"
        };
        EXPECT_TRUE(validate_result(result, expect));
    }

    {
        auto result = Utils::split("This is a,,,line ", ',');
        std::vector<std::string> expect = {
            "This is a", "line "
        };
        EXPECT_TRUE(validate_result(result, expect));
    }
    
    {
        auto result = Utils::split("         ", ' ');
        std::vector<std::string> expect = {};
        EXPECT_TRUE(validate_result(result, expect));
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
