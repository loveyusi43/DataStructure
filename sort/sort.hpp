#ifndef SORT_HPP
#define SORT_HPP

#include <cassert>
#include <utility>
#include <stack>
#include <cstdio>
#include <algorithm>

/*
    只有插入、冒泡、归并具有稳定性
*/

template<class T = int>
struct Less{
    bool operator()(const T &x, const T &y) {
        return x < y;
    }
};


template <class T = int>
struct Greater{
    bool operator()(const T &x, const T &y) {
        return x > y;
    }
};

/**********************************************************************************************/

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

/*********************************************************************************************/

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

/****************************************************************************************************/

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

/*****************************************************************************************************/

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

/*******************************************************************************************/

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

/**********************************************************************************/

template<class T>
int GetMidIndex(T *a, int left, int right) {
    assert(left < right);
    assert(a);
    int mid = left + ((right-left) >> 1);
    assert(mid >= left && mid <= right);

    if (a[left] < a[right]) {
        if (a[right] < a[mid]) {
            return right;
        } else if (a[mid] < a[left]) {
            return left;
        }
        return mid;
    } else {
        if (a[mid] > a[left]) {
            return left;
        } else if (a[right] > a[mid]) {
            return right;
        }
        return mid;
    }
}

// 单趟的时间复杂度为：O(N)
template<class T, class Compare>
int PartitionHoare(T *a, int left, int right, Compare comp) {
    // 默认排升序
    assert(a);
    assert(left <= right);

    // 三数取中可以极大的优化有序或接近有序的情况
    int mid = GetMidIndex(a, left, right);
    std::swap(a[mid], a[left]);

    int key_index = left; // 选最左边的值做key
    // 走完一趟的效果是key右边的一定比key小,左边的一定比key大
    while (left < right) {
        // 右边先走，找小于key的值; 分为两种情况
        // 1. L <- R,最后一次右边找不到小的和左边相遇，但在上一次交换后此时相遇的值一定比key要小
        // 另外还要注意有大量重复数据的情况一不小心会导致死循环
        // 而在接近有序时可能会导致越界
        while (left < right && (comp(a[key_index], a[right]) || a[key_index] == a[right])) {
            --right;
        }

        // 2. L -> R, 右边在走N(N > 0)步后找到比key小的值，但左边找不到比key大的值,此时相遇处的值也是小于key的值
        // 综上两点选定key值后让另一边先走一定可以满足条件
        // 左边后走，找大于key的值
        while (left < right && (comp(a[left], a[key_index]) || a[key_index] == a[left])) {
            ++left;
        }
        std::swap(a[left], a[right]);
    }
    std::swap(a[right], a[key_index]);
    return right;
}


template<class T, class Compare>
int PartitionPit(T *a, int left, int right, Compare comp) {
    assert(a);
    assert(left <= right);

    int mid = GetMidIndex(a, left, right);
    std::swap(a[mid], a[left]);

    T key = a[left];
    int pit_index = left;
    while (left < right) {
        // 右边先走，找小, 大于等于时跳过
        while (left < right && (comp(key, a[right]) || key == a[right])) {
            --right;
        }
        a[pit_index] = a[right];
        // right = pit_index; 由于疏忽导致的bug
        pit_index = right;

        // 左后走找大,小于等于时跳过
        while (left < right && (comp(a[left], key) || a[left] == key)) {
            ++left;
        }
        a[pit_index] = a[left];
        pit_index = left;
    }
    a[pit_index] = key;
    return pit_index;
}


template<class T, class Compare>
int PartitionPointer(T *a, int left, int right, Compare comp) {
    assert(left <= right);
    assert(a);

    int mid = GetMidIndex(a, left, right);
    std::swap(a[mid], a[left]);

    int key_index = left; // 如果选右边的值做key此时prev应初始化为-1，且在最后一次交换前要+1
    int prev_index = left;
    int cur_index = left+1;

    while (cur_index <= right) {
        // cur向右找小,cur < key
        if (comp(a[cur_index], a[key_index]) && ++prev_index != cur_index) {
            std::swap(a[prev_index], a[cur_index]);
        }
        ++cur_index; // cur无论什么情况都要向后走
    }
    std::swap(a[prev_index], a[key_index]);
    return prev_index;
}

