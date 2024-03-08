
# Cool Mart Inventory Management System

Cool Mart Inventory Management System is an object-oriented programming (OOP) based application developed in C++ for managing stock, supplies, and staff in a retail environment.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Classes and Functions](#classes-and-functions)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Introduction

This application is designed to streamline inventory-related tasks such as managing stock levels, handling supplies, and keeping track of staff details. It provides a user-friendly interface for owners, managers, and cashiers to efficiently manage day-to-day operations in a retail setting.

## Features

- **Stock Management**: View, update, and add new categories and products to the stock.
- **Supply Management**: Keep track of local and international supplies, and add new supplies to the system.
- **Staff Management**: View details of staff members, including their full name, position, and join date.
- **User Authentication**: Different access levels (Owner, Manager, Cashier, Floor Worker) ensure secure access to specific features.

## Given Task
<table>
  <tr>
    <td>Task 0</td>
    <td>Task 1</td>
    <td>Task 2</td>
  </tr>
  <tr>
    <td><img src="https://user-images.githubusercontent.com/95247831/200813042-db1c1fff-8701-4956-b4d8-793ae1134821.png" width=600></td>
    <td><img src="https://user-images.githubusercontent.com/95247831/200813048-f4ff89bf-6e7c-4ab7-a5c0-7b2b98c04281.png" width=600></td>
    <td><img src="https://user-images.githubusercontent.com/95247831/200813059-87ff2b50-f0b0-4d26-a17f-ddaf7d3c7738.png" width=600></td>
  </tr>
</table>
## Inputs
<table>
  <tr>
    <td>Inputs 0</td>
    <td>Inputs 1</td>
  </tr>
  <tr>
    <td><img src="https://user-images.githubusercontent.com/95247831/200813234-41b2d202-939f-4ab9-9a41-fb4f4cfeec51.png" width=600></td>
    <td><img src="https://user-images.githubusercontent.com/95247831/200813245-e4c06a73-ff53-4d6e-9f65-da1996e1c91b.png" width=600></td>
  </tr>
</table>
## Requeirments
<table>
  <tr>
    <td>Release Note</td>
  </tr>
  <tr>
    <td><img src="https://user-images.githubusercontent.com/95247831/200813390-fca8e700-06b6-4c32-8214-03bbfef217dc.png" width=600></td>
  </tr>
</table>
## UML Diagram
<table>
  <tr>
    <td>UML Diagram</td>
  </tr>
  <tr>
    <td><img src="https://user-images.githubusercontent.com/95247831/200813594-6d759241-3f1e-46bb-bf80-299efafbcf8b.png" width=600></td>
  </tr>
</table>
## OOP Concepts Used
<table>
  <tr>
    <td>OOP Concepts Used 0</td>
    <td>OOP Concepts Used 1</td>
  </tr>
  <tr>
    <td><img src="https://user-images.githubusercontent.com/95247831/200813470-5037de97-efc6-4507-83ec-b41a9d9f7726.png" width=600></td>
    <td><img src="https://user-images.githubusercontent.com/95247831/200813507-555d487f-08e6-4be6-af1e-81431550f9a0.png" width=600></td>
  </tr>
</table>

## Classes and Functions

### Stock Class
- `showstock()`: Display the current stock details.
- `stock_down()`: Decrease stock levels for a given product.
- `stock_up_down()`: Update stock levels based on supply transactions.
- `add_category()`: Add a new category to the stock.
- `add_product()`: Add a new product to the stock.

### Supplies Class
- `showSupplies()`: Display information about local and international supplies.
- `add_product_to_supplies()`: Add a new supply to the system.
- `pass_supplies()`: Update stock levels based on supply transactions.

### Staff Class
- `setData()`: Collect and set information about staff members.
- `showData()`: Display details of a staff member.
- `get_username()`, `get_password()`, `get_positionValue()`, `get_fullname()`: Retrieve specific details of a staff member.

### Interconnect Class
- `Initiate()`: Initialize the system with default values and staff details.
- `mainProgramme()`: The main program loop that provides the user interface and options.

## Usage

1. Clone the repository to your local machine.
2. Compile and run the application using a C++ compiler.
3. Follow the on-screen prompts to navigate through different features.
4. Use the provided staff usernames and passwords to access specific functionalities.
