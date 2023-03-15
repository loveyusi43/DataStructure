#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <ctime>

#include "sort.hpp"

int* GetRandomArray(int len);

template<class Compare = Less<int>>
void Sort(int *arr, int len, Compare comp = Compare());

void PrintArray(int *arr, int len);

/***********************************************************/


int main(void) {
    srand(time(0));

    static const int LEN = 10;
    int *array = GetRandomArray(LEN);
    std::cout << "排序前: ";
    PrintArray(array, LEN);
    Greater<int> g;
    Sort(array, LEN);
    std::cout << "排序后: ";
    PrintArray(array, LEN);

    delete []array;
    return 0;
}

/********************************************************/

template<class Compare>
void Sort(int *arr, int len, Compare comp) {
    //InsertSort(arr, len, comp);
    //ShellSort(arr, len, comp);
    //SelectSort(arr, len, comp);
    //HeapSort(arr, len, comp);
    //BubbleSort(arr, len, comp);
    //QuickSort(arr, len, comp);
    //MergeSort(arr, len, comp);
    CountSort(arr, len, comp);
}

int* GetRandomArray(int len) {
    int *arr = new int[len];

    for (int i = 0; i < len; ++i) {
        arr[i] = rand()%100;
    }
    return arr;
}

void PrintArray(int *arr, int len) {
    for (int i = 0; i < len; ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
}