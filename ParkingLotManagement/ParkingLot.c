#include "ParkingLot.h"

ParkingLot initParkingLot(int parkingLotId, double parkingHourlyRate)
{
	ParkingLot parkingLot;

	parkingLot.parkingLotId = parkingLotId;
	parkingLot.parkingHourlyRate = parkingHourlyRate;

	parkingLot.parkingCustomersArray = NULL;
	parkingLot.parkingCustomersArrayCount = 0;
	parkingLot.customersSortedBy = CUSTOMERS_UNSORTED;

	parkingLot.parkingSpacesArray = NULL;
	parkingLot.parkingSpacesArrayCount = 0;

	parkingLot.lastUsedCustomerId = 0;

	return parkingLot;
}

ParkingCustomer* findCustomerById(const ParkingLot* parkingLot, int customerId)
{
	ARRAY_FOREACH(ParkingCustomer, parkingCustomer, parkingLot->parkingCustomersArray, parkingLot->parkingCustomersArrayCount)
	{
		if (parkingCustomer->customerId == customerId)
		{
			return parkingCustomer;
		}
	}

	return NULL;
}

bool isSameParkingLotById(void* a, void* b)
{
	return ((ParkingLot*)a)->parkingLotId == ((ParkingLot*)b)->parkingLotId;
}

ArrayAddResult addCustomerToParkingLot(ParkingLot* parkingLot, ParkingCustomer parkingCustomer)
{
	if (doesCustomerExistInParkingLotById(parkingLot, &parkingCustomer))
		return ARRAY_ADD_DUPLICATE;

	ArrayAddResult result;
	ADD_ELEMENT(ParkingCustomer, parkingLot->parkingCustomersArray, parkingLot->parkingCustomersArrayCount, parkingCustomer, &result);

	return result;
}

ArrayRemoveResult removeCustomerFromParkingLot(ParkingLot* parkingLot, ParkingCustomer parkingCustomer)
{
	ArrayRemoveResult arrayRemoveResult;

	REMOVE_ELEMENT_CUSTOM_COMP(ParkingCustomer, parkingLot->parkingCustomersArray, parkingLot->parkingCustomersArrayCount, parkingCustomer, isSameCustomerById, &arrayRemoveResult);

	return arrayRemoveResult;
}

void sortCustomersInParkingLot(ParkingLot* parkingLot, CustomersSortType customersSortType)
{
	if (parkingLot->customersSortedBy == customersSortType)
	{
		return; // Already sorted by the requested type
	}

	switch (customersSortType)
	{
	case CUSTOMERS_SORT_BY_ID:
		qsort(parkingLot->parkingCustomersArray, parkingLot->parkingCustomersArrayCount, sizeof(ParkingCustomer), compareParkingCustomerById);
		break;
	case CUSTOMERS_SORT_BY_NAME:
		qsort(parkingLot->parkingCustomersArray, parkingLot->parkingCustomersArrayCount, sizeof(ParkingCustomer), compareParkingCustomerByName);
		break;
	case CUSTOMERS_SORT_BY_TOTAL_VEHICLES:
		qsort(parkingLot->parkingCustomersArray, parkingLot->parkingCustomersArrayCount, sizeof(ParkingCustomer), compareParkingCustomerByVehicleQuantity);
		break;
	case CUSTOMERS_SORT_BY_TOTAL_PAID_AMOUNT:
		qsort(parkingLot->parkingCustomersArray, parkingLot->parkingCustomersArrayCount, sizeof(ParkingCustomer), compareParkingCustomerByTotalPaidAmount);
		break;
	case CUSTOMERS_UNSORTED:
		// No sorting needed
		break;
	default:
		// No sorting needed
		break;
	}

	parkingLot->customersSortedBy = customersSortType;
}

ParkingCustomer* findCustomerByIdBinarySearch(ParkingLot* parkingLot, int customerId)
{
	ParkingCustomer parkingCustomer;
	parkingCustomer.customerId = customerId;

	sortCustomersInParkingLot(parkingLot, CUSTOMERS_SORT_BY_ID);
	return (ParkingCustomer*)bsearch(&parkingCustomer, parkingLot->parkingCustomersArray, parkingLot->parkingCustomersArrayCount, sizeof(ParkingCustomer), compareParkingCustomerById);
}

ParkingCustomer* findCustomerByNameBinarySearch(ParkingLot* parkingLot, char* name)
{
	ParkingCustomer parkingCustomer;
	parkingCustomer.name = name;

	sortCustomersInParkingLot(parkingLot, CUSTOMERS_SORT_BY_NAME);
	return (ParkingCustomer*)bsearch(&parkingCustomer, parkingLot->parkingCustomersArray, parkingLot->parkingCustomersArrayCount, sizeof(ParkingCustomer), compareParkingCustomerByName);
}

ParkingCustomer* findCustomerByVehicleCountBinarySearch(ParkingLot* parkingLot, size_t vehicleCount)
{
	ParkingCustomer parkingCustomer;
	parkingCustomer.vehicleArrayCount = vehicleCount;

	sortCustomersInParkingLot(parkingLot, CUSTOMERS_SORT_BY_TOTAL_VEHICLES);
	return (ParkingCustomer*)bsearch(&parkingCustomer, parkingLot->parkingCustomersArray, parkingLot->parkingCustomersArrayCount, sizeof(ParkingCustomer), compareParkingCustomerByVehicleQuantity);
}

ParkingCustomer* findCustomerByTotalPaidAmountBinarySearch(ParkingLot* parkingLot, double totalPaidAmount)
{
	ParkingCustomer parkingCustomer;
	parkingCustomer.totalPaidAmount = totalPaidAmount;

	sortCustomersInParkingLot(parkingLot, CUSTOMERS_SORT_BY_TOTAL_PAID_AMOUNT);
	return (ParkingCustomer*)bsearch(&parkingCustomer, parkingLot->parkingCustomersArray, parkingLot->parkingCustomersArrayCount, sizeof(ParkingCustomer), compareParkingCustomerByTotalPaidAmount);
}

