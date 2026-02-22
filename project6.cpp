#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

bool registerUser(string username, string password)
{
    ofstream file("users.txt", ios::app);
    if (!file.is_open())
        return false;

    file << username << " " << password << endl;
    return true;
}

bool loginUser(string username, string password)
{
    ifstream file("users.txt");
    if (!file.is_open())
        return false;

    string u, p;
    while (file >> u >> p)
        if (u == username && p == password)
            return true;

    return false;
}

//admin txt file should be created with username admin and password 12345
bool adminLogin(string username, string password)
{
    ifstream file("admin.txt");
    if (!file.is_open())
        return false;

    string u, p;
    while (file >> u >> p)
        if (u == username && p == password)
            return true;

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

    friend void showVehicleInfo(const Vehicle &v)
    {
        cout << "Plate: " << v.plateNumber
             << ", Type: " << v.vehicleType
             << ", Hours: " << v.parkedHours << endl;
    }
};

class Car : public Vehicle
{
public:
    Car(string plate, int hours = 1) : Vehicle(plate, "Car", hours) {}
    double calculateFee() { return parkedHours * 20; }
};

class Bike : public Vehicle
{
public:
    Bike(string plate, int hours = 1) : Vehicle(plate, "Bike", hours) {}
    double calculateFee() { return parkedHours * 10; }
};

class Truck : public Vehicle
{
public:
    Truck(string plate, int hours = 1) : Vehicle(plate, "Truck", hours) {}
    double calculateFee() { return parkedHours * 50; }
};

class ParkingLot
{
private:
    int totalSlots;
    int availableSlots;
    vector<Vehicle> parkedVehicles;
    double todayEarnings = 0;

public:
    bool isMember = false;

    ParkingLot(int slots)
    {
        totalSlots = slots;
        availableSlots = slots;
    }

    void updateParkingFile()
    {
        ofstream file("parkingLot.txt");
        if (!file.is_open())
            return;

        file << "===== CURRENT PARKING LOT STATUS =====\n";
        file << "Total Slots: " << totalSlots << endl;
        file << "Available Slots: " << availableSlots << endl;
        file << "Parked Vehicles: " << parkedVehicles.size() << "\n\n";

        for (auto &v : parkedVehicles)
        {
            file << v.vehicleType << " | " << v.plateNumber
                 << " | Hours: " << v.calculateFee() << endl;
        }
        file.close();
    }

    void saveEarnings(double fee)
    {
        ofstream file("earnings.txt", ios::app);
        if (file.is_open())
        {
            file << "Earned: Rs " << fee << endl;
        }
    }

    int findVehicleIndex(string plate)
    {
        for (int i = 0; i < parkedVehicles.size(); i++)
            if (parkedVehicles[i].plateNumber == plate)
                return i;
        return -1;
    }

    void parkVehicle(Vehicle v)
    {
        if (availableSlots <= 0)
        {
            cout << "Parking Full!\n";
            return;
        }

        if (findVehicleIndex(v.plateNumber) != -1)
        {
            cout << "Vehicle already parked.\n";
            return;
        }

        parkedVehicles.push_back(v);
        availableSlots--;
        cout << v.vehicleType << " (" << v.plateNumber << ") parked.\n";

        updateParkingFile();
    }

    void removeVehicle(string plate)
    {
        int index = findVehicleIndex(plate);
        if (index == -1)
        {
            cout << "Vehicle not found.\n";
            return;
        }

        double fee = parkedVehicles[index].calculateFee();
        if (isMember)
        {
            fee *= 0.80;
            cout << "Membership discount applied! ";
        }

        cout << "Payable Fee: Rs " << fee << endl;
        todayEarnings += fee;
        saveEarnings(fee);

        parkedVehicles.erase(parkedVehicles.begin() + index);
        availableSlots++;

        updateParkingFile();
        cout << "Vehicle Removed.\n";
    }

    void showStatus()
    {
        cout << "\n--- CURRENT PARKING STATUS ---\n";
        cout << "Available Slots: " << availableSlots << "/" << totalSlots << endl;
        cout << "Vehicles Parked: " << parkedVehicles.size() << endl;

        for (auto &v : parkedVehicles)
            showVehicleInfo(v);

        cout << endl;
    }

