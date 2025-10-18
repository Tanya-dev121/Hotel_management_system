

# Hotel Management System (C++)

A console-based Hotel Management System in C++ that allows **Admins** to manage rooms and view bookings, and **Customers** to view rooms, book rooms, and cancel their own bookings. Data is stored in simple text files (`rooms.txt` and `Booking.txt`).

---

## Features

### Admin
- Add new rooms
- View all rooms
- View all bookings
- Password-protected access (`admin123`)

### Customer
- View available rooms
- Book a room
- Cancel a booking (only their own bookings)
- Input validation for room number, price, and number of days

### General
- File-based persistence
- Console-based UI with colored text output
- Input validation for safer operations

---

Getting Started
Prerequisites

Windows / Linux / macOS

C++ compiler (g++, MinGW, or any standard C++ compiler)

Running the Program
On Windows

Clone the repository:

git clone https://github.com/YOUR_USERNAME/HotelManagement.git


Navigate to the project folder:

cd HotelManagement


Compile the program:

g++ -o HotelManagement.exe hotel.cpp


Run the executable:

HotelManagement.exe

On Linux / macOS

Clone the repository:

git clone https://github.com/YOUR_USERNAME/HotelManagement.git


Navigate to the project folder:

cd HotelManagement


Compile the program:

g++ -o HotelManagement hotel.cpp


Run the executable:

./HotelManagement

Usage

Choose Role: Admin or Customer

Admin Password: admin123

Admin can add rooms, view all rooms, and view bookings.

Customer can view rooms, book rooms, and cancel their own bookings only.

Project Structure
HotelManagement/
│
├── hotel.cpp       # Main C++ source code
├── rooms.txt       # Stores room information
├── Booking.txt     # Stores booking information
└── README.md       # Project description

Technologies

C++ – Core programming language

File Handling – Persistent storage of rooms and bookings

Console UI – Simple text-based interface with colored output

Author

Tanya Goel
