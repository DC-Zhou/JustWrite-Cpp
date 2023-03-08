#include <iostream>
#include <vector>
#include <xmmintrin.h>
#include <immintrin.h>
#include <cassert>

void test_vec_add() {
    const std::vector<int> a = {1, 2, 3, 4};
    const std::vector<int> b = {5, 6, 7, 8};

    const auto va = _mm_loadu_si128((__m128i *) a.data());
    const auto vb = _mm_loadu_si128((__m128i *) b.data());
    const auto result = _mm_add_epi32(va, vb);

    std::vector<int> v(a.size());
    _mm_storeu_si128((__m128i *) v.data(), result);

    assert((std::vector<int>{1 + 5, 2 + 6, 3 + 7, 4 + 8} == v));
}


int test_zero_add() {
    const std::vector<float> a{};
    const std::vector<float> b{};

    return 0;
}

void test_vec_multi() {

    const std::vector<int> a = {1, 2, 3, 4};
    const std::vector<int> b = {5, 6, 7, 8};

    const auto va = _mm_load_si128((__m128i *) a.data());
    std::vector<int> vec_a(a.size());
    _mm_storeu_si128((__m128i *) vec_a.data(), va);

    const auto vb = _mm_load_si128((__m128i *) b.data());
    std::vector<int> vec_b(a.size());
    _mm_storeu_si128((__m128i *) vec_b.data(), vb);

    const auto result = _mm_mullo_epi32(va, vb);
    std::vector<int> v(a.size());
    _mm_storeu_si128((__m128i *) v.data(), result);

    std::cout << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cout << v[i] << ", ";
    }
}

void test_vec_multi_add() {
    std::cout << "\n";

    const std::vector<float> a = {1.f, 2.f, 3.f, 4.f};
    const std::vector<float> b = {5.f, 6.f, 7.f, 8.f};

    const auto va = _mm_load_ps(a.data());

    const auto vb = _mm_load_ps(b.data());

    const auto vmul = _mm_mul_ps(va, vb);

    std::vector<float> v_mul(a.size());
    _mm_store_ps(v_mul.data(), vmul);

    // set a vector of v_mul[0], v_mul[1], v_mul[2], v_mul[3]
    const auto v0 = _mm_load_ps1(&v_mul[0]);
    const auto v1 = _mm_load_ps1(&v_mul[1]);
    const auto v2 = _mm_load_ps1(&v_mul[2]);
    const auto v3 = _mm_load_ps1(&v_mul[3]);

    auto v4 = _mm_add_ps(v0, v1);
    auto v5 = _mm_add_ps(v2, v3);

    v4 = _mm_add_ps(v4, v5);

    std::vector<float> add_result(a.size());
    _mm_store_ps(add_result.data(), v4);

    std::cout << "\n";
    for (int i = 0; i < a.size(); i++) {
        std::cout << add_result[i] << ". ";
    }

}

int main() {

    std::cout << "Did you know about intrisincts to support SIMD (Single Instruction, Multiple Data) instructions?"
              << std::endl;

    test_vec_add();
    test_zero_add();
    test_vec_multi();
    test_vec_multi_add();

    std::vector<float> a;
    std::cout << "sizeof a:" << sizeof a << std::endl;
}