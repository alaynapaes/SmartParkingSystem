# Smart Parking System

## Project Overview

Smart Parking System is a full-stack parking management application that allows users to park vehicles, calculate parking fees, apply membership discounts, and track parking lot status in real time.

The project includes:

- A C++ console-based implementation demonstrating OOP concepts  
- A full-stack web version built with HTML, JavaScript, Node.js, and Express  
- REST API integration between frontend and backend  
- Fee calculation logic based on vehicle type and parking duration  
- Membership-based discount system  

This project demonstrates object-oriented programming, backend API design, and frontend-backend integration.

---

## Features

### 1. Vehicle Types Supported

- Car — Rs 20 per hour  
- Bike — Rs 10 per hour  
- Truck — Rs 50 per hour  

---

### 2. Park Vehicle

- Select vehicle type  
- Enter plate number  
- Enter parking hours  
- System checks:
  - If parking lot is full  
  - If vehicle is already parked  

---

### 3. Remove Vehicle

- Enter plate number  
- Optional membership discount (20%)  
- System calculates total payable fee  
- Updates available slots  
- Tracks daily earnings (backend)

---

### 4. Parking Status

- View total available slots  
- View list of currently parked vehicles  
- Real-time status via API  

---

## Technologies Used

### C++ Version

- OOP concepts (Inheritance, Polymorphism, Encapsulation)  
- File handling  
- STL vector  
- Console-based interaction  

---

### Web Version

#### Frontend

- HTML  
- CSS  
- JavaScript  
- Fetch API  

#### Backend

- Node.js  
- Express.js  
- CORS  
- REST APIs  

---

## Project Structure

### C++ Implementation

- Vehicle (Base Class)  
- Car, Bike, Truck (Derived Classes)  
- ParkingLot Class  
- File logging (parking_lot.txt)  

---

### Web Implementation

#### Frontend
- index.html  
- script.js  
- Simple responsive UI  

#### Backend
- server.js  
- parkingLot.js  
- vehicle.js  

---

## API Endpoints

### POST /park

Parks a vehicle.

Request Body:
```json
{
  "type": "Car",
  "plate": "ABC123",
  "hours": 3
}
```

Response:
```json
{ "msg": "Vehicle parked" }
```

---

### POST /remove

Removes a vehicle and calculates fee.

Request Body:
```json
{
  "plate": "ABC123",
  "isMember": true
}
```

Response:
```json
{ "fee": 48 }
```

---

### GET /status

Returns current parking lot status.

Response:
```json
{
  "availableSlots": 8,
  "vehicles": [...]
}
```

---

## How to Run the Web Version

### 1. Install Dependencies

Navigate to the backend folder:

```bash
npm install
```

### 2. Start Server

```bash
node server.js
```

Server runs on:

```
http://localhost:3000
```

### 3. Run Frontend

Open index.html in your browser.

---

## OOP Concepts Demonstrated

- Inheritance (Car, Bike, Truck inherit from Vehicle)  
- Polymorphism (Overriding calculateFee())  
- Encapsulation (ParkingLot class managing state)  
- Modular backend architecture  

---

## Future Improvements

- Database integration (MongoDB / MySQL)  
- Admin dashboard  
- Authentication system  
- QR-based vehicle entry  
- Payment gateway integration  
- Deployment to cloud platform  

---

## Purpose of the Project

This project demonstrates:

- Strong understanding of Object-Oriented Programming  
- RESTful API design  
- Full-stack integration  
- Real-world fee calculation logic  
- Clean modular backend architecture  

It serves as a practical implementation of a scalable smart parking management system.
