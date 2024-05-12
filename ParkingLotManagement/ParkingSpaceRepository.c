#include "ParkingSpaceRepository.h"

#include "VehicleRepository.h"

bool readParkingSpaceFromFile(ParkingSpace* parkingSpace, ParkingCustomer* customerArray, size_t customerArrayCount, const FileContext* fileContext)
{
	int spaceNumber;
	if (!readIntFromFile(&spaceNumber, fileContext))
		return false;

	*parkingSpace = initParkingSpace(spaceNumber);

	size_t allowedVehicleTypesCount;
	if (!readSizeTFromFile(&allowedVehicleTypesCount, fileContext))
		return false;

	for (size_t i = 0; i < allowedVehicleTypesCount; i++)
	{
		VehicleType vehicleType;
		if (!readIntFromFile((int*)&vehicleType, fileContext))
			return false;

		addAllowedVehicleType(parkingSpace, vehicleType);
	}

	bool isOccupied;
	if (!readBoolFromFile(&isOccupied, fileContext))
		return false;

	if (isOccupied)
	{
		char vehicleLicensePlateBuffer[LICENSE_PLATE_LENGTH + 2];

		if (!readStringFromFile(vehicleLicensePlateBuffer, LICENSE_PLATE_LENGTH + 2, fileContext))
			return false;

		if (isValidLicensePlate(vehicleLicensePlateBuffer))
		{
			//Find the vehicle with the license plate
			Vehicle* parkedVehicle = NULL;
			ARRAY_FOREACH(ParkingCustomer, customer, customerArray, customerArrayCount)
			{
				ARRAY_FOREACH_PTR(Vehicle, vehicle, customer->vehicleArray, customer->vehicleArrayCount)
				{
					if (strcmp((*vehicle)->licensePlate, vehicleLicensePlateBuffer) == 0)
					{
						parkedVehicle = *vehicle;
						break;
					}
				}
			}

			parkingSpace->parkedVehicle = parkedVehicle;
		}

	}
	else
	{
		parkingSpace->parkedVehicle = NULL;
	}

	return true;
}

bool writeParkingSpaceToFile(const ParkingSpace* parkingSpace, const FileContext* fileContext)
{
	if (!writeIntToFile(parkingSpace->spaceNumber, fileContext))
		return false;

	if (!writeSizeTToFile(parkingSpace->allowedVehicleTypesCount, fileContext))
		return false;

	for (size_t i = 0; i < parkingSpace->allowedVehicleTypesCount; i++)
	{
		if (!writeIntToFile((int)parkingSpace->allowedVehicleTypesArray[i], fileContext))
			return false;
	}

	if (parkingSpace->parkedVehicle != NULL)
	{
		if (!writeBoolToFile(true, fileContext))
			return false;

		if (!writeStringToFile(parkingSpace->parkedVehicle->licensePlate, fileContext))
			return false;
	}
	else
	{
		if (!writeBoolToFile(false, fileContext))
			return false;
	}

	return true;
}
