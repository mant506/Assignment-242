/* Cosc242 assignment.
   Reads in a text file and stores it in a hash table.
   Command line options then allow the user to: print the
   contents of the hash table, search for words in the
   hash table, and print out information on how long it took
   to fill and search the hash table, and the number of
   words were in their search.
   11/09/17
   Authors: Taylor Manning, Callan Taylor, Luke Falvey
*/
#include "htable.h"
#include "mylib.h"
#include <getopt.h>

int main (int argc, char **argv) {
    FILE *infile;
    char *filename = argv[1];
    htable t;
    
    const char *optstring = "rs:pih";
    char option;
    int table_size = 0;
    /*--- Command Line Flags---*/
    int container_type = 0;
    int print = 0;
    int info = 0;
    int help = 0;
    /*---                   ---*/ 
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
        print_help(help);
        infile = open_file(filename);
        t = set_table_size(table_size);
        insert_words_into_htable(t, container_type, infile);
        print_hashtable(t, print);
        search_htable_for_words(t, print);
        print_info(info, print);
        fclose(infile);
        htable_free(t);
    }
    return EXIT_SUCCESS;
}
