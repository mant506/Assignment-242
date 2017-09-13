/* Header file for mylib.c used in cosc242 assignment
   11/09/17
   @authors Taylor Manning, Callan Taylor, Luke Falvey
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
extern int  getword(char *s, int limit, FILE *stream);
extern void print_colour_key_count(char *key, char *colour, int count);
extern void print_help();
extern void robust_opt(htable h, FILE *infile);
extern void flex_opt(htable h, FILE *infile);
extern void print_hash(htable h);
extern void print_info();
extern htable table_size_set(int i);

#endif
