#pragma once
#include "General.h"

#define LICENSE_PLATE_LENGTH 10 //MAXIMUM LICENSE PLATE LENGTH IS 10 CHARACTERS BECAUSE OF COMPRESSION

typedef enum {
	CAR, // ������
	MOTORCYCLE, // ������
	TRUCK, // �����
	ELECTRIC_CAR // ��� �����
} VehicleType;

static const char* vehicleTypeNames[] = { "Car", "Motorcycle", "Truck", "Electric Car" };
#define NUM_VEHICLE_TYPES (sizeof(vehicleTypeNames) / sizeof(vehicleTypeNames[0])) // �� �� macro

typedef struct
{
	char licensePlate[LICENSE_PLATE_LENGTH + 1];
	VehicleType vehicleType;
} Vehicle;

Vehicle initVehicle(const char* licensePlate, VehicleType vehicleType);

bool isValidLicensePlate(const char* licensePlate);

bool isSameVehicle(const Vehicle* vehicle1, const Vehicle* vehicle2);
