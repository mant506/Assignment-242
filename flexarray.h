/* Specifies the interface for flexarray.
 * 11/09/17.
 * Authors: Taylor Manning, Callan Taylor, Luke Falvey.
 */
#ifndef FLEXARRAY_H_
#define FLEXARRAY_H_

typedef struct flexarrayrec *flexarray;

extern void      flexarray_append(flexarray f, char *item);
extern void      flexarray_free(flexarray f);
extern flexarray flexarray_new();
extern int    	 flexarray_is_present(flexarray f, char *target);
extern void 	 flexarray_visit(flexarray f, void func(char *str));

#endif
