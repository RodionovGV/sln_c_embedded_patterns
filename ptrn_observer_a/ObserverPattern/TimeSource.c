#include "TimeSubject.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct ListNode {
    TimeObserver item;
    struct ListNode* next;
};

typedef struct ListNode TListNode;

TListNode listObservers = {0};
static SystemTime currentTime;

/* Local helper functions for managing the linked-list
  (implementation omitted). */
static void appendToList(const TimeObserver* observer) {
    /* Append a copy of the observer to the linked-list. */
    TListNode *pnew;
    TListNode *scan = &listObservers;

    if (scan->item.instance == NULL) {
        listObservers.item = *observer;
        listObservers.next = NULL;
    } else {
        /// Происходит динамическое выделение памяти
        pnew = (TListNode *) malloc(sizeof (pnew));
        if (pnew == NULL) {
            exit(1);
        }
        pnew->item = *observer;
        pnew->next = NULL;
        while (scan->next != NULL) {
            scan = scan->next;
        }
        scan->next = pnew;
    }
}

static void removeFromList(const TimeObserver* observer) {
    /*
     1. Первый элемент особенный. Его проверяем. Если следующего элемента нет,то зануляем и всё.
     2. Если есть второй элемент,то присваиваем следующий элемент началу.
     3. Если элемент не первый. Перебираем все элементы списка.
     4. Когда следующий элемент нужный, сохраняем текущий. Берём следующий элемент для искомого и присваиваем его следующим текущему. 
     5. Удаляем элемент найденный элемент.    
     */
    /* Identify the observer in the linked-list and
       remove that node. */
    TListNode *pdel;
    TListNode *list = &listObservers;
    do {
        if (list->item.instance == observer) {
            if (list->next != NULL) {
                memcpy((void *) list, (void *) list->next, sizeof (list));
                free(list->next);
            }
        } else {
            while (list->next != NULL) {
                if (list->next->item.instance == observer) {
                    pdel = list->next;
                    list->next = pdel->next->next;
                    free(pdel);
                    break;
                }
                list = list->next;
            }
        }

    } while (list->next != NULL);

    //while (list->next != NULL) {
    //    if (list->item.instance == observer) {
    //        list->item = list->next;
    //    }
    //}
}

/*
 Dummy stubs for the invoked functions:
 */
static SystemTime calculateNewTime(void) {
    /* Time will pass slowly in this watch... */
    SystemTime newTime = {42};

    return newTime;
}

/* See Listing 8 and the related discussion:
   Checking Subject constraints with assertions.
 */
static int isNotifying = 0;

/* Implementation of the TimeSubject interface. */
void attach(const TimeObserver* observer) {
    assert(0 == isNotifying);
    assert(NULL != observer);
    appendToList(observer);
}

void detach(const TimeObserver* observer) {
    assert(0 == isNotifying);
    assert(NULL != observer);
    removeFromList(observer);
}

/* Implementation of the original responsibility of the
   TimeSource (code for initialization, etc omitted). */
static void msTick() {
    //struct ListNode* node = observers.next;
    struct ListNode* node = &listObservers;
    /* Invoke a function encapsulating the knowledge
       about time representation. */
    currentTime = calculateNewTime();

    /* Ensure that no changes are done to the
       subject during notification. */
    isNotifying = 1;

    /* Walk through the linked-list and notify every 
       observer that another millisecond passed.\
     */
    while (NULL != node) {
        TimeObserver* observer = &node->item;
        observer->notification(observer->instance, &currentTime);
        node = node->next;
    }
    /* All observers notified, allow changes again. */
    isNotifying = 0;
}

void stepTime() {
    msTick();
}
