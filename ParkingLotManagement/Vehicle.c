#include "Vehicle.h"

/// <summary>
/// Initializes the vehicle model.
/// </summary>
/// <param name="licensePlate">Null terminated license plate</param>
/// <param name="vehicleType">A Vehicle Type</param>
/// <returns>An object of the initialized Vehicle</returns>
Vehicle initVehicle(const char* licensePlate, VehicleType vehicleType)
{
	Vehicle vehicle;

	strncpy(vehicle.licensePlate, licensePlate, LICENSE_PLATE_LENGTH + 1);
	vehicle.licensePlate[LICENSE_PLATE_LENGTH] = '\0'; //Null terminated

	vehicle.vehicleType = vehicleType;

	return vehicle;
}

/// <summary>
/// Checks if the given license plate is capital and the length of LICENSE_PLANE_LENGTH
/// </summary>
/// <param name="licensePlate">Null terminated license plate</param>
/// <returns>Boolean value</returns>
bool isValidLicensePlate(const char* licensePlate)
{
	const size_t length = strlen(licensePlate);

	if (length != LICENSE_PLATE_LENGTH)
	{
		return false; //Not the correct length
	}

	//Checks each char. Must be a digit or a capital letter
	for (size_t i = 0; i < length; i++)
	{
		if (!isdigit(licensePlate[i]) && !isupper(licensePlate[i]))
		{
			return false;
		}
	}

	return true; //Valid
}

bool isSameVehicle(const Vehicle* vehicle1, const Vehicle* vehicle2)
{
	return strcmp(vehicle1->licensePlate, vehicle2->licensePlate) == 0;
}
