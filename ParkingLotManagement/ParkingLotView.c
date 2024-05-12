#include "ParkingLotView.h"

#include "GeneralView.h"
#include "ParkingCustomerView.h"
#include "ParkingPaymentView.h"
#include "ParkingSpaceView.h"
#include "ParkingVehicleView.h"

ParkingLot createParkingLotUI(int id)
{
	double parkingHourlyRate;

	do
	{
		printf("Enter hourly rate for the parking lot: \n");
		scanf("%lf", &parkingHourlyRate);

		if (parkingHourlyRate < 0)
		{
			printf("Hourly rate cannot be below 0. Please try again.\n");
		}
	} while (parkingHourlyRate < 0);

	const ParkingLot newLot = initParkingLot(id, parkingHourlyRate);
	return newLot;
}

void displayParkingLotManagementMenu(int parkingLotId);

void displayParkingLotMainMenu(ParkingLot* parkingLot)
{
	if (parkingLot == NULL)
	{
		printf("Error: No parking lot data available.\n");
		return;
	}

	int choice;
	do
	{
		displayParkingLotManagementMenu(parkingLot->parkingLotId);
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			displayParkingLotDetails(parkingLot);
			break;
		case 2:
			displayParkingLotDiagram(parkingLot);
			break;
		case 3:
			displayAllParkingSpaces(parkingLot);
			break;
		case 4:
			addParkingSpaceToParkingLotUI(parkingLot);
			break;
		case 5:
			removeParkingSpaceFromParkingLotUI(parkingLot);
			break;
		case 6:
			selectAndDisplayParkingSpaceUI(parkingLot);
			break;
		case 7:
			displayAllCustomers(parkingLot);
			break;
		case 8:
			addCustomerToParkingLotUI(parkingLot);
			break;
		case 9:
			removeCustomerFromParkingLotUI(parkingLot);
			break;
		case 10:
			selectAndDisplayCustomerUI(parkingLot);
			break;
		case 11:
			sortCustomersUI(parkingLot);
			break;
		case 12:
			searchCustomerUI(parkingLot);
			break;
		case 13:
			addVehicleToParkingLotUI(parkingLot);
			break;
		case 14:
			removeVehicleFromParkingLotUI(parkingLot);
			break;
		case 15:
			parkVehicleInParkingLotUI(parkingLot);
			break;
		case 16:
			vacateVehicleFromParkingLotUI(parkingLot);
			break;

		case -1:
			printf("Exiting the menu...\n");
			break;
		default:
			printf("Invalid option, please try again.\n");
		}
	} while (choice != -1);
}

void displayParkingLotManagementMenu(int parkingLotId)
{
	printf("\n*** Parking Lot %d Management Menu ***\n", parkingLotId);
	printf("1. Display Parking Lot Details\n");
	printf("2. Display Parking Lot Diagram\n");

	printf("3. Show All Parking Spaces\n");
	printf("4. Add Parking Space\n");
	printf("5. Remove Parking Space\n");
	printf("6. Select Parking Space and Display Menu \n");

	printf("7. Show All Customers\n");
	printf("8. Add Customer\n");
	printf("9. Remove Customer\n");
	printf("10. Select Customer and Display Menu \n");
	printf("11. Sort Customers\n");
	printf("12. Search Customer\n");

	printf("13. Add Vehicle To Customer\n");
	printf("14. Remove Vehicle From Customer\n");

	printf("15. Park Vehicle In Parking Lot \n");
	printf("16. Vacate Vehicle From Parking Lot \n");

	printf("-1. Exit\n");
	printf("Select an option: ");
}

void displayParkingLotDetails(const ParkingLot* parkingLot)
{
	if (parkingLot == NULL)
	{
		printf("Error: No parking lot data available.\n");
		return;
	}

	printf("Parking Lot ID: %d\n", parkingLot->parkingLotId);
	printf("Hourly Rate: $%.2f\n", parkingLot->parkingHourlyRate);
	printf("Number of Customers: %llu\n", parkingLot->parkingCustomersArrayCount);
	printf("Number of Parking Spaces: %llu\n", parkingLot->parkingSpacesArrayCount);
	printf("Number of Occupied Parking Spaces: %llu\n", getOccupiedParkingSpaceCount(parkingLot));
}