// 时间复杂度O(N*logN)，其递归展开图与二叉树极为相似，所以每一层可以看作遍历一次数组，即为N，二二叉树的高度为logN
// 但是，排序数组如果是有序或接近有序，每次递归只会减少一个数据：N N-1 N-2 N-3 ... 1，此时时间复杂度为O(N^2)
template<class T, class Compare>
void QuickSortRecursion(T *a, int left, int right, Compare comp) {
    assert(a);
    if (left >= right) {
        return;
    }

    if (right-left+1 < 10) {
        InsertSort(a+left, right-left+1, comp);
    } else {
        //int key_index = PartitionPit(a, left, right, comp);
        //int key_index = PartitionHoare(a, left, right, comp);
        int key_index = PartitionPointer(a, left, right, comp);
        QuickSortRecursion(a, left, key_index-1, comp);
        QuickSortRecursion(a, key_index+1, right, comp);
    }
}


template<class T, class Compare>
void QuickSortLoop(T *a, int left, int right, Compare comp) {
    std::stack<std::pair<int, int>> range;
    range.push({left, right});

    while (!range.empty()) {
        int begin = range.top().first;
        int end = range.top().second;
        range.pop();
        //int key_index = PartitionHoare(a, begin, end, comp);
        //int key_index = PartitionPit(a, begin, end, comp);
        int key_index = PartitionPointer(a, begin, end, comp);

        // 接下来是模拟栈的关键步骤
        if (begin < key_index-1) {
            range.push({begin, key_index-1});
        }
        if (key_index+1 < end) {
            range.push({key_index+1, end});
        }
    }
}

template<class T, class Compare = Less<T>>
void QuickSort(T *a, int len, Compare comp = Compare()) {
    //QuickSortRecursion(a, 0, len-1, comp);
    QuickSortLoop(a, 0, len-1, comp);
}


/********************************************************************************************/

template<class T, class Compare>
void __MergeSortRecursiont(T *a, int left, int right, T *temp, Compare comp) {
    if (left >= right) { // 当区间不存在或区间内只有一个元素时认为该区间已经有序
        return;
    }

    int mid = left + ((right-left) >> 1);
    int begin1 = left;
    int end1 = mid;
    int begin2 = mid+1;
    int end2 = right;

    __MergeSortRecursiont(a, begin1, end1, temp, comp); // 让左区间有序
    __MergeSortRecursiont(a, begin2, end2, temp, comp); // 让右区间有序

    int index = left;
    while (begin1 <= end1 && begin2 <= end2) {
        if (comp(a[begin1], a[begin2])) {
            temp[index] = a[begin1++];
        } else {
            temp[index] = a[begin2++];
        }
        ++index;
    }
    while (begin1 <= end1) {
        temp[index++] = a[begin1++];
    }
    while (begin2 <= end2) {
        temp[index++] = a[begin2++];
    }
    // 将归并好的数据拷贝会原数组
    for (int i = left; i <= right; ++i) {
        a[i] = temp[i];
    }
}

template<class T, class Compare>
void MergeSortRecursiont(T *a, int len, Compare comp) {
    T *temp = new T[len];
    assert(a);
    //assert(left <= right);
    __MergeSortRecursiont(a, 0, len-1, temp, comp);
    delete []temp;
}


