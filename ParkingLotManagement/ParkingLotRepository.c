#include "ParkingLotRepository.h"

#include "ParkingCustomerRepository.h"
#include "ParkingSpaceRepository.h"

bool readParkingLotFromFile(ParkingLot* parkingLot, const FileContext* fileContext)
{
	int parkingLotId;
	double parkingHourlyRate;
	
	if (!readIntFromFile(&parkingLotId, fileContext))
		return false;

	if (!readDoubleFromFile(&parkingHourlyRate, fileContext))
		return false;

	*parkingLot = initParkingLot(parkingLotId, parkingHourlyRate);

	int lastUsedCustomerId;
	if (!readIntFromFile(&lastUsedCustomerId, fileContext))
		return false;
	parkingLot->lastUsedCustomerId = lastUsedCustomerId;

	size_t parkingCustomersArrayCount;
	if (!readSizeTFromFile(&parkingCustomersArrayCount, fileContext))
		return false;

	ParkingCustomer parkingCustomer;
	for (size_t i = 0; i < parkingCustomersArrayCount; i++)
	{
		readParkingCustomerFromFile(&parkingCustomer, fileContext);

		addCustomerToParkingLot(parkingLot, parkingCustomer);
	}

	CustomersSortType customersSortedBy;
	if (!readIntFromFile((int*)&customersSortedBy, fileContext))
		return false;
	if (customersSortedBy != CUSTOMERS_UNSORTED)
	{
		sortCustomersInParkingLot(parkingLot, customersSortedBy);
	}
	parkingLot->customersSortedBy = customersSortedBy;

	size_t parkingSpacesArrayCount;
	if (!readSizeTFromFile(&parkingSpacesArrayCount, fileContext))
		return false;

	ParkingSpace parkingSpace;
	for (size_t i = 0; i < parkingSpacesArrayCount; i++)
	{
		if (!readParkingSpaceFromFile(&parkingSpace, parkingLot->parkingCustomersArray, parkingLot->parkingCustomersArrayCount, fileContext))
			return false;

		addParkingSpaceToParkingLot(parkingLot, parkingSpace);
	}

	return true;
}

bool writeParkingLotToFile(const ParkingLot* parkingLot, const FileContext* fileContext)
{
	if (!writeIntToFile(parkingLot->parkingLotId, fileContext))
		return false;

	if (!writeDoubleToFile(parkingLot->parkingHourlyRate, fileContext))
		return false;

	if(!writeIntToFile(parkingLot->lastUsedCustomerId, fileContext))
		return false;

	if (!writeSizeTToFile(parkingLot->parkingCustomersArrayCount, fileContext))
		return false;

	ARRAY_FOREACH(ParkingCustomer, item, parkingLot->parkingCustomersArray, parkingLot->parkingCustomersArrayCount)
	{
		if (!writeParkingCustomerToFile(item, fileContext))
		{
			return false;
		}
	}

	if(!writeIntToFile((int)parkingLot->customersSortedBy, fileContext))
		return false;

	if (!writeSizeTToFile(parkingLot->parkingSpacesArrayCount, fileContext))
		return false;

	ARRAY_FOREACH(ParkingSpace, item, parkingLot->parkingSpacesArray, parkingLot->parkingSpacesArrayCount)
	{
		if (!writeParkingSpaceToFile(item, fileContext))
		{
			return false;
		}
	}

	return true;
}