void addParkingSpaceToParkingLotUI(ParkingLot* parkingLot)
{
	if (parkingLot == NULL)
	{
		printf("Error: No parking lot data available.\n");
		return;
	}

	const ParkingSpace newSpace = createParkingSpaceUI();

	const ArrayAddResult result = addParkingSpaceToParkingLot(parkingLot, newSpace);

	switch (result)
	{
	case ARRAY_ADD_SUCCESS:
		printf("Parking space added successfully.\n");
		break;

	case ARRAY_ADD_DUPLICATE:
		printf("Parking space with number %d already exists in the parking lot.\n", newSpace.spaceNumber);
		break;

	case ARRAY_ADD_FAILED:
		printf("Failed to add parking space. Memory allocation error.\n");
		break;

	default:
		printf("Unknown error occurred.\n");
		break;
	}
}

void removeParkingSpaceFromParkingLotUI(ParkingLot* parkingLot)
{
	if (parkingLot == NULL)
	{
		printf("Error: No parking lot data available.\n");
		return;
	}

	int spaceNumber;
	printf("Enter the space number to remove: ");
	scanf("%d", &spaceNumber);

	const ArrayRemoveResult result = removeParkingSpaceFromParkingLotBySpaceNumber(parkingLot, spaceNumber);

	switch (result)
	{
	case ARRAY_REMOVE_SUCCESS:
		printf("Parking space with number %d removed successfully.\n", spaceNumber);
		break;

	case ARRAY_REMOVE_NOT_FOUND:
		printf("Parking space with number %d not found.\n", spaceNumber);
		break;

	default:
		printf("Unknown error occurred.\n");
		break;
	}
}

void selectAndDisplayParkingSpaceUI(ParkingLot* parkingLot)
{
	if (parkingLot == NULL || parkingLot->parkingSpacesArray == NULL || parkingLot->parkingSpacesArrayCount == 0)
	{
		printf("There are no parking spaces to choose from.\n");
		return;
	}

	int spaceNumber;
	printf("Enter the space number to choose: ");
	scanf("%d", &spaceNumber);

	ParkingSpace* chosenSpace = findParkingSpaceBySpaceNumber(parkingLot, spaceNumber);
	if (chosenSpace == NULL)
	{
		printf("Parking space with number %d not found.\n", spaceNumber);
		return;
	}

	displayParkingSpaceMainMenu(chosenSpace);
}

void displayAllCustomers(const ParkingLot* parkingLot)
{
	if (parkingLot == NULL)
	{
		printf("Error: No parking lot data available.\n");
		return;
	}

	printf("Total Customers: %zu\n\n", parkingLot->parkingCustomersArrayCount);

	for (size_t i = 0; i < parkingLot->parkingCustomersArrayCount; i++)
	{
		displayParkingCustomer(&parkingLot->parkingCustomersArray[i]);
		printf("\n");
	}
}

// Vehicle type symbols for parking lot diagram
static const char vehicleTypeSymbols[] = { 'C', 'M', 'T', 'E', 'X' }; // Car, Motorcycle, Truck, Electric, Other
#define PARKING_SPACES_PER_ROW 5

void displayParkingLotDiagram(const ParkingLot* lot)
{
	printf("Parking Lot ID: %d\n", lot->parkingLotId);
	printf("Hourly Rate: $%.2f\n", lot->parkingHourlyRate);
	printf("Number of Parking Spaces: %llu\n", lot->parkingSpacesArrayCount);
	printf("Number of Occupied Parking Spaces: %llu\n", getOccupiedParkingSpaceCount(lot));

	for (size_t i = 0; i < lot->parkingSpacesArrayCount; i++)
	{
		if (lot->parkingSpacesArray[i].parkedVehicle != NULL)
		{
			const VehicleType parkingVehicleType = lot->parkingSpacesArray[i].parkedVehicle->vehicleType;

			char symbol = 'X'; // Default symbol
			if (parkingVehicleType >= 0 && parkingVehicleType < (int)(sizeof(vehicleTypeSymbols) / sizeof(vehicleTypeSymbols[0])))
			{
				symbol = vehicleTypeSymbols[parkingVehicleType];
			}

			printf("[%c] ", symbol);
		}
		else
		{
			printf("[_] ");
		}

		if ((i + 1) % PARKING_SPACES_PER_ROW == 0)
		{
			printf("\n");
		}
	}
	printf("\n");
}

