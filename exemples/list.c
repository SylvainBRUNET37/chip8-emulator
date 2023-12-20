#include "list.h"
#include <stdio.h>
#include <string.h>

// -------------------------------------------------------------
// --------------------------- NODES ---------------------------
// -------------------------------------------------------------

int Node_update (struct Node* node, const char* value) {
        char* nvalue = strdup(value);
        if (!nvalue) {
                // strdup may fail and return NULL
                // in that case Node_update fails as well
                return 1;
        }
        free(node->value);
        node->value = nvalue;
        return 0;
}

// Allocates a node.
// FOR INTERNAL USE ONLY
struct Node* Node_new (const char* value) {
        struct Node* node = malloc(sizeof(struct Node));
        if (node) {
                if (!(node->value=strdup(value))) {
                        free(node);
                        node = NULL;
                }
                node->prev = NULL;
                node->next = NULL;
        }
        return node;
}

// Frees a node.
// FOR INTERNAL USE ONLY
void Node_delete (struct Node* node) {
        if (node) {
                free(node->value);
                free(node);
        }
}

// -------------------------------------------------------------
// --------------------------- LIST ----------------------------
// -------------------------------------------------------------

struct List* List_new () {
        struct List* list = malloc(sizeof(struct List));
        if (list) {
                list->head = NULL;
                list->tail = NULL;
                list->size =    0;
        }
        return list;
}

void List_delete (struct List* list) {
        if (list) {
                List_clear(list);
                free(list);
        }
}

void List_clear (struct List* list) {
        struct Node* node = list->head;
        while (node) {
                struct Node* tmp = node->next;
                Node_delete(node);
                node = tmp;
        }
        list->head = NULL;
        list->tail = NULL;
        list->size =    0;
}

int List_push_front (struct List* list, const char* value) {
        return List_insert(list, list->head, value);
}

int List_push_back (struct List* list, const char* value) {
        return List_insert(list, NULL, value);
}

// Inserts the range of nodes [first,last] just before pos in list.
// Remarks:
//     - if pos is NULL the nodes are inserted at the end of the list;
//     - first and last cannot be NULL;
//     - this function does NOT update list->size accordingly;
//     - no check is performed.
// FOR INTERNAL USE ONLY
void List_link_range (struct List* list, struct Node* pos, struct Node* first, struct Node* last) {
        last->next = pos;
        // front
        if (list->head == pos) {
                // if the list is not empty
                if (list->head) list->head->prev = last;
                else            list->tail       = last;
                list->head  = first;
                first->prev =  NULL;
        }
        // back
        else if (!pos) {
                first->prev      = list->tail;
                list->tail->next =      first;
                list->tail       =       last;
        }
        // general case
        else {
                first->prev     = pos->prev;
                pos->prev->next =     first;
                pos->prev       =      last;
        }
}

int List_insert (struct List* list, struct Node* pos, const char* value) {
        struct Node* nnode = Node_new(value);
        if (!nnode) {
                return 1;
        }
        ++list->size;
        List_link_range(list, pos, nnode, nnode);
        return 0;
}

int List_pop_front (struct List* list) {
        return List_erase(list, list->head);
}

int List_pop_back (struct List* list) {
        return List_erase(list, NULL);
}

// Removes the range of nodes [first,last] from list.
// Remarks:
//     - first and last cannot be NULL;
//     - this function does NOT update list->size accordingly;
//     - no check is performed.
// FOR INTERNAL USE ONLY
void List_unlink_range (struct List* list, struct Node* first, struct Node* last) {
        // left
        if (first == list->head) list->head        = last->next;
        else                     first->prev->next = last->next;
        // right
        if (last == list->tail) list->tail       = first->prev;
        else                    last->next->prev = first->prev;
        // sanitize
        first->prev = last->next = NULL;
}

int List_erase (struct List* list, struct Node* pos) {
        if (!list->size) {
                return 1;
        }
        List_unlink_range(list, pos, pos);
        --list->size;
        Node_delete(pos);
        return 0;
}

void List_splice (struct List* list1, struct Node* pos1, struct List* list2, struct Node* from2, struct Node* to2) {
        struct Node *last2 = from2;
        for (struct Node *it2 = from2; it2 != to2; last2 = it2, it2 = it2->next) {
                --list2->size;
                ++list1->size;
        }
        List_unlink_range(list2,       from2, last2);
        List_link_range  (list1, pos1, from2, last2);
}

void List_swap (struct List* list, struct Node* x, struct Node* y) {
        if (x != y) {
                struct Node* prevX = x->prev;
                struct Node* nextX = x->next;
                struct Node* prevY = y->prev;
                struct Node* nextY = y->next;
                // ... X <--> Y ...
                if (nextX == y) {
                        x->prev =     y;
                        x->next = nextY;
                        y->prev = prevX;
                        y->next =     x;
                        if (prevX) { prevX->next = y; } else { list->head  = y; }
                        if (nextY) { nextY->prev = x; } else { list->tail  = x; }
                }
                else
                // ... Y <--> X ...
                if (nextY == x) {
                        x->prev = prevY;
                        x->next =     y;
                        y->prev =     x;
                        y->next = nextX;
                        if (prevY) { prevY->next = x; } else { list->head  = x; }
                        if (nextX) { nextX->prev = y; } else { list->tail  = y; }
                }
                // ... X ... Y ...
                // ... Y ... X ...
                else {
                        x->prev = prevY;
                        x->next = nextY;
                        y->prev = prevX;
                        y->next = nextX;
                        if (prevX) { prevX->next = y; } else { list->head  = y; }
                        if (nextX) { nextX->prev = y; } else { list->tail  = y; }
                        if (prevY) { prevY->next = x; } else { list->head  = x; }
                        if (nextY) { nextY->prev = x; } else { list->tail  = x; }
                }
        }
}

struct Node* List_find (struct List* list, const char* value, int (*compare)(const char*, const char*)) {
        for (struct Node* node = list->head; node; node = node->next) {
                if (compare(value, node->value) == 0) {
                        return node;
                }
        }
        return NULL;
}

void List_sort (struct List* list, int (*compare)(const char*, const char*)) {
        for (struct Node* position = list->head; position; position = position->next) {
                struct Node* min = position;
                for (struct Node* x = min->next; x; x = x->next) {
                        if (compare(x->value, min->value) < 0) {
                                min = x;
                        }
                }
                List_swap(list, position, min);
        }
}

void List_print (const struct List* list) {
        printf("[\n");
        for (const struct Node* node = list->head; node; node = node->next) {
                printf("   %s\n", node->value);
        }
        printf("]\n");
}
