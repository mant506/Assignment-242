/* Specifies the interface for helper methods used for error checking,
 * opening files and interacting with the htable based on command line
 * arguments.
 * 11/09/17.
 * Authors: Taylor Manning, Callan Taylor, Luke Falvey.
 */
#ifndef MYLIB_H_
#define MYLIB_H_

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "htable.h"

extern void *emalloc(size_t);
extern void *erealloc(void *, size_t);
extern void print_word(char *s);
extern void print_help(int option);
extern FILE *open_file(char *filename);
extern void insert_words_into_htable(htable t,
                                       int container_type, FILE *infile);
extern void search_htable_for_words(htable t, int print_option);
extern void print_hashtable(htable h, int option);
extern void print_info(int info_option, int print_option);
extern htable set_table_size(int table_size);

#endif
