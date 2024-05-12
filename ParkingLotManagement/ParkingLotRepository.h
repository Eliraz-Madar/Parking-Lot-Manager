#pragma once
#include "General.h"
#include "ParkingLot.h"
#include "FileHelper.h"

bool readParkingLotFromFile(ParkingLot* parkingLot, const FileContext* fileContext);
bool writeParkingLotToFile(const ParkingLot* parkingLot, const FileContext* fileContext);
