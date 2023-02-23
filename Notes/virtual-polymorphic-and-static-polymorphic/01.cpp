#include <iostream>
#include <array>

struct base2_t{
    virtual void perform(int val){};

    ~base2_t() {};
};

struct derived3 : public base2_t {
    void perform(int val) override{
        int r = val * 2;
        std::cout << "r:" << r << std::endl;
    }
};

struct derived4: public base2_t{
    void perform(int val) override {
        int r = val * 3;
        std::cout << "r:" << r << std::endl;
    }
};

int main(){
    derived3 d3{};
    derived4 d4{};
    std::array<base2_t*, 2> array1{&d3, &d4};

    for(auto p : array1){
        p ->perform(2);
    }
}