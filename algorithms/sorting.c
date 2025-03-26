#include "sorting.h"
#include "core.h"
#include <stdlib.h>
#include <string.h>

int insertion_sort(void* data, size_t size, size_t esize, int (*compare)(const void* key1, const void* key2))
{
    char* arr = data;
    void* temp;

    if ((temp = malloc(esize)) == NULL) {
        return -1;
    }

    for (int i = 1; i < (int)size; i++) {
        int j = i - 1;
        memcpy(temp, &arr[i * esize], esize);
        while (j >= 0 && compare(&arr[j * esize], temp) > 0) {
            memcpy(&arr[(j + 1) * esize], &arr[j * esize], esize);
            j--;
        }
        memcpy(&arr[(j + 1) * esize], temp, esize);
    }
    free(temp);
    return 0;
}

static int quick_sort_pivot(void* data, size_t esize, int left, int right, int (*comp)(const void*, const void*))
{
    int pivot = right;
    int i = left - 1;
    void* temp;
    char* arr = data;

    if ((temp = malloc(esize)) == NULL) {
        return -1;
    }

    for (int j = left; j < pivot; j++) {
        if (comp(&arr[j * esize], &arr[right * esize]) > 0) {
            i++;
            swap(&arr[j * esize], &arr[i * esize], esize);
        }
    }

    swap(&arr[(i + 1) * esize], &arr[right * esize], esize);
    free(temp);

    return i + 1;
}
int quick_sort(void* data, size_t size, size_t esize, int left, int right, int (*comp)(const void*, const void*))
{
    if (left < right) {
        int pivot = quick_sort_pivot(data, esize, left, right, comp);
        quick_sort(data, size, esize, left, pivot - 1, comp);
        quick_sort(data, size, esize, pivot + 1, right, comp);
    }
    return 0;
}

static int merge(void* arr, size_t esize, int start, int mid, int end, int (*comp)(const void*, const void*))
{
    size_t n1, n2;
    n1 = mid - start + 1;
    n2 = end - mid;

    void* arr1 = malloc(n1 * esize);
    void* arr2 = malloc(n2 * esize);

    if (!arr1 || !arr2) {
        free(arr1);
        free(arr2);
        return -1;
    }

    for (size_t i = 0; i < n1; i++) {
        memcpy((char*)arr1 + i * esize, (char*)arr + (start + i) * esize, esize);
    }

    for (size_t j = 0; j < n2; j++) {
        memcpy((char*)arr2 + j * esize, (char*)arr + (mid + j + 1) * esize, esize);
    }

    int l = 0, r = 0, k = start;
    while (l < (int)n1 && r < (int)n2) {
        if (comp((char*)arr1 + l * esize, (char*)arr2 + r * esize) <= 0) {
            memcpy((char*)arr + k * esize, (char*)arr1 + l * esize, esize);
            l++;
        } else {
            memcpy((char*)arr + k * esize, (char*)arr2 + r * esize, esize);
            r++;
        }
        k++;
    }

    while (l < (int)n1) {
        memcpy((char*)arr + k * esize, (char*)  arr1 + l * esize, esize);
        l++;
        k++;
    }

    while (r < (int)n2) {
        memcpy((char*)arr + k * esize, arr2 + r * esize, esize);
        r++;
        k++;
    }

    free(arr1);
    free(arr2);

    return 0;
}

int merge_sort(void* arr, size_t size, size_t esize, int start, int end, int (*comp)(const void*, const void*))
{
    if (start < end) {
        int mid = start + (end - start) / 2;
        merge_sort(arr, size, esize, 0, mid, comp);
        merge_sort(arr, size, esize, mid + 1, end, comp);

        merge(arr, esize, start, mid, end, comp);
    }
    return 0;
}