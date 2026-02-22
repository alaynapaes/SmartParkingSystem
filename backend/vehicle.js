class Vehicle {
  constructor(plate, type, hours = 1) {
    this.plate = plate;
    this.type = type;
    this.hours = hours;
  }

  calculateFee() {
    return this.hours * 5;
  }
}

class Car extends Vehicle {
  constructor(plate, hours) {
    super(plate, "Car", hours);
  }
  calculateFee() {
    return this.hours * 20;
  }
}

class Bike extends Vehicle {
  constructor(plate, hours) {
    super(plate, "Bike", hours);
  }
  calculateFee() {
    return this.hours * 10;
  }
}

class Truck extends Vehicle {
  constructor(plate, hours) {
    super(plate, "Truck", hours);
  }
  calculateFee() {
    return this.hours * 50;
  }
}

module.exports = { Vehicle, Car, Bike, Truck };
