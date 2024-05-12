#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
//#include <stdbool.h>

typedef enum { false, true } bool;

typedef enum
{
	ARRAY_ADD_SUCCESS,
	ARRAY_ADD_DUPLICATE,
	ARRAY_ADD_FAILED
} ArrayAddResult;

typedef enum
{
	ARRAY_REMOVE_SUCCESS,
	ARRAY_REMOVE_NOT_FOUND
} ArrayRemoveResult;

#define REMOVE_ELEMENT(TYPE, ARRAY, ARRAY_COUNT, VALUE, RESULT_PTR) do { \
    *(RESULT_PTR) = ARRAY_REMOVE_NOT_FOUND; \
    for (size_t i = 0; i < ARRAY_COUNT; i++) { \
        if (ARRAY[i] == VALUE) { \
            for (size_t j = i; j < ARRAY_COUNT - 1; j++) { \
                ARRAY[j] = ARRAY[j + 1]; \
            } \
            ARRAY_COUNT--; \
            if (ARRAY_COUNT > 0) { \
                TYPE* temp = (TYPE*)realloc(ARRAY, sizeof(TYPE) * ARRAY_COUNT); \
                if (temp != NULL) { \
                    ARRAY = temp; \
                } \
            } else { \
                free(ARRAY); \
                ARRAY = NULL; \
            } \
            *(RESULT_PTR) = ARRAY_REMOVE_SUCCESS; \
            break; /* Ensure we exit the loop after handling the found item */ \
        } \
    } \
} while(0)

#define REMOVE_ELEMENT_CUSTOM_COMP(TYPE, ARRAY, ARRAY_COUNT, VALUE, COMP_FUNC, RESULT_PTR) do { \
    *(RESULT_PTR) = ARRAY_REMOVE_NOT_FOUND; \
    for (size_t i = 0; i < ARRAY_COUNT; i++) { \
        if (COMP_FUNC(&ARRAY[i], &VALUE)) { \
            for (size_t j = i; j < ARRAY_COUNT - 1; j++) { \
                ARRAY[j] = ARRAY[j + 1]; \
            } \
            ARRAY_COUNT--; \
            if (ARRAY_COUNT > 0) { \
                TYPE* temp = (TYPE*)realloc(ARRAY, sizeof(TYPE) * ARRAY_COUNT); \
                if (temp != NULL) { \
                    ARRAY = temp; \
                } \
            } else { \
                free(ARRAY); \
                ARRAY = NULL; \
            } \
            *(RESULT_PTR) = ARRAY_REMOVE_SUCCESS; \
            break; /* Ensure we exit the loop after handling the found item */ \
        } \
    } \
} while(0)

#define ADD_ELEMENT(TYPE, ARRAY, ARRAY_COUNT, ELEMENT, RESULT_PTR) do { \
    *(RESULT_PTR) = ARRAY_ADD_FAILED; /* Assume failure until proven successful */ \
    TYPE* temp = (TYPE*)realloc(ARRAY, sizeof(TYPE) * (ARRAY_COUNT + 1)); \
    if (temp != NULL) { \
        ARRAY = temp; \
        ARRAY[ARRAY_COUNT] = ELEMENT; \
        ARRAY_COUNT++; \
        *(RESULT_PTR) = ARRAY_ADD_SUCCESS; \
    } \
} while(0)

//C# style foreach, item is a referenced pointer
#define ARRAY_FOREACH(type, item, array, count) for (type *item = (array), *end = (array) + (count); item != end; ++item)

#define ARRAY_FOREACH_PTR(type, item, array, count) for (type** item = (array), **end = (array) + (count); item != end; ++item)

void generalArrayFunction(void* array, size_t elementSize, size_t elementCount, void(*f)(void* element));

char* customStrdup(const char* str);
