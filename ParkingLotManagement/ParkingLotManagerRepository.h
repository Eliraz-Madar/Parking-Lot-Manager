#pragma once
#include "General.h"
#include "FileHelper.h"
#include "ParkingLotManager.h"

bool readParkingManagerFromFile(ParkingLotManager* parkingLotManager, const FileContext* fileContext);
bool writeParkingManagerToFile(const ParkingLotManager* parkingLotManager, const FileContext* fileContext);
