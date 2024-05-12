#pragma once

#include "General.h"

typedef void* Data;

// Node
typedef struct Node
{
	Data key;
	struct Node* next;
}Node;

// List
typedef struct
{
	Node* head;
}List;

/// <summary>
/// Defines a function pointer type for comparing two data items. The function should return true if the items are considered equal, otherwise false.
/// </summary>
/// <param name="Data">The first data item to compare.</param>
/// <param name="Data">The second data item to compare.</param>
/// <returns>True if the items are equal, false otherwise.</returns>
typedef bool (*CompareDataFunc)(Data, Data);

//#define LIST_FOREACH(item, list) for (Node* item = (list)->head; item != NULL; item = item->next)

/// <summary>
/// Iterates over each item in a linked list, providing a pointer to the current item of the specified type.
/// </summary>
/// <param name="itemType">The type of the items in the list.</param>
/// <param name="pItem">The pointer variable through which the current list item will be accessed.</param>
/// <param name="list">The list to iterate over.</param>
#define LIST_FOREACH(itemType, pItem, list) \
    for (Node* node = (list)->head; node != NULL; node = node->next) \
        for (itemType* pItem = (itemType*)node->key; pItem != NULL; pItem = NULL) // This macro cleverly utilizes an initialization-only nested for loop to declare and initialize the item pointer within the loop's scope.

/*** Function prototypes ***/

Node* initNode(Data data);

bool insertAtBeginning(List* list, Data data);

void deleteFromBeginning(List* list);

bool deleteFromList(List* list, Data data);

bool deleteFromListCustomCompare(List* list, Data data, CompareDataFunc cmp);

void freeList(List* list);
