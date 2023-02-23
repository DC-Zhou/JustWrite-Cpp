//
// Created by a'a on 2023/2/20.
//
#include <iostream>
#include <array>

template <typename Op, typename Buffer, typename ... Args>
void god_operation_interface(Op op, Buffer buf, Args... args){
    op(buf, args...);
}

struct drived_god{
    struct read_some_init{
        void operator()(std::string buf){
            std::cout << "read string " << std::endl;
        }

        void operator()(std::string buf, int size){
            std::cout << "read string, size:" << size << std::endl;
        }
    };

    struct write_some_init{
        void operator()(std::string buf){
            std::cout << "write string " << std::endl;
        }
    };

    void read_some(std::string buf){
        god_operation_interface(read_some_init{}, buf);
    }

    void read_some(std::string buf, int size){
        god_operation_interface(read_some_init{}, buf, size);
    }

    void write_some(std::string buf){
        god_operation_interface(write_some_init{}, buf);
    }
};

int main() {
    std::cout << "Hello, God Interface!" << std::endl;

    drived_god god;
    god.read_some("hello");
    god.read_some("hello", 42);
    god.write_some("world");
}
