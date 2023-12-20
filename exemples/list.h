#ifndef LIST_H
#define LIST_H

/**
 * \file  list.h
 * \brief Contains the declarations for the \ref Node and the \ref List data structures,
 *        and related functions.
 */

#include <stdlib.h>

/**
 * \struct Node
 * \brief  A node of a \ref List.
 *
 * This data structure is to be used for iterating over a list and/or for setting
 * the value of a single node. For manipulating a list (insertion, deletion, etc.),
 * please use the appropriate functions of \ref List.
 */
struct Node {

        /**
         * \brief A pointer to the previous node in the list.
         *
         * \p prev is NULL if the node has no predecessor (i.e. if it is the first element of the list).
         */
        struct Node* prev;

        /**
         * \brief A pointer to the next node in the list.
         *
         * \p next is NULL if the node has no successor (i.e. if it is the last element of the list).
         */
        struct Node* next;

        /**
         * \brief A pointer to the string stored in the node.
         *
         * The string is dynamically allocated using malloc and/or strdup.
         * \p value shall never be NULL.
         */
        char* value;

};

/**
 * \relates Node
 * \brief   Sets the string stored in a given node.
 * \param   node  The node to be updated.
 * \param   value The new string to be stored.
 * \return  0 on success, 1 in case of an error (the node is left unmodified).
 *
 * \p value is duplicated using strdup.
 */
int Node_update (struct Node* node, const char* value);

/**
 * \struct List
 * \brief  A doubly linked list of strings.
 *
 * This data structure is to be manipulated using the functions documentated below.
 */
struct List {

        /**
         * \brief The size of the list.
         *
         * \p size equals to 0 if the list is empty.
         */
        size_t size;

        /**
         * \brief A pointer to the first element of the list.
         *
         * \p head is NULL if the list is empty.
         */
        struct Node* head;

        /**
         * \brief A pointer to the last element of the list.
         *
         * \p tail is NULL if the list is empty.
         */
        struct Node* tail;

};

/**
 * \relates List
 * \brief   Allocates a new empty list.
 * \return  The new list on success, NULL in case of an error.
 *
 * The list can later be passed to \ref List_delete to be freed.
 */
struct List* List_new ();

/**
 * \relates List
 * \brief   Frees the memory allocated for a list.
 * \param   list The list to be freed.
 *
 * No operation is performed if \p list is NULL.
 */
void List_delete (struct List* list);

/**
 * \relates List
 * \brief   Clears a list (erases all its contents).
 * \param   list The list to be cleared.
 */
void List_clear (struct List* list);

/**
 * \relates List
 * \brief   Inserts a new string at the beginning of a list.
 * \param   list  The list to be modified.
 * \param   value The new string to be stored.
 * \return  0 on success, 1 in case of an error (the list is left unmodified).
 *
 * \p value is duplicated using strdup.
 */
int List_push_front (struct List* list, const char* value);

/**
 * \relates List
 * \brief   Inserts a new string at the end of a list.
 * \param   list  The list to be modified.
 * \param   value The new string to be stored.
 * \return  0 on success, 1 in case of an error (the list is left unmodified).
 *
 * \p value is duplicated using strdup.
 */
int List_push_back (struct List* list, const char* value);

/**
 * \relates List
 * \brief   Inserts a new string in a list.
 * \param   list  The list to be modified.
 * \param   pos   The node before which the value shall be inserted.
 * \param   value The new string to be stored.
 * \return  0 on success, 1 in case of an error (the list is left unmodified).
 *
 * If \p pos is NULL, \p value is inserted at the end of \p list.
 * If \p pos does not belong to \p list, the behaviour is undefined.
 * \p value is duplicated using strdup.
 */
int List_insert (struct List* list, struct Node* pos, const char* value);

/**
 * \relates List
 * \brief   Removes the first element of a list.
 * \param   list The list to be modified.
 * \return  0 on success, 1 in case of an error (the list is left unmodified).
 *
 * The function fails if the list is empty.
 */
int List_pop_front (struct List* list);

/**
 * \relates List
 * \brief   Removes the last element of a list.
 * \param   list The list to be modified.
 * \return  0 on success, 1 in case of an error (the list is left unmodified).
 *
 * The function fails if the list is empty.
 */
int List_pop_back (struct List* list);

/**
 * \relates List
 * \brief   Removes a given element of a list.
 * \param   list The list to be modified.
 * \param   pos  The element to be removed.
 * \return  0 on success, 1 in case of an error (the list is left unmodified).
 *
 * If \p pos does not belong \p list, the behaviour is undefined.
 */
int List_erase (struct List* list, struct Node* pos);

/**
 * \relates List
 * \brief   Moves the nodes from \p from2 to \p to2 (excluded) in \p list2 before \p pos1 in \p list1.
 * \param   list1 The destination list.
 * \param   pos1  The position before which the nodes shall be moved.
 * \param   list2 The source list.
 * \param   from2 The beginning of the range of nodes to be moved.
 * \param   to2   The end       of the range of nodes to be moved.
 *
 * If \p pos1 is NULL, the nodes are moved at the end of \p list1.
 * If \p  to2 is NULL, all the nodes from \p from2 in \p list2 are moved to \p list1.
 * If:
 *   - \p pos1 does not belong to \p list1,
 *   - [ \p from2, \p to2 [ does not define a valid range of nodes in \p list2,
 *   - \p list1 == \p  list2 and \p pos1 is in [ \p from2, \p to2 [,
 * the behaviour is undefined.
 */
void List_splice (struct List* list1, struct Node* pos1, struct List* list2, struct Node* from2, struct Node* to2);

/**
 * \relates List
 * \brief   Swaps two elements in a list.
 * \param   list The list to be modified.
 * \param   x The first  element.
 * \param   y The second element.
 *
 * No copy is performed; only the links are updated.
 * If \p x and/or \p y do not belong to \p list, the behaviour is undefined.
 */
void List_swap (struct List* list, struct Node* x, struct Node* y);

/**
 * \relates List
 * \brief   Finds the first occurence of a given string in a list.
 * \param   list    The list  to be searched.
 * \param   value   The value to be found.
 * \param   compare The function used to compare the strings.
 * \return  A pointer to the first occurence of value in list, or NULL if the string is not found.
 *
 * \p compare is a pointer to a function that shall return 0 if and only if
 *   the two strings are considered equal.
 * strcmp and stricmp are typical values for this parameter.
 */
struct Node* List_find (struct List* list, const char* value, int (*compare)(const char*, const char*));

/**
 * \relates List
 * \brief   Sorts a list with respect to a given comparator in ascending order.
 * \param   list    The list to be sorted.
 * \param   compare The function used to compare two strings.
 * \return
 *
 * \p compare is a pointer to a function that shall return a negative number if and only if the
 *   first string is considered less than the second.
 * strcmp and stricmp are typical values for this parameter.
 */
void List_sort (struct List* list, int (*compare)(const char*, const char*));

/**
 * \relates List
 * \brief   Prints the content of a list.
 * \param   The list to be printed.
 */
void List_print (const struct List* list);

// end of ifndef LIST_HEADER_GUARD
#endif
