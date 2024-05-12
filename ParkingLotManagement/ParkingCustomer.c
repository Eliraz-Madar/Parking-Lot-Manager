#include "ParkingCustomer.h"

ParkingCustomer initParkingCustomer(int customerId, const char* name, ParkingSubscription parkingSubscription)
{
	ParkingCustomer parkingCustomer;

	parkingCustomer.customerId = customerId;
	parkingCustomer.name = customStrdup(name);

	parkingCustomer.vehicleArray = NULL;
	parkingCustomer.vehicleArrayCount = 0;

	parkingCustomer.paymentsArray = NULL;
	parkingCustomer.paymentsArrayCount = 0;

	parkingCustomer.parkingSubscription = parkingSubscription;

	parkingCustomer.totalPaidAmount = 0.0;

	return parkingCustomer;
}

bool updateCustomerName(ParkingCustomer* customer, const char* nameBuffer)
{
	char* newName = customStrdup(nameBuffer);
	if (newName == NULL)
	{
		return false;
	}

	free(customer->name);
	customer->name = newName;

	return true;
}

//// Add a vehicle to the customer's vehicle array. Note that this function takes a Vehicle struct.
ArrayAddResult addVehicleToCustomer(ParkingCustomer* parkingCustomer, Vehicle vehicle)
{
	if (doesVehicleExistByLicensePlate(parkingCustomer, vehicle.licensePlate))
		return ARRAY_ADD_DUPLICATE;

	Vehicle* vehiclePtr = (Vehicle*)malloc(sizeof(Vehicle));
	if (vehiclePtr == NULL)
	{
		return ARRAY_ADD_FAILED;
	}

	*vehiclePtr = vehicle;

	ArrayAddResult result;
	ADD_ELEMENT(Vehicle*, parkingCustomer->vehicleArray, parkingCustomer->vehicleArrayCount, vehiclePtr, &result);

	return result;
}

//I greyed this function out because free customer will free this vehicle pointer as well, which could be unexpected behavior.
/*
/// Add a pointer of a vehicle to the customer's vehicle array.
ArrayAddResult addVehiclePtr(ParkingCustomer* parkingCustomer, Vehicle* vehiclePtr)
{
	if (doesVehicleExistByLicensePlate(parkingCustomer, vehiclePtr))
		return ARRAY_ADD_DUPLICATE;

	ArrayAddResult result;
	ADD_ELEMENT(Vehicle*, parkingCustomer->vehicleArray, parkingCustomer->vehicleArrayCount, vehiclePtr, &result);

	return result;
}
*/

/// Remove a vehicle from the customer's vehicle array
ArrayRemoveResult removeVehicle(ParkingCustomer* parkingCustomer, Vehicle* vehicle)
{
	ArrayRemoveResult arrayRemoveResult;

	REMOVE_ELEMENT(Vehicle*, parkingCustomer->vehicleArray, parkingCustomer->vehicleArrayCount, vehicle, &arrayRemoveResult);
	free(vehicle);

	return arrayRemoveResult;
}

//// Check if a vehicle exists in the customer's vehicle array
bool doesVehicleExistByLicensePlate(const ParkingCustomer* parkingCustomer, const char* licensePlate)
{
	for (int i = 0; i < parkingCustomer->vehicleArrayCount; i++)
	{
		if (strcmp(parkingCustomer->vehicleArray[i]->licensePlate, licensePlate) == 0)
		{
			return true;
		}
	}

	return false;
}

ArrayAddResult addPaymentToCustomer(ParkingCustomer* parkingCustomer, ParkingPayment payment)
{
	ArrayAddResult result;
	ADD_ELEMENT(ParkingPayment, parkingCustomer->paymentsArray, parkingCustomer->paymentsArrayCount, payment, &result);

	return result;
}

ArrayRemoveResult removePaymentFromCustomer(ParkingCustomer* parkingCustomer, ParkingPayment payment)
{
	ArrayRemoveResult arrayRemoveResult;

	REMOVE_ELEMENT_CUSTOM_COMP(ParkingPayment, parkingCustomer->paymentsArray, parkingCustomer->paymentsArrayCount, payment, isSameParkingPayment, &arrayRemoveResult);

	return arrayRemoveResult;
}

//// Get a vehicle from the customer's vehicle array by license plate. Returns NULL if not found.
Vehicle* findVehicleFromCustomerByLicensePlate(const ParkingCustomer* parkingCustomer, const char* licensePlate)
{
	for (size_t i = 0; i < parkingCustomer->vehicleArrayCount; i++)
	{
		if (strcmp(parkingCustomer->vehicleArray[i]->licensePlate, licensePlate) == 0)
		{
			return parkingCustomer->vehicleArray[i];
		}
	}

	return NULL;
}

