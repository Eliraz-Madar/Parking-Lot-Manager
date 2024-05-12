#include "DateTime.h"
#include "time.h"

/// <summary>
/// Initializes the DateTime model.
/// Please note: This initializer does not check for correct format.
/// Use <see cref="isValidDateTime"/> or <see cref="isValidDateTimeFormat"/> to check date format.
/// </summary>
/// <returns>The initialized DateTime</returns>
DateTime initDateTime(int day, int month, int year, int hour, int minute, int second)
{
	DateTime dt;

	dt.day = day;
	dt.month = month;
	dt.year = year;
	dt.hour = hour;
	dt.minute = minute;
	dt.second = second;

	return dt;
}

DateTime getCurrentDateTime()
{
	time_t now = time(NULL);
	struct tm* tm_now = localtime(&now);

	const DateTime currentDateTime = initDateTime(tm_now->tm_mday, tm_now->tm_mon + 1, tm_now->tm_year + 1900,
		tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec);
	return currentDateTime;
}

bool isLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isValidDay(int year, int month, int day)
{
	int daysInMonth[] = { 31, 28 + isLeapYear(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	return day > 0 && day <= daysInMonth[month - 1];
}

bool isValidDateTime(const DateTime* dt)
{
	return isValidDateTimeFormat(dt->day, dt->month, dt->year, dt->hour, dt->minute, dt->second);
}

/// <summary>
/// Validates a given date and time format. ASSUMPTION: Year is not before 2000.
/// </summary>
bool isValidDateTimeFormat(int day, int month, int year, int hour, int minute, int second)
{
	if(year < 2000) return false; // Assuming the year is not before 2000
	if (month < 1 || month > 12) return false;
	if (day < 1 || !isValidDay(year, month, day)) return false;
	if (hour < 0 || hour > 23) return false;
	if (minute < 0 || minute > 59) return false;
	if (second < 0 || second > 59) return false;
	return true;
}

/// <summary>
/// Note: This function returns 0 if equals, and negative/positive values suggesting which is higher
/// </summary>
/// <returns>0=equal, dt1 &lt; dt2 ? -1 : 1</returns>
int compareDateTimes(const DateTime* dt1, const DateTime* dt2)
{
	// Compare by order:

	if (dt1->year != dt2->year) return dt1->year < dt2->year ? -1 : 1;

	if (dt1->month != dt2->month) return dt1->month < dt2->month ? -1 : 1;

	if (dt1->day != dt2->day) return dt1->day < dt2->day ? -1 : 1;

	if (dt1->hour != dt2->hour) return dt1->hour < dt2->hour ? -1 : 1;

	if (dt1->minute != dt2->minute) return dt1->minute < dt2->minute ? -1 : 1;

	if (dt1->second != dt2->second) return dt1->second < dt2->second ? -1 : 1;

	return 0; //Equal
}

bool isDateTimeBetweenTwoDateTimes(const DateTime* start, const DateTime* end, const DateTime* target)
{
	int compareWithStart = compareDateTimes(start, target);
	int compareWithEnd = compareDateTimes(target, end);

	return compareWithStart <= 0 && compareWithEnd <= 0;
}

long dateTimeToTotalMinutes(const DateTime* dt)
{
	long totalDays = 0;
	int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	// Add days for the years
	for (int y = 0; y < dt->year; y++)
	{
		totalDays += 365 + isLeapYear(y);
	}

	// Add days for the months
	for (int m = 1; m < dt->month; m++)
	{
		totalDays += daysInMonth[m - 1];
		// Adjust for February in leap years
		if (m == 2 && isLeapYear(dt->year)) totalDays += 1;
	}

	// Add remaining days
	totalDays += dt->day - 1; // Subtract 1 since day starts from 1

	// Convert total days to minutes and add time of day
	long totalMinutes = totalDays * 1440 + dt->hour * 60 + dt->minute;
	return totalMinutes;
}
