#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct __node {
    int value;
    struct __node *next;
} node_t;

static bool list_is_ordered(node_t *list)
{
    bool first = true;
    int value;
    while (list) {
        if (first) {
            value = list->value;
            first = false;
        } else {
            if (list->value < value)
                return false;
            value = list->value;
        }
        list = list->next;
    }
    return true;
}

static void list_display(node_t *list)
{
    printf("%s IN ORDER : ", list_is_ordered(list) ? "   " : "NOT");
    while (list) {
        printf("%d ", list->value);
        list = list->next;
    }
    printf("\n");
}

static inline void list_add_node_t(node_t **list, node_t *node_t)
{
    node_t->next = *list;
    *list = node_t;
}

static inline void list_concat(node_t **left, node_t *right)
{
    while (*left)
        left = &((*left)->next);
    *left = right;
}

void quicksort(node_t **list)
{
    if (!*list)
        return;

    node_t *pivot = *list;
    int value = pivot->value;
    node_t *p = pivot->next;
    pivot->next = NULL;

    node_t *left = NULL, *right = NULL;
    while (p) {
        node_t *n = p;
        p = p->next;
        list_add_node_t(n->value > value ? &right : &left, n);
    }

    quicksort(&left);
    quicksort(&right);

    node_t *result = NULL;
    list_concat(&result, left);
    list_concat(&result, pivot);
    list_concat(&result, right);
    *list = result;
}

int listSize(node_t *head)
{
    int count = 0;
    node_t *tmp = head;
    while (tmp) {
        count += 1;
        tmp = tmp->next;
    }
    return count;
}

void swap_node(int L, int R, node_t **list)
{
    int L_value, R_value;
    node_t *tmp = *list, *L_node, *R_node;

    for (int i = 0; i <= R; i++) {
        if (i == L) {
            L_value = tmp->value;
            L_node = tmp;
        }
        if (i == R) {
            R_value = tmp->value;
            R_node = tmp;
        }
        tmp = tmp->next;
    }
    L_node->value = R_value;
    R_node->value = L_value;
}

int get_node_value(node_t *n, int num)
{
    for (int i = 0; i < num; i++)
        n = n->next;
    return n->value;
}
void quicksort_iter(node_t **list)
{
#define MAX_LEVELS 300

    int piv, beg[MAX_LEVELS], end[MAX_LEVELS], i = 0, L, R, swap, elements;
    elements = listSize(*list);

    beg[0] = 0;
    end[0] = elements;
    while (i >= 0) {
        L = beg[i];
        R = end[i] - 1;
        if (L < R) {
            piv = get_node_value(*list, L);
            while (L < R) {
                while (get_node_value(*list, R) >= piv && L < R)
                    R--;
                if (L < R) {
                    // arr[L++] = arr[R];
                    swap_node(L, R, list);
                    L++;
                }
                while (get_node_value(*list, L) <= piv && L < R)
                    L++;
                if (L < R)
                    // arr[R--] = arr[L];//change array to linked list
                    swap_node(L, R, list);
                R--;
            }
            // arr[L] = piv;//change array to linked list
            beg[i + 1] = L + 1;
            end[i + 1] = end[i];
            end[i++] = L;
            if (end[i] - beg[i] > end[i - 1] - beg[i - 1]) {
                swap = beg[i];
                beg[i] = beg[i - 1];
                beg[i - 1] = swap;
                swap = end[i];
                end[i] = end[i - 1];
                end[i - 1] = swap;
            }
        } else {
            i--;
        }
    }
}

node_t *list_make_node_t(node_t *list, int value)
{
    node_t *n;
    n = malloc(sizeof(node_t));
    if (!n)
        return list;
    n->value = value;
    n->next = list;
    return n;
}

void list_free(node_t **list)
{
    node_t *tmp = *list;
    while ((*list)->next) {
        list = &((*list)->next);
        free(tmp);
        tmp = *list;
    }
}

int main(int argc, char **argv)
{
    size_t count = 20;

    node_t *list = NULL;
    srand(time(NULL));
    while (count--)
        list = list_make_node_t(list, rand() % 1024);

    list_display(list);
    quicksort_iter(&list);
    list_display(list);
    if (!list_is_ordered(list))
        return EXIT_FAILURE;

    list_free(&list);
    return EXIT_SUCCESS;
}