void displayAllParkingSpaces(const ParkingLot* parkingLot)
{
	if (parkingLot == NULL)
	{
		printf("Error: No parking lot data available.\n");
		return;
	}

	printf("Total Parking Spaces: %zu\n\n", parkingLot->parkingSpacesArrayCount);

	for (size_t i = 0; i < parkingLot->parkingSpacesArrayCount; i++)
	{
		displayParkingSpace(&parkingLot->parkingSpacesArray[i]);
		printf("\n");
	}
}

void addCustomerToParkingLotUI(ParkingLot* parkingLot)
{
	if (parkingLot == NULL)
	{
		printf("Error: No parking lot data available.\n");
		return;
	}

	const ParkingCustomer parkingCustomer = createParkingCustomerUI(++parkingLot->lastUsedCustomerId);

	const ArrayAddResult result = addCustomerToParkingLot(parkingLot, parkingCustomer);

	switch (result)
	{
	case ARRAY_ADD_SUCCESS:
		printf("Customer added successfully. ID: %d\n", parkingCustomer.customerId);
		break;

	case ARRAY_ADD_DUPLICATE:
		printf("Customer with ID %d already exists in the parking lot.\n", parkingLot->lastUsedCustomerId);
		break;

	case ARRAY_ADD_FAILED:
		printf("Failed to add customer. Memory allocation error.\n");
		break;

	default:
		printf("Unknown error occurred.\n");
		break;
	}
}

void removeCustomerFromParkingLotUI(ParkingLot* parkingLot)
{
	if (parkingLot == NULL)
	{
		printf("Error: No parking lot data available.\n");
		return;
	}

	int customerId;
	printf("Enter the ID of the customer to remove: ");
	scanf("%d", &customerId);

	ParkingCustomer* customer = findCustomerById(parkingLot, customerId);
	if (customer == NULL)
	{
		printf("Customer with ID %d not found.\n", customerId);
		return;
	}

	ARRAY_FOREACH_PTR(Vehicle, vehicle, customer->vehicleArray, customer->vehicleArrayCount)
	{
		ParkingSpace* space = findParkingSpaceByVehicle(parkingLot, *vehicle);
		if (space != NULL) // If the vehicle is parked, vacate the space
		{
			vacateParkingSpace(space);
		}
	}

	freeParkingCustomer(customer); // Free the memory of the removed customer

	const ArrayRemoveResult result = removeCustomerFromParkingLot(parkingLot, *customer);

	switch (result)
	{
	case ARRAY_REMOVE_SUCCESS:
		printf("Customer with ID %d removed successfully.\n", customerId);
		break;

	case ARRAY_REMOVE_NOT_FOUND:
		printf("Customer with ID %d not found.\n", customerId);
		break;

	default:
		printf("Unknown error occurred.\n");
		break;
	}
}

void selectAndDisplayCustomerUI(ParkingLot* parkingLot)
{
	if (parkingLot == NULL || parkingLot->parkingCustomersArray == NULL || parkingLot->parkingCustomersArrayCount == 0)
	{
		printf("There are no customers to choose from.\n");
		return;
	}

	int customerId;
	printf("Enter the ID of the customer to choose: ");
	scanf("%d", &customerId);

	ParkingCustomer* chosenCustomer = findCustomerById(parkingLot, customerId);
	if (chosenCustomer == NULL)
	{
		printf("Customer with ID %d not found.\n", customerId);
		return;
	}

	displayParkingCustomerMainMenu(chosenCustomer);
}

void sortCustomersUI(ParkingLot* parkingLot)
{
	if (parkingLot == NULL)
	{
		printf("Error: No parking lot data available.\n");
		return;
	}

	int choice;

	printf("\n*** Sort Customers Menu ***\n");
	printf("1. Sort by ID\n");
	printf("2. Sort by Name\n");
	printf("3. Sort by Total Paid Amount\n");
	printf("4. Sort by Total Vehicles\n");
	printf("Select an option: ");
	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
		sortCustomersInParkingLot(parkingLot, CUSTOMERS_SORT_BY_ID);
		break;

	case 2:
		sortCustomersInParkingLot(parkingLot, CUSTOMERS_SORT_BY_NAME);
		break;

	case 3:
		sortCustomersInParkingLot(parkingLot, CUSTOMERS_SORT_BY_TOTAL_PAID_AMOUNT);
		break;

	case 4:
		sortCustomersInParkingLot(parkingLot, CUSTOMERS_SORT_BY_TOTAL_VEHICLES);
		break;

	default:
		printf("Invalid option, please try again.\n");
	}

	printf("Customers sorted successfully.\n");
}

