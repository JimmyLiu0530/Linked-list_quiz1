#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

typedef struct __node {
    int value;
    struct __node *next;
} node_t;

void add_entry(node_t **head, int new_value)
{
    node_t **indirect = head;

    node_t *new_node = malloc(sizeof(node_t));
    new_node->value = new_value;
    new_node->next = NULL;

    assert(new_node);
    while (*indirect)
        indirect = &(*indirect)->next;
    *indirect = new_node;
}

node_t *find_entry(node_t *head, int value)
{
    node_t *current = head;
    for (; current && current->value != value; current = current->next)
        /* interate */;
    return current;
}

void remove_entry(node_t **head, node_t *entry)
{
    node_t **indirect = head;

    while ((*indirect) != entry)
        indirect = &(*indirect)->next;

    *indirect = entry->next;
    free(entry);
}

node_t *swap_pair(node_t *head)
{
    for (node_t **node = &head; *node && (*node)->next; node = &(*node)->next->next) {
        node_t *tmp = *node;
        *node = (*node)->next;
        tmp->next = (*node)->next;
        (*node)->next = tmp;
    }
    return head;
}

// swap_pair without updating the new head of linked list
void swap_pair_revised(node_t **head)
{
    for (node_t **node = head; *node && (*node)->next; node = &(*node)->next->next) {
        node_t *tmp = *node;
        *node = (*node)->next;
        tmp->next = (*node)->next;
        (*node)->next = tmp;
    }
}

node_t *reverse(node_t *head)
{
    node_t *cursor = NULL;
    while (head) {
        node_t *next = head->next;
        head->next = cursor;
        cursor = head;
        head = next;
    }
    return cursor;
}

// reverse the whole linked list without updating the new head
void reverse_revised(node_t **indirect)
{
    node_t *cursor = NULL;
    while (*indirect) {
        node_t *next = (*indirect)->next;
        (*indirect)->next = cursor;
        cursor = *indirect;
        *indirect = next;
    }
    *indirect = cursor;
}

// recursively reverse the whole linked list
node_t *rev_recursive(node_t *p)
{
    if(p->next == NULL)
    {
        return p;
    }
    node_t *head = rev_recursive(p->next);
    node_t *q = p->next;
    q->next = p;
    p->next = NULL;
    return head;
}

// this swap function is under the premise that
// 1 <= p <= q <= total number of node in the linked list
// and is used to swap pth and qth node in the linked list
void swap(node_t **head, int p, int q)
{
    // nothing to do if p,q are the same
    if(p == q)
        return;

    // search for pth node in the linked list
    node_t *prevP = NULL, *currP = *head;
    for(int i = p-1; i>0; i--)
    {
        prevP = currP;
        currP = currP->next;
    }

    // search for qth node in the linked list
    node_t *prevQ = NULL, *currQ = *head;
    for(int i = q-1; i>0; i--)
    {
        prevQ = currQ;
        currQ = currQ->next;
    }
    // if pth node is head of linked list, i.e. p==1, make qth node a new head
    if (p==1)
        *head = currQ;
    else
        prevP->next = currQ;

    // if q is 1, p must be 1 either, the process will return due to line7
    prevQ->next = currP;

    // swap next pointers
    node_t *tmp = currQ->next;
    currQ->next = currP->next;
    currP->next = tmp;
}

void Fisher_Yates_shuffle(node_t **indirect)
{
    // count how many nodes are in linked list
    int totalNum = 0;
    node_t *tmp = *indirect;
    while(tmp)
    {
        totalNum += 1;
        tmp = tmp->next;
    }

    srand(time(NULL));

    // start from the first node and randomly choose a number q s.t. p<=q<=totalNum
    for(int p = 1; p <= totalNum-1; p++)
    {
        int q = (rand() % (totalNum-p+1))+p;

        swap(indirect, p, q);
    }
}

void print_list(node_t *head)
{
    for (node_t *current = head; current; current = current->next)
        printf("%d ", current->value);
    printf("\n");
}

int main(int argc, char const *argv[])
{
    node_t *head = NULL;

    add_entry(&head, 72);
    add_entry(&head, 101);
    add_entry(&head, 108);
    add_entry(&head, 109);
    add_entry(&head, 110);
    add_entry(&head, 111);

    print_list(head);

    Fisher_Yates_shuffle(&head);
    print_list(head);

    node_t *entry = find_entry(head, 101);
    remove_entry(&head, entry);
    print_list(head);

    /*head = swap_pair(head);
    print_list(head);*/

    swap_pair_revised(&head);
    print_list(head);

    /*head = reverse(head);
    print_list(head);*/

    reverse_revised(&head);
    print_list(head);

    head = rev_recursive(head);
    print_list(head);

    return 0;
}
