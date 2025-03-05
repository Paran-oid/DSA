#include "dlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_int(void *data) { printf("%d ", *(int *)data); }

void test_dlist() {
  DList dlist;
  dlist_create(&dlist, NULL, free);

  printf("Test 1: List should be empty initially.\n");
  printf("List size: %zu\n", dlist_size(&dlist));

  // Insert at the beginning
  int *value1 = malloc(sizeof(int));
  *value1 = 10;
  dlist_ins_next(&dlist, NULL, value1); // Inserting at the head of the list

  printf("Test 2: List after one insertion.\n");
  printf("List size: %zu\n", dlist_size(&dlist));
  printf("Head value: ");
  print_int(dlist_head(&dlist)->data);
  printf("\n");

  // Insert in the middle
  int *value2 = malloc(sizeof(int));
  *value2 = 20;
  dlist_ins_next(&dlist, dlist_head(&dlist),
                 value2); // Inserting after the head

  printf("Test 3: List after second insertion.\n");
  printf("List size: %zu\n", dlist_size(&dlist));
  printf("Head value: ");
  print_int(dlist_head(&dlist)->data);
  printf("\n");
  printf("Next value: ");
  print_int(dlist_next(dlist_head(&dlist))->data);
  printf("\n");

  // Insert at the end
  int *value3 = malloc(sizeof(int));
  *value3 = 30;
  dlist_ins_next(&dlist, dlist_tail(&dlist),
                 value3); // Inserting after the tail

  printf("Test 4: List after third insertion.\n");
  printf("List size: %zu\n", dlist_size(&dlist));
  printf("Tail value: ");
  print_int(dlist_tail(&dlist)->data);
  printf("\n");

  // Remove from the head
  void *removed_data;
  dlist_rem(&dlist, dlist_head(&dlist), &removed_data);
  printf("Test 5: After removal from the head.\n");
  printf("List size: %zu\n", dlist_size(&dlist));
  printf("Removed data: ");
  print_int(removed_data);
  printf("\n");
  free(removed_data);

  // Remove from the middle
  dlist_rem(&dlist, dlist_head(&dlist), &removed_data);
  printf("Test 6: After removal from the middle.\n");
  printf("List size: %zu\n", dlist_size(&dlist));
  printf("Removed data: ");
  print_int(removed_data);
  printf("\n");
  free(removed_data);

  // Remove from the tail
  dlist_rem(&dlist, dlist_head(&dlist), &removed_data);
  printf("Test 7: After removal from the tail.\n");
  printf("List size: %zu\n", dlist_size(&dlist));
  printf("Removed data: ");
  print_int(removed_data);
  printf("\n");
  free(removed_data);

  // Destroy the list
  dlist_destroy(&dlist);
  printf("Test 8: After destroying the list.\n");
  printf("List size: %zu\n", dlist_size(&dlist));
}

int main() {
  test_dlist();
  return 0;
}
