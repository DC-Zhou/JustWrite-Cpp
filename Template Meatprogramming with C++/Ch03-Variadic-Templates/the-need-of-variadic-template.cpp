#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int min_0(int count, ...)
{
    va_list args;
    va_start(args, count);
    int val = va_arg(args, int);
    for(int i = 1; i < count; i++)
    {
        int n = va_arg(args, int);
        if( n < val)
            val = n;
    }
    va_end(args);
    return val;
}

template <typename T>
T min_1(int count, ...)
{
    va_list args;
    va_start(args, count);
    T val = va_arg(args, T);
    for(int i = 1; i < count; i++)
    {
        T n = va_arg(args, T);
        if( n < val)
            val = n;
    }
    va_end(args);
    return val;
}

void test_no_variadic_template()
{
    printf("min(2,42,7) = %d", min_0(2, 42, 7));
    printf("\n");
    printf("min(1,5,3,-4,9)= %d", min_0(1, 5, 3, -4,9));
    printf("\n");

    printf("template: min<double>(2,42.0,7.5) = %d", min_1<double>(2, 42.0, 7.5));
    printf("\n");
    printf("template: min<int>(1,5,3,-4,9)= %d", min_1<int>(5, 5, 3, -4,9));
    printf("\n");
}

int main() {
    printf("find a min number in array \n");
    printf("with no variadic template: \n");
    test_no_variadic_template();
    return 0;
}
