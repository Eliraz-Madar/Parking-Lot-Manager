#include "DateTimeView.h"
#include "GeneralView.h"
#include <stdio.h>

// Function to create a DateTime from user input
DateTime createDateTimeUI()
{
	const bool useCurrentTime = getBooleanValueUI("Use current date and time?");

    if(useCurrentTime)
	{
		return getCurrentDateTime();
	}

    int day, month, year, hour, minute, second;
    bool isValid;

    do {
        printf("Enter year: (2000-)");
        scanf("%d", &year);
        printf("Enter month (1-12): ");
        scanf("%d", &month);
        printf("Enter day (1-31): ");
        scanf("%d", &day);
        printf("Enter hour (0-23): ");
        scanf("%d", &hour);
        printf("Enter minute (0-59): ");
        scanf("%d", &minute);
        printf("Enter second (0-59): ");
        scanf("%d", &second);

        isValid = isValidDateTimeFormat(day, month, year, hour, minute, second);
        if (!isValid)
        {
            printf("Invalid date/time entered. Please try again.\n");
        }
    } while (!isValid); // Repeat until a valid DateTime is entered

	const DateTime dt = initDateTime(day, month, year, hour, minute, second);
    return dt;
}

/// Function to print a DateTime   
void displayDateTime(const DateTime* dt)
{
    // Prints date in DD/MM/YYYY format and time in HH:MM:SS format
    printf("%02d/%02d/%04d %02d:%02d:%02d\n", dt->day, dt->month, dt->year, dt->hour, dt->minute, dt->second);
}
