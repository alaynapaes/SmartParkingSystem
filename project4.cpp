#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Vehicle {
protected:
    int parkedHours;

public:
    string plateNumber;
    string vehicleType;

    Vehicle(string plate, string type, int hours = 1) {
        plateNumber = plate;
        vehicleType = type;
        parkedHours = hours;
    }

    virtual double calculateFee() {
        return parkedHours * 5;
    }

    friend void showVehicleInfo(Vehicle &v) {
        cout << "Plate: " << v.plateNumber << ", Type: " << v.vehicleType << ", Hours: " << v.parkedHours << endl;
    }
};

class Car : public Vehicle {
public:
    Car(string plate, int hours = 1) : Vehicle(plate, "Car", hours) {}
    double calculateFee() {
        return parkedHours * 20;
    }
};

class Bike : public Vehicle {
public:
    Bike(string plate, int hours = 1) : Vehicle(plate, "Bike", hours) {}
    double calculateFee() {
        return parkedHours * 10;
    }
};

class Truck : public Vehicle {
public:
    Truck(string plate, int hours = 1) : Vehicle(plate, "Truck", hours) {}
    double calculateFee() {
        return parkedHours * 50;
    }
};

class ParkingLot {
private:
    int totalSlots;
    int availableSlots;
    vector<Vehicle> parkedVehicles;

public:
    ParkingLot(int slots) {
        totalSlots = slots;
        availableSlots = slots;
    }

    void fileHandling(string message) {
        ofstream file("parking_lot.txt", ios::app);
        if (file.is_open()) {
            file << message << endl;
            file.close();
        }
    }

    int findVehicleIndex(string plate) {
        for (int i = 0; i < parkedVehicles.size(); i++) {
            if (parkedVehicles[i].plateNumber == plate)
                return i;
        }
        return -1;
    }

    void parkVehicle(Vehicle v) {
        if (availableSlots <= 0) {
            cout << "Parking Full! Cannot park vehicle.\n";
            return;
        }

        int x = findVehicleIndex(v.plateNumber);
        if (x != -1) {
            cout << "Vehicle with plate " << v.plateNumber << " is already parked!\n";
            return;
        }

        parkedVehicles.push_back(v);
        availableSlots--;
        cout << v.vehicleType << " (" << v.plateNumber << ") parked successfully.\n";
        fileHandling("Parked: " + v.vehicleType + " " + v.plateNumber);
    }

    void removeVehicle(string plate) {
        int x = findVehicleIndex(plate);
        if (x == -1) {
            cout << "Vehicle with plate " << plate << " not found in lot.\n";
            fileHandling("Attempted removal of non-existent vehicle: " + plate);
            return;
        }

        cout << "Fee for " << plate << ": Rs " << parkedVehicles[x].calculateFee() << endl;
        string type = parkedVehicles[x].vehicleType;
        string num = parkedVehicles[x].plateNumber;

        for (int i = x; i < parkedVehicles.size() - 1; i++) {
            parkedVehicles[i] = parkedVehicles[i + 1];
        }

        parkedVehicles.pop_back();
        availableSlots++;
        cout << "Vehicle " << plate << " exited successfully.\n";
        fileHandling("Exited: " + type + " " + num);
    }

    void showStatus() {
        cout << "\nParking Lot Status:\n";
        cout << "Available Slots: " << availableSlots << "/" << totalSlots << endl;
        cout << "Total Parked Vehicles: " << parkedVehicles.size() << endl;
        for (int i = 0; i < parkedVehicles.size(); i++) {
            showVehicleInfo(parkedVehicles[i]);
        }
        cout << endl;
    }

    void newDayReset() {
        parkedVehicles.clear();
        availableSlots = totalSlots;
        cout << "New day started! All slots are now available.\n";
        fileHandling("---- New Day Started: All Slots Reset ----");
    }
};

int main() {
    ParkingLot pl(5);
    int choice;

    do {
        cout << "\n=== SMART PARKING SYSTEM ===\n";
        cout << "1. Park Vehicle\n";
        cout << "2. Remove Vehicle\n";
        cout << "3. Show Parking Status\n";
        cout << "4. Start New Day\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string type, plate;
            int hours;
            cout << "Enter Vehicle Type (Car/Bike/Truck): ";
            cin >> type;
            cout << "Enter Plate Number: ";
            cin >> plate;
            cout << "Enter Parked Hours: ";
            cin >> hours;

            if (type == "Car" || type == "car")
                pl.parkVehicle(Car(plate, hours));
            else if (type == "Bike" || type == "bike")
                pl.parkVehicle(Bike(plate, hours));
            else if (type == "Truck" || type == "truck")
                pl.parkVehicle(Truck(plate, hours));
            else
                cout << "Invalid vehicle type!\n";

        } 
        else if (choice == 2) {
            string plate;
            cout << "Enter Plate Number to remove: ";
            cin >> plate;
            pl.removeVehicle(plate);

        } 
        else if (choice == 3) {
            pl.showStatus();

        } 
        else if (choice == 4) {
            pl.newDayReset();

        } 
        else if (choice == 5) {
            cout << "Exiting system...\n";

        } 
        else {
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
