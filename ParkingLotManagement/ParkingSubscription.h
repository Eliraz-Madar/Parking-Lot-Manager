#pragma once
#include "general.h"
#include "DateTime.h"

typedef struct
{
    bool isActive;
    DateTime startDateTime;
    DateTime endDateTime;
    double discountPercentage; //Value between 0.0 and 100.0
} ParkingSubscription;

ParkingSubscription initParkingSubscription(bool isActive, DateTime startDateTime, DateTime endDateTime, double discountPercentage);

void activateSubscription(ParkingSubscription* parkingSubscription);

void deactivateSubscription(ParkingSubscription* parkingSubscription);

bool isSubscriptionActive(const ParkingSubscription* parkingSubscription, const DateTime* currentDateTime);
