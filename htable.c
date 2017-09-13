/* Hashtable functions used in cosc242 assignment
   11/09/17
   @authors Taylor Manning, Callan Taylor, Luke Falvey
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mylib.h"
#include "htable.h"
#include "container.h"

/* Structure of a 'htable' to hold
   variables of capacity, number of keys,
   array of frequencies and array of containers.
 */
struct htablerec {
    /* array of containers is the basis of the htable*/
    container *containers;
    /* Array of frequencies */
    int *frequencies;
    /* Amount of keys associated with containers */
    int num_keys;
    /* Max capacity of htable */
    unsigned int capacity;
};


/*Converts the key to appropriate index position.
  @param word is the string to convert to index
  @return is the index
 */
static unsigned int htable_word_to_int(char *word) {
    unsigned int result = 0;
    while (*word != '\0') {
        result = (*word++ + 31 * result);
    }
    return result;
}

/* Creates new hashtable, initialises all the values and
   allocates memory for the arrays
   Returns the hashtable just created
*/
htable htable_new(int capacity) {
    int i;
    htable result = emalloc(sizeof *(result));
    result->capacity = capacity;
    result->num_keys = 0;
    result->frequencies = emalloc(capacity * sizeof result->frequencies[0]);
    result->containers = emalloc(capacity * sizeof(*(result->containers)));
    for (i = 0; i < capacity; i++) {
        result->frequencies[i] = 0;
        result->containers[i] = NULL;
    }
    return result;                       
}

/*Frees all memory that the htable is using
  through the container_free function
  @param h is the htable to free
 */
void htable_free(htable h) {
    unsigned int i;
    free(h->frequencies);
    for (i = 0; i < h->capacity; i++) {
        if (NULL != h->containers[i]) {
            container_free(h->containers[i]);
        }
    }
    free(h->containers);
    free(h);
}

/*Inserts an item into htable container at the index
  returned by htable_word_to_int, unless full. If
  full, searches through htable by htable_step until
  an empty or matching point is found.
  
  @param h is the htable being inserted into
  @param str is the string to insert
  @param container_type is the type of container to use
  @return 1 if insertion was effective, 0 if not
 */
int htable_insert(htable h, char *str, char container_type) {
    
    unsigned int index = htable_word_to_int(str) % h->capacity;
    /* container is empty */
    if (h->containers[index] == NULL) { 
        if (container_type == 'r') {    /* rbt */
            h->containers[index] = container_new_rbt();
        } else {                        /* flexarray */
            h->containers[index] = container_new_flexarray();
        }
        container_add(h->containers[index], str); 
        h->frequencies[index] = 1;
        h->num_keys++;
        return 1;
    /* if input is already in container */
    } else {
        container_add(h->containers[index], str);
        h->frequencies[index]++;
        return h->frequencies[index];
    }
    return 1;
}

/* Calls container print on containers in the htable with
   correspondiing frequencies beforehand. Container print will
   print all items in container.
   @param h is htable to be printed
   @param stream is where to print to
 */
void htable_print(htable h, FILE *stream) {
    unsigned int i;
    for (i = 0; i < h->capacity; i++) {
        if (h->frequencies[i] != 0) {
            fprintf(stream, "%d ", i);
            container_print(h->containers[i], print_word);
            printf("\n");
        }
    }
}

/*Searches the given htbale for a string and
  returns 0 if not found in any containers
  and if found, frequency is returned
  @param h is htable to be searched
  @param str is string to search for
  @return 0 if not found, otherwise frequency of the string
 */
int htable_search(htable h, char *str) {
    unsigned int index = htable_word_to_int(str) % h->capacity;
    if (h->containers[index] != NULL) {
        return container_search(h->containers[index], str);
    }
    return 0;
}

