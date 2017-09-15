/* Implementation of the header file for hashtable.
 * 11/09/17
 * Authors Taylor Manning, Callan Taylor, Luke Falvey
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mylib.h"
#include "htable.h"
#include "container.h"

/* Structure of a 'htable' to hold
 * variables of capacity, number of keys,
 * array of frequencies and array of containers.
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

/* Hashing function: Returns an index in the htable for a given word.
 * Parameters: word string used to generate an index.
 * Returns: result generated index.
 */
static unsigned int htable_word_to_int(char *word) {
    unsigned int result = 0;
    while (*word != '\0') {
        result = (*word++ + 31 * result);
    }
    return result;
}

/* Creates new hashtable, initialises all the values and
 * allocates memory for the arrays.
 * Parameters: capacity the capacity of the new htable.
 * Returns the hashtable just created.
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

/* Frees all memory that the htable is using
 * through the container_free function.
 * Parameters: h is the htable to free.
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

/* Inserts an item into htable container at the index
 * returned by htable_word_to_int, unless full.
 * Parameters: h is the htable being inserted into.
 * Parameters: str is the string to insert.
 * Parameters: container_type is the type of container to use
 *             1 uses an rbt. 0  uses a flexarray.
 * Returns: 1 if str was inserted, 0 if not
 */
int htable_insert(htable h, char *str, int container_type) {
    
    unsigned int index = htable_word_to_int(str) % h->capacity;
    if (h->containers[index] == NULL) {
        h->containers[index] = container_new(container_type);
        container_add(h->containers[index], str); 
        h->frequencies[index] = 1;
        h->num_keys++;
        return 1;
    } else {
        container_add(h->containers[index], str);
        h->frequencies[index]++;
        return h->frequencies[index];
    }
    return 1;
}

/* Calls container print on containers in the htable with
 * correspondiing frequencies beforehand. Container print will
 * print all items in container.
 * Parameters: h is htable to be printed
 * Parameters: stream is where to print to
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

/* Searches the given htbale for a string and
 * returns 0 if not found in any containers
 * and if found, frequency is returned
 * Parameters: h is htable to be searched
 * Parameters: str is string to search for
 * Returns: 0 if not found, otherwise frequency of the string
 */
int htable_search(htable h, char *str) {
    unsigned int index = htable_word_to_int(str) % h->capacity;
    if (h->containers[index] != NULL) {
        return container_search(h->containers[index], str);
    }
    return 0;
}

