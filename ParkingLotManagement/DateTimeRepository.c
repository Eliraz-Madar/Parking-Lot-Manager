#include "DateTimeRepository.h"

bool readDateTimeFromFile(DateTime* dateTime, const FileContext* fileContext)
{
	int day, month, year, hour, minute, second;
	if (!readIntFromFile(&day, fileContext))
		return false;

	if (!readIntFromFile(&month, fileContext))
		return false;

	if (!readIntFromFile(&year, fileContext))
		return false;

	if (!readIntFromFile(&hour, fileContext))
		return false;

	if (!readIntFromFile(&minute, fileContext))
		return false;

	if (!readIntFromFile(&second, fileContext))
		return false;

	*dateTime = initDateTime(day, month, year, hour, minute, second);
	return true;
}

bool writeDateTimeToFile(const DateTime* dateTime, const FileContext* fileContext)
{
	if (!writeIntToFile(dateTime->day, fileContext))
		return false;

	if (!writeIntToFile(dateTime->month, fileContext))
		return false;

	if (!writeIntToFile(dateTime->year, fileContext))
		return false;

	if (!writeIntToFile(dateTime->hour, fileContext))
		return false;

	if (!writeIntToFile(dateTime->minute, fileContext))
		return false;

	if (!writeIntToFile(dateTime->second, fileContext))
		return false;

	return true;
}
