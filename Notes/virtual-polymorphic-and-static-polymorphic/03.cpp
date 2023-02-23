//
// Created by a'a on 2023/2/21.
//

#include <iostream>
#include <string>

std::string num_to_string(uint64_t address)
{
    std::string output = std::to_string(address >> 24);
    auto n = address >> 8;
    for (size_t i = 1; i < 4; i++) {
        output.insert(0, std::to_string(n % 256) + ".");
        n >>= 8;
    }
    return output;
}

void TEST_to_string()
{
    uint64_t a = 1271132211;
    std::string b = num_to_string(a);
    std::cout << "Use to String: IP:" << b << std::endl;
}

int main(){
    std::cout << "Serializing IPs quickly in C++" << std::endl;
    TEST_to_string();
}+