void searchCustomerUI(ParkingLot* parkingLot)
{
	if (parkingLot == NULL)
	{
		printf("Error: No parking lot data available.\n");
		return;
	}

	int choice;
	do
	{
		printf("\n*** Search Customer Menu ***\n");
		printf("1. Search by ID\n");
		printf("2. Search by Name\n");
		printf("3. Search by Total Paid Amount\n");
		printf("4. Search by Total Vehicles\n");
		printf("-1. Exit\n");
		printf("Select an option: ");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
		{
			int customerId;
			printf("Enter the ID of the customer to search: ");
			scanf("%d", &customerId);

			const ParkingCustomer* customer = findCustomerById(parkingLot, customerId);
			if (customer != NULL)
			{
				displayParkingCustomer(customer);
			}
			else
			{
				printf("Customer with ID %d not found.\n", customerId);
			}
			break;
		}

		case 2:
		{
			char name[255];
			printf("Enter the name of the customer to search: ");
			scanf("%s", name);

			const ParkingCustomer* customer = findCustomerByNameBinarySearch(parkingLot, name);
			if (customer != NULL)
			{
				displayParkingCustomer(customer);
			}
			else
			{
				printf("Customer with name %s not found.\n", name);
			}
			break;
		}

		case 3:
		{
			double totalPaidAmount;
			printf("Enter the total paid amount of the customer to search: ");
			scanf("%lf", &totalPaidAmount);

			const ParkingCustomer* customer = findCustomerByTotalPaidAmountBinarySearch(parkingLot, totalPaidAmount);
			if (customer != NULL)
			{
				displayParkingCustomer(customer);
			}
			else
			{
				printf("Customer with total paid amount %.2f not found.\n", totalPaidAmount);
			}
			break;
		}

		case 4:
		{
			size_t vehicleCount;
			printf("Enter the total vehicles of the customer to search: ");
			scanf("%zu", &vehicleCount);

			const ParkingCustomer* customer = findCustomerByVehicleCountBinarySearch(parkingLot, vehicleCount);
			if (customer != NULL)
			{
				displayParkingCustomer(customer);
			}
			else
			{
				printf("Customer with %zu vehicles not found.\n", vehicleCount);
			}
			break;
		}
		case -1:
			printf("Exiting the menu...\n");
			break;
		default:
			printf("Invalid option, please try again.\n");
			break;
		}
	} while (choice != -1);
}

void addVehicleToParkingLotUI(const ParkingLot* parkingLot)
{
	if (parkingLot == NULL)
	{
		printf("Error: No parking lot data available.\n");
		return;
	}


	int customerId;
	printf("Enter the ID of the customer to add the vehicle to: ");
	scanf("%d", &customerId);

	ParkingCustomer* parkingCustomer = findCustomerById(parkingLot, customerId);
	if (parkingCustomer == NULL)
	{
		printf("Customer with ID %d not found.\n", customerId);
		return;
	}

	Vehicle newVehicle = createVehicleUI();

	ARRAY_FOREACH(ParkingCustomer, parkingCustomerItem, parkingLot->parkingCustomersArray, parkingLot->parkingCustomersArrayCount)
	{
		const Vehicle* vehicle = findVehicleFromCustomerByLicensePlate(parkingCustomerItem, newVehicle.licensePlate);

		if (vehicle != NULL)
		{
			printf("Vehicle with license plate %s already exists in customer %d.\n", newVehicle.licensePlate, parkingCustomerItem->customerId);
			return;
		}
	}

	const ArrayAddResult result = addVehicleToCustomer(parkingCustomer, newVehicle);

	switch (result)
	{
	case ARRAY_ADD_SUCCESS:
		printf("Vehicle with license plate %s added successfully to customer %d.\n", newVehicle.licensePlate, customerId);
		break;

	case ARRAY_ADD_DUPLICATE:
		printf("Vehicle with license plate %s already exists in customer %d.\n", newVehicle.licensePlate, customerId);
		break;

	case ARRAY_ADD_FAILED:
		printf("Failed to add vehicle with license plate %s to customer %d. Memory allocation error.\n", newVehicle.licensePlate, customerId);
		break;

	default:
		printf("Unknown error occurred.\n");
		break;
	}
}

