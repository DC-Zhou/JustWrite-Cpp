//
// Created by a'a on 2023/2/20.
//

#include <iostream>
#include <string>

struct Message{
    Message(std::string msg) : msg_(std::move(msg)){}

    Message(const Message& rhs) : msg_(rhs.msg_) {
        std::cout << "copy construct " << std::endl;
    }

    Message(Message&& rhs) : msg_(std::move(rhs.msg_)) {
        std::cout << "move construct " << std::endl;
    }

    std::string msg_;
};

void TEST_move(){
    Message m1{"aa"};
    Message m2 = m1;
    Message m3 = std::move(m1);
}

void TEST_const(){
    const Message m1{"aa"};
    Message m2 = std::move(m1);
}.

int main(){
    std::cout << "move sem in copy construct and deconstruct" << std::endl;
    TEST_move();
    std::cout << "move sem only use for const : " << std::endl;
    TEST_const();
}
