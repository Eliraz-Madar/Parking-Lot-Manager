#pragma once
#include "General.h"
#include "List.h"
#include "ParkingLot.h"

typedef struct
{
	char* companyName;
	List parkingLotList;
	size_t lastUsedParkingLotId;
} ParkingLotManager;

ParkingLotManager initParkingLotManager(const char* companyName);

bool addParkingLot(ParkingLotManager* manager, ParkingLot parkingLot);

bool removeParkingLot(ParkingLotManager* parkingLotManager, ParkingLot* parkingLot);

bool removeParkingLotById(ParkingLotManager* parkingLotManager, int parkingLotId);

ParkingLot* findParkingLotById(const ParkingLotManager* manager, int id);

double summarizePayments(const ParkingLotManager* parkingLotManager);

void freeParkingLotManager(ParkingLotManager* parkingLotManager);
