#include "ll.h"
#include <stdio.h>
#include <stdlib.h>

static LLNode *init_node(void *item) {
    LLNode *node = malloc(sizeof(LLNode));
    if (node == NULL) return NULL;

    node->item = item;
    node->next = NULL;

    return node;
}

LList *ll_init() {
    LList *init = malloc(sizeof(LList));
    if (init == NULL) return NULL;

    init->head = NULL;
    init->tail = NULL;
    init->length = 0;

    return init;
}

LList *ll_initi(void *item) {
    LList *init = ll_init();
    if (init == NULL) return NULL;

    if (ll_push(init, item) != 1) return NULL;
    return init;
}

unsigned int ll_push(LList *list, void *item) {
    if (list == NULL) return 0;

    unsigned int len = list->length;

    LLNode *node = init_node(item);
    if (node == NULL) return len;

    if (len == 0) {
        list->head = node;
        list->tail = node;
    } else {
        LLNode *tail = list->tail;
        tail->next = node;
        list->tail = node;
    }

    list->length = ++len;
    return len;
}

unsigned int ll_unshift(LList *list, void *item) {
    if (list == NULL) return 0;

    unsigned int len = list->length;

    LLNode *node = init_node(item);
    if (node == NULL) return len;

    if (len == 0) {
        list->head = node;
        list->tail = node;
    } else {
        LLNode *prev_head = list->head;
        list->head = node;
        node->next = prev_head;
    }

    list->length = ++len;
    return len;
}

unsigned int ll_put(LList *list, unsigned int target_index, void *item) {
    unsigned int current_index = 0;

    LLNode *current_node = list->head;
    while (current_index <= target_index) {
        // Insert a new NULL node if we ran out of existing nodes
        if (current_node == NULL) {
            const unsigned int prev_len = list->length;
            const unsigned int new_len = ll_push(list, NULL);

            // We could not insert the new node for some reason
            if (new_len - prev_len != 1) {
                return new_len;
            }

            // Tail will now be the pushed node
            current_node = list->tail;
        }

        // If we have not reached the desired index, move on
        if (current_index != target_index) {
            current_node = current_node->next;
        }

        current_index++;
    }

    // Overwrite the value of whatever node is at the target index
    current_node->item = item;

    return list->length;
}

LLNode *ll_getn(const LList *list, unsigned int index) {
    if (index >= list->length) {
        return NULL;
    }

    LLNode *node = list->head;
    while (index > 0) {
        if (node == NULL) {
            return NULL;
        }

        index--;
        node = node->next;
    }

    return node;
}

void *ll_get(const LList *list, unsigned int index) {
    const LLNode *node = ll_getn(list, index);
    if (node == NULL) return NULL;
    return node->item;
}

int ll_find(const LList *list, const void *item) {
    int index = 0;
    LLNode *node = list->head;

    while (node != NULL) {
        if (node->item == item) {
            return index;
        }

        node = node->next;
        index++;
    }

    return -1;
}

LLNode *ll_findn(const LList *list, const void *item) {
    LLNode *node = list->head;

    while (node != NULL) {
        if (node->item == item) {
            return node;
        }

        node = node->next;
    }

    return NULL;
}

void *ll_pop(LList *list) {
    // Scenario 1: No head and tail
    if (list->length == 0) {
        return NULL;
    }

    void *removed_item = list->tail->item;

    // Scenario 2: Same head and tail
    if (list->length == 1) {
        free(list->head);

        list->head = NULL;
        list->tail = NULL;
        list->length = 0;

        return removed_item;
    }

    // Scenario 3: Different head and tail

    LLNode *new_tail = ll_getn(list, list->length - 2);

    // Remove references of old tail
    new_tail->next = NULL;
    free(list->tail);
    list->tail = new_tail;

    list->length--;

    return removed_item;
}

void *ll_shift(LList *list) {
    // Scenario 1: No head and tail
    if (list->length == 0) {
        return NULL;
    }

    void *removed_item = list->head->item;

    // Scenario 2: Same head and tail
    if (list->length == 1) {
        free(list->head);

        list->head = NULL;
        list->tail = NULL;
        list->length = 0;

        return removed_item;
    }

    // Scenario 3: Different head and tail

    LLNode *new_head = list->head->next;

    // Remove references of initial head
    free(list->head);
    list->head = new_head;

    list->length--;

    return removed_item;
}

void *ll_removei(LList *list, unsigned int index) {
    if (index == 0) {
        return ll_shift(list);
    }

    if (index == list->length - 1) {
        return ll_pop(list);
    }

    // We can be sure here we are not removing the head or tail

    LLNode *node_before_remove = ll_getn(list, index - 1);
    if (node_before_remove == NULL) {
        return NULL;
    }

    LLNode *node_to_remove = node_before_remove->next;
    if (node_to_remove == NULL) {
        return NULL;
    }

    void *removed_item = node_to_remove->item;

    node_before_remove->next = NULL;
    node_before_remove->next = node_to_remove->next;
    free(node_to_remove);

    list->length--;

    return removed_item;
}

unsigned int ll_remove(LList *list, void *item) {
    int index = ll_find(list, item);
    if (index != -1) {
        ll_removei(list, index);
    }

    return list->length;
}

unsigned int ll_len(const LList *list) { return list->length; }

unsigned int ll_len_strict(const LList *list) {
    unsigned int length = 0;

    LLNode *node = list->head;
    while (node != NULL) {
        length++;
        node = node->next;
    }

    return length;
}

void ll_partial_free(LList *list) {
    LLNode *temp = list->head;
    while (temp != NULL) {
        LLNode *next = temp->next;
        free(temp);
        temp = next;
    }

    free(list);
}