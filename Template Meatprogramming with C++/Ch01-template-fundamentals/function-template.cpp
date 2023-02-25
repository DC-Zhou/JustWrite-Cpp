#include <iostream>
#include <assert.h>

int add_int(int a, int b)
{
    return a+b;
}

template<typename T>
T add(T const a, T const b)
{
    return a + b;
}

template<typename T, typename Predicate>
int number_count_if(T const start, T const end, Predicate p)
{
    int total = 0;
    for(T i = start; i != end; i++)
    {
        if(p(*i))
            total++;
    }

    return total;
}

void test_add_int()
{
    assert(add_int(3, 4) == 7);
}

void test_add_template()
{
    assert(add(3,4) == 7);
    assert(add<double>(3.0, 4) == 7.0);
    assert(add(0.1f, 0.3f) == 0.4f);
}

void test_two_numbers_parameter()
{
    int arr[] {1,2,3,4,5,6};
    int odds = number_count_if(
                std::begin(arr), std::end(arr),
                [](int const n) { return n % 2 == 1; }
            );
    std::cout << "Count odds in arr is: " << odds << std::endl;
}


int main() {
    std::cout << "Hello, function-templates!" << std::endl;
    test_add_int();
    test_add_template();
    test_two_numbers_parameter();
    return 0;
}
