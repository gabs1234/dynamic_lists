#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//TODO:Fix sizeof array (dynamically found) -> no solution I think
#define MAX_LIST 2^10

typedef struct struct_list {
  int* array;
  unsigned int len;
  //index position in list_to_free
  unsigned int creation_index;
} list;

void init(list* my_list, int init_array[], int size);
void append(list* my_list, int value[], int size);
void pop(list* my_list, int num);
void extract(list* extracted, list* to_extract, int i, int j);
void free_lists();
void print_array(list my_list);

void example();

struct to_free{
  int* array[MAX_LIST];
  int len;
};

struct to_free list_to_free;

int main(int argc, char const *argv[]) {
  example();

  free_lists();
  return 0;
}

void example () {
  list my_list;
  list extracted;
  list singleton;
  //list, initial value

  printf("init:\n");
  init(&my_list, (int[]){1, 2, 3}, 3);
  print_array(my_list);

  printf("append: 1, 2, 3\n");
  append(&my_list, (int[]){1, 2, 3}, 3);
  print_array(my_list);

  printf("pop: 4 last\n");
  pop(&my_list, 4);
  print_array(my_list);

  printf("append: 4, 5, 6, 7, 8, 9\n");
  append(&my_list, (int[]){4, 5, 6, 7, 8, 9}, 6);
  print_array(my_list);

  printf("extract: from 2 to 4\n");
  extract(&extracted, &my_list, 2, 4);
  print_array(extracted);

  printf("extract: 1\n");
  extract(&singleton, &my_list, 0, 0);
  print_array(singleton);
}

void init(list* my_list, int init_array[], int size) {
  my_list->len = size;
  my_list->array = (int*)(calloc(my_list->len, sizeof(int)));

  //make sure we can free the list later on easily
  list_to_free.array[list_to_free.len] = my_list->array;
  my_list->creation_index = list_to_free.len;
  (list_to_free.len)++;

  if (my_list->array == NULL || my_list->len == 0) {
    //calloc should return NULL if size 0 asked
    printf("array of size 0 not created\n");
    //TODO: error handling
  }

  for (int i=0; i<size; i++) {
    my_list->array[i] = *(init_array+i);
  }
}

void append(list* my_list, int value[], int size) {
  int length = size;
  int old_len = my_list->len;

  my_list->len += length;
  my_list->array = (int*)(reallocarray(my_list->array, my_list->len, sizeof(int)));

  //update new pointer in list_to_frees
  list_to_free.array[my_list->creation_index] = my_list->array;

  if (my_list->array == NULL || length == 0) {
    //calloc should return NULL if size 0 asked
    printf("array of size 0 not created\n");
    //TODO: error handling
  }

  for (int i=0; i<length; i++) {
    my_list->array[i+old_len] = *(value+i);
  }
}

void pop(list* my_list, int num) {
  my_list->len -= num;
  my_list->array = (int*)(reallocarray(my_list->array, my_list->len, sizeof(int)));

  //update new pointer in list_to_free
  list_to_free.array[my_list->creation_index] = my_list->array;
}

void extract(list* extracted, list* to_extract, int i, int j) {
  int* extracted_array = (int*)(calloc((abs(j-i)+1), sizeof(int)));

  if (extracted_array == NULL) {
    //calloc should return NULL if size 0 asked or no more space
    printf("Theres a pb\n");
    //TODO: error handling
  }

  memcpy(extracted_array, to_extract->array+i, (abs(j-i)+1)*sizeof(int));
  init(extracted, extracted_array, abs(j-i)+1);
}

void free_lists() {
  //TODO: probably should do some error checking here
  for (int i=0; i<list_to_free.len; i++) {
    free(list_to_free.array[i]);
  }
}

void print_array(list my_list) {
  int i;
  printf("[");
  for (i=0;i<my_list.len-1; i++) {
    printf("%d, ", my_list.array[i]);
  }
  printf("%d]\n", my_list.array[i]);
}
