# Complexity Analysis
## Hospital Patient Triage & Queue Management System

### 1. Introduction

This document analyzes the time and space complexity of the main operations implemented in the Hospital Patient Triage & Queue Management System.

The system uses a priority queue to manage patients according to their medical severity and arrival time.

### 2. Time Complexity Analysis

| Operation | Time Complexity | Explanation |
|---|---|---|
| Add New Patient | O(log n) | Inserting a patient into the priority queue requires heap reordering. |
| Display Waiting Patients | O(n log n) | A temporary priority queue is copied and its elements are removed one by one. |
| Search Patient | O(n log n + d + h) | The waiting queue is copied and traversed, followed by searching doctors and treatment history. |
| Add Doctor | O(1) Amortized | Adding a doctor to a vector takes constant amortized time. |
| Display Doctors | O(d) | Every doctor is visited once. |
| Assign Doctor | O(d + log n) | The system searches for an available doctor and removes the highest-priority patient. |
| Display Patients Under Treatment | O(d) | The system checks the doctors to find patients currently receiving treatment. |
| Complete Treatment | O(d) | The system searches for the doctor treating the selected patient. |
| Display Treatment History | O(h) | Every completed treatment record is displayed once. |
| Waiting Room Statistics | O(n log n) | A temporary priority queue is created and traversed to calculate statistics. |
| Hospital Statistics | O(d + h) | The system traverses doctors and completed treatment records. |

### 3. Space Complexity Analysis

| Data Structure | Space Complexity | Purpose |
|---|---|---|
| Priority Queue | O(n) | Stores waiting patients. |
| Doctors Vector | O(d) | Stores registered doctors. |
| Treatment History Vector | O(h) | Stores completed treatment records. |
| Temporary Priority Queue | O(n) | Used for displaying and analyzing waiting patients. |

### 4. Overall Space Complexity

The overall storage complexity is:

**O(n + d + h)**

Where:

- n = Number of waiting patients.
- d = Number of registered doctors.
- h = Number of completed treatment records.

### 5. Conclusion

The priority queue provides efficient patient insertion and removal operations with O(log n) time complexity.

The system prioritizes patients based on medical severity and arrival time. Operations that require displaying or searching all waiting patients are more expensive because the priority queue does not support direct iteration or searching.

Overall, the selected data structures provide an appropriate balance between efficient patient prioritization and straightforward management of doctors and treatment records.