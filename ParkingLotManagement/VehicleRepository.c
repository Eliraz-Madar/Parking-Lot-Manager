#include "VehicleRepository.h"

#define VEHICLE_TYPE_BITS 2
#define VEHICLE_TYPE_MASK 0x3 // 2 bits for vehicle type
#define MAX_SHIFT (32 - VEHICLE_TYPE_BITS)

Vehicle decompressVehicle(unsigned long long compressedData);
unsigned long long compressLicensePlate(const char* licensePlate);
void decompressLicensePlate(unsigned long long compressedData, char* licensePlate);
unsigned long long compressVehicle(const Vehicle* vehicle);

bool readVehicleFromFile(Vehicle* vehicle, const FileContext* fileContext)
{
	if (fileContext->isBinary)
	{
		unsigned long long compressedVehicle;
		if (!readUnsignedLongLongFromFile(&compressedVehicle, fileContext))
			return false;

		*vehicle = decompressVehicle(compressedVehicle);
		return true;
	}
	else
	{
		char licensePlateBuffer[255];
		if(!readVehicleLicensePlate(licensePlateBuffer, fileContext))
			return false; // License plate is invalid

		VehicleType vehicleType;

		if (!readIntFromFile((int*)&vehicleType, fileContext))
			return false;

		*vehicle = initVehicle(licensePlateBuffer, vehicleType);
		return true;
	}
}

bool readVehicleLicensePlate(char* licensePlate, const FileContext* fileContext)
{
	if (!readStringFromFile(licensePlate, LICENSE_PLATE_LENGTH + 2, fileContext))
		return false;

	if (!isValidLicensePlate(licensePlate))
		return false; // License plate is invalid

	return true;
}

bool writeVehicleToFile(const Vehicle* vehicle, const FileContext* fileContext)
{
	if (fileContext->isBinary)
	{
		const unsigned long long compressedVehicle = compressVehicle(vehicle);
		writeUnsignedLongLongToFile(fileContext, compressedVehicle);
	}
	else
	{
		if (fprintf(fileContext->file, "%s\n", vehicle->licensePlate) < 0)
			return false;

		if (fprintf(fileContext->file, "%d\n", vehicle->vehicleType) < 0)
			return false;
	}
	return true;
}

unsigned long long compressLicensePlate(const char* licensePlate)
{
	unsigned long long result = 0;
	for (int i = 0; licensePlate[i] != '\0' && i < LICENSE_PLATE_LENGTH; ++i) {
		unsigned int value = 0;
		if (licensePlate[i] >= 'A' && licensePlate[i] <= 'Z') {
			value = licensePlate[i] - 'A';
		}
		else if (licensePlate[i] >= '0' && licensePlate[i] <= '9') {
			value = 26 + (licensePlate[i] - '0');
		}
		result |= ((unsigned long long)value << (6 * i));
	}
	return result;
}

void decompressLicensePlate(unsigned long long compressedData, char* licensePlate)
{
	int i = 0;
	for (i = 0; i < LICENSE_PLATE_LENGTH; ++i) {
		const unsigned int value = (compressedData >> (6 * i)) & 0x3F; // Extract 6 bits
		if (value < 26) {
			licensePlate[i] = 'A' + value;
		}
		else if (value < 36) {
			licensePlate[i] = '0' + (value - 26);
		}
		else {
			licensePlate[i] = '\0'; // Invalid or end
			break;
		}
	}

	licensePlate[i] = '\0'; // Null-terminate the string
}

unsigned long long compressVehicle(const Vehicle* vehicle)
{
	unsigned long long result = compressLicensePlate(vehicle->licensePlate);
	// Assuming vehicleType fits within 2 bits, place it in the last 2 bits of the 64-bit integer.
	result |= ((unsigned long long)vehicle->vehicleType & 0x3) << 60; // Shift left by 60 bits to place at the end of the 64-bit integer.
	return result;
}

Vehicle decompressVehicle(unsigned long long compressedData)
{
	Vehicle vehicle;
	// Extract the last 2 bits for the vehicle type
	vehicle.vehicleType = (VehicleType)(compressedData >> 60 & 0x3); // Extract the vehicle type from the last 2 bits.

	// Decompress the license plate, using the remaining bits.
	// Note: This uses the updated decompressLicensePlate function which needs to be implemented accordingly.
	decompressLicensePlate(compressedData & (~(0x3ULL << 60)), vehicle.licensePlate); // Mask out the vehicle type bits before passing.

	return vehicle;
}
