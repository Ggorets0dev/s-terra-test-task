#include "binary.h"

void* getBitInformation(void* args)
{	
    struct OperationArgs* arg = (struct OperationArgs*)args;    
    bool is_zero = arg->mode == ZERO_BIT;
    PNode current = is_zero ? head : tail;
    uint64_t bits_cnt;

    while (atomic_load(&free_cnt) < arg->list_size)
    {
        current = is_zero ? head : tail;

        if (current == NULL || current->is_occupied)
            break;

        // --------- Произвести подсчет элемента
        atomic_store(&current->is_occupied, true);

        bits_cnt = is_zero ? countOneBits(~current->value) : countOneBits(current->value);
        arg->report->bit_cnt += bits_cnt;
        arg->report->elem_cnt++;
        // ---------

        pthread_mutex_lock(&changes);

        // --------- Удалить ссылку на себя у элемента-кандидата
        if (is_zero && current->next != NULL)
            current->next->prev = NULL;
        if (!is_zero && current->prev != NULL)
            current->prev->next = NULL;
        // ---------

        // --------- Перенести указатель на элемент-кандидат
        if (is_zero)
            head = current->next;
        else
            tail = current->prev;

        if (head == tail)
        {
            if (is_zero)
                head = NULL;
            else
                tail = NULL;
        }
        // ---------

        pthread_mutex_unlock(&changes);

        atomic_fetch_add(&free_cnt, 1);
        free(current);
    }
}

uint64_t countOneBits(uint16_t value)
{
    uint64_t cnt = 0;

    while (value)
    {
        ++cnt;
        value &= value - 1;
    }

    return cnt;
}

void printReport(struct OperationReport* report)
{
    printf("Количество найденных битов: %"PRIu64, report->bit_cnt);
    printf("\n");

    printf("Количество обработанных элементов списка: %"PRIu32, report->elem_cnt);
    printf("\n");
}

inline void setBorders(PNode head_p, PNode tail_p)
{
    head = head_p;
    tail = tail_p;
}

inline void initMutex()
{
    pthread_mutex_init(&changes, NULL);
}

inline void delMutex()
{
    pthread_mutex_destroy(&changes);
}
