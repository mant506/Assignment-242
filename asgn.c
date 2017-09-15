/*  Cosc242 assignment.
 *  Reads in a text file and stores it in a hash table.
 *  Command line options then allow the user to: print the
 *  contents of the hash table, search for words in the
 *  hash table, and print out information on how long it took
 *  to fill and search the hash table, and the number of
 *  words were in their search.
 *  11/09/17
 *  Authors: Taylor Manning, Callan Taylor, Luke Falvey.
 */
#include <string.h>
#include "htable.h"
#include "mylib.h"
#include <getopt.h>

#define DEFAULT_SIZE 3877 /*Default Hash Table Size. */

int main (int argc, char **argv) {
    FILE *infile; /* File to be read in from stdin. */
    char *filename = NULL; /* Name of the file to be read from stdin. */
    htable t; /*Hash table used to store words. */
    const char *optstring = "rs:pih"; /* Allowed command line arguements. */
    char option; /* Used to store each command line arguement. */
    int table_size = DEFAULT_SIZE; /* Used to store table size if specified. */
    int index; /* Stores index of non-option arguements - including
                  the index of the .txt file used to fill hash table. */
    
    /*--- Command Line Flags---*/
    unsigned int container_type = 0;
    unsigned int print = 0;
    unsigned int info = 0;
    unsigned int help = 0;
    /*---                   ---*/

    /* Sets flags according to option command line arguements. */
    if (argc > 1) {
        while ((option = getopt(argc, argv, optstring)) != EOF) {
            switch (option) {
                case 'h':
                    help = 1;
                    break;
                case 's':
                    table_size = atoi(optarg);
                    break;
                case 'r':
                    container_type = 1;
                    break;
                case 'p':
                    print = 1;
                    break;
                case 'i':
                    info = 1;
                    break;
                default:
                    break;
            }
        }
        /* Processes remaining non-option command line arguments
         * including .txt file used to fill the hash table.
         */
        for (index = optind; index < argc; index++) {
            /* Checks for the .txt extension in the command line. */
            if (strstr(argv[index], ".txt") != NULL) { 
                filename = argv[index];
            } else {
                /* Triggered if a command line option is unrecognised
                 * Prints error message to stderr and prints help options.
                 */
                fprintf(stderr, "Non-option argument %s\n", argv[index]);
                print_help(1);
                return EXIT_FAILURE;
            }
        }
        /* Following methods are executed based on command line flags set. 
         * Methods are defined in mylib.c and htable.c.
         */
        print_help(help);
        infile = open_file(filename);
        t = set_table_size(table_size);
        insert_words_into_htable(t, container_type, infile);
        print_hashtable(t, print);
        search_htable_for_words(t, print);
        print_info(info, print);
        fclose(infile);
        htable_free(t);
    } else {
        print_help(1);
    }
    return EXIT_SUCCESS;
}
