/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (!q)
        return NULL;
    q->size = 0;
    q->head = NULL;
    q->tail = NULL;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    list_ele_t *remove_element;
    if (!q)
        return;
    else {
        while (q->head != NULL) {
            remove_element = q->head;
            q->head = q->head->next;
            if (remove_element->value)
                free(remove_element->value);
            free(remove_element);
        }
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* What should you do if the q is NULL? */
    if (!q)
        return false;

    // malloc check
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->value = malloc(strlen(s) + 1);
    if (!newh->value) {
        free(newh);
        return false;
    }

    // initialize the new node, and connect to queue
    strcpy(newh->value, s);
    if (q->size == 0) {
        q->tail = newh;
    }
    newh->next = q->head;
    q->head = newh;
    q->size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */

    /* What should you do if the q is NULL? */
    if (!q)
        return false;

    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->value = malloc(strlen(s) + 1);
    if (!newh->value) {
        free(newh);
        return false;
    }

    strcpy(newh->value, s);
    if (q->size == 0) {
        q->head = newh;
    } else {
        q->tail->next = newh;
    }
    newh->next = NULL;
    q->size++;
    q->tail = newh;
    return true;
    return false;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (!q || q->size == 0)
        return false;

    list_ele_t *remove_element;
    remove_element = q->head;

    // copy to *sp
    if (sp) {
        strncpy(sp, remove_element->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }

    // head==tail or not ?
    if (q->head == q->tail) {
        q->head = NULL;
        q->tail = NULL;
    } else {
        q->head = q->head->next;
    }
    q->size--;

    // free string
    free(remove_element->value);
    free(remove_element);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q)
        return 0;
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */

    // null queue || empty queue || single node queue doesn't have to reverse
    if (q == NULL || q->head == NULL || q->head->next == NULL)
        return;
    else {
        int first = 1;
        list_ele_t *pre_element, *current_element, *next_element;
        pre_element = q->head;
        current_element = q->head->next;
        next_element = q->head->next->next;

        // not the last two node
        if (next_element != NULL) {
            while (1) {
                if (first == 1) {
                    pre_element->next = NULL;
                    first = 0;
                }
                current_element->next = pre_element;

                if (next_element == NULL)
                    break;

                pre_element = current_element;
                current_element = next_element;
                next_element = next_element->next;
            }
            list_ele_t *tmp;
            tmp = q->tail;
            q->tail = q->head;
            q->head = tmp;
        }
        // only exist two node
        else {
            current_element->next = pre_element;
            pre_element->next = NULL;
            list_ele_t *tmp;
            tmp = q->tail;
            q->tail = q->head;
            q->head = tmp;
        }
    }
}
