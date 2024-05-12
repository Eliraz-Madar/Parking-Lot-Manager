#pragma once
#include "General.h"
#include "FileHelper.h"
#include "ParkingCustomer.h"

bool readParkingCustomerFromFile(ParkingCustomer* pCustomer, const FileContext* fileContext);
bool writeParkingCustomerToFile(const ParkingCustomer* pCustomer, const FileContext* fileContext);
