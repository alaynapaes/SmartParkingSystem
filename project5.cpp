#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

bool registerUser(string username, string password) 
{
    ofstream file("users.txt", ios::app);
    if (!file.is_open()) return false;

    file << username << " " << password << endl;
    file.close();
    return true;
}

bool loginUser(string username, string password) 
{
    ifstream file("users.txt");
    if (!file.is_open()) return false;

    string u, p;
    while (file >> u >> p) {
        if (u == username && p == password)
            return true;
    }
    return false;
}

class Vehicle 
{
    protected:
    int parkedHours;

    public:
    string plateNumber;
    string vehicleType;

    Vehicle(string plate, string type, int hours = 1) 
    {
        plateNumber = plate;
        vehicleType = type;
        parkedHours = hours;
    }

    virtual double calculateFee() 
    {
        return parkedHours * 5;
    }

    friend void showVehicleInfo(Vehicle &v) 
    {
        cout << "Plate: " << v.plateNumber << ", Type: " << v.vehicleType
             << ", Hours: " << v.parkedHours << endl;
    }
};

class Car : public Vehicle 
{
    public:
    Car(string plate, int hours = 1) : Vehicle(plate, "Car", hours) {}
    double calculateFee() 
    {  
        return parkedHours * 20; 
    }
};

class Bike : public Vehicle 
{
    public:
    Bike(string plate, int hours = 1) : Vehicle(plate, "Bike", hours) {}
    double calculateFee() 
    { 
        return parkedHours * 10; 
    }
};

class Truck : public Vehicle 
{
    public:
    Truck(string plate, int hours = 1) : Vehicle(plate, "Truck", hours) {}
    double calculateFee() 
    { 
        return parkedHours * 50; 
    }
};

class ParkingLot 
{
    private:
    int totalSlots;
    int availableSlots;
    vector<Vehicle> parkedVehicles;

    public:
    bool isMember = false; 

    ParkingLot(int slots) 
    {
        totalSlots = slots;
        availableSlots = slots;
    }

    void fileHandling(string message) 
    {
        ofstream file("parking_lot.txt", ios::app);
        if (file.is_open()) {
            file << message << endl;
            file.close();
        }
    }

    int findVehicleIndex(string plate) 
    {
        for (int i = 0; i < parkedVehicles.size(); i++) {
            if (parkedVehicles[i].plateNumber == plate)
                return i;
        }
        return -1;
    }

    void parkVehicle(Vehicle v) 
    {
        if (availableSlots <= 0) 
        {
            cout << "Parking Full! Cannot park vehicle.\n";
            return;
        }

        int x = findVehicleIndex(v.plateNumber);
        if (x != -1) 
        {
            cout << "Vehicle with plate " << v.plateNumber
                 << " is already parked!\n";
            return;
        }

        parkedVehicles.push_back(v);
        availableSlots--;
        cout << v.vehicleType << " (" << v.plateNumber
             << ") parked successfully.\n";
        fileHandling("Parked: " + v.vehicleType + " " + v.plateNumber);
    }

    void removeVehicle(string plate) 
    {
        int x = findVehicleIndex(plate);
        if (x == -1) 
        {
            cout << "Vehicle with plate " << plate << " not found.\n";
            fileHandling("Failed removal: " + plate);
            return;
        }

        double fee = parkedVehicles[x].calculateFee();
        if (isMember) 
        {
            fee *= 0.80;  // 20% discount
            cout << "Membership discount applied! ";
        }

        cout << "Fee for " << plate << ": Rs " << fee << endl;

        string type = parkedVehicles[x].vehicleType;
        string num = parkedVehicles[x].plateNumber;

        for (int i = x; i < parkedVehicles.size() - 1; i++)
            parkedVehicles[i] = parkedVehicles[i + 1];

        parkedVehicles.pop_back();
        availableSlots++;

        cout << "Vehicle " << plate << " exited successfully.\n";
        fileHandling("Exited: " + type + " " + num);
    }

