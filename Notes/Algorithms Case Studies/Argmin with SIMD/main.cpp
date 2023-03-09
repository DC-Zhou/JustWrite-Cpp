#include <iostream>
#include <algorithm>
#include <time.h>
#include <immintrin.h>

int argmin_native(int *a, int n){
    int k = 0;
    for(int i = 0; i < n; i++)
        if(a[i] < a[k])
            k = i;
    return k;
}

int argmin_update_min_native(int *a, int n){
    int k = 0;
    for(int i = 0; i < n; i++)
        if(a[i] < a[k]) [[unlikely]]
            k = i;
    return k;
}

int argmin_stl(int *a, int n){
    int k = std::min_element(a, a + n) - a;
    return k;
}

typedef __m256i reg;

int min(int *a, int n)
{
    int min = INT_MAX, idx = 0;

    reg p = _mm256_set1_epi32(min);

    for(int i = 0; i < n; i += 32) {
        reg y1 = _mm256_load_si256((reg *) & a[i]);
        reg y2 = _mm256_load_si256((reg *) & a[i + 8]);
        reg y3 = _mm256_load_si256((reg *) & a[i + 16]);
        reg y4 = _mm256_load_si256((reg *) & a[i + 24]);

        y1= _mm256_min_epi32(y1, y2);
        y3 = _mm256_min_epi32(y3, y4);
        y1 = _mm256_min_epi32(y1, y3);

        reg mask = _mm256_cmpgt_epi32(p, y1);

        if(!_mm256_testz_si256(mask, mask)) { [[unlikely]]
            idx = i;
            for(int j = i; j < i + 32; j++)
                min = (a[j] < min ? a[j] : min);
        }
    }

    return min;
}

int ctz(unsigned x) {
    unsigned y, bz, b4, b3, b2, b1, b0;
    y = x & -x; // Isolate rightmost 1-bit.
    bz = y ? 0 : 1; // 1 if y = 0.
    b4 = (y & 0x0000FFFF) ? 0 : 16;
    b3 = (y & 0x00FF00FF) ? 0 : 8;
    b2 = (y & 0x0F0F0F0F) ? 0 : 4;
    b1 = (y & 0x33333333) ? 0 : 2;
    b0 = (y & 0x55555555) ? 0 : 1;
    return bz + b4 + b3 + b2 + b1 + b0;
}

unsigned get_mask(reg m) {
    return _mm256_movemask_ps(_mm256_castsi256_ps(m));
}

reg cmp(reg x, int *p) {
    reg y = _mm256_load_si256( (reg*) p );
    return _mm256_cmpeq_epi32(x, y);
}

int find(int *a, const int n, int needle)
{
    reg x = _mm256_set1_epi32(needle);

    for (int i = 0; i < n; i += 32) {
        reg m1 = cmp(x, &a[i]);
        reg m2 = cmp(x, &a[i + 8]);
        reg m3 = cmp(x, &a[i + 16]);
        reg m4 = cmp(x, &a[i + 24]);

        reg m12 = _mm256_or_si256(m1, m2);
        reg m34 = _mm256_or_si256(m3, m4);
        reg m = _mm256_or_si256(m12, m34);

        if (!_mm256_testz_si256(m, m)) {
            unsigned mask = (get_mask(m4) << 24)
                            + (get_mask(m3) << 16)
                            + (get_mask(m2) << 8)
                            +  get_mask(m1);
            return i + ctz(mask);
        }
    }

    return 0;
}

const int B = 256;

// returns the minimum and its first block
std::pair<int, int> approx_argmin(int *a, int n) {
    int res = INT_MAX, idx = 0;
    for (int i = 0; i < n; i += B) {
        int val = min(a + i, B);
        if (val < res) {
            res = val;
            idx = i;
        }
    }
    return {res, idx};
}

int argmin(int *a, int n) {
    auto [needle, base] = approx_argmin(a, n);
    int idx = find(a + base, B, needle);
    return base + idx;
}

int argmin_avx(int *a, int n){
    // indices on the current iteration
    reg cur = _mm256_setr_epi32(0, 1, 2, 3, 4, 5, 6, 7);
    // the current minimum for each slice
    reg min = _mm256_set1_epi32(INT_MAX);
    // its index (argmin) for each slice
    reg idx = _mm256_setzero_si256();

    for(int i = 0; i < n; i += 8){
        // load a new SIMD block
        reg x = _mm256_load_si256((reg*) &a[i]);
        // find the slices where the minimum is updated
        reg mask = _mm256_cmpgt_epi32(min, x);
        // update the indices
        idx = _mm256_blendv_epi8(idx, cur, mask);
        // update the minimum (can also similarly use a "blend" here, but min is faster)
        min = _mm256_min_epi32(x, min);
        // update the current indices
        const reg eight = _mm256_set1_epi32(8);
        cur = _mm256_add_epi32(cur, eight);
        // can also use a "blend" here but min is faster
    }
    // find the argmin in the "min" register and return its real index
    int min_arr[8], idx_arr[8];
    _mm256_storeu_si256((reg*)min_arr, min);
    _mm256_storeu_si256((reg*)idx_arr, idx);

    int k = 0, m = min_arr[0];

    for(int i = 1; i < 8; i ++)
        if(min_arr[i] < m)
            m = min_arr[k = i];

    return idx_arr[k];
}

