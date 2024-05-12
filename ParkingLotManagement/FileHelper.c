#include "FileHelper.h"

bool readUnsignedCharFromFile(unsigned char* value, const FileContext* fileContext)
{
	if (fileContext == NULL || value == NULL)
	{
		return false;
	}

	if (fileContext->isBinary)
	{
		return fread(value, sizeof(unsigned char), 1, fileContext->file) == 1;
	}
	else
	{
		int temp;
		if (fscanf(fileContext->file, "%d", &temp) == 1)
		{
			if (temp >= 0 && temp <= 255)
			{ // Ensure valid range for unsigned char
				*value = (unsigned char)temp;
				return true;
			}
		}
		return false;
	}
}

bool readDoubleFromFile(double* pVal, const FileContext* fileContext)
{
	if (fileContext->isBinary)
	{
		return fread(pVal, sizeof(double), 1, fileContext->file) == 1;
	}
	else
	{
		return fscanf(fileContext->file, "%lf\n", pVal) == 1;
	}
}

bool readCharsFromFile(char* arr, size_t size, const FileContext* fileContext)
{
	if (fileContext->isBinary)
	{
		return fread(arr, sizeof(char), size, fileContext->file) == size;
	}
	else
	{
		return fgets(arr, size, fileContext->file) != NULL;
	}
}

bool readBoolFromFile(bool* pVal, const FileContext* fileContext)
{
	if (fileContext->isBinary)
	{
		return fread(pVal, sizeof(bool), 1, fileContext->file) == 1;
	}
	else
	{
		int temp;
		if (fscanf(fileContext->file, "%d\n", &temp) == 1)
		{
			*pVal = temp != 0;
			return true;
		}
		return false;
	}
}

bool readUnsignedIntFromFile(unsigned* value, const FileContext* fileContext)
{
	if (fileContext->isBinary)
	{
		return fread(value, sizeof(unsigned), 1, fileContext->file) == 1;
	}
	else
	{
		return fscanf(fileContext->file, "%u\n", value) == 1;
	}
}

bool readIntFromFile(int* pVal, const FileContext* fileContext)
{
	if (fileContext->isBinary)
	{
		return fread(pVal, sizeof(int), 1, fileContext->file) == 1;
	}
	else
	{
		return fscanf(fileContext->file, "%d\n", pVal) == 1;
	}
}

bool readSizeTFromFile(size_t* pVal, const FileContext* fileContext)
{
	if (fileContext->isBinary)
	{
		return fread(pVal, sizeof(size_t), 1, fileContext->file) == 1;
	}
	else
	{
		return fscanf(fileContext->file, "%zu\n", pVal) == 1;
	}
}

bool readStringFromFile(char* str, int maxStrLength, const FileContext* fileContext)
{
	// Input validation
	if (str == NULL || fileContext == NULL || maxStrLength <= 0)
	{
		return false;
	}

	if (fileContext->isBinary)
	{
		size_t strLength;
		if (!readSizeTFromFile(&strLength, fileContext) || strLength >= (size_t)maxStrLength)
		{
			// Ensure there is room for null terminator in maxStrLength check
			return false;
		}

		if (!readCharsFromFile(str, (int)strLength, fileContext))
		{
			return false;
		}

		str[strLength] = '\0'; // Null terminate the string
		return true;
	}
	else
	{
		if (fgets(str, maxStrLength, fileContext->file) == NULL)
		{
			return false;
		}

		// Remove potential newline character
		size_t len = strlen(str);
		if (len > 0 && str[len - 1] == '\n')
		{
			str[len - 1] = '\0';
		}
		return true;
	}
}

bool writeUnsignedCharToFile(const FileContext* fileContext, unsigned char value)
{
	if (fileContext->isBinary)
	{
		return fwrite(&value, sizeof(unsigned char), 1, fileContext->file) == 1;
	}
	else
	{
		return fprintf(fileContext->file, "%d\n", value) > 0;
	}
}

bool writeDoubleToFile(double val, const FileContext* fileContext)
{
	if (fileContext->isBinary)
	{
		return fwrite(&val, sizeof(double), 1, fileContext->file) == 1;
	}
	else
	{
		return fprintf(fileContext->file, "%lf\n", val) > 0;
	}
}

bool writeCharsToFile(const char* arr, int size, const FileContext* fileContext)
{
	if (fileContext->isBinary)
	{
		return fwrite(arr, sizeof(char), size, fileContext->file) == size;
	}
	else
	{
		return fprintf(fileContext->file, "%s\n", arr) > 0;
	}
}

bool writeBoolToFile(bool pVal, const FileContext* fileContext)
{
	if (fileContext->isBinary)
	{
		return fwrite(&pVal, sizeof(bool), 1, fileContext->file) == 1;
	}
	else
	{
		return fprintf(fileContext->file, "%d\n", pVal) > 0;
	}
}

bool writeIntToFile(int val, const FileContext* fileContext)
{
	if (fileContext->isBinary)
	{
		return fwrite(&val, sizeof(int), 1, fileContext->file) == 1;
	}
	else
	{
		return fprintf(fileContext->file, "%d\n", val) > 0;
	}
}

bool writeSizeTToFile(size_t val, const FileContext* fileContext)
{
	if (fileContext->isBinary)
	{
		return fwrite(&val, sizeof(size_t), 1, fileContext->file) == 1;
	}
	else
	{
		return fprintf(fileContext->file, "%zu\n", val) > 0;
	}
}

bool writeStringToFile(const char* str, const FileContext* fileContext)
{
	// Input validation
	if (str == NULL || fileContext == NULL)
	{
		return false;
	}

	if (fileContext->isBinary)
	{
		const size_t strLength = strlen(str);
		if (strLength > INT_MAX)
		{
			return false;
		}

		if (!writeSizeTToFile(strLength, fileContext))
		{
			return false;
		}

		return writeCharsToFile(str, (int)strLength, fileContext); // Cast is now checked for safety
	}
	else
	{
		return fprintf(fileContext->file, "%s\n", str) > 0;
	}
}

bool writeUnsignedIntToFile(const FileContext* fileContext, unsigned value)
{
	if (fileContext->isBinary)
	{
		return fwrite(&value, sizeof(unsigned), 1, fileContext->file) == 1;
	}
	else
	{
		return fprintf(fileContext->file, "%u\n", value) > 0;
	}
}

bool writeUnsignedLongLongToFile(const FileContext* fileContext, unsigned long long value)
{
		if (fileContext->isBinary)
	{
		return fwrite(&value, sizeof(unsigned long long), 1, fileContext->file) == 1;
	}
	else
	{
		return fprintf(fileContext->file, "%llu\n", value) > 0;
	}
}

bool readUnsignedLongLongFromFile(unsigned long long* value, const FileContext* fileContext)
{
	if (fileContext->isBinary)
	{
		return fread(value, sizeof(unsigned long long), 1, fileContext->file) == 1;
	}
	else
	{
		return fscanf(fileContext->file, "%llu\n", value) == 1;
	}
}
