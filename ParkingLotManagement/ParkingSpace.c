#include "ParkingSpace.h"

/// <summary>
/// Initializes the ParkingSpace model.
/// allowedVehicleTypeArray and parkedVehicle are set to NULL.
/// allowedVehicleTypeCount is set to 0.
/// isOccupied is set to false.
/// </summary>
/// <param name="spaceNumber">Space number</param>
/// <returns>The initialized ParkingSpace</returns>
ParkingSpace initParkingSpace(int spaceNumber)
{
	ParkingSpace parkingSpace;

	parkingSpace.spaceNumber = spaceNumber;
	parkingSpace.allowedVehicleTypesArray = NULL;
	parkingSpace.allowedVehicleTypesCount = 0;
	parkingSpace.parkedVehicle = NULL;

	return parkingSpace;
}

/// <summary>
/// Parks a specific vehicle in the parking space.
/// </summary>
/// <param name="parkingSpace">A pointer to the Parking Space that will now contain a vehicle</param>
/// <param name="vehicle">A const pointer to the Vehicle to be parked</param>
/// <returns>Status of the parking operation</returns>
ParkVehicleResponse parkVehicle(ParkingSpace* parkingSpace, Vehicle* vehicle) //vehicle cannot be a const as it is added to parkingSpace which is not a const, so therefore vehicle can be change from parkingSpace
{
	if (parkingSpace->parkedVehicle != NULL)
	{
		return PARKING_SPACE_ALREADY_OCCUPIED;
	}

	if (!isVehicleTypeAllowed(parkingSpace, vehicle->vehicleType))
	{
		return VEHICLE_TYPE_NOT_ALLOWED;
	}

	parkingSpace->parkedVehicle = vehicle;

	return VEHICLE_PARKED_SUCCESSFULLY;
}

/// <summary>
/// Vacates the Parking Space from a Vehicle.
/// </summary>
/// <param name="parkingSpace">A pointer to the Parking Space that will be vacated from a Vehicle</param>
/// <returns>The vacated Vehicle. NULL if parking space had no Vehicle.</returns>
Vehicle* vacateParkingSpace(ParkingSpace* parkingSpace)
{
	Vehicle* vehicle = parkingSpace->parkedVehicle;

	parkingSpace->parkedVehicle = NULL;

	return vehicle;
}

/// <summary>
/// Checks if the Vehicle Type is allowed in this Parking Space, that is, it is in the allowed types array.
/// </summary>
/// <param name="parkingSpace">A const pointer to the Parking Space that will be checked</param>
/// <param name="vehicleType">A Vehicle Type to be checked</param>
/// <returns>Boolean value</returns>
bool isVehicleTypeAllowed(const ParkingSpace* parkingSpace, VehicleType vehicleType)
{
	for (int i = 0; i < parkingSpace->allowedVehicleTypesCount; i++)
	{
		if (parkingSpace->allowedVehicleTypesArray[i] == vehicleType)
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// Checks if the parking space is free for a new vehicle
/// </summary>
/// <param name="parkingSpace">A const pointer to the Parking Space that will be checked</param>
/// <returns>Boolean value</returns>
bool isParkingSpaceAvailable(const ParkingSpace* parkingSpace)
{
	return parkingSpace->parkedVehicle == NULL;
}

/// <summary>
/// Adds a vehicle type to the allowed vehicle type array of the parking space.
/// </summary>
/// <param name="parkingSpace">A pointer to the parking space</param>
/// <param name="vehicleType">Vehicle type to be added</param>
/// <returns>Response for the operation</returns>
ArrayAddResult addAllowedVehicleType(ParkingSpace* parkingSpace, VehicleType vehicleType)
{
	if (isVehicleTypeAllowed(parkingSpace, vehicleType))
		return ARRAY_ADD_DUPLICATE;

	ArrayAddResult result;
	ADD_ELEMENT(VehicleType, parkingSpace->allowedVehicleTypesArray, parkingSpace->allowedVehicleTypesCount, vehicleType, &result);

	return result;

	/*if (isVehicleTypeAllowed(parkingSpace, vehicleType))
	{
		return ARRAY_ADD_DUPLICATE;
	}

	VehicleType* vehicleTypeArray = (VehicleType*)realloc(parkingSpace->allowedVehicleTypeArray, sizeof(VehicleType) * (parkingSpace->allowedVehicleTypeCount + 1));
	
	if (!vehicleTypeArray)
	{
		return ARRAY_ADD_FAILURE;
	}

	parkingSpace->allowedVehicleTypeArray = vehicleTypeArray;
	parkingSpace->allowedVehicleTypeArray[parkingSpace->allowedVehicleTypeCount++] = vehicleType;

	return ARRAY_ADD_SUCCESS;*/
}

/// <summary>
/// Removes a vehicle type from the allowed vehicle type array of the parking space.
/// </summary>
/// <param name="parkingSpace">A pointer to the parking space</param>
/// <param name="vehicleType">Vehicle type to be removed</param>
/// <returns>
/// True if the type was removed, False if type was not found.
/// Anyway after that operation the specific vehicle type doesn not exist.
/// </returns>
ArrayRemoveResult removeAllowedVehicleType(ParkingSpace* parkingSpace, VehicleType vehicleType)
{
	ArrayRemoveResult arrayRemoveResult;

	REMOVE_ELEMENT(VehicleType, parkingSpace->allowedVehicleTypesArray, parkingSpace->allowedVehicleTypesCount, vehicleType, &arrayRemoveResult);

	return arrayRemoveResult;
}

bool isSameParkingSpaceBySpaceNumber(const ParkingSpace* a, const ParkingSpace* b)
{
	return a->spaceNumber == b->spaceNumber;
}

/// <summary>
/// Frees any allocated memory within a ParkingSpace
/// </summary>
/// <param name="parkingSpace">A pointer to the parking space</param>
void freeParkingSpace(ParkingSpace* parkingSpace)
{
	free(parkingSpace->allowedVehicleTypesArray);

	parkingSpace->allowedVehicleTypesArray = NULL;
	parkingSpace->allowedVehicleTypesCount = 0;
}
