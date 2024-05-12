#pragma once
#include "General.h"
#include "Vehicle.h"

typedef struct
{
	int spaceNumber;
	VehicleType* allowedVehicleTypesArray;
	size_t allowedVehicleTypesCount;
	Vehicle* parkedVehicle;
} ParkingSpace;

typedef enum
{
	VEHICLE_PARKED_SUCCESSFULLY,
	PARKING_SPACE_ALREADY_OCCUPIED,
	VEHICLE_TYPE_NOT_ALLOWED
} ParkVehicleResponse;

ParkingSpace initParkingSpace(int spaceNumber);

ParkVehicleResponse parkVehicle(ParkingSpace* parkingSpace, Vehicle* vehicle);
Vehicle* vacateParkingSpace(ParkingSpace* parkingSpace);

bool isVehicleTypeAllowed(const ParkingSpace* parkingSpace, VehicleType vehicleType);

bool isParkingSpaceAvailable(const ParkingSpace* parkingSpace);

ArrayAddResult addAllowedVehicleType(ParkingSpace* parkingSpace, VehicleType vehicleType);

ArrayRemoveResult removeAllowedVehicleType(ParkingSpace* parkingSpace, VehicleType vehicleType);

bool isSameParkingSpaceBySpaceNumber(const ParkingSpace* a, const ParkingSpace* b);

void freeParkingSpace(ParkingSpace* parkingSpace);
