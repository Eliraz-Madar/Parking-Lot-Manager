#define _CRT_SECURE_NO_WARNINGS
#include "General.h"
#include "ParkingLotManagerView.h"
#include "ParkingLotManagerRepositoryView.h"
#include "GeneralView.h"

int main()
{
	ParkingLotManager parkingLotManager;

	const bool shouldLoadFromRepository = getBooleanValueUI("Load from repository?");
	if (shouldLoadFromRepository)
	{
		if (!loadParkingLotManagerFromRepositoryUI(&parkingLotManager))
		{
			printf("Failed to load from repository!\n");
			return 1; // We don't want to continue if we can't load from the repository after the user has requested it
		}
	}
	else
	{
		clearInputBuffer();
		parkingLotManager = createParkingLotManagerUI();
	}

	displayParkingLotManagerMainMenu(&parkingLotManager); // This is the main menu for the parking lot manager

	const bool shouldSaveToRepository = getBooleanValueUI("Save to repository?");
	if (shouldSaveToRepository)
	{
		clearInputBuffer();
		if (saveParkingLotManagerToRepositoryUI(&parkingLotManager))
		{
			printf("Saved to repository!\n");
		}
		else
		{
			printf("Failed to save to repository!\n");
		}
	}

	freeParkingLotManager(&parkingLotManager);
}
