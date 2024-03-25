#include "binary.h"

void* getBitInformation(void* args)
{
    struct OperationArgs* arg = (struct OperationArgs*)args;

    pthread_mutex_lock(&changing_element);

    if (arg->element == NULL || proccessed_count >= arg->list_size)
    {
        pthread_mutex_unlock(&changing_element);
        pthread_exit(NULL);
    }
    else
    {
        ++proccessed_count;
        pthread_mutex_unlock(&changing_element);
    }

    if (arg->mode == ZERO_BIT)
    {
        arg->report->bit_cnt += countZeroBits(arg->element->value);
        arg->report->elem_cnt++;

        arg->element = arg->element->next;
    }

    else if (arg->mode == ONE_BIT)
    {
        arg->report->bit_cnt += countOneBits(arg->element->value);
        arg->report->elem_cnt++;

        arg->element = arg->element->prev;
    }

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

uint32_t countZeroBits(uint32_t value)
{
    uint32_t final_cnt = 0;
    uint32_t temp_cnt = 0;

    while (value)
    {
        if (value & 1)
        {
            final_cnt += temp_cnt;
            temp_cnt = 0;
        }

        else
        {
            ++temp_cnt;
        }

        value >>= 1;
    }

    return final_cnt;
}

void printReport(struct OperationReport* report)
{
    printf("Количество найденных битов: %"PRIu32, report->bit_cnt);
    printf("\n");

    printf("Количество обработанных элементов списка: %"PRIu32, report->elem_cnt);
    printf("\n");
}

void initMutex()
{
    pthread_mutex_init(&changing_element, NULL);
}

void delMutex()
{
    pthread_mutex_destroy(&changing_element);
}
