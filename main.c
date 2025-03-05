#include "core.h"
#include "list.h"

int main(void) {

  int x = 3;
  int y = 4;

  List *mylist;
  list_create(mylist, data_destroy);
  list_ins_next(mylist, NULL, &x);
  list_ins_next(mylist, NULL, &y);

  printf("value of list at 0 and 1 are [%d %d]", *(int *)mylist->head->data,
         *(int *)mylist->head->next->data);

  printf("hello world\n");

  list_destroy(mylist);
  return 0;
}