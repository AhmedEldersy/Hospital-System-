# Test Scenario Logs
## Hospital Patient Triage & Queue Management System

### Test Environment

- Programming Language: C++
- Standard: C++17
- Main Data Structure: std::priority_queue
- Testing Method: Manual Functional Testing

### Test Case 1: Add New Patient

**Objective:** Verify that the system can register a new patient.

**Input:**
- Name: Ahmed
- Age: 25
- Severity Code: 3

**Expected Result:**
- Patient is registered successfully.
- A unique patient ID is generated.
- Patient is added to the waiting queue.

**Actual Result:** Patient registered successfully.

**Status:** PASS

---

### Test Case 2: Patient Priority Ordering

**Objective:** Verify that patients are arranged according to medical severity.

**Input:**

| Patient | Severity Code | Arrival Order |
|---|---:|---:|
| Ahmed | 3 | 1 |
| Mohamed | 1 | 2 |
| Ali | 2 | 3 |

**Expected Result:**

1. Mohamed
2. Ali
3. Ahmed

**Actual Result:** Patients are displayed according to severity priority.

**Status:** PASS

---

### Test Case 3: Same Severity Priority

**Objective:** Verify that patients with the same severity are prioritized according to arrival time.

**Input:**

| Patient | Severity Code | Arrival Order |
|---|---:|---:|
| Ahmed | 2 | 1 |
| Mohamed | 2 | 2 |
| Ali | 2 | 3 |

**Expected Result:**
Ahmed should appear first, followed by Mohamed and Ali.

**Actual Result:** Earlier arrivals receive higher priority when severity codes are equal.

**Status:** PASS

---

### Test Case 4: Search for a Patient

**Objective:** Verify patient searching using the patient ID.

**Input:**
- Existing Patient ID.

**Expected Result:**
The system displays the patient's information and current status.

**Actual Result:** Patient information is displayed correctly.

**Status:** PASS

---

### Test Case 5: Assign Doctor to Patient

**Objective:** Verify doctor assignment and patient removal from the waiting queue.

**Input:**
- Register a doctor.
- Add at least one patient.
- Select the doctor assignment operation.

**Expected Result:**
- The highest-priority patient is assigned.
- The doctor becomes unavailable.
- The patient appears under treatment.

**Actual Result:** Doctor assignment is completed successfully.

**Status:** PASS

---

### Test Case 6: Complete Treatment

**Objective:** Verify treatment completion and history recording.

**Input:**
- Select a patient currently under treatment.
- Complete the treatment.

**Expected Result:**
- Treatment end time is recorded.
- Waiting time and treatment duration are calculated.
- A treatment record is stored.
- The doctor becomes available again.

**Actual Result:** Treatment is completed and recorded successfully.

**Status:** PASS

---

### Test Case 7: Waiting Room Statistics

**Objective:** Verify waiting room statistics calculations.

**Input:**
- Register multiple patients with different severity codes.
- Keep the patients in the waiting queue.
- Open Waiting Room Statistics.

**Expected Result:**
The system displays:
- Total waiting patients.
- Number of patients in each severity category.
- Average waiting time.
- Longest waiting time.
- Shortest waiting time.
- Highest-priority waiting patient.

**Actual Result:** Waiting room statistics are displayed.

**Status:** PASS

---

### Test Case 8: Hospital Statistics

**Objective:** Verify overall hospital statistics.

**Input:**
- Register patients and doctors.
- Assign patients to doctors.
- Complete at least one treatment.
- Open Hospital Statistics.

**Expected Result:**
The system displays:
- Total registered patients.
- Waiting patients.
- Patients under treatment.
- Completed treatments.
- Total doctors.
- Available doctors.
- Busy doctors.
- Average waiting time.
- Average treatment duration.

**Actual Result:** Hospital statistics are displayed.

**Status:** PASS

---

### Test Case 9: Invalid Input Validation

**Objective:** Verify that the system handles invalid input.

**Input Examples:**
- Enter letters instead of a numeric age.
- Enter a negative age.
- Enter a severity code outside the range 1–5.
- Enter an invalid menu option.

**Expected Result:**
The system rejects invalid values and requests valid input.

**Actual Result:** Invalid input is rejected.

**Status:** PASS

---

### Test Case 10: Empty Waiting Room

**Objective:** Verify system behavior when no patients are waiting.

**Input:**
- Open the waiting patients display and waiting room statistics without registering patients.

**Expected Result:**
The system displays an appropriate empty waiting room message and does not crash.

**Actual Result:** Empty waiting room is handled correctly.

**Status:** PASS

---

### Final Testing Summary

| Test Category | Result |
|---|---|
| Patient Registration | PASS |
| Priority Ordering | PASS |
| Arrival Time Ordering | PASS |
| Patient Search | PASS |
| Doctor Assignment | PASS |
| Treatment Completion | PASS |
| Waiting Room Statistics | PASS |
| Hospital Statistics | PASS |
| Input Validation | PASS |
| Empty Queue Handling | PASS |

**Note:** These are expected test results based on the implemented functionality. Before submitting the project, execute each scenario and replace the actual-result and status fields with the results observed during your own testing.