#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../array.h"

int sum (int num1, int num2) {
  return num1 + num2;
}

int increment (int a) {
  return a + 1;
}

Bool is_less_than_3 (int a) {
  return a < 3;
}

Array_ptr copy_in_list(int * set, int length) {
  Array_ptr list = creat_list(length);
  list->array = malloc(sizeof(int) * length);
  for (int i = 0; i < length; i++) {
    list->array[i] = set[i];
  }
  return list;
}

void test_reduce (void) {
  printf("testing reduce\n");
  int a[] = {1,2,3,4};
  assert(reduce(copy_in_list(a, 4), 0, &sum) == 10);
  printf("\tpassed...\n");
}

void test_map (void) {
  printf("\ntesting map\n");
  int a[] = {1,2,3,4};
  Array_ptr list = map(copy_in_list(a, 4), &increment);
  for (int i = 0; i < list->length; i++) {
    assert(list->array[i] == a[i] +1);
  }
  assert(list->length == 4);
  printf("\tpassed...\n");
}

void test_filter (void) {
  printf("\ntesting filter\n");
  int a[] = {1,2,3,4};
  Array_ptr list = filter(copy_in_list(a, 4), &is_less_than_3);
  for (int i = 0; i < list->length; i++) {
    assert(list->array[i] < 3);
  }
  printf("\tpassed...\n");
  assert(list->length == 2);
}

int main (void) {
  test_reduce();
  test_map();
  test_filter();
  return 0;
}