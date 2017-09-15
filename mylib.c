/* Implementation for the mylib interface
 * 11/09/17.
 * Authors: Taylor Manning, Callan Taylor, Luke Falvey.
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <assert.h>
#include <ctype.h>
#include "mylib.h"
#include "htable.h"
#include "container.h"

double fill_time; /*Time taken to fill the hash table. */
double search_time; /*Time taken to seaxrch htable. */
int unknown_words; /*Number of words searched for but not found in the htable.*/


/* Error checking method for allocating memory.
 * Prints error message to stderr if failed and
 * exits the program.
 * Parameter: s the size of memory to be allocated in bytes.
 * Returns: A pointer to the memory allocated by call to malloc.
 */
void *emalloc(size_t s) {
    void *result = malloc(s);
    if (NULL == result) {
        fprintf(stderr, "Memory Allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

/* Error checking method for re-allocating memory.
 * Prints error message to stderr if failed and exits program.
 * Parameters: *p a pointer to an existing memory block.
 * Parameters: s the size of memory to be allocated in bytes.
 * Returns: A pointer to the memory allocated by call to malloc.
 */
void *erealloc(void *p, size_t s) {
    void *result = realloc(p,s);
    if (NULL == result) {
        fprintf(stderr, "Memory Allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

/* Prints a given word using printf.
 * Parameters: s the word to print
 */
void print_word(char *s) {
    printf("%s ", s);
}

/* Gets a word from an input stream.
 * Parameters: s is the word.
 * Parameters: limit is amount of letters.
 * Parameters: stream is the input file.
 * Returns: the number of characters left in the file or an EOF.
 */
static int getword(char *s, int limit, FILE *stream) {
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

/* Prints a help message to show  command line arguments if passed value 1.
 * Parameters: option represents whether user as selected the help option.
 *             1 means the user has selected this option. 0 means the user
 *             hasn't.
 */
void print_help(int option) {
    if (option == 1) {
        fprintf(stderr, "Command Line Arguments: \n\
-r: \t Initialises hashtable with a red black tree container type. \n\
-s: \t Sets the size of hashtable to the following arguement. \n\
-i: \t Prints the search, fill time and the number of  unknown words. \n\
-p: \t Prints the index of each container and it's contents.\n\
-h: \t Prints this help message.\n");
        exit(EXIT_SUCCESS);
    }
    
}

/* Opens a given file with the passed filename.
 * Parameters: filename the name of the file to be opened.
 * Returns: the opened file.
 * Exits the program if a file with the filename doesn't exist.
 */
FILE *open_file(char *filename) {
    FILE *infile = NULL;
    if (NULL == (infile = fopen(filename, "r"))) {
        fprintf(stderr, "./asgn: can't find file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    return infile;
}

/* Reads words from a passed file and inserts them into the passed Hash Table.
 * Parameters: t the table which words are to be inserted into.
 * Parameters: container_type the type of container which the htable will
 *             insert words into 1 indicates the container_type to be a red
 *             black tree, 0 indicates a flexarray.
 */
void insert_words_into_htable(htable t, int container_type, FILE *infile) {
    clock_t start, end;
    char word[256];
    start = clock();
    while (getword(word, sizeof word, infile) != EOF) {
        htable_insert(t, word, container_type);
    }
    end = clock();
    fill_time = (end-start) / (double)CLOCKS_PER_SEC;
    
}

/* Prints out the htable using htable_print method.
 * Parameters: h is the htable being printed.
 * Parameters: option is 1 if user wants to print htable
 *             or 0 if user doesn't.
 */
void print_hashtable(htable t, int option ) {
    if (option == 1) {
        htable_print(t, stdout);
    }
}

/* Searches the passed htable if the user doesn't want to print
 * the contents of the htable.
 * Parameters: t the htable to search.
 * Parameters: print_option set to 1 if user wants to print contents
 *             of htable or 0 if user doesn't.
 */
void search_htable_for_words(htable t, int print_option) {
    clock_t start, end;
    char word[256];
    unknown_words = 0;
    if (print_option != 1) {
        start = clock();
        while (getword(word, sizeof word, stdin) != EOF) {  
            if (htable_search(t, word) == 0) {
                fprintf(stdout, "%s\n", word);
                unknown_words++;
            }
        }
        end = clock();
        search_time = (end-start) / (double)CLOCKS_PER_SEC;
    }
}

/* Prints the time taken to fill and search the htable and the number
 * of entered words that were not found in the htable.
 * Parameters: info_option set to 1 if user wants to print hash table stats
 *             or 0 if user doesn't.
 * Parameters: print_option if set to 1 if user can't print hash
 *             table stats.
 */
void print_info(int info_option, int print_option) {
    if (print_option == 0 && info_option == 1) { 
        fprintf(stderr,
                "Fill time :\t%f\nSearch time :\t%f\nUnknown words : %d\n",
                fill_time, search_time,unknown_words);
    }
}

/* Creates and returns an htable of either default
 * size or input size.
 * Parameters: table_size the number of containers to be in the htable.
 * Returns: t with table_size containers.
 */
htable set_table_size(int table_size) {
    htable t;
    if (table_size > 0) {
        t = htable_new(table_size);
    } else {
        fprintf(stderr, "Table Size must be an int greater than 0\n");
        print_help(1);
    }
    return t;
}