    void resetForNewDay()
    {
        parkedVehicles.clear();
        availableSlots = totalSlots;
        todayEarnings = 0;

        updateParkingFile();

        cout << "New Day Reset Completed.\n";
    }

    void viewDailyEarnings()
    {
        cout << "Total Earnings Today: Rs " << todayEarnings << endl;
    }
};

int main()
{
    ParkingLot pl(10);
    const int MEMBERSHIP_FEE = 200;

    cout << "\n========================================\n";
    cout << "      WELCOME TO SMART PARKING SYSTEM\n";
    cout << "========================================\n";

    int startChoice;
    cout << "\nLogin as:\n";
    cout << "1. User\n";
    cout << "2. Admin\n";
    cout << "Enter choice: ";
    cin >> startChoice;

    if (startChoice == 2)
    {
        string u, p;
        cout << "\n--- ADMIN LOGIN ---\n";
        cout << "Admin Username: ";
        cin >> u;
        cout << "Admin Password: ";
        cin >> p;

        if (!adminLogin(u, p))
        {
            cout << "Admin login failed! Exiting...\n";
            return 0;
        }

        int a;
        cout << "\n--- ADMIN PANEL ---\n";
        cout << "1. Reset New Day\n";
        cout << "2. View Daily Earnings\n";
        cout << "Enter choice: ";
        cin >> a;

        if (a == 1)
            pl.resetForNewDay();
        else if (a == 2)
            pl.viewDailyEarnings();
        else
            cout << "Invalid Option.\n";

        return 0;
    }

    cout << "\nDo you want membership? (20% discount) (y/n): ";
    char mem;
    cin >> mem;

    if (mem == 'y' || mem == 'Y')
    {
        int choice;
        cout << "1. Login\n2. Register\nEnter choice: ";
        cin >> choice;

        string u, p;
        cout << "Username: ";
        cin >> u;
        cout << "Password: ";
        cin >> p;

        if (choice == 1)
        {
            if (loginUser(u, p))
            {
                cout << "Login successful! Membership active.\n";
                pl.isMember = true;
            }
            else
                cout << "Invalid login.\n";
        }
        else
        {
            if (registerUser(u, p))
            {
                cout << "Registered. Membership Fee: Rs 200\n";
                pl.isMember = true;
            }
        }
    }

    int ch;
    do
    {
        cout << "\n==== SMART PARKING MENU ====\n";
        cout << "1. Park Vehicle\n";
        cout << "2. Remove Vehicle\n";
        cout << "3. Show Parking Status\n";
        cout << "4. Admin Menu\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> ch;

        if (ch == 1)
        {
            string type, plate;
            int hrs;

            cout << "Vehicle Type (Car/Bike/Truck): ";
            cin >> type;
            cout << "Plate Number: ";
            cin >> plate;
            cout << "Hours Parked: ";
            cin >> hrs;
            if (hrs > 12)
            {
                cout << "Parking not availabe for more than 12 hours. ";
                continue;
            }
            if (type == "Car" || type == "car")
                pl.parkVehicle(Car(plate, hrs));
            else if (type == "Bike" || type == "bike")
                pl.parkVehicle(Bike(plate, hrs));
            else if (type == "Truck" || type == "truck")
                pl.parkVehicle(Truck(plate, hrs));
            else
                cout << "Invalid Vehicle Type.\n";
        }

        else if (ch == 2)
        {
            string plate;
            cout << "Enter Plate: ";
            cin >> plate;
            pl.removeVehicle(plate);
        }

        else if (ch == 3)
        {
            pl.showStatus();
        }

        else if (ch == 4)
        {
            string u, p;
            cout << "\n--- ADMIN LOGIN ---\n";
            cout << "Admin Username: ";
            cin >> u;
            cout << "Admin Password: ";
            cin >> p;

            if (adminLogin(u, p))
            {
                int a;
                cout << "\n--- ADMIN PANEL ---\n";
                cout << "1. Reset New Day\n";
                cout << "2. View Daily Earnings\n";
                cout << "Enter choice: ";
                cin >> a;

                if (a == 1)
                    pl.resetForNewDay();
                else if (a == 2)
                    pl.viewDailyEarnings();
                else
                    cout << "Invalid Option.\n";
            }
            else
                cout << "Admin login failed.\n";
        }

    } while (ch != 5);

    cout << "Exiting System...\n";
    return 0;
}
