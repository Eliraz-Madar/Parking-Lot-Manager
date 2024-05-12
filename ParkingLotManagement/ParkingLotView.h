#pragma once

#include "ParkingLot.h"

ParkingLot createParkingLotUI(int id);

void displayParkingLotMainMenu(ParkingLot* parkingLot);

void displayParkingLotDetails(const ParkingLot* parkingLot);

void displayParkingLotDiagram(const ParkingLot* lot);

void displayAllParkingSpaces(const ParkingLot* parkingLot);

void addParkingSpaceToParkingLotUI(ParkingLot* parkingLot);

void removeParkingSpaceFromParkingLotUI(ParkingLot* parkingLot);

void selectAndDisplayParkingSpaceUI(ParkingLot* parkingLot);

void displayAllCustomers(const ParkingLot* parkingLot);

void addCustomerToParkingLotUI(ParkingLot* parkingLot);

void removeCustomerFromParkingLotUI(ParkingLot* parkingLot);

void selectAndDisplayCustomerUI(ParkingLot* parkingLot);

void sortCustomersUI(ParkingLot* parkingLot);

void searchCustomerUI(ParkingLot* parkingLot);

void addVehicleToParkingLotUI(const ParkingLot* parkingLot);

void removeVehicleFromParkingLotUI(const ParkingLot* parkingLot);

void parkVehicleInParkingLotUI(const ParkingLot* parkingLot);

void vacateVehicleFromParkingLotUI(const ParkingLot* parkingLot);
