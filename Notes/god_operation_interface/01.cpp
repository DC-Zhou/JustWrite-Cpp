#include <iostream>
#include <vector>

int &foo(std::vector<int> &v, int val) {
    auto iter = std::find(v.begin(), v.end(), val);
    if (iter == v.end())
        v.push_back(val);
    return iter == v.end() ? v.back() : *iter;
}

int main() {
    std::cout << "Hello, C++ iterator out of bound!" << std::endl;
    std::vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8};
    auto b = foo(a, 2);
    std::cout << "b = foo(a,8):" << b << std::endl;
    return 0;
}
