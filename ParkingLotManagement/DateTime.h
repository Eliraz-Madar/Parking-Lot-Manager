#pragma once
#include "general.h"

typedef struct
{
	int year;
    int month;  // 1 to 12
    int day;    // 1 to 31 depending on month
    int hour;   // 0 to 23
    int minute; // 0 to 59
    int second; // 0 to 59
} DateTime;

DateTime initDateTime(int day, int month, int year, int hour, int minute, int second);

DateTime getCurrentDateTime();

bool isValidDateTime(const DateTime* dt);

bool isValidDateTimeFormat(int day, int month, int year, int hour, int minute, int second);

int compareDateTimes(const DateTime* dt1, const DateTime* dt2);

bool isDateTimeBetweenTwoDateTimes(const DateTime* start, const DateTime* end, const DateTime* target);

long dateTimeToTotalMinutes(const DateTime* dt);
