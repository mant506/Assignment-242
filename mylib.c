#include <stdio.h> /* for fprintf */
#include <stdlib.h> /* for size_t, malloc, realloc, exit */
#include <time.h>
#include <assert.h>
#include <ctype.h>
#include "mylib.h"
#include "htable.h"
#include "container.h"

#define DEFAULT_SIZE 3877

clock_t start, end;
double fill_time;
double search_time;
int unknown_words = 0;
char word[256];


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

/*Takes a word, its size and an input stream
  @param s is the word
  @param limit is amount of letters
  @param stream is the input file
  @return the word returned
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

/*Prints help message to show the command line options.
 */
void print_help() {
    printf("Command Line Arguments: \n\
-r: \t Initialises hashtabe with Red-Black-Tree container type. \n\
-s: \t Sets the size of hashtable to int argument 'table size'. \n\
-i: \t Prints search and fill time info with a list of unknown words. \n\
-p: \t Prints the contents of hashtable with the index of each container.\n\
-h: \t Prints this help message.\n");
}

/*Sets the container type to a RBT and prints
  any misspelt words.
  @param t is the htable being used
  @param infile is input file
 */
void robust_opt(htable t, FILE *infile) {
    printf("Robust option selected\n");
    start = clock();
    while (getword(word, sizeof word, infile) != EOF) {
        htable_insert(t, word, 'r');
    }
    printf("Words inserted\n");
    end = clock();
    fill_time = (end-start) / (double)CLOCKS_PER_SEC;
    start = clock();
    while (getword(word, sizeof word, stdin) != EOF) {  
        if (htable_search(t, word) == 0) {
            if (unknown_words == 0) {
                printf("Unknown words:\n");
            }
            unknown_words++;
            printf(word);
            printf("\n");
        }
    }
    if (unknown_words > 0) {
        printf("\n");
    }
    
    end = clock();
    search_time = (end-start) / (double)CLOCKS_PER_SEC;
}

/*Sets the container type to a flexarray and prints
  any misspelt words.
  @param t is the htable being used
  @param infile is input file
*/
void flex_opt(htable h, FILE *infile) {
    printf("flexarry option selected\n");
    start = clock();
    while (getword(word, sizeof word, infile) != EOF) {
        htable_insert(h, word, 'f');
    }
    printf("Words inserted\n");
    end = clock();
    fill_time = (end-start) / (double)CLOCKS_PER_SEC;
    start = clock();
    while (getword(word, sizeof word, stdin) != EOF) {  
        if (htable_search(h, word) == 0) {
            if (unknown_words == 0) {
                printf("Unknown words:\n");
            }
            unknown_words++;
            printf(word);
            printf("\n");
        }
    }
    if (unknown_words > 0) {
        printf("\n");
    }
    end = clock();
    search_time = (end-start) / (double)CLOCKS_PER_SEC;
}

/*Prints out the htable using htable_print method.
  @param h is the htable being printed
 */
void print_hash(htable h) {
    printf("Hashtable contents: \n");
    htable_print(h, stdout);
    printf("\n");
}

/*Prints info about search and fill times and unknown words.
 */
void print_info() {
    printf("Fill time :\t%f\nSearch time :\t%f\nUnknown words : %d\n",
           fill_time, search_time,unknown_words);
}

/*Creates and returns an htable of either default
  size or input size.
  @param i is input size
  @return t is the htable
 */
htable table_size_set(int i) {
    htable t;
    if (i != 0) {
        t = htable_new(i);
        printf("Table size set to %d\n", i);
    } else {
        t = htable_new(DEFAULT_SIZE);
        printf("Table size set to %d\n", DEFAULT_SIZE);
    }

    return t;
    
}
