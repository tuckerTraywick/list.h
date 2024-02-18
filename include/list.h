#ifndef LIST_H
#define LIST_H

#include <stddef.h>

// Represents a dynamic array that can grow and shrink at runtime.
struct List {
    size_t elementSize; // The size in bytes of one element.
    size_t capacity; // The number of elements allocated.
    size_t length; // The current number of elements.
    void *elements; // The buffer containing the elements.
};

// Returns a new list. The list must be destroy by `listDestroy()`.
struct List ListCreate(size_t elementSize, size_t capacity);

// Deallocates a list's elements and zeroes its memory. Be sure to destroy each element if needed
// before calling this function.
void ListDestroy(struct List *list);

// Returns a pointer to the element at `index`.
void *ListGet(struct List *list, size_t index);

// Copies `element` to the element at `index`.
void ListSet(struct List *list, size_t index, void *element);

// Swaps the elements at `indexA` and `indexB`.
void ListSwap(struct List *list, size_t indexA, size_t indexB);

// Inserts `element` at `index`.
void ListInsert(struct List *list, size_t index, void *element);

// Appends `element` to the end of the list.
void ListAppend(struct List *list, void *element);

// Removes the element at `index`. Be sure to destroy the element if needed before calling this
// function.
void ListRemove(struct List *list, size_t index);

#endif // LIST_H
