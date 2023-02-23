//
// Created by a'a on 2023/2/21.
//
#include <iostream>
#include <array>

struct base_t{
    using FuncType = void (*)(void*, int);

    base_t(base_t::FuncType func) : func_(func) {}

    void perform(int val){
        func_(this, val);
    }

private:
    FuncType func_;
};

struct derived1 : public base_t{
    derived1() : base_t(derived1::do_perform){}

    void perform(int val){
        int r = val * 2;
    }

private:
    static void do_perform(void * owner, int val){
        int r = val * 2;
        std::cout << "r:" << r << std::endl;
    }
};

struct derived2 : public base_t{
    derived2() : base_t(derived2::do_perform){}

    void perform(int val){
        int r = val * 3;
    }

private:
    static void do_perform(void * owner, int val){
        int r = val * 3;
        std::cout << "r:" << r << std::endl;
    }
};



int main(){
    derived1 d1{};
    derived2 d2{};
    std::array<base_t*, 2> array1{&d1, &d2};

    for(auto p : array1){
        p ->perform(2);
    }
}