#pragma once
#include "General.h"
#include "Vehicle.h"
#include "ParkingPayment.h"
#include "ParkingSubscription.h"

typedef struct
{
	int customerId;
	char* name;
	ParkingSubscription parkingSubscription;

	Vehicle** vehicleArray; //מערך של מצביעים
	size_t vehicleArrayCount;

	ParkingPayment* paymentsArray;
	size_t paymentsArrayCount;

	double totalPaidAmount; //This value might not be accurate, it's better to calculate it on the fly. It is here for sorting purposes.
} ParkingCustomer;

ParkingCustomer initParkingCustomer(int customerId, const char* name, ParkingSubscription parkingSubscription);

bool updateCustomerName(ParkingCustomer* customer, const char* nameBuffer);

ArrayAddResult addVehicleToCustomer(ParkingCustomer* parkingCustomer, Vehicle vehicle);

//ArrayAddResult addVehiclePtr(ParkingCustomer* parkingCustomer, Vehicle* vehiclePtr);

ArrayRemoveResult removeVehicle(ParkingCustomer* parkingCustomer, Vehicle* vehicle);

bool doesVehicleExistByLicensePlate(const ParkingCustomer* parkingCustomer, const char* licensePlate);

Vehicle* findVehicleFromCustomerByLicensePlate(const ParkingCustomer* parkingCustomer, const char* licensePlate);

ArrayAddResult addPaymentToCustomer(ParkingCustomer* parkingCustomer, ParkingPayment payment);

ArrayRemoveResult removePaymentFromCustomer(ParkingCustomer* parkingCustomer, ParkingPayment payment);

ParkingPayment* findUnpaidPaymentFromCustomerByVehicle(const ParkingCustomer* parkingCustomer, const Vehicle* vehicle);

void updateCustomerSubscription(ParkingCustomer* parkingCustomer, ParkingSubscription parkingSubscription);

bool isCustomerSubscribed(const ParkingCustomer* parkingCustomer, const DateTime* currentDateTime);

bool isSameCustomerById(const ParkingCustomer* a, const ParkingCustomer* b);

double calculateTotalAmountPaid(const ParkingCustomer* customer);

int compareParkingCustomerById(const void* a, const void* b);

int compareParkingCustomerByName(const void* a, const void* b);

int compareParkingCustomerByTotalPaidAmount(const void* a, const void* b);

int compareParkingCustomerByVehicleQuantity(const void* a, const void* b);

void freeParkingCustomer(ParkingCustomer* parkingCustomer);
