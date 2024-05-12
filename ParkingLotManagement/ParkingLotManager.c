#include "ParkingLotManager.h"

ParkingLotManager initParkingLotManager(const char* companyName)
{
	ParkingLotManager manager;

	manager.companyName = customStrdup(companyName); // Copy the company name.
	manager.parkingLotList.head = NULL;
	manager.lastUsedParkingLotId = 0;

	return manager;
}

bool addParkingLot(ParkingLotManager* manager, ParkingLot parkingLot)
{
	if (manager == NULL)
	{
		return false;
	}

	ParkingLot* newLot = (ParkingLot*)malloc(sizeof(ParkingLot));
	if (newLot == NULL)
	{
		return false; // Memory allocation failed.
	}

	*newLot = parkingLot;

	return insertAtBeginning(&(manager->parkingLotList), newLot);
}

bool removeParkingLot(ParkingLotManager* parkingLotManager, ParkingLot* parkingLot)
{
	if (parkingLotManager == NULL)
	{
		return false;
	}

	if (!deleteFromListCustomCompare(&(parkingLotManager->parkingLotList), parkingLot, isSameParkingLotById))
	{
		return false;
	}

	freeParkingLot(parkingLot);
	free(parkingLot);
	return true;
}

bool removeParkingLotById(ParkingLotManager* parkingLotManager, int parkingLotId)
{
	if (parkingLotManager == NULL)
	{
		return false;
	}

	ParkingLot* parkingLotPtr = findParkingLotById(parkingLotManager, parkingLotId);

	if (parkingLotPtr == NULL)
	{
		return false;
	}

	return removeParkingLot(parkingLotManager, parkingLotPtr);
}

ParkingLot* findParkingLotById(const ParkingLotManager* manager, int id)
{
	if (manager == NULL || manager->parkingLotList.head == NULL)
	{
		return NULL;
	}

	const Node* current = manager->parkingLotList.head;
	while (current != NULL)
	{
		ParkingLot* currentLot = (ParkingLot*)current->key;
		if (currentLot != NULL && currentLot->parkingLotId == id)
		{
			return currentLot; // Found the matching ParkingLot
		}
		current = current->next;
	}

	return NULL;
}

double summarizePayments(const ParkingLotManager* parkingLotManager)
{
	double total = 0.0;

	LIST_FOREACH(ParkingLot, parkingLot, &parkingLotManager->parkingLotList)
	{
		ARRAY_FOREACH(ParkingCustomer, parkingCustomer, parkingLot->parkingCustomersArray, parkingLot->parkingCustomersArrayCount)
		{
			ARRAY_FOREACH(ParkingPayment, parkingPayment, parkingCustomer->paymentsArray, parkingCustomer->paymentsArrayCount)
			{
				total += parkingPayment->amountPaid;
			}
		}
	}

	return total;
}

void freeParkingLotManager(ParkingLotManager* parkingLotManager)
{
	if (parkingLotManager == NULL) return;

	free(parkingLotManager->companyName);
	parkingLotManager->companyName = NULL;

	// Free each ParkingLot in the list.
	const Node* current = parkingLotManager->parkingLotList.head;
	while (current != NULL)
	{
		if (current != NULL && current->key != NULL)
		{
			freeParkingLot(current->key);
			free(current->key); // Free the ParkingLot.
		}
		current = current->next;
	}

	freeList(&(parkingLotManager->parkingLotList));

	parkingLotManager->parkingLotList.head = NULL;
}
