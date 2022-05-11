#ifndef SORT_HEAD_H_2022_03_17
#define SORT_HEAD_H_2022_03_17

namespace templates
{
    /** Определение типа функции сравнения элементов
    \return
    \li > 0  - pElem1 меньше pElem2
    \li 0   - элементы pElem1 и pElem2 равны
    \li < 0 - pElem1 больше pElem2
    */
    typedef  int (CompareSortType)(const void *pElem1, const void *pElem2);

    void Merge(void** ppArray, void** ppArrayCopy, int left, int right, CompareSortType pCompareFunc) {
        if (left >= right) {
            return;
        }
        int middle = (left + right) / 2;
        Merge(ppArray, ppArrayCopy, left, middle, pCompareFunc);
        Merge(ppArray, ppArrayCopy, middle, right, pCompareFunc);

        for (int i= left; i < right; ++i) {
            ppArrayCopy[i] = ppArray[i];
        }
        int i = left;
        int j = left;
        int k = middle;
        while (i < middle & k < right) {
            if (pCompareFunc(ppArrayCopy[i], ppArrayCopy[k]) < 0) {
                ppArray[j] = ppArrayCopy[i];
                ++i;
            }
            else {
                ppArray[j] = ppArrayCopy[k];
                ++k;
            }
            ++j;
        }
        while (k < right) {
            ppArray[j] = ppArrayCopy[k];
            ++j;
            ++k;
        }
        while (i < middle) {
            ppArray[j] = ppArrayCopy[i];
            ++i;
            ++j;
        }

    }

    void mergeSort(void** ppArray, int length, CompareSortType pCompareFunc) {
        void** array_copy = new void* [length];
        Merge(ppArray, array_copy, 0, length, pCompareFunc);
    }
    void heapSort(void **ppArray, int length, CompareSortType pCompareFunc);

    template <class T>
    void mergeSort(T **ppArray, int length, int (pCompareFunc)(const T *pElem1, const T *pElem2))
    {
        mergeSort(reinterpret_cast<void**>(ppArray), length, (CompareSortType*)pCompareFunc);
    }
    template <class T>
    void heapSort(T **ppArray, int length, int (pCompareFunc)(const T *pElem1, const T *pElem2))
    {
        heapSort(reinterpret_cast<void**>(ppArray), length, (CompareSortType*)pCompareFunc);
    }
}; // namespace templates

#endif // #define SORT_HEAD_H_2021_02_25
