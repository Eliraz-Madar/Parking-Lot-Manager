#pragma once
#include "General.h"
#include "ParkingSpace.h"
#include "ParkingCustomer.h"
#include "FileHelper.h"

bool readParkingSpaceFromFile(ParkingSpace* parkingSpace, ParkingCustomer* customerArray, size_t customerArrayCount, const FileContext* fileContext);
bool writeParkingSpaceToFile(const ParkingSpace* parkingSpace, const FileContext* fileContext);
