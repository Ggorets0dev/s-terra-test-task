#include "list_node.h"

struct ListNode* createNode()
{
    struct ListNode* elem = (struct ListNode*)malloc(sizeof(struct ListNode));

    elem->value = getRandomNumber();
    elem->next = NULL;
    elem->prev = NULL;
    elem->is_occupied = false;

    return elem;
}

struct ListNode* addNode(struct ListNode* prev)
{
    struct ListNode* elem = createNode();

    if (prev != NULL)
    {
        prev->next = elem;
        elem->prev = prev;
    }

    return elem;
}

void printNodes(struct ListNode* head)
{
    uint32_t inx = 1;
    struct ListNode* head_c = head;

    while (head_c != NULL)
    {
        printf("%"PRIu32") Value is %"PRIu32, inx, head_c->value);
        printf("\n");

        head_c = head_c->next;
        ++inx;
    }
}
