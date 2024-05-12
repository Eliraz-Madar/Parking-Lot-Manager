#include "General.h"

void generalArrayFunction(void* array, size_t elementSize, size_t elementCount, void(*f)(void* element))
{
	for (size_t i = 0; i < elementCount; i++)
	{
		void* currentElement = (char*)array + (i * elementSize);

		f(currentElement);
	}
}

/// <summary>
/// Creates a duplicate of the given string by dynamically allocating memory for the copy and then copying the input string into this new memory space.
/// </summary>
/// <param name="str">The input string to be duplicated. If NULL, the function returns NULL.</param>
/// <returns>A pointer to the newly allocated and copied string, or NULL if memory allocation fails.</returns>
char* customStrdup(const char* str)
{
    if (str == NULL)
    {
        return NULL;
    }

    char* duplicate = (char*)malloc(strlen(str) + 1); // +1 for the null terminator.
    if (duplicate == NULL)
    {
        return NULL; // Memory allocation failed.
    }

    strcpy(duplicate, str); // Consider using strncpy or memcpy for safer copying.

    return duplicate;
}

