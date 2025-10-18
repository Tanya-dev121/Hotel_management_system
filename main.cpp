#include <iostream>
#include <limits>
#include <string>
#include <fstream> //for file handling
using namespace std;

class Room
{
  int roomNumber;
  string roomType;
  float pricePerNight;
  bool isBooked;

public:
  void addRoom();
  void displayRoom();
  void BookRoom();
  void cancelBooking();
  void showBookings();
};

// Function definitions

int getPositiveInt(const string &prompt)
{
  int num;
  while (true)
  {
    cout << prompt;
    if (cin >> num && num > 0)
      return num;
    cout << "\033[31mInvalid input! Please enter a positive number.\033[0m\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
}

float getPositiveFloat(const string &prompt)
{
  float num;
  while (true)
  {
    cout << prompt;
    if (cin >> num && num > 0)
      return num;
    cout << "\033[31mInvalid input! Please enter a positive number.\033[0m\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
}

void Room::addRoom()
{
  int rn;      // temp variable for room number from file
  string rt;   // temp variable for room type from file
  float price; // temp variable for price from file
  bool booked;

  roomNumber = getPositiveInt("Enter the room number you want to Add: ");

  // if there is room already exist

  ifstream Check("rooms.txt");
  while (Check >> rn >> rt >> price >> booked)
  {
    if (roomNumber == rn)
    {
      cout << "\033[31mRoom number " << roomNumber << " already exists!\033[0m\n";
      Check.close();
      return;
    }
  }
  Check.close();

  // if room does not exist

  // Get room type with simple validation
  while (true)
  {
    cout << "Enter the Type (AC or Non-A/C) of Room: ";
    cin >> roomType;
    if (roomType == "AC" || roomType == "Non-A/C")
      break;
    cout << "\033[31mInvalid input! Please enter 'AC' or 'Non-A/C'.\033[0m\n";
  }

  pricePerNight = getPositiveFloat("Enter the price per night for the room: ");

  isBooked = false; // When the room is added it will be empty

  // Open file to store the information of room //if file does not exist it will be created automatically

  ofstream file("rooms.txt", ios::app);
  if (!file)
  {
    cout << "Error Opening File!";
    return;
  }

  // Write Data to the file rooms.txt

  file << roomNumber << " " << roomType << " " << pricePerNight << " " << isBooked << endl;
  file.close();

  cout << "\033[32mRooms has been added successfully\033[0m\n";
  cout << "--------------\n";
}

void Room::displayRoom()
{
  ifstream file("rooms.txt"); // Open the file to read

  if (!file)
  {
    cout << "\033[31mError in opening the file!\033[0m\n";
    return;
  }

  cout << "\n\033[1;34m==== ALL ROOMS ARE ====\033[0m\n\n";

  int rn;
  string rt;
  float price;
  bool booked;
  bool found = false;

  while (file >> rn >> rt >> price >> booked)
  {
    found = true;
    // read one room at a time
    cout << "Room Number : " << rn << endl;
    cout << "Room Type : " << rt << endl;
    cout << "Price per night for the room : " << price << endl;
    cout << "Status of room : " << (booked ? "Room is Booked" : "Room is not booked yet") << endl;
    cout << "--------------------" << endl;
  }
  if (!found)
  {
    cout << "\033[33mNo rooms to display!\033[0m\n";
  }
  cout << "\n"; // extra newline after all rooms
  file.close();
}

void Room::BookRoom()
{
  int roomToBook = getPositiveInt("Enter the Room Number you want to book: ");

  // open rooms.txt for reading
  ifstream inFile("rooms.txt");
  if (!inFile)
  {
    cout << "Error opening rooms file!\n";
    return;
  }
  // Temporary file to store the updated data

  ofstream tempFile("temp.txt");
  if (!tempFile)
  {
    cout << "Error opening temporary file!\n";
    inFile.close();
    return;
  }
  int rn;
  string rt;
  float price;
  bool isBooked;
  bool found = false;

  while (inFile >> rn >> rt >> price >> isBooked)
  {
    if (rn == roomToBook)
    {
      found = true;
      if (isBooked)
      {
        cout << "\033[31mRoom is already Booked\033[0m\n";
        tempFile << rn << "  " << rt << "  " << price << "  " << isBooked << endl;
      }
      else
      {
        string customerName;
        int days;
        cout << "Enter the Customer Name: " << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clears leftover newline
        getline(cin, customerName);

        for (auto &ch : customerName)
        {
          if (ch == ' ')
          {
            ch = '_';
          }
        }
        days = getPositiveInt("Enter the number of days: ");

        float TotalCost = price * days;
        cout << "\033[32mRoom has been booked successfully for the customer " << customerName << "\033[0m\n";
        cout << "Total cost : " << TotalCost << " INR" << endl;

        // Write Booking Details to the bookings.txt

        ofstream bookingFile("Booking.txt", ios::app);

        if (!bookingFile)
        {
          cout << "Error in file opening" << endl;
          return;
        }
        bookingFile << rn << " " << customerName << " " << days << " " << TotalCost << endl;
        bookingFile.close();

        // update room status to booked
        isBooked = true;
        tempFile << rn << " " << rt << " " << price << " " << isBooked << endl;
      }
    }
    else
    {
      tempFile << rn << " " << rt << " " << price << " " << isBooked << endl;
    }
  }
  inFile.close();
  tempFile.close();

  // Replace old file with the updated file
  remove("rooms.txt");
  rename("temp.txt", "rooms.txt");

  if (!found)
  {
    cout << "\033[31mThis Room number doesn't exist. Please choose other\033[0m\n";
  }
}

void Room::cancelBooking()
{
  int roomToCancel = getPositiveInt("Enter the room number you want to cancel: ");

  // Check if the room exists and its booking status
  ifstream inFile("rooms.txt");
  if (!inFile)
  {
    cout << "Error in file opening!" << endl;
    return;
  }

  int rn;
  string rt;
  float price;
  bool isBooked;
  bool roomExists = false;

  while (inFile >> rn >> rt >> price >> isBooked)
  {
    if (rn == roomToCancel)
    {
      roomExists = true;
      if (!isBooked)
      {
        cout << "\033[33mRoom is already available (not booked)!\033[0m\n";
        inFile.close();
        return; // Stop here, no need to ask for name
      }
      break;
    }
  }
  inFile.close();

  if (!roomExists)
  {
    cout << "\033[31mRoom not found!\033[0m\n";
    return;
  }

  // Ask for customer name to verify ownership
  string enteredName;
  cout << "Enter your name (used during booking): ";
  cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
  getline(cin, enteredName);

  // Replace spaces with underscores for comparison
  for (auto &ch : enteredName)
    if (ch == ' ')
      ch = '_';

  // Verify if the customer booked this room
  ifstream inBooking("Booking.txt");
  ofstream tempBooking("tempBooking.txt");
  bool authorized = false;
  int days;
  float totalCost;
  string cname;

  while (inBooking >> rn >> cname >> days >> totalCost)
  {
    if (rn == roomToCancel && cname == enteredName)
    {
      authorized = true; // Customer booked this room
    }
    else
    {
      // Copy other bookings to temp file
      tempBooking << rn << " " << cname << " " << days << " " << totalCost << endl;
    }
  }
  inBooking.close();
  tempBooking.close();

  if (!authorized)
  {
    cout << "\033[31mUnauthorized! You did not book this room.\033[0m\n";
    return;
  }

  // Update rooms.txt to mark room as available
  ifstream inFile2("rooms.txt");
  ofstream tempFile("temp.txt");
  while (inFile2 >> rn >> rt >> price >> isBooked)
  {
    if (rn == roomToCancel)
      isBooked = false; // Cancel the booking
    tempFile << rn << " " << rt << " " << price << " " << isBooked << endl;
  }
  inFile2.close();
  tempFile.close();

  remove("rooms.txt");
  rename("temp.txt", "rooms.txt");
  remove("Booking.txt");
  rename("tempBooking.txt", "Booking.txt");

  cout << "\033[32mBooking has been cancelled successfully for room " << roomToCancel << "\033[0m\n";
}

void Room::showBookings()
{
  ifstream bookingFile("Booking.txt");
  if (!bookingFile)
  {
    cout << "\033[31mError! No Bookings\033[0m\n";
    return;
  }
  int rn;
  int days;
  string customerName;
  float totalCost;
  bool found = false;
  cout << "\n\033[1;34m==== ALL BOOKINGS ====\033[0m\n\n";

  while (bookingFile >> rn >> customerName >> days >> totalCost)
  {
    for (char &c : customerName)
      if (c == '_')
      {
        c = ' ';
      }

    found = true;
    cout << "Room Number: " << rn << endl;
    cout << "Customer Name: " << customerName << endl;
    cout << "Number of Days: " << days << endl;
    cout << "Total Cost: " << totalCost << " INR" << endl;
    cout << "---------------------" << endl;
  }
  if (!found)
  {
    cout << "\033[33mNo bookings to display!\033[0m\n";
  }
  cout << "\n";
  bookingFile.close();
}

void adminMenu()
{
  int choice;
  Room r;

  do
  {
    cout << "\n===== ADMIN MENU =====\n";
    cout << "1. Add Room\n";
    cout << "2. View All Rooms\n";
    cout << "3. View All Bookings\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      r.addRoom();
      break;
    case 2:
      r.displayRoom();
      break;
    case 3:
      r.showBookings();
      break;
    case 4:
      cout << "Exiting Admin Menu...\n";
      break;
    default:
      cout << "\033[31mInvalid choice!\033[0m\n";
    }

  } while (choice != 4);
}
void customerMenu()
{
  Room r;
  int choice;

  do
  {
    cout << "\n===== CUSTOMER MENU =====\n";
    cout << "1. View Available Rooms\n";
    cout << "2. Book a Room\n";
    cout << "3. Cancel Booking\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      r.displayRoom();
      break;
    case 2:
      r.BookRoom();
      break;
    case 3:
      r.cancelBooking();
      break;
    case 4:
      cout << "Thank you for visiting!\n";
      break;
    default:
      cout << "\033[31mInvalid choice!\033[0m\n";
    }

  } while (choice != 4);
}

int main()
{
  int roleChoice;
  cout << "\n===================================\n";
  cout << "     HOTEL MANAGEMENT SYSTEM\n";
  cout << "===================================\n";
  cout << "Select your role:\n";
  cout << "1. Admin\n";
  cout << "2. Customer\n";
  cout << "Enter choice: ";
  cin >> roleChoice;

  if (roleChoice == 1)
  {
    string password;
    cout << "Enter admin password: ";
    cin >> password;
    if (password != "admin123")
    {
      cout << "\033[31mIncorrect password! Access denied.\033[0m\n";
      return 0;
    }
    else
    {
      adminMenu();
    }
  }
  else if (roleChoice == 2)
  {
    // Customer menu
    customerMenu();
  }
  else
  {
    cout << "\033[31mInvalid choice! Exiting...\033[0m\n";
    return 0;
  }
  return 0;
}