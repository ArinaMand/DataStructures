// sort_testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "sort.h"
#include <iostream>
#include <random>
#include <array>

void templates::mergeSort(void **ppArray, int length, CompareSortType pCompareFunc) {
    {
        if (length <= 1) {
            return;
        }
        templates:: mergeSort(ppArray, length / 2, pCompareFunc);
        int amount = sizeof(ppArray);
        /*int amount = ppArray.size() / length + ppArray.size() % length > 0 ? 1 : 0;
        if amount % 2 == 0{
            for (int i = 0, i < amount; i += 2) {
                int iter_1 = length * i;
                int iter_2 = length * (i + 1);

            }
        }*/
    }
}

int main()
{
    int Comparator(const int* elem_1, const int* elem_2){
        return 0;
    };

    //test 30 numbers in [0, 100]
    std::linear_congruential_engine<int, 7, 4, 100> device;
    std::array<int, 30> numbers;
    int* ptr_numbers[30];
    for (int i = 0; i < 30; ++i) {
        numbers[i] = device();
        ptr_numbers[i] = &numbers[i];
    };
    templates::mergeSort(ptr_numbers, 30, Comparator);
    std::sort(numbers.begin(), numbers.end());
    int i = 0;
    bool flag = true;
    while (i < 30 && flag) {
        if (*ptr_numbers[i] != numbers[i]) {
            flag = false;
        }
        ++i;
    }
    if (i == 30 && flag == true) {
        std::printf("MergeSort with 30 numbers correct");
    }
    else {
        std::printf("MergeSort with 30 numbers failed");
    }

    std::linear_congruential_engine<int, 7, 4, 100> device;
    std::array<int, 30> numbers;
    int* ptr_numbers[30];
    for (int i = 0; i < 30; ++i) {
        numbers[i] = device();
        ptr_numbers[i] = &numbers[i];
    };
    templates::mergeSort(ptr_numbers, 30, Comparator);
    std::sort(numbers.begin(), numbers.end());
    int i = 0;
    bool flag = true;
    while (i < 30 && flag) {
        if (*ptr_numbers[i] != numbers[i]) {
            flag = false;
        }
        ++i;
    }
    if (i == 30 && flag == true) {
        std::printf("MergeSort with 30 numbers correct");
    }
    else {
        std::printf("MergeSort with 30 numbers failed");
    }

}

