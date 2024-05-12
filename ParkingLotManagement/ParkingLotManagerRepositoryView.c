#include "ParkingLotManagerRepositoryView.h"
#include "ParkingLotManagerRepository.h"

#include "GeneralView.h"

#define BIN_FILE_NAME "ParkingLotManager.bin"
#define TXT_FILE_NAME "ParkingLotManager.txt"

bool loadParkingLotManagerFromRepositoryUI(ParkingLotManager* parkingLotManager)
{
	FileContext fileContext;

	fileContext.isBinary = getBooleanValueUI("Do you want to load the file in binary mode?");

	FILE* file;
	if (fileContext.isBinary)
		file = fopen(BIN_FILE_NAME, "rb");
	else
		file = fopen(TXT_FILE_NAME, "r");
	if (!file)
		return false;

	fileContext.file = file;

	if(!readParkingManagerFromFile(parkingLotManager, &fileContext))
	{
		printf("Error reading file\n");
		return false;
	}
	
	if (fclose(file) != 0) //fclose(file) returns 0 if the file is closed successfully
	{
		printf("Error closing file\n");
		return false;
	}

	return true;
}

bool saveParkingLotManagerToRepositoryUI(const ParkingLotManager* parkingLotManager)
{
	FileContext fileContext;

	fileContext.isBinary = getBooleanValueUI("Do you want to save the file in binary mode?");

	FILE *file;
	if (fileContext.isBinary)
		file = fopen(BIN_FILE_NAME, "wb");
	else
		file = fopen(TXT_FILE_NAME, "w");
	if (!file)
		return false;

	fileContext.file = file;

	if(!writeParkingManagerToFile(parkingLotManager, &fileContext))
	{
		printf("Error writing file\n");

		if (fclose(file) != 0) //fclose(file) returns 0 if the file is closed successfully
		{
			printf("Error closing file\n");
			return false;
		}

		return false; // Error writing file
	}

	if (fclose(file) != 0) //fclose(file) returns 0 if the file is closed successfully
	{
		printf("Error closing file\n");
		return false;
	}

	return true; // File saved successfully
}
