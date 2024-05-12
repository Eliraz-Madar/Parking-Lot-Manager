#pragma once
#include "General.h"
#include "ParkingLotManager.h"

ParkingLotManager createParkingLotManagerUI();

void displayParkingLotManagerMainMenu(ParkingLotManager* parkingLotManager);

void displayAllParkingLotsDetails(const ParkingLotManager* parkingLotManager);

void displayPaymentSummary(const ParkingLotManager* parkingLotManager);

void addParkingLotUI(ParkingLotManager* parkingLotManager);

void removeParkingLotUI(ParkingLotManager* parkingLotManager);

void selectAndDisplayParkingLotUI(const ParkingLotManager* parkingLotManager);
