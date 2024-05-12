#pragma once
#include "General.h"
#include "FileHelper.h"
#include "ParkingSubscription.h"

bool readParkingSubscriptionFromFile(ParkingSubscription* parkingSubscription, const FileContext* fileContext);
bool writeParkingSubscriptionToFile(const ParkingSubscription* parkingSubscription, const FileContext* fileContext);
