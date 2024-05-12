#include "ParkingLotManagerView.h"
#include "ParkingLotView.h"

//Not best practice.
static int lastParkingLotId = 0;

ParkingLotManager createParkingLotManagerUI()
{
	char companyName[255];
	printf("Enter the name of the parking lot company: ");
	fgets(companyName, 255, stdin);
	companyName[strcspn(companyName, "\n")] = 0;

	const ParkingLotManager manager = initParkingLotManager(companyName);

	return manager;
}

void displayParkingLotManagerMainMenu(ParkingLotManager* parkingLotManager)
{
	int choice;
	do {
		printf("\n*** %s Parking Lots Manager ***\n", parkingLotManager->companyName);
		printf("1. Display All Parking Lots Details\n");
		printf("2. Summarize All Payments\n");
		printf("3. Add Parking Lot\n");
		printf("4. Remove Parking Lot\n");
		printf("5. Select Parking Lot and Display Menu\n");
		printf("-1. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			displayAllParkingLotsDetails(parkingLotManager);
			break;
		case 2:
			displayPaymentSummary(parkingLotManager);
			break;
		case 3:
			addParkingLotUI(parkingLotManager);
			break;
		case 4:
			removeParkingLotUI(parkingLotManager);
			break;
		case 5:
			selectAndDisplayParkingLotUI(parkingLotManager);
			break;
		case -1:
			printf("Exiting...\n");
			break;
		default:
			printf("Invalid choice. Please try again.\n");
		}
	} while (choice != -1);
}

void displayAllParkingLotsDetails(const ParkingLotManager* parkingLotManager)
{
	if (parkingLotManager == NULL || parkingLotManager->parkingLotList.head == NULL)
	{
		printf("No parking lots to display.\n");
		return;
	}

	printf("Parking Lots Details:\n");
	Node* current = parkingLotManager->parkingLotList.head;
	while (current != NULL)
	{
		displayParkingLotDetails((ParkingLot*)current->key);
		printf("----\n");
		current = current->next;
	}
}

void displayPaymentSummary(const ParkingLotManager* parkingLotManager)
{
	double totalPayments = summarizePayments(parkingLotManager);
	printf("Total Payments: $%.2f\n", totalPayments);
}

void addParkingLotUI(ParkingLotManager* parkingLotManager)
{
	const ParkingLot newLot = createParkingLotUI((int)++(parkingLotManager->lastUsedParkingLotId));

	if (addParkingLot(parkingLotManager, newLot))
	{
		printf("Parking lot added successfully.\n");
	}
	else
	{
		printf("Failed to add parking lot.\n");
	}
}

void removeParkingLotUI(ParkingLotManager* parkingLotManager)
{
	if (parkingLotManager == NULL || parkingLotManager->parkingLotList.head == NULL)
	{
		printf("There are no parking lots to remove.\n");
		return;
	}

	int parkingLotId;
	printf("Enter the ID of the parking lot to remove: ");
	scanf("%d", &parkingLotId);

	ParkingLot* parkingLotToRemove = findParkingLotById(parkingLotManager, parkingLotId);
	if (parkingLotToRemove == NULL)
	{
		printf("Parking lot with ID %d not found.\n", parkingLotId);
		return;
	}

	const bool removalResult = removeParkingLot(parkingLotManager, parkingLotToRemove);
	if (removalResult)
	{
		printf("Parking lot with ID %d has been successfully removed.\n", parkingLotId);
	}
	else
	{
		printf("Failed to remove the parking lot with ID %d.\n", parkingLotId);
	}
}

void selectAndDisplayParkingLotUI(const ParkingLotManager* parkingLotManager)
{
	if (parkingLotManager == NULL || parkingLotManager->parkingLotList.head == NULL)
	{
		printf("There are no parking lots to choose from.\n");
		return;
	}

	int parkingLotId;
	printf("Enter the ID of the parking lot to choose: ");
	scanf("%d", &parkingLotId);

	ParkingLot* chosenParkingLot = findParkingLotById(parkingLotManager, parkingLotId);
	if (chosenParkingLot == NULL)
	{
		printf("Parking lot with ID %d not found.\n", parkingLotId);
		return;
	}

	displayParkingLotMainMenu(chosenParkingLot);
}
