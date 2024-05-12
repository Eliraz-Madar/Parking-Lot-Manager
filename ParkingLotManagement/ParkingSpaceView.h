#pragma once
#include "General.h"
#include "ParkingSpace.h"

ParkingSpace createParkingSpaceUI();

void displayParkingSpaceMainMenu(ParkingSpace* parkingSpace);

void displayParkingSpace(const ParkingSpace* parkingSpace);

void addAllowedVehicleTypeUI(ParkingSpace* parkingSpace);

void removeAllowedVehicleTypeUI(ParkingSpace* parkingSpace);
