#include "array.h"
#include "funcs.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// basic functionality

Array array_create(void *arr, size_t size, DataType type) {
  ASSERT(size != 0, "number of elements in array size can't be \n");
  ASSERT(arr != NULL, "array passed is NULL \n");

  Array res = {0};
  size_t elsize = type_map(type);

  if (!arr) {
    void *ownArr = calloc(size, elsize);
    ASSERT(ownArr != NULL, "couldn't allocate memory for the array");
    res.data = ownArr;
    res.size = res.capacity = 0;
    res.element_size = elsize;
  }
  void *ownArr = malloc(size * elsize);

  ASSERT(ownArr != NULL, "couldn't allocate memory for the array");

  memcpy(ownArr, arr, size * elsize);

  res.data = ownArr;
  res.element_size = elsize;

  res.size = size;
  res.capacity = size;

  return res;
}

void array_destroy(Array *arr) { free(arr->data); }

// Dynamic Functionality

void *array_get(const Array *arr, int index) {
  ASSERT(arr && arr->data, "Null/Null data passed\n");
  ASSERT(index >= 0 && index < (int)arr->size, "Index out of range");
  return (char *)arr->data + (index * arr->element_size);
}
void array_set(Array *arr, int index, void *item) {
  ASSERT(arr != NULL && arr->data != NULL, "Array is NULL or uncreateialized");
  ASSERT(index > 0 && index < (int)arr->size, "Index out of range");
  memcpy((char *)arr->data + index * arr->element_size, item,
         arr->element_size);
}
void array_pushback(Array *arr, void *item) {
  ASSERT(arr != NULL && arr->data != NULL, "Array is NULL or uncreateialized");
  if (arr->size == arr->capacity)
    array_resize(arr);

  memcpy((char *)arr->data + arr->size * arr->element_size, item,
         arr->element_size);
  arr->size++;
}
void *array_popback(Array *arr) {
  ASSERT(arr != NULL && arr->data != NULL, "Array is NULL or uncreateialized");
  ASSERT(arr->size > 0, "Array is empty when you tried to pop it...\n");
  void *res = (char *)arr->data + (arr->size - 1) * arr->element_size;
  arr->size--;
  return res;
}
void array_resize(Array *arr) {
  ASSERT(arr != NULL && arr->data != NULL, "Array is NULL or uncreateialized");
  arr->capacity = arr->capacity == 0 ? 1 : 2 * arr->capacity;
  arr->data = realloc(arr->data, arr->capacity);

  if (!arr->data) {
    perror("error reallocating array\n");
    exit(EXIT_FAILURE);
  }
}

// Search Algorithms

bool binary_search(Array *arr, void *item) {
  int l = 0, r = arr->size - 1;
  while (l <= r) {
    int mid = l + (r - l) / 2;
    int comp = memcmp((char *)arr->data + mid * arr->element_size, item,
                      arr->element_size);
    if (comp == 0) {
      return true;
    } else if (comp < 0) {
      l = ++mid;
    } else {
      r = --mid;
    }
  }
  return false;
}

bool linear_search(Array *arr, void *item) {
  for (size_t i = 0; i < arr->size; i++) {
    if (memcmp((char *)arr->data + i * arr->element_size, item,
               arr->element_size) == 0) {
      return true;
    }
  }
  return false;
}

// Sort Algorithms

void selection_sort(Array *arr, bool isAscending) {
  for (size_t i = 0; i < arr->size; i++) {
    size_t diff = i;
    for (size_t j = i + 1; j < arr->size; j++) {
      int res = memcmp((char *)arr->data + j * arr->element_size,
                       (char *)arr->data + diff * arr->element_size,
                       arr->element_size);
      if ((!isAscending && res < 0) || (isAscending && res > 0)) {
        diff = j;
      }
    }
    if (memcmp((char *)arr->data + i * arr->element_size,
               (char *)arr->data + diff * arr->element_size,
               arr->element_size) != 0) {
      void *temp = malloc(arr->element_size);
      memcpy(temp, (char *)arr->data + i * arr->element_size,
             arr->element_size);
      memcpy((char *)arr->data + i * arr->element_size,
             (char *)arr->data + diff * arr->element_size, arr->element_size);
      memcpy((char *)arr->data + diff * arr->element_size, temp,
             arr->element_size);
      free(temp);
    }
  }
}

void bubble_sort(Array *arr, bool isAscending) {
  bool isSorted = false;
  int tempN = arr->size;
  while (!isSorted) {
    isSorted = true;
    for (int i = 1; i < tempN; i++) {
      int res =
          memcmp((char *)arr->data + (i - 1) * arr->element_size,
                 (char *)arr->data + i * arr->element_size, arr->element_size);

      if ((res < 0 && !isAscending) || (res > 0 && isAscending)) {
        isSorted = false;
        void *temp = malloc(arr->element_size);
        memcpy(temp, (char *)arr->data + (i - 1) * arr->element_size,
               arr->element_size);
        memcpy((char *)arr->data + (i - 1) * arr->element_size,
               (char *)arr->data + i * arr->element_size, arr->element_size);
        memcpy((char *)arr->data + i * arr->element_size, temp,
               arr->element_size);
        free(temp);
      }
    }
    tempN--;
  }
}

