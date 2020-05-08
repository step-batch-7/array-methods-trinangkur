#include <stdlib.h>
#include "array.h"

Array_ptr creat_list(int length) {
  Array_ptr new_list = malloc(sizeof(Array));
  new_list->array = malloc(sizeof(int) * length);
  new_list->length = length;
  return new_list;
}


Array_ptr map(Array_ptr list, Mapper mapper_fn) {
  Array_ptr new_list = creat_list(list->length);
  for (int i = 0; i < list->length; i++)
  {
    new_list->array[i] = mapper_fn(list->array[i]);
  }
  return new_list;
}

Array_ptr filter(Array_ptr list, Predicate predicate) {
  int *temp = malloc(sizeof(int) * list->length);
  int length = 0;
  for (int i = 0; i < list->length; i++) {
    if ((*predicate)(list->array[i])) {
      temp[length] = list->array[i];
      length++;
    }
  }
  Array_ptr new_list = creat_list(length);
  new_list->array = (int *)realloc(temp, length * sizeof(int));
  return new_list;
}

int reduce(Array_ptr list, int context, Reducer reducer) {
  for (int i = 0; i < list->length; i++) {
    context = reducer(context, list->array[i]);
  }
  return context;
}