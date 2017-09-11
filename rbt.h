/* Header file for rbt.c used in cosc242 assignment
   11/09/17
   @authors Taylor Manning, Callan Taylor, Luke Falvey
*/
#ifndef RBT_H
#define RBT_H

#include <stdio.h>

typedef struct rbt_node *rbt;


extern rbt   rbt_delete(rbt b, char *str);
extern rbt   rbt_free(rbt b);
extern void  rbt_inorder(rbt b, void f(char *str));
extern rbt   rbt_insert(rbt b, char *str);
extern rbt   rbt_new();
extern void  rbt_preorder(rbt b, void f(char *str1));
extern int   rbt_search(rbt b, char *str);

#endif
