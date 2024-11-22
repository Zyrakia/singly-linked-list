#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/**
 * Represents a node within a singly linked list.
 *
 * It needs to be said that a doubly-linked list would greatly improve
 * efficiency when removing after the head, but I decided against implementing
 * it. ^-^
 */
typedef struct LLNode {
    void *item;
    struct LLNode *next;
} LLNode;

/**
 * Represents a head-tail tracking linked list.
 */
typedef struct {
    LLNode *head;
    LLNode *tail;
    unsigned int length;
} LList;

/**
 * Initializes a new linked list without any items.
 *
 * @return a pointer to the dynamically allocated list
 */
LList *ll_init();

/**
 * Initializes a new linked list with the given initial item.
 *
 * @param item the initial item of the list
 * @return a pointer to the dynamically allocated list
 */
LList *ll_initi(void *item);

/**
 * Adds an item to the end of a linked list.
 *
 * @param list a pointer to the list to push into
 * @param item the item to push into the list
 * @return the new length of the list
 */
unsigned int ll_push(LList *list, void *item);

/**
 * Adds an item to the start of a linked list.
 *
 * @param list a pointer to the list to unshift into
 * @param item the item to unshift into the list
 * @return the new length of the list
 */
unsigned int ll_unshift(LList *list, void *item);

/**
 * Adds an item into a linked list so that it's index will
 * be the specified index.
 *
 * If the list has an existing item at that index, it will be replaced by the
 * new value.
 *
 * If the length of the list is less than the specified index, it will be
 * resized will NULL items until the index is reached. SO DON'T GO OVER THE
 * LENGTH OF THE LIST UNLESS YOU TRUST YOURSELF :D.
 *
 * @param list a pointer to the list to insert into
 * @param index the index at which to insert into
 * @param item the item to insert into the list
 * @return the new length of the list
 */
unsigned int ll_put(LList *list, unsigned int index, void *item);

/**
 * Adds an item into a linked list so that it's index will be in the specified
 * index.
 *
 * Unlike, `ll_put`, if the list has an existing item at the specifeid index, it
 * will be pushed forward, having only it's position replaced with the inserted
 * item, but not it's value.
 *
 * If the length of the list is less than the specified index, it will be
 * resized will NULL items until the index is reached. SO DON'T GO OVER THE
 * LENGTH OF THE LIST UNLESS YOU TRUST YOURSELF :D.
 *
 * @param list a pointer to the list to insert into
 * @param index the index at which to insert into
 * @param item the item to insert into the list
 * @return the new length of the list
 */
unsigned int ll_insert(LList *list, unsigned int index, void *item);

/**
 * Returns the node at a certain index within a linked list.
 *
 * @param list a pointer to the list to get the item from
 * @param index the index of the node to get
 * @return the node at the given index, or NULL
 */
LLNode *ll_getn(const LList *list, unsigned int index);

/**
 * Returns the item at a certain index within a linked list.
 *
 * @param list a pointer to the list to get the item from
 * @param index the index of the item to get
 * @return the item at the given index, or NULL
 */
void *ll_get(const LList *list, unsigned int index);

/**
 * Returns the index of the node within a linked list that holds a specific
 * item.
 *
 * @param list a pointer to the list to find the item in
 * @param item the item to find
 * @return the index of the item, or -1 if it was not found
 */
int ll_find(const LList *list, const void *item);

/**
 * Returns the node within a linked list that holds a specific item.
 *
 * @param list a pointer to the list to find the item in
 * @param item the item to find
 * @return the node that holds the item, or NULL if it was not found
 */
LLNode *ll_findn(const LList *list, const void *item);

/**
 * Removes the last item from a linked list and returns it.
 *
 * @param list a pointer to the list to pop from
 * @return the item that was at the end, or NULL
 */
void *ll_pop(LList *list);

/**
 * Removes the first item from a linked list and returns it.
 *
 * @param list a pointer to the list to shift from
 * @return the item that was at the start, or NULL
 */
void *ll_shift(LList *list);

/**
 * Removes the node at a specific index within a linked list and returns it.
 *
 * @param list a pointer to the list to remove from
 * @param index the index to remove
 * @return the item at the removed node, or NULL
 */
void *ll_removei(LList *list, unsigned int index);

/**
 * Removes the node that holds a specific from a linked list.
 *
 * @param list a poitner to the list to remove from
 * @param item the item to remove
 * @return the new length of the list after removal
 */
unsigned int ll_remove(LList *list, void *item);

/**
 * Returns the length of the given linked list. This will not calculate the
 * length, but simply return the lifetime tracked length of the list.
 *
 * @param list a pointer to the list to get the length of
 * @return the tracked length of the list
 */
unsigned int ll_len(const LList *list);

/**
 * Returns the length of the given linked list. This will iterate throughout the
 * list and calculate the exact length.
 *
 * @param list a pointer to the list to get the length of
 * @return the calculated length of the list
 */
unsigned int ll_len_strict(const LList *list);

/**
 * Frees the list, including every node within it. IT WILL NOT free
 * the data pointer within the node, hence the partial.
 *
 * @param list a pointer to the list to free, this pointer will not be usable
 * after execution
 */
void ll_partial_free(LList *list);

#endif