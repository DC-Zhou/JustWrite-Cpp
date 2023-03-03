//
// Created by Zhouzhou on 2023/2/25.
//

#include <iostream>
#include <type_traits>
#include <assert.h>

template <typename T>
class simple_wrapper
{
public:

    simple_wrapper(T const v) : value(v) {}

    T value;
};

template <typename T>
class fancy_wrapper{
public:
    fancy_wrapper(T const v) :value(v) {}
    T const & get() const { return value; }
    template<typename U>
    U as() const
    {
        return static_cast<U>(value);
    }

private:
    T value;
};

//
template<typename T, typename U, template<typename> typename W = fancy_wrapper>
class wrapping_pair{
public:
    wrapping_pair(T const a, U const b) :
    item1(a), item2(b)
    {}

    W<T> item1;
    W<U> item2;
};

int main()
{
    simple_wrapper<int> p0(100);

    wrapping_pair<int, double> p1(42, 42.0);
    std::cout << p1.item1.get() << " " << p1.item2.get() << "\n";

    wrapping_pair<int, double, simple_wrapper> p2(42, 42.0);
    std::cout << p2.item1.value << " " << p2.item2.value << "\n";
}