#include <stdio.h> /* for fprintf */
#include <stdlib.h> /* for size_t, malloc, realloc, exit */
#include "mylib.h"
#include <assert.h>
#include <ctype.h>

/*Error checking method for allocating memory.
  Prints error message to stderr if failed and
  exits the program.
  @param s is the size of memory to allocate
  @return the memory space
 */
void *emalloc(size_t s) {
    void *result = malloc(s);
    if (NULL == result) {
        fprintf(stderr, "Memory Allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

/*Error checking method for re-allocating memory.
  Prints error message to stderr if failed
  @param s is the size of memory to allocate
  @return the memory space
*/
void *erealloc(void *p, size_t s) {
    void *result = realloc(p,s);
    if (NULL == result) {
        fprintf(stderr, "Memory Allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

/*Prints a given word using printf.
  @param s is the word to print
 */
void print_word(char *s) {
    printf("%s ", s);
}

/*
  @param
  @param
  @param
  @return
 */
int getword(char *s, int limit, FILE *stream) {
    int c;
    char *w = s;
    assert(limit > 0 && s != NULL && stream != NULL);
    /* skip to the start of the word */
    while (!isalnum(c = getc(stream)) && EOF != c)
        ;
    if (EOF == c) {
        return EOF;
    } else if (--limit > 0) { /* reduce limit by 1 to allow for the \0 */
        *w++ = tolower(c);
    }
    while (--limit > 0) {
        if (isalnum(c = getc(stream))) {
            *w++ = tolower(c);
        } else if ('\'' == c) {
            limit++;
        } else {
            break;
        }
    }
    *w = '\0';
    return w - s;
}

/*Prints three variables with headers for each.
  @param key is a string that represents a key for a hashtable
  @param colour is a string representing the colour of a node
  @param count is the count associated with the key
 */
void print_colour_key_count(char *key, char *colour, int count) {
    printf("Colour: %s, Key: %s, Count: %d\n", colour, key, count);
}
