#include "sorting.h"
#include "stdio.h"

int comp(const void* key1, const void* key2)
{
    return (*(const int*)key1 - *(const int*)key2);
}

int main(void)
{
    int arr[] = { 9, 2, 10, 3, 4952, 2, 33, 4 };
    size_t n = sizeof(arr) / sizeof(arr[0]);
    quick_sort(arr, n, sizeof(arr[0]), 0, n - 1, comp);

    printf("{");
    for (size_t i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("}\n");

    return 0;
}
