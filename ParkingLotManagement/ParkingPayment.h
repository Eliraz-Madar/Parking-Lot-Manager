#pragma once
#include "general.h"
#include "DateTime.h"
#include "Vehicle.h"

typedef struct
{
	bool isPaid;
	Vehicle vehicle;
	DateTime entryDateTime;
	DateTime exitDateTime;
	double parkingHourlyRate;
	double amountPaid;
} ParkingPayment;

ParkingPayment initParkingPayment(Vehicle vehicle, DateTime entryDateTime, double parkingHourlyRate);

typedef enum
{
	PAYMENT_COMPLETED,
	ENTRY_DATE_AFTER_EXIT_DATE,
	INVALID_RATE
} MakePaymentResponse;

MakePaymentResponse makePayment(ParkingPayment* parkingPayment, const DateTime* exitDateTime);

double calculateAmountToPay(const ParkingPayment* parkingPayment, const DateTime* endDateTime);

int compareParkingPayments(const ParkingPayment* a, const ParkingPayment* b);

bool isSameParkingPayment(const ParkingPayment* a, const ParkingPayment* b);