void removeVehicleFromParkingLotUI(const ParkingLot* parkingLot)
{
	if (parkingLot == NULL)
	{
		printf("Error: No parking lot data available.\n");
		return;
	}

	char licensePlateBuffer[255];
	getVehicleLicensePlateUI(licensePlateBuffer);

	ARRAY_FOREACH(ParkingCustomer, parkingCustomer, parkingLot->parkingCustomersArray, parkingLot->parkingCustomersArrayCount)
	{
		Vehicle* vehicle = findVehicleFromCustomerByLicensePlate(parkingCustomer, licensePlateBuffer);
		if (vehicle != NULL)
		{
			const ParkingSpace* parkingSpace = findParkingSpaceByVehicle(parkingLot, vehicle);
			if (parkingSpace != NULL)
			{
				printf("Vehicle with license plate %s is parked in parking space %d and cannot be removed.\n", licensePlateBuffer, parkingSpace->spaceNumber);
				return;
			}

			/*printf("This operation will remove all payments associated with this vehicle.\n");
			if (!getBooleanValueUI("Continue?"))
			{
				return;
			}*/

			/*ARRAY_FOREACH(ParkingPayment, payment, parkingCustomer->paymentsArray, parkingCustomer->paymentsArrayCount)
			{
				if (isSameVehicle(payment->vehicle, vehicle))
				{
					removePaymentFromCustomer(parkingCustomer, *payment);
				}
			}*/

			const ArrayRemoveResult result = removeVehicle(parkingCustomer, vehicle);

			switch (result)
			{
			case ARRAY_REMOVE_SUCCESS:
				printf("Vehicle with license plate %s removed successfully from customer %d.\n", licensePlateBuffer, parkingCustomer->customerId);
				break;

			case ARRAY_REMOVE_NOT_FOUND:
				printf("Vehicle with license plate %s not found in customer %d.\n", licensePlateBuffer, parkingCustomer->customerId);
				break;

			default:
				printf("Unknown error occurred.\n");
				break;
			}

			return;
		}
	}

	printf("Vehicle with license plate %s not found in any customer.\n", licensePlateBuffer);
}

bool isVehicleAlreadyParked(const ParkingLot* parkingLot, const char* licensePlate)
{
	ARRAY_FOREACH(ParkingSpace, parkingSpace, parkingLot->parkingSpacesArray, parkingLot->parkingSpacesArrayCount)
	{
		if (parkingSpace->parkedVehicle != NULL && strcmp(parkingSpace->parkedVehicle->licensePlate, licensePlate) == 0)
		{
			printf("Vehicle with license plate %s is already parked in space %d.\n", licensePlate, parkingSpace->spaceNumber);
			return true;
		}
	}
	return false;
}

ParkingSpace* getParkingSpace(const ParkingLot* parkingLot, int spaceNumber)
{
	ParkingSpace* parkingSpace = findParkingSpaceBySpaceNumber(parkingLot, spaceNumber);
	if (parkingSpace == NULL)
	{
		printf("Parking space with number %d not found.\n", spaceNumber);
	}
	else if (parkingSpace->parkedVehicle != NULL)
	{
		printf("Parking space %d is already occupied.\n", spaceNumber);
		return NULL;
	}
	return parkingSpace;
}

bool processVehicleParking(const ParkingLot* parkingLot, ParkingSpace* parkingSpace, const char* licensePlate)
{
	ARRAY_FOREACH(ParkingCustomer, parkingCustomer, parkingLot->parkingCustomersArray, parkingLot->parkingCustomersArrayCount)
	{
		Vehicle* vehicle = findVehicleFromCustomerByLicensePlate(parkingCustomer, licensePlate);
		if (vehicle != NULL)
		{
			if (!isVehicleTypeAllowed(parkingSpace, vehicle->vehicleType))
			{
				printf("Vehicle with license plate %s is not allowed in space %d.\n", licensePlate, parkingSpace->spaceNumber);
				return false;
			}
			parkVehicle(parkingSpace, vehicle);

			const double hourlyRate = parkingLot->parkingHourlyRate;

			ParkingPayment payment = createParkingPaymentUI(*vehicle, hourlyRate);

			if (parkingCustomer->parkingSubscription.isActive && isSubscriptionActive(&parkingCustomer->parkingSubscription, &payment.entryDateTime)) // Check if subscription is active
			{
				payment.parkingHourlyRate *= 1 - (parkingCustomer->parkingSubscription.discountPercentage / 100.0); // Apply discount
			}

			addPaymentToCustomer(parkingCustomer, payment);

			printf("Vehicle with license plate %s parked successfully in space %d.\n", licensePlate, parkingSpace->spaceNumber);
			return true;
		}
	}
	printf("Vehicle with license plate %s not found in any customer.\n", licensePlate);
	return false;
}