int argmin_update_min_avx(int *a, int n)
{
    int min = INT_MAX, idx = 0;

    reg p = _mm256_set1_epi32(min);
    for(int i = 0; i < n; i += 32){
        reg y1 = _mm256_load_si256((reg*) &a[i]);
        reg y2 = _mm256_load_si256((reg*) &a[i + 8]);
        reg y3 = _mm256_load_si256((reg*) &a[i + 16]);
        reg y4 = _mm256_load_si256((reg*) &a[i + 24]);

        y1= _mm256_min_epi32(y1, y2);
        y3 = _mm256_min_epi32(y3, y4);
        y1 = _mm256_min_epi32(y1, y3);

        reg mask = _mm256_cmpgt_epi32(p, y1);
        if(!_mm256_testz_si256(mask, mask)) { [[unlikely]]
            idx = i;
            for(int j = i; j < i + 32; j++)
                min = (a[j] < min ? a[j] : min);
            p = _mm256_set1_epi32(min);
        }
    }

    for (int i = idx; i < idx + 31; i++)
        if (a[i] == min)
            return i;

    return idx + 31;
}


void test_argmin()
{
    const int N = (1 << 16);
    alignas(32) int a[N];

    for (int i = 0; i < N; i++)
        a[i] = rand();

    int stl_res = argmin_stl(a, N);
    int native_res = argmin_native(a, N);
    int avx_res = argmin_avx(a, N);
    int min_avx_res = argmin_update_min_avx(a,N);

    std::cout << "\nnative     argmin = "<< native_res << std::endl;
    std::cout << "\nSTL        argmin = "<< stl_res << std::endl;
    std::cout << "\nAVX        argmin = "<< avx_res << std::endl;
    std::cout << "\nupdate AVX argmin = "<< min_avx_res << std::endl;
}

void test_avx()
{
    int a[16] = {3, 4, 1, 4, 5, 7, 9, 3};
    int n = 16;

    reg cur = _mm256_setr_epi32(0, 1, 2, 3, 4, 5, 6, 7);

    reg min = _mm256_set1_epi32(INT_MAX);

    reg idx = _mm256_setzero_si256();

    reg x = _mm256_load_si256((reg*) &a);
    // find the slices where the minimum is updated
    reg mask = _mm256_cmpgt_epi32(min, x);
    // update the indices
    idx = _mm256_blendv_epi8(idx, cur, mask);
    // update the minimum (can also similarly use a "blend" here, but min is faster)
    min = _mm256_min_epi32(x, min);
    // update the current indices
    const reg eight = _mm256_set1_epi32(8);
    cur = _mm256_add_epi32(cur, eight);
    // can also use a "blend" here but min is faster

    int temp[8];
    _mm256_storeu_si256((reg*)temp, min);

    for(int i = 0; i < 8; i++)
        std::cout << temp[i] << ", ";

    // find the argmin in the "min" register and return its real index

    int min_arr[8], idx_arr[8];
    _mm256_storeu_si256((reg*)min_arr, min);
    _mm256_storeu_si256((reg*)idx_arr, idx);

    int k = 0, m = min_arr[0];

    for(int i = 1; i < 8; i ++)
        if(min_arr[i] < m)
            m = min_arr[k = i];
}

void test_min_avx()
{
    int a[32] = {3, 4, 9, 4, 5, 7, 9, 3,3, 4, 11, 4, 5, 7, 9, 3, 12, 4, 1, 4, 5, 7, 9, 3,3, 4, 1, 4, 5, 7, 9, 3};
    int n = 32;
    int val = min(a, n);
    std::cout << "min(a,n) = " << val << std::endl;
}

void test_find_avx()
{
    int a[32] = {3, 4, 9, 4, 5, 7, 9, 3,3, 4, 11, 4, 5, 7, 9, 3, 12, 4, 1, 4, 5, 7, 9, 3, 3, 4, 1, 4, 5, 7, 9, 3};
    int n = 32;
    int val = find(a, n, 1);
    std::cout << "find(a,n) = " << val << std::endl;
}

void test_ctz()
{
    unsigned int a = 6;
    std::cout<<"ctz("<<a<<")="<<ctz(a)<<std::endl;
}


int main() {
    std::cout << "Hello, argmin optimization!" << std::endl;
//    test_argmin();
//    test_avx();
//    test_min_avx();
    test_find_avx();
//    test_ctz();

    return 0;
}
