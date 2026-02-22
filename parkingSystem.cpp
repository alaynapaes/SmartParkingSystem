#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Vehicle 
{
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

    virtual double calculateFee(){
        return parkedHours*5;
    }

    void display() {
        cout << "Plate: " << plateNumber << " Type: " << vehicleType << " Hours: " << parkedHours << endl;
    }
};

class Car : public Vehicle 
{
    public:
    Car(string plate, int hours) : Vehicle(plate, "Car", hours) {}
    Car(string plate) : Vehicle(plate, "Car", 1) {}

    double calculateFee() {
        return parkedHours * 20;
    }
};

class Bike : public Vehicle 
{
    public:
    Bike(string plate, int hours) : Vehicle(plate, "Bike", hours) {}
    Bike(string plate) : Vehicle(plate, "Bike", 1) {}

    double calculateFee() {
        return parkedHours * 10;
    }
};

class Truck : public Vehicle 
{
    public:
    Truck(string plate, int hours) : Vehicle(plate, "Truck", hours) {}
    Truck(string plate) : Vehicle(plate, "Truck", 1) {}

    double calculateFee() {
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

    void parkVehicle(Vehicle &v) {
        if (availableSlots <= 0) {
            cout << "Parking Full! Cannot park vehicle.\n";
            return;
        }
        parkedVehicles.push_back(v);
        availableSlots--;
        cout << v.vehicleType << " (" << v.plateNumber << ") parked successfully.\n";
        fileHandling("Parked: " + v.vehicleType + " " + v.plateNumber);
    }

    void removeVehicle(string plate) {
        int x = -1;
        for (int i = 0; i < parkedVehicles.size(); i++) 
        {
            if (parkedVehicles[i].plateNumber == plate) {
                x = i;
                break;
            }
        }

        if (x == -1) {
            cout << "Vehicle with plate " << plate << " not found in lot.\n";
            return;
        }

        cout << "Fee for " << plate << ": Rs " << parkedVehicles[x].calculateFee() << endl;
        for (int i = x; i < parkedVehicles.size() - 1; i++) 
        {
            parkedVehicles[i] = parkedVehicles[i + 1];
        }
        parkedVehicles.pop_back();
        availableSlots++;
        cout << "Vehicle " << plate << " exited successfully.\n";
        fileHandling("Exited: " + parkedVehicles[x].vehicleType + " " + parkedVehicles[x].plateNumber);
    }

    void showStatus() {
        cout << "\nParking Lot Status:\n";
        cout << "Available Slots: " << availableSlots << "/" << totalSlots << endl;
        cout << "Total Parked Vehicles: " << parkedVehicles.size() << endl << endl;
    }
};

int main() {
    ParkingLot pl(5);

    Car c1("ABC123", 3);
    Bike b1("XYZ789", 2);
    Truck t1("TRK555", 4);

    pl.parkVehicle(c1);
    pl.parkVehicle(b1);
    pl.parkVehicle(t1);

    pl.showStatus();

    //pl.removeVehicle("ABC123");
    //pl.removeVehicle("XYZ789");
   //pl.showStatus();

    return 0;
}