void parkVehicleInParkingLotUI(const ParkingLot* parkingLot)
{
	if (parkingLot == NULL)
	{
		printf("Error: No parking lot data available.\n");
		return;
	}

	if (parkingLot->parkingSpacesArrayCount == 0)
	{
		printf("No parking spaces available.\n");
		return;
	}

	if (getAvailableParkingSpaceCount(parkingLot) == 0)
	{
		printf("All parking spaces are occupied.\n");
		return;
	}

	char licensePlateBuffer[255];
	getVehicleLicensePlateUI(licensePlateBuffer);

	if (isVehicleAlreadyParked(parkingLot, licensePlateBuffer))
	{
		return; // Vehicle is already parked
	}

	int spaceNumber;
	printf("Enter the parking space number to park the vehicle: ");
	scanf("%d", &spaceNumber);
	clearInputBuffer(); // Clear the buffer after reading input

	ParkingSpace* parkingSpace = getParkingSpace(parkingLot, spaceNumber);
	if (parkingSpace == NULL) {
		return; // Suitable parking space not found
	}

	processVehicleParking(parkingLot, parkingSpace, licensePlateBuffer);
}

bool checkVehiclePaymentForCustomerUI(ParkingCustomer* customer, Vehicle* vehicle)
{
	ParkingPayment* unpaidPayment = findUnpaidPaymentFromCustomerByVehicle(customer, vehicle);

	if (unpaidPayment != NULL)
	{
		if (!unpaidPayment->isPaid)
		{
			printf("Vehicle with license plate %s has not paid for parking.\n", vehicle->licensePlate);
			const bool pay = getBooleanValueUI("Would you like to pay now?");
			if (!pay)
			{
				printf("Payment not made. Vehicle with license plate %s cannot vacate.\n", vehicle->licensePlate);
				return false;
			}

			if (!makePaymentUI(unpaidPayment))
			{
				printf("Payment failed. Vehicle with license plate %s cannot vacate.\n", vehicle->licensePlate);
				return false;
			}

			customer->totalPaidAmount += unpaidPayment->amountPaid; // Update total paid amount, mostly for sorting purposes. Do not rely on this value for financial calculations!
		}
	}
	else
	{
		printf("Payment not found for vehicle with license plate %s.\n", vehicle->licensePlate);
	}

	return true; // Payment successful or not required
}

void vacateVehicleFromParkingLotUI(const ParkingLot* parkingLot)
{
	if (parkingLot == NULL)
	{
		printf("Error: No parking lot data available.\n");
		return;
	}

	if (getOccupiedParkingSpaceCount(parkingLot) == 0)
	{
		printf("No vehicles are parked in the parking lot.\n");
		return;
	}

	char licensePlateBuffer[255];
	getVehicleLicensePlateUI(licensePlateBuffer);

	ARRAY_FOREACH(ParkingSpace, parkingSpace, parkingLot->parkingSpacesArray, parkingLot->parkingSpacesArrayCount)
	{
		if (parkingSpace->parkedVehicle != NULL && strcmp(parkingSpace->parkedVehicle->licensePlate, licensePlateBuffer) == 0)
		{
			ARRAY_FOREACH(ParkingCustomer, customer, parkingLot->parkingCustomersArray, parkingLot->parkingCustomersArrayCount)
			{
				Vehicle* vehicle = findVehicleFromCustomerByLicensePlate(customer, licensePlateBuffer);

				if (vehicle != NULL)
				{
					if (!checkVehiclePaymentForCustomerUI(customer, vehicle))
					{
						return;
					}

					vacateParkingSpace(parkingSpace);
					printf("Vehicle with license plate %s vacated successfully from space %d.\n", vehicle->licensePlate, parkingSpace->spaceNumber);
					return; // Vehicle found and vacated
				}
			}

			printf("Vehicle with license plate %s not found in any customer.\n", licensePlateBuffer);
			return;
		}
	}

	printf("Vehicle with license plate %s not found in any parking space.\n", licensePlateBuffer);
}