    void showStatus() 
    {
        cout << "\nParking Lot Status:\n";
        cout << "Available Slots: " << availableSlots << "/" << totalSlots << endl;
        cout << "Total Parked Vehicles: " << parkedVehicles.size() << endl;
        cout << "Membership: " << (isMember ? "Active" : "Not Active") << endl;

        for (int i = 0; i < parkedVehicles.size(); i++)
            showVehicleInfo(parkedVehicles[i]);

        cout << endl;
    }

    void newDayReset() 
    {
        parkedVehicles.clear();
        availableSlots = totalSlots;
        cout << "New day started! All slots reset.\n";
        fileHandling("---- New Day Started ----");
    }
};

int main() {

    /* 
    ===================== PROGRAM INSTRUCTIONS =====================
    
        This Smart Parking System allows the user to:
    1. optionally register/login for a membership.
       - Membership Fee = Rs 200 (one-time)
       - Members get 20% discount on parking fees.
       - Login/Register stored in "users.txt".

    2. Park vehicles (Car / Bike / Truck)
    3. Remove vehicles
    4. Show parking lot status
    5. Reset parking lot for a new day

    Additional Features:
    - Every time a vehicle is parked or removed, the details are saved
      in "parking_lot.txt".
    - All currently parked vehicles and remaining available slots are
      continuously recorded in "parking_lot.txt" through the fileHandling()
      function.
    - Membership is optional. If user skips it, they can still use the
      full parking system normally but without discount.


    ================================================================
    */

    const int MEMBERSHIP_FEE = 200;
    ParkingLot pl(5);

    cout << "\nDo you want to register for membership and get 20% discount? (y/n): ";
    char ch;
    cin >> ch;

    if (ch == 'y' || ch == 'Y') {
        int opt;
        cout << "\n1. Login\n2. Register\nEnter option: ";
        cin >> opt;

        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        if (opt == 1) {
            if (loginUser(username, password)) 
            {
                cout << "Login successful! Membership active.\n";
                pl.isMember = true;
            } else 
            {
                cout << "Invalid login. Continuing without membership.\n";
            }
        }
        else if (opt == 2) 
        {
            if (registerUser(username, password)) 
            {
                cout << "Registration successful!\n";
                cout << "Membership fee charged: Rs " << MEMBERSHIP_FEE << endl;
                pl.isMember = true;
            } 
        }
        else 
        {
            cout << "Invalid option. Using system without membership.\n";
        }
    }
    else 
    {
        cout << "Using parking system without membership.\n";
        pl.isMember = false;
    }

    int choice;

    do {
        cout << "\n=== SMART PARKING SYSTEM ===\n";
        cout << "1. Park Vehicle\n";
        cout << "2. Remove Vehicle\n";
        cout << "3. Show Parking Status\n";
        cout << "4. Start New Day\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) 
        {
            string type, plate;
            int hours;

            cout << "Enter Vehicle Type (Car/Bike/Truck): ";
            cin >> type;
            cout << "Enter Plate Number: ";
            cin >> plate;
            cout << "Enter Hours Parked: ";
            cin >> hours;

            if (type == "Car" || type == "car")
                pl.parkVehicle(Car(plate, hours));
            else if (type == "Bike" || type == "bike")
                pl.parkVehicle(Bike(plate, hours));
            else if (type == "Truck" || type == "truck")
                pl.parkVehicle(Truck(plate, hours));
            else
                cout << "Invalid type.\n";
        }

        else if (choice == 2) 
        {
            string plate;
            cout << "Enter Plate Number to remove: ";
            cin >> plate;
            pl.removeVehicle(plate);
        }

        else if (choice == 3) 
        {
            pl.showStatus();
        }

        else if (choice == 4) 
        {
            pl.newDayReset();
        }

        else if (choice == 5) 
        {
            cout << "Exiting system...\n";
        }

        else
            cout << "Invalid choice.\n";

    } while (choice != 5);

    return 0;
}
