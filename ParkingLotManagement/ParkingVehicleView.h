#pragma once
#include "General.h"
#include "Vehicle.h"

Vehicle createVehicleUI();

void getVehicleLicensePlateUI(char* licensePlateBuffer);

VehicleType getVehicleTypeUI();

void displayVehicle(const Vehicle* vehicle);
