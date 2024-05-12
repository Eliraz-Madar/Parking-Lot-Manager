#pragma once
#include "General.h"
#include "ParkingCustomer.h"

ParkingCustomer createParkingCustomerUI(int id);

void displayParkingCustomerMainMenu(ParkingCustomer* customer);

void displayParkingCustomer(const ParkingCustomer* customer);

void updateCustomerDetailsUI(ParkingCustomer* customer);

void updateSubscriptionDetailsUI(ParkingCustomer* customer);

//void addVehicleToCustomerUI(ParkingCustomer* customer);

void showAllVehiclesOfCustomerUI(const ParkingCustomer* customer);

void showAllPaymentsOfCustomerUI(const ParkingCustomer* customer);

void removePaymentFromCustomerUI(ParkingCustomer* customer);
