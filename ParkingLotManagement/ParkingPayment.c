#include "ParkingPayment.h"

/// <summary>
/// Initializes the ParkingPayment model.
/// isPayed is set to false
/// exitDateTime is set to 0
/// amountPayed is set to 0
/// </summary>
ParkingPayment initParkingPayment(Vehicle vehicle, DateTime entryDateTime, double parkingHourlyRate)
{
	ParkingPayment parkingPayment = { 0 };

	parkingPayment.isPaid = false;
	parkingPayment.vehicle = vehicle;
	parkingPayment.entryDateTime = entryDateTime;
	parkingPayment.parkingHourlyRate = parkingHourlyRate;

	return parkingPayment;
}

MakePaymentResponse makePayment(ParkingPayment* parkingPayment, const DateTime* exitDateTime)
{
	if (parkingPayment->parkingHourlyRate < 0)
	{
		return INVALID_RATE;
	}

	const long startTotalHours = dateTimeToTotalMinutes(&parkingPayment->entryDateTime);
	const long endTotalHours = dateTimeToTotalMinutes(exitDateTime);

	if (endTotalHours < startTotalHours)
	{
		return ENTRY_DATE_AFTER_EXIT_DATE;
	}

	const double amount = calculateAmountToPay(parkingPayment, exitDateTime);
	
	parkingPayment->exitDateTime = *exitDateTime;
	parkingPayment->amountPaid = amount;
	parkingPayment->isPaid = true;

	return PAYMENT_COMPLETED;
}

double calculateAmountToPay(const ParkingPayment* parkingPayment, const DateTime* endDateTime)
{
	const long startTotalMinutes = dateTimeToTotalMinutes(&parkingPayment->entryDateTime);
	const long endTotalMinutes = dateTimeToTotalMinutes(endDateTime);

	const long totalMinutesParked = endTotalMinutes - startTotalMinutes;

	if(totalMinutesParked < 0)
	{
		return 0;
	}

	return totalMinutesParked * (parkingPayment->parkingHourlyRate / 60.0);
}

/// <summary>
/// Note: This function returns 0 if equals, and negative/positive values suggesting which is higher
/// </summary>
/// <returns>0=equal, a &lt; b ? -1 : 1</returns>
int compareParkingPayments(const ParkingPayment* a, const ParkingPayment* b)
{
	if(!isSameVehicle(&a->vehicle, &b->vehicle)) return strcmp(a->vehicle.licensePlate, b->vehicle.licensePlate);
	if (a->isPaid != b->isPaid) return a->isPaid ? 1 : -1;
	const int exitDateTimeComp = compareDateTimes(&a->exitDateTime, &b->exitDateTime);
	if (exitDateTimeComp != 0) return exitDateTimeComp;
	if (a->parkingHourlyRate != b->parkingHourlyRate) return (a->parkingHourlyRate > b->parkingHourlyRate) ? 1 : -1;
	if (a->amountPaid != b->amountPaid) return (a->amountPaid > b->amountPaid) ? 1 : -1;

	// If all else is equal, consider them equal.
	return 0;
}

bool isSameParkingPayment(const ParkingPayment* a, const ParkingPayment* b)
{
	return compareParkingPayments(a, b) == 0;
}
