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

int main()
{
    srand(time(NULL));

    uint32_t size;

    printf("Введите размер списка: ");
    scanf("%"SCNu32, &size);

    if (size == 0)
        return 0;

    // --------- Заполнение двусвязного списка
    struct ListNode* head = createNode();
    struct ListNode* head_free_backup = head;

    struct ListNode* tail = head;

    for (uint32_t i = 0; i < size - 1; ++i)
        tail = addNode(tail);
    // ---------

    printNodes(head);

    // --------- Подготовка и запуск потоков
    pthread_t one_thread, zero_thread;

    struct OperationReport one_report = { 0, 0 };
    struct OperationReport zero_report = { 0, 0 };

    struct OperationArgs one_args = { ONE_BIT, &one_report, tail, size };
    struct OperationArgs zero_args = { ZERO_BIT, &zero_report, head, size };

    initMutex();

    pthread_create(&zero_thread, NULL, getBitInformation, (void*)&zero_args);
    pthread_create(&one_thread, NULL, getBitInformation, (void*)&one_args);

    pthread_join(one_thread, NULL);
    pthread_join(zero_thread, NULL);

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

    freeNodes(head_free_backup);

    return 0;
}
