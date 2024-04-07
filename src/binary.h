#ifndef BINARY_H
#define BINARY_H

#include <stdint.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdatomic.h>
#include "list_node.h"
#include "typedefs.h"

enum OperationMode
{
    ZERO_BIT,
    ONE_BIT
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
};

static pthread_mutex_t changes;
static atomic_uint free_cnt = ATOMIC_VAR_INIT(0);
static PNode head = NULL;
static PNode tail = NULL;

void initMutex();
void delMutex();
void setBorders(PNode head_p, PNode tail_p);

void* getBitInformation(void* args);

uint64_t countOneBits(uint16_t value);

void printReport(struct OperationReport* report);

#endif // BINARY_H
