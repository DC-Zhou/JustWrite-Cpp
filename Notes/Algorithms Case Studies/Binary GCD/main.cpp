#include <iostream>
#include <bits/stdc++.h>
#include <assert.h>

int gcd_native_0(int a, int b)
{
    while (b > 0){
        a %= b;
        std::swap(a, b);
    }
    return a;
}

int gcd_native_1(int a, int b)
{
    while (b) b ^= a ^= b ^= a %= b;
    return a;
}

int gcd_binary_0(int a, int b)
{
    if (a == 0) return b;
    if (b == 0) return a;
    if (a == b) return a;

    if(a % 2 == 0){
        if(b % 2 == 0)      // a is even , b is even(2)
            return 2 * gcd_binary_0(a / 2, b / 2);
        else                // a is even, b is odd (3)
            return gcd_binary_0(a/2, b);
    } else {
        if (b % 2 == 0)     // a is odd, b is even (3)
            return gcd_binary_0(a, b/2);
        else                // a is odd, b is odd (4)
            return gcd_binary_0(std::abs(a - b), std::min(a, b));
    }
}

int binary_gcd_1(int a, int b)
{
    if (a == 0) return b;
    if (b == 0) return a;

    int az = __builtin_ctz(a);
    int bz = __builtin_ctz(b);

    int shift = std::min(az, bz);
    a >>= az, b >>= b;

    while(a != 0) {
        int diff = a - b;
        b = std::min(a, b);
        a = std::abs(diff);
        a >>= __builtin_ctz(a);
    }

    return b << shift;
}

void test_gcd_native()
{
    int a = gcd_native_0(90, 48);
    std::cout << "gcd(7,15):" << a << std::endl;
}


int main() {
    std::cout << "Hello, Binary_gcd!" << std::endl;

    // swap
    int a = 10;
    int b = 11;
    a ^= b ^= a ^= b;
    std::cout << "swap(a,b) = " << a << ","<<b << std::endl;

    //
    unsigned short c = 5;
    std::cout << "builtin only use in gcc\n";
    std::cout << "__builtin_popcount(" << c <<"):" << __builtin_popcount(c) << std::endl;
    std::cout << "__builtin_ctz(" << c <<"):" << __builtin_ctz(c) << std::endl;

    test_gcd_native();

    return 0;
}
