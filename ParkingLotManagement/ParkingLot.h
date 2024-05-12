#pragma once
#include "General.h"
#include "ParkingCustomer.h"
#include "ParkingSpace.h"

typedef enum
{
	CUSTOMERS_UNSORTED,
	CUSTOMERS_SORT_BY_ID,
	CUSTOMERS_SORT_BY_NAME,
	CUSTOMERS_SORT_BY_TOTAL_VEHICLES,
	CUSTOMERS_SORT_BY_TOTAL_PAID_AMOUNT
} CustomersSortType;

typedef struct
{
	int parkingLotId;

	double parkingHourlyRate;
	//double totalEarnedMoney; //מתכון לטעויות

	int lastUsedCustomerId; // Track the last used customer ID in this parking lot

	ParkingCustomer* parkingCustomersArray;
	size_t parkingCustomersArrayCount;
	CustomersSortType customersSortedBy;

	ParkingSpace* parkingSpacesArray;
	size_t parkingSpacesArrayCount;

} ParkingLot;



ParkingLot initParkingLot(int parkingLotId, double parkingHourlyRate);

bool isSameParkingLotById(void* a, void* b);

ArrayAddResult addCustomerToParkingLot(ParkingLot* parkingLot, ParkingCustomer parkingCustomer);

ArrayRemoveResult removeCustomerFromParkingLot(ParkingLot* parkingLot, ParkingCustomer parkingCustomer);

ParkingCustomer* findCustomerById(const ParkingLot* parkingLot, int customerId);

void sortCustomersInParkingLot(ParkingLot* parkingLot, CustomersSortType customersSortType);
ParkingCustomer* findCustomerByIdBinarySearch(ParkingLot* parkingLot, int customerId);
ParkingCustomer* findCustomerByNameBinarySearch(ParkingLot* parkingLot, char* name);
ParkingCustomer* findCustomerByVehicleCountBinarySearch(ParkingLot* parkingLot, size_t vehicleCount);
ParkingCustomer* findCustomerByTotalPaidAmountBinarySearch(ParkingLot* parkingLot, double totalPaidAmount);

bool doesCustomerExistInParkingLotById(const ParkingLot* parkingLot, const ParkingCustomer* parkingCustomer);

ArrayAddResult addParkingSpaceToParkingLot(ParkingLot* parkingLot, ParkingSpace parkingSpace);

ArrayRemoveResult removeParkingSpaceFromParkingLot(ParkingLot* parkingLot, ParkingSpace parkingSpace);

ArrayRemoveResult removeParkingSpaceFromParkingLotBySpaceNumber(ParkingLot* parkingLot, int spaceNumber);

bool doesParkingSpaceExistInParkingLotBySpaceNumber(const ParkingLot* parkingLot, const ParkingSpace* parkingSpace);

ParkingSpace* findParkingSpaceBySpaceNumber(const ParkingLot* parkingLot, int spaceNumber);

ParkingSpace* findParkingSpaceByVehicle(const ParkingLot* parkingLot, const Vehicle* vehicle);

size_t getOccupiedParkingSpaceCount(const ParkingLot* parkingLot);

size_t getAvailableParkingSpaceCount(const ParkingLot* parkingLot);

void freeParkingLot(ParkingLot* parkingLot);
