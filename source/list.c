#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

// Resizes a list to best fit its length.
static void ListRealloc(struct List *list) {
    if (list->length == list->capacity) {
        list->capacity *= 2;
    } else if (list->length < list->capacity/2) {
        list->capacity /= 2;
    }
    void *newElements = realloc(list->elements, list->elementSize*list->capacity);
    // TODO: Handle failed `realloc()`.
    assert(newElements && "`realloc()` failed.");
    list->elements = newElements;
}

struct List ListCreate(size_t elementSize, size_t capacity) {
    void *elements = malloc(elementSize*capacity);
    // TODO: Handle failed `malloc()`.
    assert(elements && "`malloc()` failed.");
    return (struct List){
        .elementSize = elementSize,
        .capacity = capacity,
        .length = 0,
        .elements = elements,
    };
}

void ListDestroy(struct List *list) {
    assert(list);

    free(list->elements);
    *list = (struct List){0};
}

void *ListGet(struct List *list, size_t index) {
    assert(list);
    assert(index < list->length && "Index out of bounds.");

    return (char*)list->elements + list->elementSize*index;
}

void ListSet(struct List *list, size_t index, void *element) {
    assert(list);
    assert(element);
    assert(index < list->length && "Index out of bounds.");

    memcpy((char*)list->elements + list->elementSize*index, element, list->elementSize);
}

void ListSwap(struct List *list, size_t indexA, size_t indexB) {
    assert(list);
    assert(indexA < list->length && "`indexA` out of bounds.");
    assert(indexB < list->length && "`indexB` out of bounds.");

    // Equivalent to: `temp = list[indexA]; list[indexA] = list[indexB]; list[indexB] = temp;`
    void *temp = malloc(list->elementSize);
    // TODO: Handle failed `malloc()`.
    assert(temp && "`malloc()` failed.");
    memcpy(temp, ListGet(list, indexA), list->elementSize);
    memcpy(ListGet(list, indexA), ListGet(list, indexB), list->elementSize);
    memcpy(ListGet(list, indexB), temp, list->elementSize);
}

void ListInsert(struct List *list, size_t index, void *element) {
    assert(list);
    assert(element);
    assert(index <= list->length && "Index out of bounds.");
    assert(list->length <= list->capacity && "Length incremented too much.");

    ListRealloc(list);
    // Shift the elements starting at `index` one to the right to make room for the new element.
    memmove(
        (char*)list->elements + list->elementSize*(index + 1),
        (char*)list->elements + list->elementSize*index,
        list->elementSize*(list->length - index)
    );
    memcpy((char*)list->elements + list->elementSize*index, element, list->elementSize);
    ++list->length;
}

void ListAppend(struct List *list, void *element) {
    assert(list);
    assert(element);

    ListRealloc(list);
    memcpy((char*)list->elements + list->elementSize*list->length, element, list->elementSize);
    ++list->length;
}

void ListRemove(struct List *list, size_t index) {
    assert(list);
    assert(index < list->length && "Index out of bounds.");

    // Shift the elements starting at `index` one to the left.
    memmove(
        (char*)list->elements + list->elementSize*index,
        (char*)list->elements + list->elementSize*(index + 1),
        list->elementSize*(list->length - index)
    );
    --list->length;
    ListRealloc(list);
}
