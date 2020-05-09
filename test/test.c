#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../array.h"
#include "../array_void.h"

int sum (int num1, int num2) {
  return num1 + num2;
}

int increment (int a) {
  return a + 1;
}

Bool is_less_than_3 (int a) {
  return a < 3;
}

void *increment_addr (void *a) {
  int *b = malloc(sizeof(int));
  *b = *((int *)a) + 1;
  return b;
}

Bool is_less_than_5 (void *a) {
  return *(int *)a < 5;
}

void * sum_using_ref(void *a, void *b) {
  int *c = malloc(sizeof(int));
  *c = *(int *) a + *(int *)b;
  return c;
}

Array_ptr copy_in_list(int * set, int length) {
  Array_ptr list = creat_list(length);
  list->array = malloc(sizeof(int) * length);
  for (int i = 0; i < length; i++) {
    list->array[i] = set[i];
  }
  return list;
}

ArrayVoid_ptr create_int_object_array(int *src, unsigned length) {
  ArrayVoid_ptr list = creat_void_list(length);
  list->array = malloc(sizeof(Object) * length);
  for (int i = 0; i < length; i++) {
    int *temp = malloc(sizeof(int));
    *temp = src[i];
    list->array[i] = temp;
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

void test_void_map(void) {
  printf("\ntesting map_void\n");
  int a[] = {1,2,3,4};
  ArrayVoid_ptr list = create_int_object_array(a,4);
  list = map_void(list, &increment_addr);
  for (int i = 0; i < list->length; i++)
  {
    int *temp = list->array[i];
    assert(*temp == a[i] +1);
  }
  assert(list->length == 4);
  printf("\tpassed...\n");
}

void test_void_filter(void) {
  printf("\ntesting filter_void\n");
  int a[] = {3,4,5,6};
  ArrayVoid_ptr list = create_int_object_array(a,4);
  list = filter_void(list, &is_less_than_5);
  for (int i = 0; i < list->length; i++) {
    assert(*(int *)list->array[i] < 5);
  }
  assert(list->length == 2);
  printf("\tpassed...\n");
}

void test_void_reduce(void) {
  printf("\ntesting reduce_void\n");
  int a[] = {1,2,3,4};
  ArrayVoid_ptr list = create_int_object_array(a,4);
  int b = 0;
  assert(*(int *)reduce_void(list, &b, &sum_using_ref) == 10);
  printf("\tpassed...\n");
}

int main (void) {
  test_reduce();
  test_map();
  test_filter();
  test_void_map();
  test_void_filter();
  test_void_reduce();
  return 0;
}