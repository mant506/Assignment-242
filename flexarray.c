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
   of capacity, itemcount and array of items.
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
   allocates memory for the array of items
   Returns the flexarray just created
*/
flexarray flexarray_new() {
    flexarray result = emalloc(sizeof *result);
    result->capacity = 2;
    result->itemcount = 0;
    result->items = emalloc(result->capacity * sizeof result->items[0]);
    return result;
}

/* Insertion sort algorith to sort items in array
   Input - words is array to be sorted
   - n is the amount of items in array
*/
static void insertion_sort(char **words, int n) {
    int i;
    for (i = 1; i < n; i++) {   
        char *key = words[i];
        int index = i;
        while (index > 0 && strcmp(words[index-1],key) > 0) {
            index--;
            words[index+1] = words[index];
        }
        words[index] = key;        
    }
}

/* Searches through a flexarray and returns whether an item is present
   Input - f is the flexarray to search
         - target is the item being searched for
   Output- 1 if present, 0 if not
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

/* Performs a given function on a given flexarray
   Inputs - f is flexarray to visit
   - function is the function to apply to each item
*/
void flexarray_visit(flexarray f, void func(char *str), FILE *stream) {
    int i;
    for (i = 0; i < f->itemcount; i++) {
        func(stream, f->items[i]);
    }
}

/* Adds an item to array, if the array is full,
   then a new array of same size is appended to
   the end to allow room.
   Input - f is the flexarray bein added to
         - item is the string being added
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

/* Prints items in array on new lines
   Input - f is the flexarray to be printed
*/
void flexarray_print(flexarray f) {
    /* a "for" loop to print out each cell of f->items */
    int i;
    for (i = 0; i < f->itemcount; i++) {
        printf("%s ", f->items[i]); 
    }
    printf("\n");
}

/* Calls insertion sort passing it the array of items and item count
   Input - f is the flex array that contains array to be printed
*/
void flexarray_sort(flexarray f) {
    insertion_sort(f->items, f->itemcount);
}

/* Frees all the memory the flex array is using
   Input - f is the flexarray using the memory
*/
void flexarray_free(flexarray f) {
    /* free the memory associated with the flexarray */
    int i;
    for (i = 0; i < f->itemcount; i++) {
    	free(f->items[i]);
    }
    free(f);
}
