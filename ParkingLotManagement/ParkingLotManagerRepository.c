#include "ParkingLotManagerRepository.h"
#include "ParkingLotRepository.h"
#include "FileHelper.h"

bool readParkingManagerFromFile(ParkingLotManager* parkingLotManager, const FileContext* fileContext)
{
	char nameBuffer[255];
	if (!readStringFromFile(nameBuffer, 255, fileContext))
		return false;

	*parkingLotManager = initParkingLotManager(nameBuffer);

	size_t lastUsedParkingLotId;
	if (!readSizeTFromFile(&lastUsedParkingLotId, fileContext))
		return false;
	parkingLotManager->lastUsedParkingLotId = lastUsedParkingLotId;

	size_t parkingLotCount;
	if (!readSizeTFromFile(&parkingLotCount, fileContext))
		return false;

	if(lastUsedParkingLotId < parkingLotCount)
		parkingLotManager->lastUsedParkingLotId = parkingLotCount + 1;

	ParkingLot parkingLot;
	for (size_t i = 0; i < parkingLotCount; i++)
	{
		if (!readParkingLotFromFile(&parkingLot, fileContext))
			return false;

		addParkingLot(parkingLotManager, parkingLot);
	}

	return true;
}

bool writeParkingManagerToFile(const ParkingLotManager* parkingLotManager, const FileContext* fileContext)
{
	if (!writeStringToFile(parkingLotManager->companyName, fileContext))
		return false;

	if (!writeSizeTToFile(parkingLotManager->lastUsedParkingLotId, fileContext))
		return false;

	size_t parkingLotCount = 0;
	LIST_FOREACH(ParkingLot, item, &parkingLotManager->parkingLotList)
	{
		parkingLotCount++;
	}

	if (!writeSizeTToFile(parkingLotCount, fileContext))
		return false;

	LIST_FOREACH(ParkingLot, item, &parkingLotManager->parkingLotList)
	{
		if (!writeParkingLotToFile(item, fileContext))
		{
			return false;
		}
	}

	return true;
}
