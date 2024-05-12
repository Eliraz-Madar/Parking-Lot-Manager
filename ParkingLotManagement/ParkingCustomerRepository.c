#include "FileHelper.h"
#include "ParkingCustomerRepository.h"
#include "ParkingSubscriptionRepository.h"
#include "VehicleRepository.h"
#include "ParkingPaymentRepository.h"

bool readParkingCustomerFromFile(ParkingCustomer* pCustomer, const FileContext* fileContext)
{
	int customerId;
	if (!readIntFromFile(&customerId, fileContext))
		return false;

	char name[255];
	if (!readStringFromFile(name, 255, fileContext))
		return false;

	ParkingSubscription parkingSubscription;
	readParkingSubscriptionFromFile(&parkingSubscription, fileContext);

	*pCustomer = initParkingCustomer(customerId, name, parkingSubscription);

	size_t vehicleArrayCount;
	if (!readSizeTFromFile(&vehicleArrayCount, fileContext))
		return false;

	for (size_t i = 0; i < vehicleArrayCount; i++)
	{
		Vehicle vehicle;
		if (!readVehicleFromFile(&vehicle, fileContext))
			return false;

		addVehicleToCustomer(pCustomer, vehicle);
	}

	size_t paymentsArrayCount;
	if (!readSizeTFromFile(&paymentsArrayCount, fileContext))
		return false;

	for (size_t i = 0; i < paymentsArrayCount; i++)
	{
		ParkingPayment payment;
		if (!readParkingPaymentFromFile(&payment, fileContext))
			return false;

		addPaymentToCustomer(pCustomer, payment);
	}

	double totalPaidAmount;
	if(!readDoubleFromFile(&totalPaidAmount, fileContext))
		return false;
	pCustomer->totalPaidAmount = totalPaidAmount;

	return true;
}

bool writeParkingCustomerToFile(const ParkingCustomer* pCustomer, const FileContext* fileContext)
{
	if (!writeIntToFile(pCustomer->customerId, fileContext))
		return false;

	if (!writeStringToFile(pCustomer->name, fileContext))
		return false;

	if (!writeParkingSubscriptionToFile(&pCustomer->parkingSubscription, fileContext))
		return false;

	if (!writeSizeTToFile(pCustomer->vehicleArrayCount, fileContext))
		return false;

	for (size_t i = 0; i < pCustomer->vehicleArrayCount; i++)
	{
		if (!writeVehicleToFile(pCustomer->vehicleArray[i], fileContext))
			return false;
	}

	if (!writeSizeTToFile(pCustomer->paymentsArrayCount, fileContext))
		return false;

	for (size_t i = 0; i < pCustomer->paymentsArrayCount; i++)
	{
		if (!writeParkingPaymentToFile(&pCustomer->paymentsArray[i], fileContext))
			return false;
	}

	if(!writeDoubleToFile(pCustomer->totalPaidAmount, fileContext))
		return false;

	return true;
}
