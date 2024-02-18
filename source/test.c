#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "list.h"

void testListCreateCase(size_t elementSize, size_t capacity) {
    struct List list = ListCreate(elementSize, capacity);
    assert(list.elementSize == elementSize);
    assert(list.capacity == capacity);
    assert(list.length == 0);
    ListDestroy(&list);
}

void testListCreate(void) {
    for (size_t i = 0; i < 10; ++i) {
        testListCreateCase(i, 10);
    }

    for (size_t i = 0; i < 10; ++i) {
        testListCreateCase(sizeof (int), i);
    }
}

void testListDestroyCase(size_t elementSize, size_t capacity) {
    struct List list = ListCreate(elementSize, capacity);
    ListDestroy(&list);
    assert(list.elementSize == 0);
    assert(list.capacity == 0);
    assert(list.length == 0);
    assert(list.elements == NULL);
}

void testListDestroy(void) {
    for (size_t i = 0; i < 10; ++i) {
        testListDestroyCase(i, 10);
    }

    for (size_t i = 0; i < 10; ++i) {
        testListDestroyCase(sizeof (int), i);
    }
}

void testListGetAndSet(void) {
    struct List list = ListCreate(sizeof (size_t), 100);
    list.length = 100;
    for (size_t i = 0; i < 100; ++i) {
        ListSet(&list, i, &i);
        assert(*(size_t*)ListGet(&list, i) == i);
    }
    ListDestroy(&list);
}

void testListSwap(void) {
    struct List list = ListCreate(sizeof (size_t), 100);
    for (size_t i = 0; i < list.length; ++i) {
        size_t indexA = rand()%(list.length - 1);
        size_t indexB = rand()%(list.length - 1);
        size_t a = *(size_t*)ListGet(&list, indexA);
        size_t b = *(size_t*)ListGet(&list, indexB);
        ListSwap(&list, a, b);
        assert(*(size_t*)ListGet(&list, indexA) == b);
        assert(*(size_t*)ListGet(&list, indexB) == a);
    }
    ListDestroy(&list);
}

void testListInsertCase(struct List *list, size_t index, size_t element) {
    size_t oldLength = list->length;
    ListInsert(list, index, &element);
    assert(*(size_t*)ListGet(list, index) == element);
    assert(list->length == oldLength + 1);
    assert(list->capacity >= list->length);
}

void testListInsert(void) {
    struct List list = ListCreate(sizeof (size_t), 100);
    for (size_t i = 0; i < 100; ++i) {
        ListAppend(&list, &i);
    }

    for (size_t i = 0; i < 50; ++i) {
        size_t index = rand()%(list.length - 1);
        testListInsertCase(&list, index, i);
    }

    testListInsertCase(&list, 0, 123);
    testListInsertCase(&list, list.length, 456);

    ListDestroy(&list);
}

void testListAppendCase(struct List *list, size_t index, size_t element) {
    size_t oldLength = list->length;
    ListAppend(list, &element);
    assert(*(size_t*)ListGet(list, index) == element);
    assert(list->length == oldLength + 1);
    assert(list->capacity >= list->length);
}

void testListAppend(void) {
    struct List list = ListCreate(sizeof (size_t), 100);
    testListAppendCase(&list, 0, 123);
    for (size_t i = 0; i < 100; ++i) {
        testListAppendCase(&list, i, i);
    }

    for (size_t i = 0; i < 100; ++i) {
        testListAppendCase(&list, i, i);
    }

    ListDestroy(&list);
}

void testListRemoveCase(struct List *list, size_t index) {
    size_t oldLength = list->length;
    ListRemove(list, index);
    assert(list->length == oldLength - 1);
    assert(list->capacity >= list->length);
}

void testListRemove(void) {
    struct List list = ListCreate(sizeof (size_t), 100);
    for (size_t i = 0; i < 100; ++i) {
        ListAppend(&list, &i);
    }

    testListRemoveCase(&list, 0);
    testListRemoveCase(&list, list.length - 1);
    for (size_t i = 0; i < 50; ++i) {
        size_t index = rand()%(list.length - 1);
        testListRemoveCase(&list, index);
    }
    ListDestroy(&list);
}

int main(void) {
    srand(time(NULL));

    testListCreate();
    testListDestroy();
    testListGetAndSet();
    testListSwap();
    testListInsert();
    testListRemove();

    puts("Tests passed.");
    return 0;
}
