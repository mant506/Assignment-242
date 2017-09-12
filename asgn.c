#include "htable.h"
#include "container.h"
#include "mylib.h"
#include <time.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_SIZE 3877


/*
int main (void) {
    container c = container_new_rbt();
    container_add(c, "Hi");
    container_free(c);
    return EXIT_SUCCESS;
}


int main (int argc, char **argv) {
    FILE *infile;
    htable t = htable_new(DEFAULT_SIZE);
    char word[256];
    if (argc > 1) {
        if (NULL == (infile = fopen(argv[1], "r"))) {
            fprintf(stderr, "%s: can't find file %s\n", argv[0], argv[1]);
            return EXIT_FAILURE;
        }
        while (getword(word, sizeof word, infile) != EOF) {
            htable_insert(t, word, 'r');
        }
        while (getword(word, sizeof word, stdin) != EOF) {
            if (htable_search(t, word) != 1) {
                printf("%s not spelt correctly\n", word);
            }
        }
    }
    htable_free(t);
    return EXIT_SUCCESS;
}
*/

int main (int argc, char **argv) {
    FILE *infile;
    char *filename = argv[1];
    htable t;
    const char *optstring = "rs:pih";
    char option;
    clock_t start, end;
    double fill_time;
    double search_time;
    int unknown_words = 0;
    char word[256];

    /*--- Command Line Flags---*/
    int robust = 0;
    int table_size = 0;
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
                    table_size = 1;
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
    
    if (help == 1) {
        fprintf(stderr, "How to use the program...\n");
        return EXIT_SUCCESS;
    }
    if (NULL == (infile = fopen(filename, "r"))) {
        fprintf(stderr, "%s: can't find file %s\n", argv[0], filename);
        return EXIT_FAILURE;
    }
    printf("Opened %s successfully\n", filename);
    if (table_size != 0) {
        t = htable_new(table_size);
        printf("Table size set to %d\n", table_size);
    } else {
        t = htable_new(DEFAULT_SIZE);
        printf("Table size set to %d\n", DEFAULT_SIZE);
    }
    if (info == 1) {
        if (robust == 1) {
            printf("Robust option selected\n");
            start = clock();
            while (getword(word, sizeof word, infile) != EOF) {
                htable_insert(t, word, 'r');
            }
            printf("Words inserted\n");
            end = clock();
            fill_time = (end-start) / (double)CLOCKS_PER_SEC;
            if (print == 1) {
                printf("Print hash table info to stdout\n");
                htable_print(t, stdout);
            }
            start = clock();
            while (getword(word, sizeof word, stdin) != EOF) {
                if (htable_search(t, word) == 0) {
                    unknown_words++;
                    printf("%s not spelt correctly\n", word);
                }
            }
            end = clock();
            search_time = (end-start) / (double)CLOCKS_PER_SEC;
        } else {
            printf("Flexarray option being used\n");
            start = clock();
            while (getword(word, sizeof word, infile) != EOF) {
                htable_insert(t, word, 'f');
            }
            printf("Words inserted\n");
            end = clock();
            fill_time = (end-start) / (double)CLOCKS_PER_SEC;
            if (print == 1) {
                printf("Print hash table info to stdout\n");
                htable_print(t, stdout);
            }
            start = clock();
            while (getword(word, sizeof word, stdin) != EOF) {
                if (htable_search(t, word) == 0) {
                    unknown_words++;
                    printf("%s not spelt correctly\n", word);
                }
            }
            end = clock();
            search_time = (end-start) / (double)CLOCKS_PER_SEC;
        }
        printf("Fill time :\t%f\nSearch time :\t%f\nUnknown words : %d\n", fill_time, search_time,unknown_words);
    } else {
        if (robust == 1) {
            printf("Robust option selected\n");
            while (getword(word, sizeof word, infile) != EOF) {
                htable_insert(t, word, 'r');
            }
            printf("Words inserted\n");
            if (print == 1) {
                printf("Print hash table info to stdout\n");
                htable_print(t, stdout);
            }
        } else {
            printf("Flexarray option being used\n");
            while (getword(word, sizeof word, infile) != EOF) {
                htable_insert(t, word, 'f');
            }
            printf("Words inserted\n");
            if (print == 1) {
                printf("Print hash table info to stdout\n");
                htable_print(t, stdout);
            }
        }
    }

    /* if search = 0 instaed != 1 */
    printf("Insert and Search Complete\n");
    fclose(infile);
    htable_free(t);
    return EXIT_SUCCESS;
}

