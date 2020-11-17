# Dynamic lists
in this implementation, the dynamic lists are initialized by a `struct` called list.

### functions
```
void init(list* my_list, int init_array[], int size);
void append(list* my_list, int value[], int size);
void pop(list* my_list, int num);
void extract(list* extracted, list* to_extract, int i, int j);
void free_lists();
void print_array(list my_list);
```

### Usage
Go check the example function in the main file.
let's define a `list` called `my_list` and initialize it with the function `init()`:

```
list my_list;
init(&my_list, (int*)({1, 2, 3}), 3);
```

We now have a list that can grow dynamically. (see append, pop, extract functions)

**In order to free the memory, call `free_lists()` at the end of your program or manually free list by using the `free` function. (i.e: `free(my_list.array)`).
