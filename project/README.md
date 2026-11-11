# Hospital Patient Triage & Queue Management System

## Project Overview

The Hospital Patient Triage & Queue Management System is a C++ application designed to simulate how emergency departments manage patients based on medical urgency and arrival time.

The system uses a Priority Queue to ensure that patients with more critical medical conditions receive higher priority, while also considering arrival time when patients have the same severity level.

It also provides doctor assignment, treatment tracking, patient searching, and hospital statistics.

> **Note:** This project is an educational simulation and is not intended for real-world medical decision-making.

## Features

- **Patient Registration:** Register new patients with their personal information and severity level.
- **Priority-Based Queue:** Organize patients according to medical severity and arrival time.
- **Patient Search:** Search for patients using their unique ID.
- **Doctor Management:** Add and display doctors.
- **Doctor Assignment:** Assign available doctors to the highest-priority waiting patients.
- **Treatment Management:** Track patients currently receiving treatment.
- **Treatment Completion:** Record treatment start and end times, waiting time, and treatment duration.
- **Treatment History:** View completed treatment records.
- **Waiting Room Statistics:** Display waiting patient counts, severity distribution, and waiting-time statistics.
- **Hospital Statistics:** Display overall patient and doctor statistics.
- **Input Validation:** Handle invalid user input.

## Technologies & Concepts

- Programming Language: C++
- C++ Standard: C++17
- Data Structures:
  - `std::priority_queue`
  - `std::vector`
  - `struct`
  - Custom Comparator
- Algorithms:
  - Priority-based sorting
  - Searching
  - Statistical calculations
- Concepts:
  - Object-Oriented Programming
  - Time Complexity
  - Space Complexity

## Project Structure

```text
Hospital-Patient-Triage-System/
│
├── src/
│   └── main.cpp
│
├── docs/
│   ├── Complexity_Analysis.md
│   └── Test_Scenario_Logs.md
│
└── README.md
```

## Patient Priority Rules

Patients are prioritized using the following rules:

1. Lower severity codes receive higher priority.
2. If two patients have the same severity code, the patient who arrived earlier receives higher priority.
3. If both severity and arrival timestamps are equal, the patient with the smaller ID receives priority.

### Severity Classification

| Severity Code | Classification |
|---|---|
| 1 | Critical |
| 2 | Emergency |
| 3 | Urgent |
| 4 | Less Urgent |
| 5 | Non-Urgent |

## How to Compile and Run

### Requirements

- A C++ compiler supporting C++17.
- GCC / MinGW or another compatible compiler.

### Windows

Open the terminal inside the project directory and run:

```bash
g++ -std=c++17 -Wall -Wextra src/main.cpp -o hospital.exe
```

Run the application:

```bash
.\hospital.exe
```

If `main.cpp` is located directly in the project root instead of the `src` folder, use:

```bash
g++ -std=c++17 -Wall -Wextra main.cpp -o hospital.exe
```

## Main Menu

The application provides the following operations:

1. Add New Patient
2. Display Waiting Patients
3. Search Patient
4. Add Doctor
5. Display Doctors
6. Assign Doctor To Patient
7. Display Patients Under Treatment
8. Complete Treatment
9. Display Treatment History
10. Waiting Room Statistics
11. Hospital Statistics
0. Exit

## Complexity Analysis

| Operation | Time Complexity |
|---|---|
| Add Patient | O(log n) |
| Display Waiting Patients | O(n log n) |
| Search Patient | O(n log n + d + h) |
| Add Doctor | O(1) Amortized |
| Display Doctors | O(d) |
| Assign Doctor | O(d + log n) |
| Complete Treatment | O(d) |
| Display Treatment History | O(h) |
| Waiting Room Statistics | O(n log n) |
| Hospital Statistics | O(d + h) |

Where:

- `n` = Number of waiting patients.
- `d` = Number of doctors.
- `h` = Number of completed treatment records.

Overall Space Complexity: **O(n + d + h)**.

For detailed explanations, see `docs/Complexity_Analysis.md`.

## Testing

The system is designed to be tested using multiple scenarios, including:

- Patient registration.
- Priority ordering.
- Arrival-time ordering.
- Patient searching.
- Doctor assignment.
- Treatment completion.
- Waiting room statistics.
- Hospital statistics.
- Invalid input handling.
- Empty waiting room handling.

Detailed test scenarios and execution results are documented in `docs/Test_Scenario_Logs.md`.

## Limitations

- Patient and doctor data are stored in memory and are not permanently saved.
- Data is lost when the application is closed.
- The system is designed for educational purposes and does not replace professional medical triage systems.

## Author

**Ahmed Mohmed Hamed Eldersy**

Data Science Student  
Helwan University

## License

This project was developed for educational and academic purposes.