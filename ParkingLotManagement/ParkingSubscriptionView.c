#include "ParkingSubscriptionView.h"
#include "DateTimeView.h"
#include "GeneralView.h"

ParkingSubscription createParkingSubscriptionUI()
{
    double discountPercentage;

	const bool isActiveInput = getBooleanValueUI("Is the subscription initially active?");

    // Collect start and end DateTime using createDateTimeUI
    printf("Enter start date and time for the subscription:\n");
    const DateTime startDateTime = createDateTimeUI();

    printf("Enter end date and time for the subscription:\n");
    const DateTime endDateTime = createDateTimeUI();

    if(compareDateTimes(&startDateTime, &endDateTime) > 0)
	{
		printf("End date and time must be after start date and time.\n");
		return createParkingSubscriptionUI();
	}

    // Validate discount percentage input
    do
    {
        printf("Enter discount percentage (0-100): ");
        scanf("%lf", &discountPercentage);
        if (discountPercentage < 0 || discountPercentage > 100) {
            printf("Invalid input. Please enter a value between 0 and 100.\n");
        }
    } while (discountPercentage < 0 || discountPercentage > 100);

    // Initialize and return the ParkingSubscription object
    return initParkingSubscription(isActiveInput, startDateTime, endDateTime, discountPercentage);
}

void displayParkingSubscription(const ParkingSubscription* parkingSubscription)
{
	printf("Subscription Active: %s\n", parkingSubscription->isActive ? "Yes" : "No");

    if(parkingSubscription->isActive)
	{
        printf("Start Date and Time: ");
        displayDateTime(&parkingSubscription->startDateTime);
        printf("End Date and Time: ");
        displayDateTime(&parkingSubscription->endDateTime);
        printf("Discount Percentage: %.2lf%%\n", parkingSubscription->discountPercentage);
	}
}
