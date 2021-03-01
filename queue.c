#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    /* TODO: What if malloc returned NULL? */
    queue_t *q;
    if (!(q = malloc(sizeof(queue_t))))
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (!q)
        return;
    while (q->head) {
        list_ele_t *tmp = q->head;
        q->head = q->head->next;
        free(tmp->value);
        free(tmp);
    }
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    size_t slen = strlen(s) + 1;
    /* TODO: What should you do if the q is NULL? */
    if (!q) {
        return false;
    }
    if (!(newh = malloc(sizeof(list_ele_t))))
        return false;
    if (!(newh->value = malloc(slen))) {
        free(newh);
        return false;
    }
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    memcpy(newh->value, s, slen);
    if (!q->head)
        q->tail = newh;
    newh->next = q->head;
    q->head = newh;
    q->size++;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    list_ele_t *newh;
    size_t slen = strlen(s) + 1;
    if (!q)
        return false;
    if (!(newh = malloc(sizeof(list_ele_t))))
        return false;
    if (!(newh->value = malloc(slen))) {
        free(newh);
        return false;
    }
    memcpy(newh->value, s, slen);
    newh->next = NULL;
    q->tail->next = newh;
    q->tail = newh;
    q->size++;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    // if (!q)
    //    return true;
    if (!q)
        return false;
    list_ele_t *tmp = q->head;
    if (!tmp)
        return false;
    q->head = tmp->next;
    memcpy(sp, tmp->value, bufsize);
    free(tmp->value);
    free(tmp);
    q->size--;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (!q)
        return 0;
    /* TODO: You need to write the code for this function */
    return q->size;
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    return 0;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q)
        return;
    list_ele_t *cur;
    list_ele_t *tmp = NULL;
    if (!(q->head))
        return;
    q->tail = q->head;
    while (q->head) {
        cur = q->head;
        q->head = cur->next;
        cur->next = tmp;
        tmp = cur;
    }
    q->head = cur;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
static list_ele_t *merge(list_ele_t *, list_ele_t *);
static list_ele_t *mergesort(list_ele_t *);
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q)
        return;
    if (!(q->head) || !(q->head->next))
        return;
    q->head = mergesort(q->head);
    list_ele_t *tmp = q->head;
    while (tmp->next) {
        tmp = tmp->next;
    }
    q->tail = tmp;
}

static list_ele_t *merge(list_ele_t *left, list_ele_t *right)
{
    list_ele_t *tmp, *q;
    int compare = 0;
    if (right && left)
        compare = strcmp(left->value, right->value);
    if (compare < 0 || !(right)) {
        tmp = left;
        left = left->next;
    } else {
        tmp = right;
        right = right->next;
    }
    q = tmp;
    while (left && right) {
        compare = strcmp(left->value, right->value);
        if (compare < 0) {
            tmp->next = left;
            left = left->next;
            tmp = tmp->next;
        } else {
            tmp->next = right;
            right = right->next;
            tmp = tmp->next;
        }
    }
    if (!left) {
        tmp->next = right;
    } else {
        tmp->next = left;
    }
    return q;
}

static list_ele_t *mergesort(list_ele_t *head)
{
    if (!(head) || !(head->next)) {
        return head;
    }
    list_ele_t *right = head->next;
    list_ele_t *left = head;
    while (right && right->next) {
        left = left->next;
        right = right->next->next;
    }
    right = left->next;
    left->next = NULL;

    head = mergesort(head);
    right = mergesort(right);
    return merge(head, right);
}
