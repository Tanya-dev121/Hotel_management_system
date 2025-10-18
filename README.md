

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
## Getting Started

### Prerequisites
- Windows / Linux / macOS
- C++ compiler (g++, MinGW, or any standard C++ compiler)

### Running the Program

#### On Windows
1. Clone the repository:
   ```bash
   git clone https://github.com/YOUR_USERNAME/HotelManagement.git

2. Navigate to the project folder:
   ```bash
   cd HotelManagement

3.  Compile the program:
      ```bash
   g++ -o HotelManagement.exe hotel.cpp

4. Run the executable:
    ```bash
   HotelManagement.exe

Author
Tanya Goel
