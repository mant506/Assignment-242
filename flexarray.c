/* Flexarray functions used in cosc242 assignment
11/09/17
@authors Taylor Manning, Callan Taylor, Luke Falvey
    */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "flexarray.h"

    /* Structure of a 'flexarray', holds variables
       of capacity, itemcount and the array of items.
    */
    struct flexarrayrec {
        /* capacity is the amount of items the current items array can hold */
        int capacity;
        /* itemcount is the amount of items currently in the flexarray */
        int itemcount;
        /* items is the actual array of items */
        char **items;
    };

/* Creates new flexarray, initialises all the values and
   allocates memory for the array of items.
   @return the flexarray just created
*/
flexarray flexarray_new() {
    flexarray result = emalloc(sizeof *result);
    result->capacity = 2;
    result->itemcount = 0;
    result->items = emalloc(result->capacity * sizeof result->items[0]);
    return result;
}


/* Searches through a flexarray and returns whether an item is present.
   @param f is the flexarray to search
   @param target is the item being searched for
   @return 1 if present, 0 if not
*/
int flexarray_is_present(flexarray f, char *target) {
    int i;
    for (i = 0; i < f->itemcount; i++) {
        if (strcmp(f->items[i], target) == 0) {
            return 1;
        }	
    }
    return 0;
}

/* Performs a given function on a given flexarray.
   @param f is flexarray to visit
   @param function is the function to apply to each item
*/
void flexarray_visit(flexarray f, void func(char *str)) {
    int i;
    for (i = 0; i < f->itemcount; i++) {
        func(f->items[i]);
    }
}

/* Adds an item to array, if the array is full,
   then a new array of same size is appended to
   the end to allow room.
   @param f is the flexarray bein added to
   @param item is the string being added
*/
void flexarray_append(flexarray f, char *item) {
    if (f->itemcount == f->capacity) {
        /* doubles capacity if the array is full */
        f->capacity += f->capacity;
        f->items = erealloc(f->items, f->capacity * sizeof f->items[0]);
    }
    /* insert the item in the last free space */
    f->items[f->itemcount] = emalloc((strlen(item)+1) * sizeof f->items[0][0]);
    strcpy(f->items[f->itemcount], item);
    f->itemcount++;
}

/* Frees all the memory the flex array is using.
   @param f is the flexarray using the memory
*/
void flexarray_free(flexarray f) {
    int i;
    for (i = 0; i < f->itemcount; i++) {
    	free(f->items[i]);
    }
    free(f);
}
