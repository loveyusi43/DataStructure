#ifndef SORT_HPP
#define SORT_HPP

#include <cassert>
#include <utility>


template<class T = int>
struct Less{
    bool operator()(T &x, T &y) {
        return x < y;
    }
};


template <class T = int>
struct Greater{
    bool operator()(T &x, T &y) {
        return x > y;
    }
};


// 核心思想，把一个数插入一段有序的区间
// 时间复杂度：等差数列 O(N^2) 最好：接近有序 最坏：逆序
// 空间复杂度：O(1)
template <class T, typename Compare = Less<T>>
void InsertSort(T *a, int n, Compare comp = Compare()) {
    assert(a);

    for (int i = 0; i < n-1; ++i) {
        // 把x插入到end的后面
        int end_index = i;
        T x = a[end_index+1]; // 元素向后移动可能会覆盖，提前保存起来

        while (end_index >= 0) {
            // 默认排升序
            // a[end]>x
            if (comp(x, a[end_index])) {
                a[end_index+1] = a[end_index--];
            } else {
                break;
            }
        }
        a[end_index+1] = x;
    }
}


// 时间复杂度：最好：O(N)
// 以插入排序位基础，核心思想同插入排序："插入"
// 数据量大才能发挥优势
template<class T, class Compare = Less<T>>
void ShellSort(T *a, int len, Compare comp = Compare()) {
    assert(a);
    int gap = len;
    while (gap > 1) { // gap不能等于1，否则会多排一次,也可能会死循环
        // 任何一个大于2的数不断除2最终都会等于1
        // gap /= 2;
        // 不断减小分组，分组越大，预排一次越块，但也不接近有序
        gap = gap/3 + 1; // 每次除3有可能最后一次达不到1，例如：6/3=2,2/3=0直接跳出循环，最后一次的分组是2
        // 一层循环同时进行多个分组的排序，当然也可以再加一层循环一个分组排完再排下一组
        for (int i = 0; i < len-gap; ++i) {
            int end_index = i;
            T x = a[end_index+gap];
            // 每个分组中的其中一趟排序
            while (end_index >= 0) {
                // 默认排升序
                // x<end
                if (comp(x, a[end_index])) {
                    a[end_index+gap] = a[end_index];
                    end_index -= gap;
                } else {
                    break;
                }
            }
            a[end_index+gap] = x;
        }
    }
}


// 时间复杂度：O(N)  N N-2 N-4 N-6 ... ; 最好的情况也还是O(N)
// 整体而言最差的排序
template<class T, class Compare = Less<T>>
void SelectSort(T *a, int len, Compare comp = Compare()) {
    assert(a);
    int begin = 0;
    int end = len-1;
    while (begin < end) {
        int max_index = begin;
        int min_index = begin;
        for (int i = begin; i <= end; ++i) {
            // max < i
            if (comp(a[max_index], a[i])) {
                max_index = i;
            }
            // i < min
            if (comp(a[i], a[min_index])) {
                min_index = i;
            }
        }
        std::swap(a[min_index], a[begin]);
        if (max_index == begin) {
            max_index = min_index;
        }
        std::swap(a[max_index], a[end]);
        ++begin;
        --end;
    }
}


template<class T, class Compare>
void AdjustDown(T *a, int n/*该参数不是数组的长度，而是要调整的边界*/, int parents, Compare comp) {
    int child = parents*2 + 1;
    while (child < n) {
        if (child+1 < n && comp(a[child], a[child+1])) {
            ++child;
        }

        if (comp(a[parents], a[child])) {
            std::swap(a[parents], a[child]);
            parents = child;
            child = parents*2 + 1;
        } else {
            break;
        }
    }
}


template<class T, class Compare = Less<T>>
void HeapSort(T *a, int len, Compare comp = Compare()) {
    assert(a);
    // 默认建大堆
    // 1.**向下**调整建大堆
    // 建堆的时间复杂度是O(N)，而且向下建堆更优，向下建堆是从最后一个节点的父节点开始，也就意味着是从倒数第二层开始调整，而根据二叉树的性质最后一层的节点占比接近一半
    for (int i = (len-1-1)/2; i >= 0; --i) {
        AdjustDown(a, len, i, comp);
    }
    // 2.交换堆顶数据再**向下**调整
    for (int i = len-1; i > 0; --i) {
        std::swap(a[0], a[i]);
        AdjustDown(a, i, 0, comp);
    }
}


// 时间复杂度：标准的O(N^2) 在最好的情况下优化版本可以达到O(N)
template<class T, class Compare = Less<T>>
void BubbleSort(T *a, int len, Compare comp = Compare()) {
    assert(a);
    for (int i = 0; i < len; ++i) {
        // 每一趟开始的时候设置一个是否发送交换的标记
        int exchange = 0;
        for (int j = 0; j < len-1-i; ++j) {
            // i+1 < i
            if (comp(a[j+1], a[j])) {
                exchange = 1;
                std::swap(a[j+1], a[j]);
            }
        }
        if (0 == exchange) {
            break;
        }
    }
}

#endif