const BASE_URL = "http://localhost:3000";

// PARK VEHICLE
function parkVehicle() {
  const type = document.getElementById("type").value;
  const plate = document.getElementById("plate").value;
  const hours = Number(document.getElementById("hours").value);

  fetch(`${BASE_URL}/park`, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ type, plate, hours })
  })
  .then(res => res.json())
  .then(data => alert(data.msg))
  .catch(err => alert("Error: " + err));
}

// REMOVE VEHICLE
function removeVehicle() {
  const plate = document.getElementById("removePlate").value;
  const isMember = document.getElementById("member").checked;

  fetch(`${BASE_URL}/remove`, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ plate, isMember })
  })
  .then(res => res.json())
  .then(data => {
    if (data.fee !== undefined)
      alert("Payable Fee: Rs " + data.fee);
    else
      alert(data.msg);
  })
  .catch(err => alert("Error: " + err));
}

// GET STATUS
function getStatus() {
  fetch(`${BASE_URL}/status`)
    .then(res => res.json())
    .then(data => {
      document.getElementById("status").textContent =
        JSON.stringify(data, null, 2);
    });
}
