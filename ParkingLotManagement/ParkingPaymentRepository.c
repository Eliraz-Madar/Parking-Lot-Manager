#include "ParkingPaymentRepository.h"

#include "DateTimeRepository.h"
#include "VehicleRepository.h"

bool readParkingPaymentFromFile(ParkingPayment* parkingPayment, const FileContext* fileContext)
{
	bool isPaid;
	if (!readBoolFromFile(&isPaid, fileContext))
		return false;

	Vehicle vehicle;
	if (!readVehicleFromFile(&vehicle, fileContext))
		return false;

	DateTime entryDateTime;
	if (!readDateTimeFromFile(&entryDateTime, fileContext))
		return false;

	DateTime exitDateTime;
	if (!readDateTimeFromFile(&exitDateTime, fileContext))
		return false;

	double parkingHourlyRate;
	if (!readDoubleFromFile(&parkingHourlyRate, fileContext))
		return false;

	double amountPaid;
	if (!readDoubleFromFile(&amountPaid, fileContext))
		return false;

	*parkingPayment = initParkingPayment(vehicle, entryDateTime, parkingHourlyRate);
	parkingPayment->isPaid = isPaid;
	parkingPayment->exitDateTime = exitDateTime;
	parkingPayment->amountPaid = amountPaid;
	return true;
}

bool writeParkingPaymentToFile(const ParkingPayment* parkingPayment, const FileContext* fileContext)
{
	if (!writeBoolToFile(parkingPayment->isPaid, fileContext))
		return false;

	if (!writeVehicleToFile(&parkingPayment->vehicle, fileContext))
		return false;

	if (!writeDateTimeToFile(&parkingPayment->entryDateTime, fileContext))
		return false;

	if (!writeDateTimeToFile(&parkingPayment->exitDateTime, fileContext))
		return false;

	if (!writeDoubleToFile(parkingPayment->parkingHourlyRate, fileContext))
		return false;

	if (!writeDoubleToFile(parkingPayment->amountPaid, fileContext))
		return false;

	return true;
}
