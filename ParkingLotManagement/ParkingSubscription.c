#include "ParkingSubscription.h"

/// <summary>
/// Initializes the ParkingSubscription model.
/// </summary>
/// <param name="startDateTime"></param>
/// <param name="endDateTime"></param>
/// <param name="discountPercentage">Discount percentage from 0.0-100.0 in double</param>
/// <returns></returns>
ParkingSubscription initParkingSubscription(bool isActive, DateTime startDateTime, DateTime endDateTime, double discountPercentage)
{
    ParkingSubscription parkingSubscription;

    parkingSubscription.isActive = isActive;
    parkingSubscription.startDateTime = startDateTime;
    parkingSubscription.endDateTime = endDateTime;
    parkingSubscription.discountPercentage = discountPercentage;

    return parkingSubscription;
}

void activateSubscription(ParkingSubscription* parkingSubscription)
{
    parkingSubscription->isActive = true;
}

void deactivateSubscription(ParkingSubscription* parkingSubscription)
{
    parkingSubscription->isActive = false;
}

bool isSubscriptionActive(const ParkingSubscription* parkingSubscription, const DateTime* currentDateTime)
{
    return parkingSubscription->isActive && isDateTimeBetweenTwoDateTimes(&parkingSubscription->startDateTime, &parkingSubscription->endDateTime, currentDateTime);
}
