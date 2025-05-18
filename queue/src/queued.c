#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node_t {
    int val;
    struct _node_t *next;
    struct _node_t *prev;
} node_t;

typedef struct _queue {
    node_t *item;
    size_t count;
} queue_t;

void append_queue(queue_t **q, int val, int *op);
void pop_queue(queue_t **q, int *op);
void free_queue(queue_t *q, int *op);
void print_queue(queue_t *q, int *op);

int main(void)
{
    int op = 0;

    queue_t *q = {0};
    append_queue(&q, 10, &op);
    append_queue(&q, 20, &op);
    append_queue(&q, 30, &op);
    append_queue(&q, 40, &op);
    print_queue(q, &op);

    pop_queue(&q, &op);
    pop_queue(&q, &op);
    print_queue(q, &op);

    free_queue(q, &op);

    return 0;
}

void append_queue(queue_t **q, int val, int *op)
{
    node_t *temp = malloc(sizeof(*temp));
    assert(temp != NULL);
    memset(temp, 0, sizeof(*temp));

    temp->val = val;
    temp->next = NULL;
    temp->prev = NULL;

    if (*q == NULL) {
        *q = malloc(sizeof(**q));
        assert(*q != NULL);
        memset(*q, 0, sizeof(**q));
        (*q)->item = temp;
    } else {
        temp->prev = (*q)->item;
        (*q)->item->next = temp;
        (*q)->item = (*q)->item->next;
    }

    (*q)->count += 1;

    printf("%d: INFO: appended value: %d\n", (*op += 1), val);
}

void pop_queue(queue_t **q, int *op)
{
    node_t *temp = (*q)->item;
    int n = temp->val;
    (*q)->item = (*q)->item->prev;
    free(temp);
    (*q)->item->next = NULL;
    (*q)->count -= 1;
    printf("%d: INFO: popped value: %d\n", (*op += 1), n);
}

void free_queue(queue_t *q, int *op)
{
    int n = 0;
    while (q->item != NULL) {
        node_t *temp = q->item;
        q->item = q->item->prev;
        n = temp->val;  
        free(temp);
        printf("%d: INFO: popping & cleaning item: %d\n", (*op += 1), n);
    }
    free(q);
    printf("%d: INFO: `queue` all cleaned up!\n", (*op += 1));
}

void print_queue(queue_t *q, int *op)
{
    size_t i = q->count;
    node_t *curr = q->item;
    printf("%d: INFO: `queue` length of %zu: ", (*op += 1), q->count);
    while (curr != NULL) {
        if (i < q->count) printf("<-");
        printf("%d", curr->val);
        curr = curr->prev;
        i -= 1;
    }
    printf("\n");
}
