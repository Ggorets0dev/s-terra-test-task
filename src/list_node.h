#ifndef LIST_NODE_H
#define LIST_NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "inttypes.h"
#include "random.h"

struct ListNode
{
    int32_t value;
    bool is_occupied;

    struct ListNode* prev;
    struct ListNode* next;
};

struct ListNode* createNode();

struct ListNode* addNode(struct ListNode* prev);

void printNodes(struct ListNode* head);

#endif // LIST_NODE_H
