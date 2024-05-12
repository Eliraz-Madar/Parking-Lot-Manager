#include "ParkingVehicleView.h"
#include "General.h"
#include "GeneralView.h"
#include "Vehicle.h"

Vehicle createVehicleUI()
{
	char licensePlateBuffer[255];

	getVehicleLicensePlateUI(licensePlateBuffer);

	const VehicleType selectedType = getVehicleTypeUI();

	return initVehicle(licensePlateBuffer, selectedType);
}

void getVehicleLicensePlateUI(char* licensePlateBuffer)
{
	bool validLicensePlate = false;

	clearInputBuffer();

	do
	{
		printf("Enter the vehicle's license plate (%d uppercase/numbers): ", LICENSE_PLATE_LENGTH);
		
		fgets(licensePlateBuffer, LICENSE_PLATE_LENGTH + 2, stdin);

		licensePlateBuffer[strcspn(licensePlateBuffer, "\n")] = 0;

		//Check if the license plate is valid
		validLicensePlate = isValidLicensePlate(licensePlateBuffer);

		if (!validLicensePlate)
		{
			printf("Invalid license plate. Please enter a valid license plate:\n");
		}
	} while (!validLicensePlate);
}

VehicleType getVehicleTypeUI()
{
	int choice = -1;
	printf("Please select a vehicle type:\n");
	for (size_t i = 0; i < NUM_VEHICLE_TYPES; i++)
	{
		printf("%llu. %s\n", i + 1, vehicleTypeNames[i]);
	}


	printf("Enter your choice (1-%llu): ", NUM_VEHICLE_TYPES);
	scanf("%d", &choice);

	clearInputBuffer(); // Assuming this function correctly clears any remaining characters in the input buffer

	while (choice < 1 || choice > NUM_VEHICLE_TYPES)
	{
		printf("Invalid input. Please enter a number between 1 and %llu: ", NUM_VEHICLE_TYPES);
		scanf("%d", &choice);
		clearInputBuffer();
	}

	// Adjusting choice to match VehicleType enum indexing
	return (VehicleType)(choice - 1);
}

void displayVehicle(const Vehicle* vehicle)
{
	if(vehicle == NULL)
	{
		printf("Vehicle is NULL.\n");
		return;
	}

	printf("License Plate: %s, Vehicle Type: %s\n", vehicle->licensePlate, vehicleTypeNames[vehicle->vehicleType]);
}
