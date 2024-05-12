#pragma once
#include "General.h"

typedef struct {
    FILE* file;
    bool isBinary;
} FileContext;

// Read functions
bool readUnsignedCharFromFile(unsigned char* value, const FileContext* fileContext);
bool readDoubleFromFile(double* pVal, const FileContext* fileContext);
bool readCharsFromFile(char* arr, size_t size, const FileContext* fileContext);
bool readBoolFromFile(bool* pVal, const FileContext* fileContext);
bool readUnsignedIntFromFile(unsigned int* value, const FileContext* fileContext);
bool readUnsignedLongLongFromFile(unsigned long long* value, const FileContext* fileContext);
bool readIntFromFile(int* pVal, const FileContext* fileContext);
bool readSizeTFromFile(size_t* pVal, const FileContext* fileContext);
bool readStringFromFile(char* str, int maxStrLength, const FileContext* fileContext);

// Write functions
bool writeUnsignedCharToFile(const FileContext* fileContext, unsigned char value);
bool writeDoubleToFile(double val, const FileContext* fileContext);
bool writeCharsToFile(const char* arr, int size, const FileContext* fileContext);
bool writeBoolToFile(bool pVal, const FileContext* fileContext);
bool writeUnsignedIntToFile(const FileContext* fileContext, unsigned int value);
bool writeUnsignedLongLongToFile(const FileContext* fileContext, unsigned long long value);
bool writeIntToFile(int val, const FileContext* fileContext);
bool writeSizeTToFile(size_t val, const FileContext* fileContext);
bool writeStringToFile(const char* str, const FileContext* fileContext);
