#include <stdlib.h>
#include "array.h"
#include "array_void.h"

Array_ptr creat_list(int length) {
  Array_ptr new_list = malloc(sizeof(Array));
  new_list->length = length;
  return new_list;
}

ArrayVoid_ptr creat_void_list(int length) {
  ArrayVoid_ptr new_list = malloc(sizeof(ArrayVoid));
  new_list->length = length;
  return new_list;
}

Array_ptr map(Array_ptr list, Mapper mapper_fn) {
  Array_ptr new_list = creat_list(list->length);
  new_list->array = malloc(sizeof(int) * list->length);
  for (int i = 0; i < list->length; i++)
  {
    new_list->array[i] = mapper_fn(list->array[i]);
  }
  return new_list;
}

ArrayVoid_ptr map_void(ArrayVoid_ptr src, MapperVoid mapper) {
  ArrayVoid_ptr new_list = creat_void_list(src->length);
  new_list->array = malloc(sizeof(src->array[0]) * src->length);
  for (int i = 0; i < src->length; i++) {
    new_list->array[i] = mapper(src->array[i]);
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
  new_list->array = realloc(temp, length * sizeof(int));
  return new_list;
}

ArrayVoid_ptr filter_void(ArrayVoid_ptr src, PredicateVoid predicate) {
  Object *temp = malloc(sizeof(src->array[0]) * src->length);
  int length = 0;
  for (int i = 0; i < src->length; i++) {
    if ((*predicate)(src->array[i])) {
      temp[length] = src->array[i];
      length++;
    }
  }
  ArrayVoid_ptr new_list = creat_void_list(length);
  new_list->array = realloc(temp, length * sizeof(src->array[0]));
  return new_list;
}

int reduce(Array_ptr list, int context, Reducer reducer) {
  for (int i = 0; i < list->length; i++) {
    context = reducer(context, list->array[i]);
  }
  return context;
}

Object reduce_void(ArrayVoid_ptr src, Object init, ReducerVoid reducer) {
  for (int i = 0; i < src->length; i++) {
    init = reducer(init, src->array[i]);
  }
  return init;
}