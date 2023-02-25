//
// Created by Zhouzhou on 2023/2/25.
//

#include <iostream>
#include <assert.h>
#include <type_traits>

template <typename T, size_t S>
class buffer
{
    T data_[S];
public:
    constexpr T const * data() const { return data_; }

    constexpr T& operator[](size_t const index)
    {
        return data_[index];
    }

    constexpr T const& operator[](size_t const index) const
    {
        return data_[index];
    }
};

// pass an argument for the non-type template parameter of the class template
struct device
{
    virtual void output() = 0;
    virtual ~device() {}
};
template<void (*action)()>
struct smart_device : device
{
    void output() override
    {
        (*action)();
    }
};

//
template<typename Command, void(Command::*action)()>
struct smart_device2 : device
{
    smart_device2(Command& command) : cmd(command) {}

    void output() override
    {
        (cmd.*action)();
    }

private:
    Command& cmd;
};

struct hello_command
{
    void say_hello_in_english()
    {
        std::cout << "hello world! \n";
    }

    void say_hello_in_spanish()
    {
        std::cout << "hola mundo! \n";
    }
};

void say_hello_in_english()
{
    std::cout << "hello world! \n";
}

void say_hello_in_spanish()
{
    std::cout << "hola mundo! \n";
}

void test_device01()
{
    // this show how to pass function pointer, to non-type template as parameter
    auto w1 = std::make_unique<smart_device<&say_hello_in_english>>();
    w1->output();

    auto w2 = std::make_unique<smart_device<&say_hello_in_spanish>>();
    w2->output();

    static_assert(!std::is_same_v<decltype(w1), decltype(w2)>);
}

void test_device02()
{
    hello_command cmd;
    auto w1 = std::make_unique<smart_device2<hello_command, &hello_command::say_hello_in_english>>(cmd);
    w1 ->output();

    auto w2 = std::make_unique<smart_device2<hello_command, &hello_command::say_hello_in_spanish>>(cmd);
    w2 -> output();
}


void test_buffer()
{
    buffer<int, 10> b1;
    buffer<int, 2 * 5> b2;
    static_assert(std::is_same_v<decltype(b1), decltype(b2)>);
}
int main()
{
    std::cout << "Hello, non type template parameters: \n";
    test_buffer();
    test_device01();
    test_device02();

}