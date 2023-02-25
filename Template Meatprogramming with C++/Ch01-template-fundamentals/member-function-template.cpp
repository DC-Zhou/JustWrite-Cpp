//
// Created by Zhouzhou on 2023/2/25.
//
#include <iostream>
#include <assert.h>

// member function in class template
template <typename T>
class class_01
{
public:
    T add(T const a, T const b)
    {
        return a + b;
    }
};

// member function template in class
class class_02
{
public:
    template<typename T>
    T add(T const a, T const b)
    {
        return a + b;
    }
};

// What if we have two template parameter
template <typename T>
class wrapper{
public:
    wrapper(T const v) : value(v) { }

    T const& get() const { return value; }

    template< typename U>
    U as() const
    {
        return static_cast<U>(value);
    }

private:
    T value;
};

void test_01()
{
    class_01<int> a;
    int b = a.add(22, 33);  // int

    class_02 c;
    int d = c.add<int>(22,33);
}

void test_as()
{
    wrapper<double> a(2.0);
    auto b = a.get();
    std::cout<< "wrapper double get use size: " << sizeof(b) << "\n";

    auto c = a.as<int>();
    std::cout<< "wrapper int as function use size: " << sizeof(c) << "\n";
}

int main()
{
    std::cout << "Hello member function template !\n";
    test_01();
    test_as();
}

