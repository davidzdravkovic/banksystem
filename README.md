# Bank System Application

## Content
1. [Project Description](#project-description)
2. [Features](#features)
3. [Technologies Used](#technologies-used)
4. [Installation](#installation)
5. [Application Flow Demo](#application-flow-demo)

---

## Project Description

A simple banking system application built with C++ (Drogon) and React, following core OOP principles, supporting multiple user types, account management, and transactions via REST API.

## Features

- **User profile creation**: Create a user profile according to the selected user type.
- **Login and access**: Log in and access an existing user profile.
- **Account management**: Users can create different types of accounts and search for accounts.
- **Transaction creation**: Create transactions between accounts.
- **Balance transfer**: Perform money transfers between users’ accounts, with options to send or request funds.
- **Sent transactions (Sent)**: View sent transactions from an account, with the ability to decline.
- **Received transactions (Inbox)**: View incoming transactions to an account, with the option to accept or decline.
- **Balance updates**: Automatically update account balances after each transaction action.
- **Transaction history**: Maintain a full history of all transactions.
- **User-friendly GUI**: Built with React, HTML, and CSS.
- **REST API**: Backend implemented with RESTful API endpoints.

## Technologies Used

- **Programming Language**: C++
- **Framework**: Drogon
- **Frontend**: React
- **Database**: PostgreSQL
- **API**: REST
- **Version Control**: Git

## Installation

### Prerequisites

To run this project, the following technologies are required:

- C++ compiler (e.g., GCC 9+ / Clang 10+)
- CMake 3.20+
- Node.js 18+
- npm or yarn
- Database (PostgreSQL)

### Steps

Open a terminal in your development environment and execute the commands below:

```bash
# Step 1. Clone repository

git clone <repo-url>
cd <project-folder>

# Step 2. Backend build

cd src
cmake .
make
# (Run the backend executable manually if needed, e.g., ./BankSystem.exe)

# Step 3. Frontend start (for Windows PowerShell users)

cd ../Views
npm install
Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass
npm start
```

## Application Flow Demo

Watch a demo of the application demonstrating its main features and workflow: [Demo Video](https://youtu.be/qdXNN0GQK5o)
