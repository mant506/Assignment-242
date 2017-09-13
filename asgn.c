#include "htable.h"
#include "container.h"
#include "mylib.h"
#include <time.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_SIZE 3877


int main (int argc, char **argv) {
    /* Input file */
    FILE *infile;
    /* First command line argument */
    char *filename = argv[1];
    /* Htable being used */
    htable t;
    /* Option string */
    const char *optstring = "rs:pih";
    /* Option used for switch cases */
    char option;
    /* Table size */
    int size = 0;

    /*--- Command Line Flags---*/
    int robust = 0;
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
                    size = atoi(optarg);
                    break;
                case 'r':
                    robust = 1;
                    break;
                case 'p':
                    print = 1;
                    break;
                case 'i':
                    info = 1;
                    break;
                default:
                    printf("Invalid command line argument\n");
            }
        }
    }
    
    /* Error fiding file, return filename so user can check*/
    if (NULL == (infile = fopen(filename, "r"))) {
        fprintf(stderr, "%s: can't find file %s\n", argv[0], filename);
        return EXIT_FAILURE;
    }
    /*File open success*/
    printf("Opened %s successfully\n", filename);


    
    /* ------- Command Line Options ------- */    

    /* Prints help message */
    if (help == 1) {
        print_help();
        return EXIT_SUCCESS;
    }

    /*Calls table_size_set to set the size of the table.*/
    t = table_size_set(size);

    /* Calls robust_opt to set the container type to a Red Black Tree,
       and prints any misspelt words. */
    if (robust == 1) {
        robust_opt(t, infile);
    }
    
    /* Calls flex_opt to set the container type to Flexarray,
     and prints any misspelt words.*/
    else {
        flex_opt(t, infile);
    }
       
    /* Print htable to stdout one line per non-empty container.
       Does not read anything from stdin or ptint anything else. */
    if (print == 1) {
        print_hash(t);
    }

    /*Calls print_info to print info on search and fill times
      and unknown words.*/
    else if (info == 1) {
        print_info();
    }

    printf("Insert and Search Complete\n");
    
    fclose(infile);
    htable_free(t);
    return EXIT_SUCCESS;
}
