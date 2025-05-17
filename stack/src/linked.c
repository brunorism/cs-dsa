#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node_t {
    int val;
    struct _node_t *next;
} node_t;

typedef struct _list {
    node_t *item;
    size_t count;
} list_t;

void append_list(list_t **list, int val, int *op);
void pop_list(list_t **list, int *op);
void free_list(list_t *list, int *op);
void print_list(list_t *list, int *op);

int main(void)
{
    int op = 0;

    list_t *list = {0};
    append_list(&list, 10, &op);
    append_list(&list, 20, &op);
    append_list(&list, 30, &op);
    append_list(&list, 40, &op);
    print_list(list, &op);

    pop_list(&list, &op);
    pop_list(&list, &op);
    print_list(list, &op);

    free_list(list, &op);

    return 0;
}

void append_list(list_t **list, int val, int *op)
{
    node_t *temp = malloc(sizeof(*temp));
    assert(temp != NULL);

    memset(temp, 0, sizeof(*temp));
    temp->val = val; 

    if (*list == NULL) {
        temp->next = NULL;

        *list = malloc(sizeof(**list));
        assert(*list != NULL);

        memset(*list, 0, sizeof(**list));
        (*list)->item = temp;
        (*list)->count += 1; 
    } else {
        temp->next = (*list)->item;

        (*list)->item = temp;
        (*list)->count += 1; 
    }

    printf("%d: INFO: appended value: %d\n", (*op += 1), val);
}

void pop_list(list_t **list, int *op)
{
    node_t *temp = (*list)->item;
    int n = temp->val;
    (*list)->item = (*list)->item->next;
    free(temp);
    (*list)->count -= 1;
    printf("%d: INFO: popped value: %d\n", (*op += 1), n);
}

void free_list(list_t *list, int *op)
{
    int n = 0;
    while (list->item != NULL) {
        node_t *temp = list->item;
        list->item = list->item->next;
        n = temp->val;
        free(temp);
        printf("%d: INFO: popping & cleaning item: %d\n", (*op += 1), n);
    }
    free(list);
    printf("%d: INFO: `list` all cleaned up!\n", (*op += 1));
}

void print_list(list_t *list, int *op)
{
    size_t i = 0;
    node_t *curr = list->item;
    printf("%d: INFO: `list` length of %zu: ", (*op += 1), list->count);
    while (curr != NULL) {
        printf("%d", curr->val);
        curr = curr->next;
        i += 1;
        if (i < list->count) printf("->");
    }
    printf("\n");
}
