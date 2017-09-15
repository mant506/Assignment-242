/* Specifies the interface for hashtable.
 * 11/09/17.
 * Authors: Taylor Manning, Callan Taylor, Luke Falvey.
 */
#ifndef HTABLE_H_
#define HTABLE_H_

#include <stdio.h>

typedef struct htablerec *htable;

extern void   htable_free(htable h);
extern int    htable_insert(htable h, char *str, int container_type);
extern htable htable_new(int capacity);
extern void   htable_print(htable h, FILE *stream);
extern int    htable_search(htable h, char *str);
extern char    **get(htable h);

#endif
