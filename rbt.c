/* Implemantation of the header file for red-black tree.
 * 11/09/17
 * Authors Taylor Manning, Callan Taylor, Luke Falvey
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mylib.h"
#include "rbt.h"

#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

typedef enum { RED, BLACK } rbt_colour;

/* Structure of rbt, holds
 * variables of the key that references
 * the tree, color of the base node,
 * black count, and the children nodes.
 */
struct rbt_node {
    /* The key that references the rbt. */
    char *key;
    /* Color of the root node. */
    rbt_colour colour;
    /* Left child node. */
    rbt left;
    /* Right child node. */
    rbt right;
};

/* Creates new rbt, assigns root to null.
 * Returns: new is the rbt
 */
rbt rbt_new() {
    rbt new = NULL;
    return new;
}

/* Recursively searches through a rbt for a
 * given string and determines if present.
 * Parameters: b is the rbt to search
 * Parameters: str is the string to search for
 * Returns: 1 if found, 0 if not
 */
int rbt_search(rbt b, char *str) {
    if (NULL == b) {
        return 0;
    } else if (strcmp(b->key, str) == 0) {
        return 1;
    }  else if (strcmp(b->key,str) > 0) {
        return rbt_search(b->left,str);
    } else if (strcmp(b->key,str) < 0) {
        return rbt_search(b->right,str);
    }
    return 1;
}

/* Rotates the rbt to the right.
 * Parameters: b is the rbt to rotate
 * Returns: the updated rbt
 */
static rbt right_rotate(rbt b) {
    rbt temp = b;
    b = b->left;
    temp->left = b->right;
    b->right = temp;
    return b;
}

/* Rotates the rbt to the left.
 * Parameters: b is the rbt to rotate
 * Returns: the updated rbt
 */
static rbt left_rotate(rbt b) {
    rbt temp = b;
    b = b->right;
    temp->right = b->left;
    b->left = temp;
    return b;
}

/* Fixes the root to be black.
 * Parameters: b is the rbt to fix
 * Returns: is the fixed root
 */
rbt root_fix(rbt b) {
    b->colour = BLACK;
    return b;
}

/* Fixes the colors of the rbt to
 * fit specifications of a rbt except
 * root being black.
 * Parameters: b is the rbt to fix
 * Returns: the fixed rbt
 */
static rbt rbt_fix(rbt b) {
    if (IS_RED(b->left) && IS_RED(b->left->left)) {
        if (IS_RED(b->right)) {
            b->colour = RED;
            b->left->colour = BLACK;
            b->right->colour = BLACK;
        } else if (IS_BLACK(b->right)) {
            b = right_rotate(b);
            b->colour = BLACK;
            b->right->colour = RED;
        }
    } else if (IS_RED(b->left) && IS_RED(b->left->right)) {
        if (IS_RED(b->right)) {
            b->colour = RED;
            b->left->colour = BLACK;
            b->right->colour = BLACK;
        } else if (IS_BLACK(b->right)) {
            b->left = left_rotate(b->left);
            b = right_rotate(b);
            b->colour = BLACK;
            b->right->colour = RED;
        }
    } else if (IS_RED(b->right) && IS_RED(b->right->left)) {
        if (IS_RED(b->left)) {
            b->colour = RED;
            b->left->colour = BLACK;
            b->right->colour = BLACK;
        } else if (IS_BLACK(b->left)) {
            b->right = right_rotate(b->right);
            b = left_rotate(b);
            b->colour = BLACK;
            b->left->colour = RED;
        }
    } else if (IS_RED(b->right) && IS_RED(b->right->right)) {
        if (IS_RED(b->left)) {
            b->colour = RED;
            b->left->colour = BLACK;
            b->right->colour = BLACK;
        } else if (IS_BLACK(b->left)) {
            b = left_rotate(b);
            b->colour = BLACK;
            b->left->colour = RED;
        }
    }
    return b;
}

/* Inserts a string into given rbt in
 * the appropriate position and
 * fixes to ensure the tree is correct.
 * Parameters: b is rbt to insert into
 * Parameters: str is the string to insert
 * Returns: the new rbt
 */
rbt rbt_insert(rbt b, char *str) {
    if (NULL == b) {
        b = emalloc(sizeof *(b));
        b->colour = RED;
        b->left = NULL;
        b->right = NULL;
        b->key = emalloc((strlen(str) + 1) * sizeof(b->key));
        strcpy(b->key, str);
        return b;
    } else if (strcmp(b->key,str) > 0) {
        b->left = rbt_insert(b->left,str);
    } else if (strcmp(b->key,str) < 0) {
        b->right = rbt_insert(b->right,str);
    } else if (strcmp(b->key,str) == 0) {
        b->left = rbt_insert(b->left,str);
    }
    b = rbt_fix(b);
    return b;
}

/* Frees all memory the given rbt is using.
 * Parameters: b is the rbt using the memory
 * Returns: the rbt using no memory
 */
rbt rbt_free(rbt b) {
    if (NULL == b) {
        return b;
    } 
    b->left = rbt_free(b->left);
    b->right = rbt_free(b->right);
    free(b->key);
    free(b);
    return b;
}

/* Performs a given function on all items
 * through preorder traversal (print used
 * for this assignment).
 * Parameters: b is rbt to traverse
 * Parameters: f is the function to perform
 */
void rbt_preorder(rbt b, void f(char *str1)) {
    if (NULL == b) {
        return;
    }
    f(b->key);
    rbt_preorder(b->left,f);
    rbt_preorder(b->right,f);
}







