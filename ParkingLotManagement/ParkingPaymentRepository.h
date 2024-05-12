#pragma once
#include "General.h"
#include "ParkingPayment.h"
#include "FileHelper.h"

bool readParkingPaymentFromFile(ParkingPayment* parkingPayment, const FileContext* fileContext);
bool writeParkingPaymentToFile(const ParkingPayment* parkingPayment, const FileContext* fileContext);
