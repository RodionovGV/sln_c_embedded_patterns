#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "SystemTime.h"
#include "TimeObserver.h"

// Структура узла списка
struct ListNode {
    TimeObserver item;
    struct ListNode* next;
};

typedef struct ListNode TListNode;

// Глобальный список (головной узел)
static TListNode listObservers = { 0 };

static void appendToList(const TimeObserver* observer) {
    TListNode* pnew;
    TListNode* scan = &listObservers;

    // Если список пуст
    if (scan->item.instance == NULL && scan->next == NULL) {
        listObservers.item = *observer;
        listObservers.next = NULL;
        return;
    }

    // Ищем конец списка
    while (scan->next != NULL) {
        scan = scan->next;
    }

    // Создаём новый узел
    pnew = (TListNode*)malloc(sizeof(TListNode));
    if (pnew == NULL) {
        exit(1);
    }

    pnew->item = *observer;
    pnew->next = NULL;
    scan->next = pnew;
}

static void removeFromList(const TimeObserver* observer) {
    TListNode* current = &listObservers;
    TListNode* prev = NULL;
    TListNode* toDelete = NULL;

    // Особый случай: первый элемент
    if (current->item.instance == observer->instance) {
        if (current->next != NULL) {
            // Копируем следующий узел в первый
            TListNode* nextNode = current->next;
            current->item = nextNode->item;
            current->next = nextNode->next;
            free(nextNode);
        }
        else {
            // Список с одним элементом - просто зануляем
            memset(&current->item, 0, sizeof(TimeObserver));
        }
        return;
    }

    // Поиск элемента для удаления
    prev = current;
    current = current->next;

    while (current != NULL) {
        if (current->item.instance == observer->instance) {
            toDelete = current;
            prev->next = current->next;
            free(toDelete);
            return;
        }
        prev = current;
        current = current->next;
    }
}

static int isNotifying = 0;

void updateDataObservers(SystemTime* currentTime) {
    struct ListNode* node = listObservers.next;

    isNotifying = 1;

    while (node != NULL) {
        TimeObserver* observer = &node->item;
        if (observer->notification != NULL) {
            observer->notification(observer->instance, currentTime);
        }
        node = node->next;
    }

    isNotifying = 0;
}

void attach(const TimeObserver* observer) {
    assert(0 == isNotifying);
    assert(NULL != observer);
    assert(NULL != observer->instance);
    assert(NULL != observer->notification);

    appendToList(observer);
}

void detach(const TimeObserver* observer) {
    assert(0 == isNotifying);
    assert(NULL != observer);

    removeFromList(observer);
}