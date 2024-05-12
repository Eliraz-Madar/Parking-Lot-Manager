#pragma once
#include "General.h"
#include "ParkingPayment.h"

ParkingPayment createParkingPaymentUI(Vehicle vehicle, double hourlyRate);

void displayParkingPayment(const ParkingPayment* parkingPayment);

bool makePaymentUI(ParkingPayment* parkingPayment);
