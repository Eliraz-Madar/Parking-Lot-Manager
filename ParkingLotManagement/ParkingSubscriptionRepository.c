#include "ParkingSubscriptionRepository.h"

#include "DateTimeRepository.h"

bool readParkingSubscriptionFromFile(ParkingSubscription* parkingSubscription, const FileContext* fileContext)
{
	bool isActive;
	DateTime startDateTime;
	DateTime endDateTime;
	double discountPercentage;

	if (!readBoolFromFile(&isActive, fileContext))
		return false;

	if (!readDateTimeFromFile(&startDateTime, fileContext))
		return false;

	if (!readDateTimeFromFile(&endDateTime, fileContext))
		return false;

	if (!readDoubleFromFile(&discountPercentage, fileContext))
		return false;

	*parkingSubscription = initParkingSubscription(isActive, startDateTime, endDateTime, discountPercentage);

	return true;
}

bool writeParkingSubscriptionToFile(const ParkingSubscription* parkingSubscription, const FileContext* fileContext)
{
	if (!writeBoolToFile(parkingSubscription->isActive, fileContext))
		return false;

	if (!writeDateTimeToFile(&parkingSubscription->startDateTime, fileContext))
		return false;

	if (!writeDateTimeToFile(&parkingSubscription->endDateTime, fileContext))
		return false;

	if (!writeDoubleToFile(parkingSubscription->discountPercentage, fileContext))
		return false;

	return true;
}
