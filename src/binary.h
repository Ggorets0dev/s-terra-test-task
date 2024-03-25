#ifndef BINARY_H
#define BINARY_H

#include <stdint.h>
#include <limits.h>
#include <stdio.h>
#include <pthread.h>
#include "list_node.h"

enum OperationMode
{
    ONE_BIT,
    ZERO_BIT
};

struct OperationReport
{
    uint64_t bit_cnt;
    uint32_t elem_cnt;
};

struct OperationArgs
{
    enum OperationMode mode;
    struct OperationReport* report;
    struct ListNode* element;
    uint32_t list_size;
};

static pthread_mutex_t changing_element;

static uint32_t proccessed_count = 0;

void initMutex();
void delMutex();

void* getBitInformation(void* args);

uint32_t countOneBits(uint32_t value);

uint32_t countZeroBits(uint32_t value);

void printReport(struct OperationReport* report);

#endif // BINARY_H
