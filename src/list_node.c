#include "list_node.h"

PNode createNode()
{
    PNode elem = (PNode)malloc(sizeof(struct ListNode));

    elem->value = getRandomNumber();
    elem->next = NULL;
    elem->prev = NULL;
    elem->is_occupied = ATOMIC_VAR_INIT(false);

    return elem;
}

PNode addNode(PNode prev)
{
    PNode elem = createNode();

    if (prev != NULL)
    {
        prev->next = elem;
        elem->prev = prev;
    }

    return elem;
}

void printNodes(PNode head)
{
    uint32_t inx = 1;
    PNode head_c = head;

    while (head_c != NULL)
    {        
        printf("%"PRIu32") Value is %"PRIu32, inx, head_c->value);
        printf("\n");

        head_c = head_c->next;
        ++inx;
    }
}
