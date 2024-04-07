#ifndef LIST_NODE_H
#define LIST_NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdatomic.h>
#include "inttypes.h"
#include "typedefs.h"
#include "random.h"

struct ListNode
{
    int16_t value;
    atomic_bool is_occupied;

    PNode prev;
    PNode next;
};

PNode createNode();

PNode addNode(PNode prev);

void printNodes(PNode head);

#endif // LIST_NODE_H
