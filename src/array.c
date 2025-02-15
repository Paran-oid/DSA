#include "array.h"

#include <stdlib.h>
#include <string.h>

// basic functionality
Array init_arr(i32 arr[], usize n) {
  Array res;

  i32 *ownArr = (i32 *)malloc(sizeof(i32) * n);
  memcpy(ownArr, arr, n * sizeof(i32));

  res.data = ownArr;
  res.n = n;
  return res;
}
void print_arr(Array *arr) {
  printf("{");
  for (usize i = 0; i < arr->n; i++) {
    if (i != arr->n - 1) {
      printf("%d, ", arr->data[i]);
    } else {
      printf("%d", arr->data[i]);
    }
  }
  printf("}\n");
}
void destroy_arr(Array *arr) { free(arr->data); }

// Search Algorithms
bool binary_search_arr(Array *arr, i32 item) {
  i32 l = 0, r = arr->n - 1;
  while (l <= r) {
    i32 mid = l + (r - l) / 2;
    if (arr->data[mid] == item) {
      return true;
    } else if (arr->data[mid] < item) {
      l = ++mid;
    } else {
      r = --mid;
    }
  }
  return false;
}
bool search_arr(Array *arr, i32 item) {
  for (usize i = 0; i < arr->n; i++) {
    if (arr->data[i] == item) {
      return true;
    }
  }
  return false;
}

// Sort Algorithms
void selection_sort(Array *arr, bool isAscending) {
  for (usize i = 0; i < arr->n; i++) {
    usize diff = i;
    for (usize j = i + 1; j < arr->n; j++) {
      if ((!isAscending && arr->data[j] > arr->data[diff]) ||
          (isAscending && arr->data[j] < arr->data[diff])) {
        diff = j;
      }
    }
    if (arr->data[diff] != arr->data[i]) {
      swap((void *)&arr->data[i], (void *)&arr->data[diff], sizeof(i32));
    }
  }
}
void bubble_sort(Array *arr, bool isAscending) {
  bool isSorted = false;
  isize tempN = arr->n;
  while (!isSorted) {
    isSorted = true;
    for (isize i = 1; i < tempN; i++) {
      if ((arr->data[i - 1] < arr->data[i] && !isAscending) |
          -(arr->data[i - 1] > arr->data[i] && isAscending)) {
        isSorted = false;
        swap((void *)&arr->data[i], (void *)&arr->data[i - 1], sizeof(i32));
      }
    }
    tempN--;
  }
}
void insertion_sort(Array *arr, bool isAscending) {
  for (usize i = 1; i < (usize)arr->n; i++) {
    i32 temp = arr->data[i];
    isize j = (isize)i - 1;
    while (j >= 0 && ((arr->data[j] < temp && !isAscending) ||
                      (arr->data[j] > temp && isAscending))) {
      arr->data[j + 1] = arr->data[j];
      j--;
    }
    arr->data[j + 1] = temp;
  }
}
void cycle_sort(Array *arr, bool isAscending) {
  usize writes = 0;

  for (usize cycle_start = 0; cycle_start < arr->n; cycle_start++) {
    i32 item = arr->data[cycle_start];

    usize pos = cycle_start;
    for (usize i = cycle_start + 1; i < arr->n; i++)
      if ((arr->data[i] < item && isAscending) ||
          (arr->data[i] > item && !isAscending))
        pos++;

    if (pos == cycle_start)
      continue;

    while (item == arr->data[pos])
      pos++;

    if (pos != cycle_start) {
      swap(&item, &arr->data[pos], sizeof(i32));
      writes++;
    }

    while (pos != cycle_start) {
      pos = cycle_start;

      for (usize i = cycle_start + 1; i < arr->n; i++)
        if ((arr->data[i] < item && isAscending) ||
            (arr->data[i] > item && !isAscending))
          pos++;

      while (item == arr->data[pos])
        pos++;

      if (item != arr->data[pos]) {
        swap(&item, &arr->data[pos], sizeof(i32));
        writes++;
      }
    }
  }

  char message[100];
  snprintf(message, 100,
           "Number of memory writes or swaps for cycle sort was %zu", writes);
}

// Quick Sort
static isize partition(Array *arr, isize low, isize high, bool isAscending) {
  isize i = low - 1;
  for (isize j = low; j < high; j++) {
    if ((arr->data[j] <= arr->data[high] && isAscending) ||
        (arr->data[j] >= arr->data[high] && !isAscending)) {
      i++;
      swap(&arr->data[i], &arr->data[j], sizeof(i32));
    }
  }
  swap(&arr->data[i + 1], &arr->data[high], sizeof(i32));

  return i + 1;
}
void quick_sort(Array *arr, isize low, isize high, bool isAscending) {
  if (low < high) {
    isize pivot = partition(arr, low, high, isAscending);

    quick_sort(arr, low, pivot - 1, isAscending);
    quick_sort(arr, pivot + 1, high, isAscending);
  }
}

// Merge Sort
static void merge(Array *arr, isize l, isize m, isize r, bool isAscending) {
  isize i, j, k;
  usize n1 = m - l + 1;
  usize n2 = r - m;

  i32 lTemp[n1], rTemp[n2];
  for (usize i = 0; i < n1; i++) {
    lTemp[i] = arr->data[l + i];
  }
  for (usize j = 0; j < n2; j++) {
    rTemp[j] = arr->data[m + 1 + j];
  }

  i = 0, j = 0, k = l;
  while (i < (isize)n1 && j < (isize)n2) {
    if ((isAscending && lTemp[i] <= rTemp[j]) ||
        (!isAscending && lTemp[i] > rTemp[j])) {
      arr->data[k] = lTemp[i];
      i++;
    } else {
      arr->data[k] = rTemp[j];
      j++;
    }
    k++;
  }

  while (i < (isize)n1) {
    arr->data[k] = lTemp[i];
    i++;
    k++;
  }

  while (j < (isize)n2) {
    arr->data[k] = rTemp[j];
    j++;
    k++;
  }
}
void merge_sort(Array *arr, isize l, isize r, bool isAscending) {
  if (l < r) {
    isize m = l + (r - l) / 2;
    merge_sort(arr, l, m, isAscending);
    merge_sort(arr, m + 1, r, isAscending);

    merge(arr, l, m, r, isAscending);
  }
}