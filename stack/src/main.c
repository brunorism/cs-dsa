#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node_t node_t;
struct node_t {
    int val;
    node_t *next;
};

void alloc_node(node_t *head, int val) {
    node_t temp = {0};
    temp.next = malloc(sizeof(node_t));
    temp.next->val = 0;
    temp.next->next = NULL;

    if (!head) {
        head->val = val;
        head->next = temp.next;
    } else {
        node_t *curr = head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->val = val;
        curr->next = temp.next;
    }
}

void pop_node(node_t **head, int target) {
    int ret = -1;
    if ((*head)->val == target) {
        node_t *temp = *head;
        *head = (*head)->next;
        free(temp);
        // return head;
    } else {
        node_t *curr = *head;
        while (curr->next) {
            if (curr->next->val == target) {
                node_t *temp = curr->next;
                curr->next = temp->next;
                free(temp);
                ret = target;
                // return curr;
            }
            curr = curr->next;
        }
    }

    // return NULL;
}

void free_node(node_t *head) {
    node_t *temp = NULL;

    while (head->next != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void print_node(node_t *head) {
    while (head) {
        if (!head->next) {
            printf("NULL\n");
            break;
        }
        printf("%d->", head->val);
        head = head->next;
    }
}

int main(void) {
    // node_t head = malloc(sizeof(node_t));
    node_t head = {0};
    // head->next = NULL;

    alloc_node(&head, 10);
    alloc_node(&head, 20);
    alloc_node(&head, 30);

    print_node(&head);

    pop_node(&head, 10);
    // printf("%s: %d\n", pop > 0 ? "INFO: node of value" : "ERROR: value not found", pop);
    
    print_node(&head);

    free_node(head.next);

    return 0;
}
