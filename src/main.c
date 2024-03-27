#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#include "random.h"
#include "list_node.h"
#include "binary.h"

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        fprintf(stderr, "В аргументах командной строки не указан размер списка\n");
        return 1;
    }

    srand(time(NULL));

    uint32_t size;

    if (sscanf(argv[1], "%"SCNu32, &size) != 1)
    {
        fprintf(stderr, "Не удалось преобразовать аргумент к целочисленному типу\n");
        return 1;
    }

    if (size == 0)
        return 0;

    // --------- Заполнение двусвязного списка
    struct ListNode* head = NULL;
    struct ListNode* tail = NULL;

    for (uint32_t i = 0; i < size; ++i)
    {
        if (i == 0)
        {
            head = addNode(NULL);
            tail = head;
        }
        else
        {
            tail = addNode(tail);
        }
    }
    // ---------

    printNodes(head);

    // --------- Подготовка и запуск потоков
    pthread_t one_thread, zero_thread;

    struct OperationReport one_report = { 0, 0 };
    struct OperationReport zero_report = { 0, 0 };

    struct OperationArgs one_args = { ONE_BIT, &one_report, tail, size };
    struct OperationArgs zero_args = { ZERO_BIT, &zero_report, head, size };

    initMutex();

    int status;

    status = pthread_create(&zero_thread, NULL, getBitInformation, (void*)&zero_args);

    if (status != 0)
    {
        fprintf(stderr, "Ошибка при создании потока для чтения нулевых битов\n");
        return 1;
    }

    status = pthread_create(&one_thread, NULL, getBitInformation, (void*)&one_args);

    if (status != 0)
    {
        fprintf(stderr, "Ошибка при создании потока для чтения единичных битов\n");
        return 1;
    }

    status = pthread_join(one_thread, NULL);

    if (status != 0)
    {
        fprintf(stderr, "Не удалось дождаться завершения потока для подсчета единичных битов\n");
        return 1;
    }

    status = pthread_join(zero_thread, NULL);

    if (status != 0)
    {
        fprintf(stderr, "Не удалось дождаться завершения потока для подсчета нулевых битов\n");
        return 1;
    }

    delMutex();
    // ---------

    // --------- Просмотр результатов
    printf("\n");

    printf("Результаты подсчета единичных битов: \n");
    printReport(&one_report);

    printf("\n");

    printf("Результаты подсчета нулевых битов: \n");
    printReport(&zero_report);
    // ---------

    return 0;
}
