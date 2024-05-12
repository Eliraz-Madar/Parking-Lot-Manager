#include "ParkingCustomerView.h"

#include "ParkingSubscriptionView.h"
#include "ParkingVehicleView.h"
#include "GeneralView.h"
#include "ParkingPaymentView.h"

ParkingCustomer createParkingCustomerUI(int id)
{
	char nameBuffer[256]; //Buffer for name input

	//Prompt user for customer name
	clearInputBuffer(); //Clear the buffer to handle any leftovers from stdin
	printf("Enter the customer's name: ");
	fgets(nameBuffer, sizeof(nameBuffer), stdin);
	nameBuffer[strcspn(nameBuffer, "\n")] = 0;

	const bool isSubscriptionActive = getBooleanValueUI("Does the customer have a subscription?");

	clearInputBuffer(); //Clear the buffer to handle any leftovers from stdin

	DateTime zeroDateTime = { 0 }; //Initializes all fields to 0
	ParkingSubscription subscription = isSubscriptionActive ? createParkingSubscriptionUI() : initParkingSubscription(false, zeroDateTime, zeroDateTime, 0);

	return initParkingCustomer(id, nameBuffer, subscription);
}

void displayParkingCustomerMainMenu(ParkingCustomer* customer)
{
	int choice;
	do
	{
		printf("\n---- Customer %s Main Menu ----\n", customer->name);
		printf("1. View Customer Details\n");
		printf("2. Update Customer Details\n");
		printf("3. View Subscription Details\n");
		printf("4. Update Subscription Details\n");
		printf("5. Activate Subscription\n");
		printf("6. Deactivate Subscription\n");
		printf("7. Show All Vehicles\n");
		printf("8. Show All Payments\n");
		printf("9. Remove Payment\n");
		printf("-1. Exit\n");

		printf("Enter your choice: ");
		if (scanf("%d", &choice) != 1)
		{
			printf("Invalid input. Please enter a number.\n");
			clearInputBuffer();
		}
		else
		{
			switch (choice)
			{
			case 1:
				displayParkingCustomer(customer);
				break;
			case 2:
				updateCustomerDetailsUI(customer);
				break;
			case 3:
				displayParkingSubscription(&customer->parkingSubscription);
				break;
			case 4:
				updateSubscriptionDetailsUI(customer);
				break;
			case 5:
				activateSubscription(&customer->parkingSubscription);
				printf("Subscription activated.\n");
				break;
			case 6:
				deactivateSubscription(&customer->parkingSubscription);
				printf("Subscription deactivated.\n");
				break;
			case 7:
				showAllVehiclesOfCustomerUI(customer);
				break;
			case 8:
				showAllPaymentsOfCustomerUI(customer);
				break;
			case 9:
				removePaymentFromCustomerUI(customer);
				break;
			case -1:
				printf("Exiting Customer Main Menu.\n");
				break;
			default:
				printf("Invalid choice. Please enter a valid option.\n");
				break;
			}
		}
	} while (choice != -1);
}

void displayParkingCustomer(const ParkingCustomer* customer)
{
	printf("Customer ID: %d\n", customer->customerId);
	printf("Customer Name: %s\n", customer->name);
	printf("Total Vehicles: %llu\n", customer->vehicleArrayCount);
	printf("Total Payments: %llu\n", customer->paymentsArrayCount);
	printf("Total Paid Amount: $%.2f\n", customer->totalPaidAmount);
	printf("Subscription: \n");
	displayParkingSubscription(&customer->parkingSubscription);
	printf("\n");
}

void updateCustomerDetailsUI(ParkingCustomer* customer)
{
	char nameBuffer[256]; //Buffer for name input

	//Prompt user for customer name
	clearInputBuffer(); //Clear the buffer to handle any leftovers from stdin
	printf("Enter the customer's name: ");
	fgets(nameBuffer, sizeof(nameBuffer), stdin);
	nameBuffer[strcspn(nameBuffer, "\n")] = 0;

	//Update the customer's name
	updateCustomerName(customer, nameBuffer);
}

void updateSubscriptionDetailsUI(ParkingCustomer* customer)
{
	const bool isSubscription = getBooleanValueUI("Does the customer have a subscription?");

	const DateTime dt = { 0 }; //Initializes all fields to 0
	const ParkingSubscription subscription = isSubscription == 1 ? createParkingSubscriptionUI() : initParkingSubscription(false, dt, dt, 0);

	updateCustomerSubscription(customer, subscription);
}

void showAllVehiclesOfCustomerUI(const ParkingCustomer* customer)
{
	if (customer->vehicleArrayCount == 0)
	{
		printf("No vehicles found for customer %s.\n", customer->name);
		return;
	}

	printf("Vehicles of customer %s:\n", customer->name);
	for (size_t i = 0; i < customer->vehicleArrayCount; i++)
	{
		printf("%llu. ", i + 1);
		displayVehicle(customer->vehicleArray[i]);
	}
}

void showAllPaymentsOfCustomerUI(const ParkingCustomer* customer)
{
	if (customer->paymentsArrayCount == 0)
	{
		printf("No payments found for customer %s.\n", customer->name);
		return;
	}

	printf("Payments of customer %s:\n", customer->name);
	for (size_t i = 0; i < customer->paymentsArrayCount; i++)
	{
		printf("%llu. ", i + 1);
		displayParkingPayment(&customer->paymentsArray[i]);
		printf("----\n");
	}
}

void removePaymentFromCustomerUI(ParkingCustomer* customer)
{
	if (customer->paymentsArrayCount == 0)
	{
		printf("No payments found for customer %s.\n", customer->name);
		return;
	}

	printf("Payments of customer %s:\n", customer->name);
	for (size_t i = 0; i < customer->paymentsArrayCount; i++)
	{
		printf("%llu. ", i + 1);
		displayParkingPayment(&customer->paymentsArray[i]);
		printf("----\n");
	}

	size_t paymentIndex;
	printf("Enter the index of the payment to remove: ");
	if (scanf("%llu", &paymentIndex) != 1)
	{
		printf("Invalid input. Please enter a number.\n");
		clearInputBuffer();
		return;
	}

	if (paymentIndex < 1 || paymentIndex > customer->paymentsArrayCount)
	{
		printf("Invalid index. Please enter a valid index.\n");
		return;
	}

	const ArrayRemoveResult result = removePaymentFromCustomer(customer, customer->paymentsArray[paymentIndex - 1]);

	switch (result)
	{
	case ARRAY_REMOVE_SUCCESS:
		printf("Payment removed successfully.\n");
		break;

	case ARRAY_REMOVE_NOT_FOUND:
		printf("Payment not found.\n");
		break;

	default:
		printf("Unknown error occurred.\n");
		break;
	}

	customer->totalPaidAmount = calculateTotalAmountPaid(customer); //Update the total paid amount
}
