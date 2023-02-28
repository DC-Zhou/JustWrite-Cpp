//
// Created by a'a on 2023/2/28.
//

#ifndef CH01_TEMPLATE_FUNDAMENTALS_WRAPPER_H
#define CH01_TEMPLATE_FUNDAMENTALS_WRAPPER_H

template <typename T>
struct wrapper{
    T data;
};
 extern template wrapper<int> // [1]  explicit instantiation declaration
#endif //CH01_TEMPLATE_FUNDAMENTALS_WRAPPER_H
