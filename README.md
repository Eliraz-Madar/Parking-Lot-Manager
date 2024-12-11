# Parking Lot Management System

Welcome to the **Parking Lot Management System**! This repository provides a comprehensive system designed to manage parking lot operations, including tracking customers, vehicles, payments, and subscriptions.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
  - [Main Menu](#main-menu)
  - [Parking Lot Management](#parking-lot-management)
  - [Parking Space Management](#parking-space-management)
  - [Customer Management](#customer-management)
- [System Architecture](#system-architecture)
- [Known Issues](#known-issues)
- [Contributing](#contributing)
- [License](#license)

## Overview
The Parking Lot Management System is designed to help businesses track and manage multiple parking facilities. Each parking lot can maintain records for customers, vehicles, payments, and available parking spaces. This system uses a linked list to store parking lots and provides detailed menus for managing operations at each level.

## Features
- **Linked List of Parking Lots**: Allows efficient management of multiple facilities.
- **Customer and Vehicle Management**: Track customers and their vehicles.
- **Payment and Subscription Tracking**: Handle parking payments and subscriptions with discounts.
- **Interactive Menus**: Intuitive menus for managing parking lots, spaces, and customers.

## Installation
1. Clone this repository:
   ```bash
   git clone https://github.com/your-username/parking-lot-management.git
   ```
2. Navigate to the project directory:
   ```bash
   cd parking-lot-management
   ```
3. Ensure a compatible C compiler is installed on your system (e.g., GCC).

## Usage
### Main Menu
The main menu allows you to:
- Display all existing parking lots.
- Summarize total payments across all lots.
- Add or remove parking lots.
- Access the management menu for a specific parking lot by selecting its ID.

### Parking Lot Management
From the parking lot management menu, you can:
- Display parking lot details.
- View, add, or remove parking spaces.
- Manage customer records, including adding or removing customers.
- Handle vehicle parking and payment operations.

### Parking Space Management
Within the parking space menu, you can:
- Add or remove allowed vehicle types.
- Park or vacate vehicles in specific spaces.
- Display a diagram of parking space availability.

### Customer Management
For customer management:
- Add or remove customers and their vehicles.
- Update subscription details, including discounts and validity.
- View payment history and outstanding balances.

## System Architecture
The system is structured around key components:
- **Parking Lot Manager**: Manages the linked list of parking lots.
- **Parking Lot**: Contains customers, spaces, and payment details.
- **Customer**: Tracks personal details, vehicles, and payments.
- **Parking Space**: Records availability and allowed vehicle types.
- **Subscription**: Provides discounts and validity tracking.

Refer to the [Template Diagram](Template%20Diagram.pdf) for a detailed architecture diagram.

## Known Issues
- Customers must register vehicles before using parking spaces.
- Subscriptions must be active and valid at the time of parking to apply discounts.
- Removing a vehicle linked to unpaid balances is restricted.
- Certain UI elements may not handle invalid input gracefully.

## Contributing
We welcome contributions! To contribute:
1. Fork this repository.
2. Create a new branch for your feature or bug fix.
3. Submit a pull request with a detailed explanation of your changes.

## License
This project is licensed under the MIT License. See the LICENSE file for details.

---
We hope this system simplifies your parking lot management tasks!

