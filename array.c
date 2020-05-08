#include <stdlib.h>
#include "array.h"

Array_ptr creat_list(int count) {
  Array_ptr new_list;
  new_list->array = malloc(sizeof(int) * count);
  new_list->length = count;
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
  int temp[list->length], length = 0;
  for (int i = 0; i < list->length; i++) {
    if (predicate(list->array[i])) {
      temp[length] = list->array[i];
      length++;
    }
  }
  Array_ptr new_list = creat_list(length);
  for (int i = 0; i < length; i++) {
    new_list->array[i] = temp[i];
  }
  return new_list;
}

int reduce(Array_ptr list, int context, Reducer reducer) {
  for (int i = 0; i < list->length; i++) {
    context = reducer(context, list->array[i]);
  }
  return context;
}