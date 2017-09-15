/* Header file for container.c
 * 11/09/17
 * Authors: Taylor Manning, Callan Taylor, Luke Falvey
 */
#ifndef CONTAINER_H_
#define CONTAINER_H_

typedef enum container_e {FLEX_ARRAY, RED_BLACK_TREE} container_t;
typedef struct containerrec* container;

extern void      container_add(container c, char *word);
extern container container_new(int container_type);
extern void      container_free(container c);
extern void      container_print(container c, void f(char *word));
extern int       container_search(container c, char *target);      

#endif