bool doesCustomerExistInParkingLotById(const ParkingLot* parkingLot, const ParkingCustomer* parkingCustomer)
{
	ARRAY_FOREACH(ParkingCustomer, item, parkingLot->parkingCustomersArray, parkingLot->parkingCustomersArrayCount)
	{
		if (isSameCustomerById(parkingCustomer, item))
		{
			return true;
		}
	}

	return false;
}

ArrayAddResult addParkingSpaceToParkingLot(ParkingLot* parkingLot, ParkingSpace parkingSpace)
{
	if (doesParkingSpaceExistInParkingLotBySpaceNumber(parkingLot, &parkingSpace))
		return ARRAY_ADD_DUPLICATE;

	ArrayAddResult result;
	ADD_ELEMENT(ParkingSpace, parkingLot->parkingSpacesArray, parkingLot->parkingSpacesArrayCount, parkingSpace, &result);

	return result;
}

ArrayRemoveResult removeParkingSpaceFromParkingLot(ParkingLot* parkingLot, ParkingSpace parkingSpace)
{
	ArrayRemoveResult arrayRemoveResult;

	REMOVE_ELEMENT_CUSTOM_COMP(ParkingSpace, parkingLot->parkingSpacesArray, parkingLot->parkingSpacesArrayCount, parkingSpace, isSameParkingSpaceBySpaceNumber, &arrayRemoveResult);

	return arrayRemoveResult;
}

ArrayRemoveResult removeParkingSpaceFromParkingLotBySpaceNumber(ParkingLot* parkingLot, int spaceNumber)
{
	ParkingSpace parkingSpace;
	parkingSpace.spaceNumber = spaceNumber;

	ArrayRemoveResult arrayRemoveResult;

	REMOVE_ELEMENT_CUSTOM_COMP(ParkingSpace, parkingLot->parkingSpacesArray, parkingLot->parkingSpacesArrayCount, parkingSpace, isSameParkingSpaceBySpaceNumber, &arrayRemoveResult);

	return arrayRemoveResult;
}

bool doesParkingSpaceExistInParkingLotBySpaceNumber(const ParkingLot* parkingLot, const ParkingSpace* parkingSpace)
{
	ARRAY_FOREACH(ParkingSpace, item, parkingLot->parkingSpacesArray, parkingLot->parkingSpacesArrayCount)
	{
		if (isSameParkingSpaceBySpaceNumber(item, parkingSpace))
		{
			return true;
		}
	}

	return false;
}

ParkingSpace* findParkingSpaceBySpaceNumber(const ParkingLot* parkingLot, int spaceNumber)
{
	ARRAY_FOREACH(ParkingSpace, parkingSpace, parkingLot->parkingSpacesArray, parkingLot->parkingSpacesArrayCount)
	{
		if (parkingSpace->spaceNumber == spaceNumber)
		{
			return parkingSpace;
		}
	}

	return NULL;
}

ParkingSpace* findParkingSpaceByVehicle(const ParkingLot* parkingLot, const Vehicle* vehicle)
{
	ARRAY_FOREACH(ParkingSpace, parkingSpace, parkingLot->parkingSpacesArray, parkingLot->parkingSpacesArrayCount)
	{
		if (parkingSpace->parkedVehicle != NULL && isSameVehicle(parkingSpace->parkedVehicle, vehicle))
		{
			return parkingSpace;
		}
	}

	return NULL;
}

size_t getOccupiedParkingSpaceCount(const ParkingLot* parkingLot)
{
	size_t count = 0;

	ARRAY_FOREACH(ParkingSpace, parkingSpace, parkingLot->parkingSpacesArray, parkingLot->parkingSpacesArrayCount)
	{
		if (parkingSpace->parkedVehicle != NULL)
		{
			count++;
		}
	}

	return count;
}

size_t getAvailableParkingSpaceCount(const ParkingLot* parkingLot)
{
	size_t count = 0;

	ARRAY_FOREACH(ParkingSpace, parkingSpace, parkingLot->parkingSpacesArray, parkingLot->parkingSpacesArrayCount)
	{
		if (parkingSpace->parkedVehicle == NULL)
		{
			count++;
		}
	}

	return count;
}

void freeParkingLot(ParkingLot* parkingLot)
{
	// Free the dynamic memory allocated for the parkingCustomersArray, if any
	if (parkingLot->parkingCustomersArray != NULL)
	{
		// Free each customer in the array
		if (parkingLot->parkingCustomersArrayCount > 0)
		{
			generalArrayFunction(parkingLot->parkingCustomersArray, sizeof(ParkingCustomer), parkingLot->parkingCustomersArrayCount, freeParkingCustomer);
		}

		free(parkingLot->parkingCustomersArray);
		parkingLot->parkingCustomersArray = NULL;
		parkingLot->parkingCustomersArrayCount = 0;
	}

	// Free the dynamic memory allocated for the parkingSpacesArray, if any
	if (parkingLot->parkingSpacesArray != NULL)
	{
		// Free each parking space in the array
		if (parkingLot->parkingSpacesArrayCount > 0)
		{
			generalArrayFunction(parkingLot->parkingSpacesArray, sizeof(ParkingSpace), parkingLot->parkingSpacesArrayCount, freeParkingSpace);
		}

		free(parkingLot->parkingSpacesArray);
		parkingLot->parkingSpacesArray = NULL;
		parkingLot->parkingSpacesArrayCount = 0;
	}
}
