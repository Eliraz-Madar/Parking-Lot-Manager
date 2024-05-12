#include "ParkingSpaceView.h"
#include "ParkingSpace.h"
#include "ParkingVehicleView.h"
#include "GeneralView.h"


ParkingSpace createParkingSpaceUI()
{
	int spaceNumber;
	printf("Enter the space number: ");
	scanf("%d", &spaceNumber);

	ParkingSpace parkingSpace = initParkingSpace(spaceNumber);

	do
	{
		bool choice = getBooleanValueUI("Do you want to add an allowed vehicle type?");

		if (choice)
		{
			addAllowedVehicleTypeUI(&parkingSpace);
		}
		else
		{
			break;
		}
	} while (true);

	return parkingSpace;
}

void displayParkingSpaceMainMenu(ParkingSpace* parkingSpace)
{
	int choice;

	do {
		printf("----- Parking Space Menu -----\n");
		printf("1. Display Parking Space\n");
		printf("2. Add Allowed Vehicle Type\n");
		printf("3. Remove Allowed Vehicle Type\n");
		printf("-1. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			displayParkingSpace(parkingSpace);
			break;
		case 2:
			addAllowedVehicleTypeUI(parkingSpace);
			break;
		case 3:
			removeAllowedVehicleTypeUI(parkingSpace);
			break;
		default:
			printf("Invalid choice. Please try again.\n");
			break;
		}

	} while (choice != -1);
}

void displayParkingSpace(const ParkingSpace* parkingSpace)
{
	printf("Space number: %d\n", parkingSpace->spaceNumber);

	if (parkingSpace->allowedVehicleTypesCount == 0)
	{
		printf("No allowed vehicle types.\n");
	}
	else
	{
		printf("Allowed vehicle types: ");

		int c = 1;
		ARRAY_FOREACH(VehicleType, vehicleType, parkingSpace->allowedVehicleTypesArray, parkingSpace->allowedVehicleTypesCount)
		{
			printf("%d. %s ", c, vehicleTypeNames[*vehicleType]);
			c++;
		}

		printf("\n");
	}

	if (parkingSpace->parkedVehicle != NULL)
	{
		printf("Parked vehicle:\n");
		displayVehicle(parkingSpace->parkedVehicle);
	}
	else
	{
		printf("No vehicle parked.\n");
	}
}

void addAllowedVehicleTypeUI(ParkingSpace* parkingSpace)
{
	const VehicleType vehicleType = getVehicleTypeUI();

	const ArrayAddResult result = addAllowedVehicleType(parkingSpace, vehicleType);

	switch (result)
	{
	case ARRAY_ADD_SUCCESS:
		printf("Vehicle type added successfully.\n");
		break;
	case ARRAY_ADD_FAILED:
		printf("Memory error. Vehicle type not added.\n");
		break;
	case ARRAY_ADD_DUPLICATE:
		printf("Vehicle type already exists in the allowed types.\n");
		break;
	default:
		printf("Unknown error occured.\n");
		break;
	}
}

void removeAllowedVehicleTypeUI(ParkingSpace* parkingSpace)
{
	const VehicleType vehicleType = getVehicleTypeUI();

	const ArrayRemoveResult result = removeAllowedVehicleType(parkingSpace, vehicleType);

	switch (result)
	{
	case ARRAY_REMOVE_SUCCESS:
		printf("Vehicle type removed successfully.\n");
		break;
	case ARRAY_REMOVE_NOT_FOUND:
		printf("Vehicle type not found in the allowed types.\n");
		break;
	default:
		printf("Unknown error occured.\n");
		break;
	}
}
