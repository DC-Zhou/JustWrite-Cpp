//
// Created by Zhouzhou on 2023/3/6.
//
#include <iostream>
#include <functional>

template <typename T, typename... Args>
T sum(T a, Args... args)
{
    if constexpr (sizeof...(args) == 0)
        return a;
    else
        return a + sum(args...);
}

template<typename... Ts>
constexpr auto get_type_sizes()
{
    return std::array<std::size_t, sizeof...(Ts)> {sizeof(Ts)...};
}

template <typename... Ts, typename... Us>
constexpr auto multipacks(Ts... args1, Us... args2)
{
    std::cout << sizeof...(args1) << ", " << sizeof...(args2) << "\n";
}

template <typename... Ts, typename... Us>
constexpr auto mulipacks_equal(Ts... args1, Us... args2)
{
    static_assert(
            sizeof...(args1) == sizeof...(args2),
            "Packs must be of equal sizes.");
}

template<typename, typename>
struct func_pair;
template<typename R1, typename... A1,
         typename R2, typename... A2>
 struct func_pair<R1(A1...), R2(A2...)>
 {
     std::function<R1(A1...)> f;
     std::function<R2(A2...)> g;
 };

bool twice_as(int a, int b)
{
    return a >= b * 2;
}

double sum_and_div(int a, int b, double c)
{
    return (a + b) /c;
}

void test_multipacks()
{
    multipacks<int>(1, 2, 3, 4, 5, 6, 7, 8, 9);
    multipacks<int, int, int>(1, 2, 3, 4, 5, 6, 7, 8, 9);
    multipacks<int, int, int, int>(1, 2, 3, 4, 5, 6, 7, 8, 9);
    multipacks<int, int, int, int, int>(1, 2, 3, 4, 5, 6, 7, 8, 9);
}

void test_multipacks_equal()
{
    mulipacks_equal<int>(1, 2);
    mulipacks_equal<int, int>(1, 2, 3, 4);
    mulipacks_equal<int, int, int, int>(1, 2, 3, 4, 1.0, 2.0, 3.0, 4.0);
}

void test_func_pair()
{
    func_pair<bool(int, int), double(int, int, double)> funcs{
            twice_as, sum_and_div};
    funcs.f(42, 12);
    funcs.g(42, 12, 10.0);
}

int main()
{
    std::cout << "Hello variadic template: \n";
    test_multipacks();
    test_multipacks_equal();
    test_func_pair();
}
