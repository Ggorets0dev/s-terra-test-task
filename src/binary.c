#include "binary.h"

void* getBitInformation(void* args)
{	
    struct OperationArgs* arg = (struct OperationArgs*)args;
    struct ListNode* current = arg->element;

    if (atomic_load(&free_cnt) >= arg->list_size || current == NULL || current->is_occupied)
        pthread_exit(NULL);
    else
        current->is_occupied = true;

    uint32_t bits_cnt = (arg->mode == ONE_BIT) ? countOneBits(current->value) : countOneBits(~(current->value));

    arg->report->elem_cnt++;
    arg->report->bit_cnt += bits_cnt;

    pthread_mutex_lock(&changing_element);

    if (arg->mode == ZERO_BIT && current->next != NULL)
    {
        current->next->prev = NULL;

        if (current->next->is_occupied)
            arg->element = NULL;
        else
            arg->element = current->next;
    }

    else if (arg->mode == ONE_BIT && current->prev != NULL)
    {
        current->prev->next = NULL;

        if (current->prev->is_occupied)
            arg->element = NULL;
         else
            arg->element = current->prev;
    }

    pthread_mutex_unlock(&changing_element);

    atomic_fetch_add(&proc_cnt, 1);
    atomic_fetch_add(&free_cnt, 1);

    free(current);

    getBitInformation((void*)arg);
}

uint32_t countOneBits(uint32_t value)
{
    uint32_t cnt = 0;

    while (value)
    {
        ++cnt;
        value &= value - 1;
    }

    return cnt;
}

void printReport(struct OperationReport* report)
{
    printf("Количество найденных битов: %"PRIu32, report->bit_cnt);
    printf("\n");

    printf("Количество обработанных элементов списка: %"PRIu32, report->elem_cnt);
    printf("\n");
}

inline void initMutex()
{
    pthread_mutex_init(&changing_element, NULL);

    proc_cnt = ATOMIC_VAR_INIT(0);
    free_cnt = ATOMIC_VAR_INIT(0);
}

inline void delMutex()
{
    pthread_mutex_destroy(&changing_element);

    printf("PROCESSED %lu \n", atomic_load(&proc_cnt));
    printf("FREED %lu \n", atomic_load(&free_cnt));
}
