const express = require("express");
const cors = require("cors");
const ParkingLot = require("./parkingLot");
const { Car, Bike, Truck } = require("./vehicle");

const app = express();
app.use(cors());
app.use(express.json());

const parkingLot = new ParkingLot(10);

app.post("/park", (req, res) => {
  const { type, plate, hours } = req.body;
  let vehicle;

  if (type === "Car") vehicle = new Car(plate, hours);
  else if (type === "Bike") vehicle = new Bike(plate, hours);
  else if (type === "Truck") vehicle = new Truck(plate, hours);
  else return res.status(400).json({ msg: "Invalid vehicle type" });

  res.json({ msg: parkingLot.parkVehicle(vehicle) });
});

app.post("/remove", (req, res) => {
  const { plate, isMember } = req.body;
  const fee = parkingLot.removeVehicle(plate, isMember);

  if (fee === null)
    return res.status(404).json({ msg: "Vehicle not found" });

  res.json({ fee });
});

app.get("/status", (req, res) => {
  res.json({
    availableSlots: parkingLot.availableSlots,
    vehicles: parkingLot.parkedVehicles
  });
});

app.listen(3000, () =>
  console.log("Smart Parking Backend running on port 3000")
);
