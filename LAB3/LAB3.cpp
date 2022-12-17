#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include "time.h"
#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"

#pragma warning(suppress : 4996)

struct Unit
{
    int data;
    Unit* next;
    Unit* prev;
    int priority;
}; /*Структура единичного экземпляра элемента с
    указателями на следующий и предыдущий, и сами данные с номером приоритета*/


struct Queue
{
    Unit* head;
    Unit* tail;

}; /*Структура очереди, состоящая из первого(головы) и последнего(хвоста), которые
    содержат элементы структуры типа Unit, находящиеся в начале и конце очереди соответственно*/

static Unit* UnitInst(int dat, int prior) {
    Unit* Units = (Unit*)malloc(sizeof(Unit)); // Создаём элемент типа Unit, выделяем память
 

    Units->data = dat;                   //
    Units->priority = prior;             //           Здесь идёт заполнение элемента данными, но
    Units->next = NULL;                  //               указатели на следующий и предыдущий 
    Units->prev = NULL;                  //    остаются пустыми, так как положение в очереди задаётся потом
                        
    return Units;    
}

Queue* NewQueue(void)
{
    Queue* Queue_unit = (Queue*)malloc(sizeof(Queue)); // Создаём очередь
    

    Queue_unit->head = NULL; 
    Queue_unit->tail = NULL; 

    return Queue_unit;
}

int QueueIsEmpty(Queue* Qunit) { // Проверка очереди на заполненность, если она пуста(NULL), то возвращаем true
    return (Qunit->head == NULL);
}

void PushInQueue(Queue* Qunit_psh, int dat_psh, int prior_psh) {
    Unit* Units = UnitInst(dat_psh, prior_psh);

    if (QueueIsEmpty(Qunit_psh)) {
        Qunit_psh->head = Qunit_psh->tail = Units; //Если очередь пуста, заполняем её новоиспеченным элементом
    }
    else {
        Unit* last = Qunit_psh->tail; //Берём в работу последний элемент очереди

        while (last && last->priority > prior_psh) {
            last = last->prev; // Если приоритет добавляемого элемента меньше чем у последнего, то ставим его в конец
        }
        while (last && last->priority == prior_psh && last->data < dat_psh) //Если приоритет добавляемого равен последнему, то сравниваем значения данных, и решаем ставить ли его в конец
            last = last->prev;

        if (!last) { //Если элемент вышел с наивысшим приоритетом, то вставляем его вместо головы очереди
            Units->next = Qunit_psh->head;
            Qunit_psh->head->prev = Units;
            Qunit_psh->head = Units;
        }
        else if (last == Qunit_psh->tail) { //Если вышел с наименьшим, то вставляем его вместо хвоста очереди
            Units->prev = Qunit_psh->tail;
            Qunit_psh->tail->next = Units;
            Qunit_psh->tail = Units;
        }
        else { //Элемент между наивысшим и наименьшим приоритетами, значит
            Units->prev = last; 
            Units->next = last->next;
            last->next->prev = Units;
            last->next = Units;
        }
    }
}

unsigned QueueSize(Queue* Qunit) { 
    unsigned size = 0;
    Unit* Units;

    for (Units = Qunit->head; Units; Units = Units->next)
        ++size;

    return size;
}

void QueuePrint(Queue* Qunit) {
    Unit* last = Qunit->head;
    printf("------------------------------------ \n");

    while (last && last != Qunit->tail)
    {
        
        printf("%d ", (int)last->data);
        printf("%d \n", (int)last->priority);

        last = last->next;
    }
    printf("%d ", (int)Qunit->tail->data);
    printf("%d \n", (int)Qunit->tail->priority);
    printf("------------------------------------");


}

int main()
{
    int d, pr;
    Queue* Q = NewQueue(); //создание очереди
  
    while (true)
    {
        printf("\n   The Menu \n");
        printf("1. Add element \n");
        printf("2. Overview \n");       
        short n;
        scanf("%d",&n);
        switch (n)
        {
        case 1:
        {
            printf("Enter data(int): \n");
            scanf("%d", &d);
            printf("Enter it's priority: \n");
            scanf("%d", &pr);
            PushInQueue(Q, d, pr);
            break;
        }
        case 2:
        {
            if (QueueSize(Q) == 0)
            {
                printf("Queue is empty! \n");
                break;
            }
            QueuePrint(Q);
            break;
        }               
        default:
            printf("Wrong command! \n");
            break;
        }
    }   
    return 0;
}