#pragma once
#include "General.h"
#include "Vehicle.h"
#include "FileHelper.h"

bool readVehicleFromFile(Vehicle* vehicle, const FileContext* fileContext);

bool readVehicleLicensePlate(char* licensePlate, const FileContext* fileContext);

bool writeVehicleToFile(const Vehicle* vehicle, const FileContext* fileContext);
