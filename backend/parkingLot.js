class ParkingLot {
  constructor(slots) {
    this.totalSlots = slots;
    this.availableSlots = slots;
    this.parkedVehicles = [];
    this.todayEarnings = 0;
  }

  findVehicle(plate) {
    return this.parkedVehicles.find(v => v.plate === plate);
  }

  parkVehicle(vehicle) {
    if (this.availableSlots <= 0)
      return "Parking Full";

    if (this.findVehicle(vehicle.plate))
      return "Vehicle already parked";

    this.parkedVehicles.push(vehicle);
    this.availableSlots--;
    return "Vehicle parked";
  }

  removeVehicle(plate, isMember) {
    const index = this.parkedVehicles.findIndex(v => v.plate === plate);
    if (index === -1)
      return null;

    let vehicle = this.parkedVehicles[index];
    let fee = vehicle.calculateFee();

    if (isMember)
      fee *= 0.8;

    this.todayEarnings += fee;
    this.parkedVehicles.splice(index, 1);
    this.availableSlots++;

    return fee;
  }
}

module.exports = ParkingLot;
