/* Container functions used in cosc242 assignment
   11/09/17
   @authors Taylor Manning, Callan Taylor, Luke Falvey
*/
#include "mylib.h"
#include "flexarray.h"
#include "rbt.h"
#include "container.h"

/*Structure of container, holds
  variables of the container type
  and its contents
 */
struct containerrec {
    /* Type of container */
    container_t type;
    /* Contents of the container */
    void *contents;
};

/*Function inserts a word into specified container
  using the rbt_insert or flexarray_append
  functions appropriately.
  @param c is container being inserted into
  @param word is the word to be inserted
 */
void container_add(container c, char *word) {
    if (c->type == RED_BLACK_TREE) {
        c->contents = root_fix(rbt_insert(c->contents, word));
    } else {
        flexarray_append(c->contents, word);
    }
}

/*Creates new container of type rbt,
  initialises the variables and
  allocates memory.
  @return result is the new container
 */
container container_new_rbt() {
    container result = emalloc (sizeof *(result));
    result->type = RED_BLACK_TREE;
    result->contents = rbt_new();
    return result;
}

/*Creates new container of type flexarray,
  initialises the variables and
  allocates memory.
  @return result is the new container
*/
container container_new_flexarray() {
    container result = emalloc (sizeof *(result));
    result->type = FLEX_ARRAY;
    result->contents = flexarray_new();
    return result;
}

/*Frees all memory the container is using
  @param c is the container to free
 */
void container_free(container c) {
    if (c->type == RED_BLACK_TREE) {
        rbt_free(c->contents);
    } else {
        flexarray_free(c->contents);
    }
    free(c);
}

/*Searches the container for a word by using
  rbt_search and flexarray_is_present appropriately.
  @param c is container to search
  @param target is the string to search for
*/
int container_search(container c, char *target) {
    if (c->type == RED_BLACK_TREE) {
        return rbt_search(c->contents, target);
    }
    return flexarray_is_present(c->contents, target);
}

/*Prints contents of the container by referencing
  rbt_preorder and flexarray_visit appropriately/
  @param c is container to print
  @param f will take the print function to be used
*/
void container_print(container c, void f(char *word)) {
    if (c->type == RED_BLACK_TREE) {
        rbt_preorder(c->contents, f);
    } else {
        flexarray_visit(c->contents, f);
    }
}
