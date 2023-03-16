#ifndef COMMON_H
#define COMMON_H

#include <algorithm>
#include <stdexcept>

template<class T>
void ChangeLength1D(T* &a, int OldLength, int NewLength) {
    if (NewLength < 0) {
        throw std::range_error("new length must be >= 0");
    }
    T *temp = new T[NewLength];
    int num = std::min(OldLength, NewLength);
    // 原生类型的原生指针也可以充当迭代器
    std::copy(a/*first*/, a+num/*last*/, temp/*result*/);
    delete []a;
    a = temp;
}

#endif