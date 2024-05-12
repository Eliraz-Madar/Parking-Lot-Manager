#include "ParkingPaymentView.h"

#include "DateTimeView.h"
#include "ParkingVehicleView.h"

ParkingPayment createParkingPaymentUI(Vehicle vehicle, double hourlyRate)
{
	printf("Enter entry date and time:\n");
	const DateTime entryDateTime = createDateTimeUI();

	const ParkingPayment parkingPayment = initParkingPayment(vehicle, entryDateTime, hourlyRate);

	return parkingPayment;
}

void displayParkingPayment(const ParkingPayment* parkingPayment)
{
	if (parkingPayment == NULL) {
		printf("No parking payment information available.\n");
		return;
	}

	printf("Parking Payment Details:\n");
	printf("Payment Status: %s\n", parkingPayment->isPaid ? "Paid" : "Not Paid");

	// Display vehicle information
	printf("Vehicle: ");
	displayVehicle(&parkingPayment->vehicle); // Display vehicle details

	// Display entry and exit DateTime
	printf("Entry Time: ");
	displayDateTime(&parkingPayment->entryDateTime);

	if(parkingPayment->isPaid)
	{
		printf("Exit Time: ");
		displayDateTime(&parkingPayment->exitDateTime);
	}

	printf("Parking Hourly Rate: $%.2f\n", parkingPayment->parkingHourlyRate);
	printf("Amount Paid: $%.2f\n", parkingPayment->amountPaid);
}

bool makePaymentUI(ParkingPayment* parkingPayment)
{
	if (parkingPayment == NULL)
	{
		printf("No parking payment information available.\n");
		return false;
	}

	if (parkingPayment->isPaid)
	{
		printf("Payment has already been made.\n");
		return false;
	}

	printf("Enter exit date and time:\n");
	const DateTime exitDateTime = createDateTimeUI();

	const MakePaymentResponse response = makePayment(parkingPayment, &exitDateTime);

	switch (response)
	{
	case PAYMENT_COMPLETED:
		printf("Payment completed successfully.\n");
		printf("Amount paid: $%.2f\n", parkingPayment->amountPaid);
		return true;
	case ENTRY_DATE_AFTER_EXIT_DATE:
		printf("Error: Entry date and time is after exit date and time.\n");
		return false;
	case INVALID_RATE:
		printf("Error: Invalid parking hourly rate.\n");
		return false;
	default:
		printf("Error: An unknown error occurred.\n");
		return false;
	}
}
