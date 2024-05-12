#include "List.h"

void initList(List* list)
{
    list->head = NULL;
}

// Function to create a new Node
Node* initNode(Data data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }

    newNode->key = data;
    newNode->next = NULL;

    return newNode;
}

// Function to insert at the beginning of the list
bool insertAtBeginning(List* list, Data data)
{
    Node* newNode = initNode(data);

    if (newNode == NULL)
    {
        return false;
    }
    
    newNode->next = list->head;
    list->head = newNode;

    return true;
}

// Function to delete the first element of the list
void deleteFromBeginning(List* list)
{
    if (list->head != NULL)
    {
        Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
    }
}

bool deleteFromList(List* list, Data data)
{
    if (list == NULL || list->head == NULL)
    {
        return false; // List is empty or not valid.
    }

    Node* current = list->head;
    Node* prev = NULL;

    while (current != NULL)
    {
        if (current->key == data)
        { // Direct comparison, adjust as necessary for complex types.
            if (prev == NULL)
            {
                // Removing the head of the list.
                list->head = current->next;
            }
            else
            {
                // Removing a non-head node.
                prev->next = current->next;
            }
            free(current); // Free the removed node.
            return true; // Node removed successfully.
        }
        prev = current;
        current = current->next;
    }

    return false; // Data not found in the list.
}

bool deleteFromListCustomCompare(List* list, Data data, CompareDataFunc cmp)
{
    if (list == NULL || list->head == NULL || cmp == NULL)
    {
        return false; // List is empty, not valid, or no comparison function provided.
    }

    Node* current = list->head;
    Node* prev = NULL;

    while (current != NULL)
    {
        if (cmp(current->key, data))
        { // Use the custom comparison function.
            if (prev == NULL)
            {
                // Removing the head of the list.
                list->head = current->next;
            }
            else
            {
                // Removing a non-head node.
                prev->next = current->next;
            }
            free(current); // Free the removed node.
            return true; // Node removed successfully.
        }
        prev = current;
        current = current->next;
    }

    return false; // Data not found in the list, according to the comparison function.
}

// Function to free the entire list
void freeList(List* list)
{
    Node* current = list->head;
    while (current != NULL)
    {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    list->head = NULL;
}