void insertion_sort(Array *arr, bool isAscending) {
  void *temp = malloc(arr->element_size);
  for (size_t i = 1; i < arr->size; i++) {
    memcpy(temp, (char *)arr->data + i * arr->element_size, arr->element_size);
    int j = i - 1;

    while (j >= 0) {
      int res = memcmp((char *)arr->data + j * arr->element_size, temp,
                       arr->element_size);
      if (!((res < 0 && !isAscending) || (res > 0 && isAscending))) {
        break;
      }
      memcpy((char *)arr->data + (j + 1) * arr->element_size,
             (char *)arr->data + j * arr->element_size, arr->element_size);
      j--;
    }
    memcpy((char *)arr->data + (j + 1) * arr->element_size, temp,
           arr->element_size);
  }
  free(temp);
}

void cycle_sort(Array *arr, bool isAscending) {
  void *temp = malloc(arr->element_size);

  for (size_t cycle_start = 0; cycle_start < arr->size - 1; cycle_start++) {
    memcpy(temp, (char *)arr->data + cycle_start * arr->element_size,
           arr->element_size);

    size_t pos = cycle_start;
    for (size_t i = cycle_start + 1; i < arr->size; i++) {
      int comp = memcmp((char *)arr->data + i * arr->element_size, temp,
                        arr->element_size);
      if ((isAscending && comp < 0) || (!isAscending && comp > 0)) {
        pos++;
      }
    }

    if (pos == cycle_start) {
      continue;
    }

    while (memcmp((char *)arr->data + pos * arr->element_size, temp,
                  arr->element_size) == 0) {
      pos++;
    }

    if (pos != cycle_start) {
      swap((char *)arr->data + pos * arr->element_size, temp,
           arr->element_size);
    }

    while (pos != cycle_start) {
      pos = cycle_start;
      for (size_t i = cycle_start + 1; i < arr->size; i++) {
        int comp = memcmp((char *)arr->data + i * arr->element_size, temp,
                          arr->element_size);
        if ((isAscending && comp < 0) || (!isAscending && comp > 0)) {
          pos++;
        }
      }

      while (memcmp((char *)arr->data + pos * arr->element_size, temp,
                    arr->element_size) == 0) {
        pos++;
      }

      if (memcmp(temp, (char *)arr->data + pos * arr->element_size,
                 arr->element_size) != 0) {
        swap(temp, (char *)arr->data + pos * arr->element_size,
             arr->element_size);
      }
    }
  }

  free(temp);
}

// Quick Sort

static int partition(Array *arr, int low, int high, bool isAscending) {
  int i = low - 1;
  for (int j = low; j < high; j++) {
    int res =
        memcmp((char *)arr->data + j * arr->element_size,
               (char *)arr->data + high * arr->element_size, arr->element_size);
    if ((res < 0 && isAscending) || (res >= 0 && !isAscending)) {
      i++;
      void *temp = malloc(arr->element_size);
      memcpy(temp, (char *)arr->data + i * arr->element_size,
             arr->element_size);
      memcpy((char *)arr->data + i * arr->element_size,
             (char *)arr->data + j * arr->element_size, arr->element_size);
      memcpy((char *)arr->data + j * arr->element_size, temp,
             arr->element_size);
      free(temp);
    }
  }
  void *temp = malloc(arr->element_size);
  memcpy(temp, (char *)arr->data + (i + 1) * arr->element_size,
         arr->element_size);
  memcpy((char *)arr->data + (i + 1) * arr->element_size,
         (char *)arr->data + high * arr->element_size, arr->element_size);
  memcpy((char *)arr->data + high * arr->element_size, temp, arr->element_size);
  free(temp);

  return i + 1;
}

void quick_sort(Array *arr, int low, int high, bool isAscending) {
  if (low < high) {
    int pivot = partition(arr, low, high, isAscending);
    quick_sort(arr, low, pivot - 1, isAscending);
    quick_sort(arr, pivot + 1, high, isAscending);
  }
}

// Merge Sort

static void merge(Array *arr, int l, int m, int r, bool isAscending) {
  int n1 = m - l + 1;
  int n2 = r - m;

  void *L = malloc(n1 * arr->element_size);
  void *R = malloc(n2 * arr->element_size);

  memcpy(L, (char *)arr->data + l * arr->element_size, n1 * arr->element_size);
  memcpy(R, (char *)arr->data + (m + 1) * arr->element_size,
         n2 * arr->element_size);

  int i = 0, j = 0, k = l;

  while (i < n1 && j < n2) {
    int comp = memcmp((char *)L + i * arr->element_size,
                      (char *)R + j * arr->element_size, arr->element_size);

    if ((isAscending && comp <= 0) || (!isAscending && comp > 0)) {
      memcpy((char *)arr->data + k * arr->element_size,
             (char *)L + i * arr->element_size, arr->element_size);
      i++;
    } else {
      memcpy((char *)arr->data + k * arr->element_size,
             (char *)R + j * arr->element_size, arr->element_size);
      j++;
    }
    k++;
  }

  while (i < n1) {
    memcpy((char *)arr->data + k * arr->element_size,
           (char *)L + i * arr->element_size, arr->element_size);
    i++;
    k++;
  }

  while (j < n2) {
    memcpy((char *)arr->data + k * arr->element_size,
           (char *)R + j * arr->element_size, arr->element_size);
    j++;
    k++;
  }

  free(L);
  free(R);
}

void merge_sort(Array *arr, int l, int r, bool isAscending) {
  if (l < r) {
    int m = l + (r - l) / 2;
    merge_sort(arr, l, m, isAscending);
    merge_sort(arr, m + 1, r, isAscending);
    merge(arr, l, m, r, isAscending);
  }
}