template<class T, class Compare>
void MergeSortLoop1(T *a, int len, Compare comp) {
    T *temp = new T[len];
    assert(a);

    int gap = 1; // 每个被归并区间的最小值
    while (gap < len) {
        for (int i = 0; i < len; i += 2*gap) {
            // 采用左闭右闭区间
            int begin1 = i;
            int end1 = i+gap-1;
            int begin2 = i+gap;
            int end2 = i+2*gap-1;
            // 进行区间修正，除begin1之外都有可能越界
            if (end2 >= len) {
                end2 = len-1;
            }
            if (begin2 >= len) {
                //begin2 = len;
                end2 = begin2-1;
                //printf("[%d, %d]", begin2, end2);
                assert(begin2 > end2); // 该区间不存在，对于不存在区间不是要进行区间修正，而是要确保不会让该区间进入下面的循环
            }
            if (end1 >= len) {
                end1 = len-1;
                assert(begin2 > end2); // 第二个归并区间不存在
            }

            int index = begin1;
            while (begin1 <= end1 && begin2 <= end2) {
                if (comp(a[begin1], a[begin2])) {
                    temp[index] = a[begin1++];
                } else {
                    temp[index] = a[begin2++];
                }
                ++index;
            }
            while (begin1 <= end1) {
                temp[index++] = a[begin1++];
            }
            while (begin2 <= end2) {
                temp[index++] = a[begin2++];
            }
        }

        // 所有小区间归并完后再拷贝
        // 这种方式要求在循环体内不能有任何的跳出循环行为，否则可能会导致越界或随机值
        for (int i = 0; i < len; ++i) {
            a[i] = temp[i];
        }

        gap *= 2;
    }

    delete []temp;
}


template<class T, class Compare>
void MergeSortLoop2(T *a, int len, Compare comp) {
    T *temp = new T[len];
    int gap = 1;
    while (gap < len) {
        // gap的含义是每次归并的两个小分组的元素个数，因此每次循环应跳过2个gap
        for (int i = 0; i < len; i += 2*gap) {
            int begin1 = i;
            int end1 = i+gap-1;
            int begin2 = i+gap;
            int end2 = i+2*gap-1;

            if (end1 >= len) {
                break;
            }
            if (end2 >= len) {
                end2 = len-1;
            }

            int index = begin1;
            while (begin1 <= end1 && begin2 <= end2) {
                if (comp(a[begin1], a[begin2])) {
                    temp[index] = a[begin1++];
                } else {
                    temp[index] = a[begin2++];
                }
                ++index;
            }
            while (begin1 <= end1) {
                temp[index++] = a[begin1++];
            }
            while (begin2 <= end2) {
                temp[index++] = a[begin2++];
            }

            for (int j = i; j <= end2; ++j) {
                a[j] = temp[j];
            }
        }

        gap *= 2;
    }

    delete []temp;
}


// 时间复杂度：O(N*logN)
// 空间复杂度：O(N)
template<class T, class Compare = Less<T>>
void MergeSort(T *a, int len, Compare comp = Compare()) {
    //MergeSortRecursiont(a, len, comp);
    MergeSortLoop2(a, len, comp);
}


/************************************************************************************************/

// 限制很多，能发挥作用的场景不多，但效率非常高
template<class T, class Compare = Less<T>>
void CountSort(T *a, int len, Compare comp = Compare()) {
    T max_element = a[0];
    T min_element = a[0];
    // 采用相对映射，遍历找出最大值和最小值
    for (int i = 0; i < len; ++i) {
        if (a[i] > max_element) {
            max_element = a[i];
        }
        if (a[i] < min_element) {
            min_element = a[i];
        }
    }

    const int width = max_element-min_element+1;
    T *temp = new T[width] {T()};
    for (int i = 0; i < len; ++i) {
        temp[a[i]-min_element]++;
    }

    int index = 0;
    for (int i = 0; i < width; ++i) {
        while (temp[i]--) {
            a[index++] = i+min_element;
        }
    }

    if (comp(1, 0)) {
        std::reverse(a, a+len);
    }

    delete []temp;
}

#endif