ParkingPayment* findUnpaidPaymentFromCustomerByVehicle(const ParkingCustomer* parkingCustomer, const Vehicle* vehicle)
{
	for (size_t i = 0; i < parkingCustomer->paymentsArrayCount; i++)
	{
		if (isSameVehicle(&parkingCustomer->paymentsArray[i].vehicle, vehicle))
		{
			if (!parkingCustomer->paymentsArray[i].isPaid)
			{
				return &parkingCustomer->paymentsArray[i];
			}
		}
	}

	return NULL;
}

void updateCustomerSubscription(ParkingCustomer* parkingCustomer, ParkingSubscription parkingSubscription)
{
	parkingCustomer->parkingSubscription = parkingSubscription;
}

bool isCustomerSubscribed(const ParkingCustomer* parkingCustomer, const DateTime* currentDateTime)
{
	return isSubscriptionActive(&parkingCustomer->parkingSubscription, currentDateTime);
}

bool isSameCustomerById(const ParkingCustomer* a, const ParkingCustomer* b)
{
	return a->customerId == b->customerId;
}

int compareParkingCustomerById(const void* a, const void* b)
{
	const ParkingCustomer* customerA = (const ParkingCustomer*)a;
	const ParkingCustomer* customerB = (const ParkingCustomer*)b;

	if (customerA->customerId < customerB->customerId) return -1;
	else if (customerA->customerId > customerB->customerId) return 1;
	else return 0;
}

int compareParkingCustomerByName(const void* a, const void* b)
{
	const ParkingCustomer* customerA = (const ParkingCustomer*)a;
	const ParkingCustomer* customerB = (const ParkingCustomer*)b;

	return strcmp(customerA->name, customerB->name);
}

double calculateTotalAmountPaid(const ParkingCustomer* customer)
{
	double total = 0.0;

	ARRAY_FOREACH(ParkingPayment, payment, customer->paymentsArray, customer->paymentsArrayCount)
	{
		total += payment->amountPaid; // Note that payment is a pointer here
	}

	return total;
}

int compareParkingCustomerByTotalPaidAmount(const void* a, const void* b)
{
	const ParkingCustomer* customerA = (const ParkingCustomer*)a;
	const ParkingCustomer* customerB = (const ParkingCustomer*)b;

	// Removed the calculation of total amount paid here because this function is used for qsort and bsearch.
	/*double totalA = calculateTotalAmountPaid(customerA);
	double totalB = calculateTotalAmountPaid(customerB);*/

	double totalA = customerA->totalPaidAmount;
	double totalB = customerB->totalPaidAmount;

	// doubles have possible floating-point precision issues.
	// We compare with a small epsilon value to determine if totals are effectively equal or not.
	double diff = totalA - totalB;
	double epsilon = 0.001; // Adjust as needed for acceptable precision

	if (diff > epsilon) return 1; // A > B
	else if (diff < -epsilon) return -1; // A < B
	else return 0; // A == B
}

int compareParkingCustomerByVehicleQuantity(const void* a, const void* b)
{
	const ParkingCustomer* customerA = (const ParkingCustomer*)a;
	const ParkingCustomer* customerB = (const ParkingCustomer*)b;

	size_t vehiclesA = customerA->vehicleArrayCount;
	size_t vehiclesB = customerB->vehicleArrayCount;

	if (vehiclesA < vehiclesB) return -1;
	else if (vehiclesA > vehiclesB) return 1;
	else return 0;
}

/// Helper function to free a Vehicle* element
void freeVehicleHelper(void* element)
{
	// Cast the void pointer to Vehicle** (pointer to a pointer of a Vehicle)
	Vehicle** vehiclePtr = (Vehicle**)element;
	// Free the Vehicle* pointed to by vehiclePtr
	free(*vehiclePtr);
}

void freeParkingCustomer(ParkingCustomer* parkingCustomer)
{
	// Free each vehicle in the vehicleArray
	if (parkingCustomer->vehicleArrayCount > 0)
	{
		generalArrayFunction(parkingCustomer->vehicleArray, sizeof(Vehicle*), parkingCustomer->vehicleArrayCount, freeVehicleHelper);
	}

	// Free the vehicleArray itself
	free(parkingCustomer->vehicleArray);
	parkingCustomer->vehicleArray = NULL;
	parkingCustomer->vehicleArrayCount = 0;

	// Free the paymentsArray
	free(parkingCustomer->paymentsArray);
	parkingCustomer->paymentsArray = NULL;
	parkingCustomer->paymentsArrayCount = 0;

	// Free the name
	free(parkingCustomer->name);
	parkingCustomer->name = NULL;

}
