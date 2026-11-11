
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <limits>
#include <stdexcept>

using namespace std;

struct Patient {
    int id;
    string name;
    int age;
    int severityCode;
    time_t arrivalTime;
};

struct Doctor {
    int id;
    string name;
    bool isAvailable = true;
    Patient currentPatient{};
    time_t treatmentStartTime = 0;
};

struct TreatmentRecord {
    int patientID;
    string patientName;
    int patientAge;
    int severityCode;

    int doctorID;
    string doctorName;

    time_t arrivalTime;
    time_t treatmentStartTime;
    time_t treatmentEndTime;

    double waitingTime;
    double treatmentDuration;
};

struct ComparePatients {

    bool operator()(const Patient& p1,
                    const Patient& p2) const {

        if (p1.severityCode != p2.severityCode) {
            return p1.severityCode > p2.severityCode;
        }

        if (p1.arrivalTime != p2.arrivalTime) {
            return p1.arrivalTime > p2.arrivalTime;
        }

        return p1.id > p2.id;
    }
};

class HospitalSystem {

private:

    priority_queue<
        Patient,
        vector<Patient>,
        ComparePatients
    > waitingQueue;

    vector<Doctor> doctors;
    vector<TreatmentRecord> treatmentHistory;

    int nextPatientID = 1;
    int nextDoctorID = 1;
    int totalRegisteredPatients = 0;

    int readInteger(string message, int minValue, int maxValue) {

        while (true) {

            cout << message;

            string input;
            getline(cin, input);

            try {

                size_t pos;
                int value = stoi(input, &pos);

                if (pos != input.size()) {
                    throw invalid_argument("Invalid input");
                }

                if (value < minValue || value > maxValue) {
                    cout << "Value must be between "
                         << minValue << " and "
                         << maxValue << ".\n";
                    continue;
                }

                return value;

            }
            catch (...) {
                cout << "Invalid input! Enter a valid number.\n";
            }
        }
    }

    string readString(string message) {

        string value;

        while (true) {

            cout << message;
            getline(cin, value);

            if (!value.empty() &&
                value.find_first_not_of(" \t") != string::npos) {
                return value;
            }

            cout << "Input cannot be empty!\n";
        }
    }

    string formatTime(time_t timestamp) {

        if (timestamp == 0) {
            return "Not Available";
        }

        tm* timeInfo = localtime(&timestamp);

        if (timeInfo == nullptr) {
            return "Invalid Time";
        }

        stringstream ss;
        ss << put_time(timeInfo, "%Y-%m-%d %H:%M:%S");

        return ss.str();
    }

    string getSeverityName(int severity) {

        switch (severity) {

            case 1: return "Critical";
            case 2: return "Emergency";
            case 3: return "Urgent";
            case 4: return "Less Urgent";
            case 5: return "Non-Urgent";

            default: return "Unknown";
        }
    }

    int findAvailableDoctor() {

        for (int i = 0; i < (int)doctors.size(); i++) {

            if (doctors[i].isAvailable) {
                return i;
            }
        }

        return -1;
    }

public:

    void addPatient() {

        cout << "\n========== ADD NEW PATIENT ==========\n";

        Patient p;

        p.name = readString("Enter Patient Name: ");
        p.age = readInteger("Enter Patient Age: ", 1, 120);

        p.severityCode =
            readInteger("Enter Severity Code (1-5): ", 1, 5);

        p.id = nextPatientID++;
        p.arrivalTime = time(nullptr);

        waitingQueue.push(p);
        totalRegisteredPatients++;

        cout << "\nPatient Added Successfully!\n";
        cout << "Patient ID: " << p.id << endl;
        cout << "Patient Name: " << p.name << endl;

        cout << "Severity: "
             << getSeverityName(p.severityCode) << endl;

        cout << "Arrival Time: "
             << formatTime(p.arrivalTime) << endl;
    }

    void displayWaitingPatients() {

        cout << "\n========== WAITING PATIENTS ==========\n";

        if (waitingQueue.empty()) {
            cout << "No Patients Waiting.\n";
            return;
        }

        auto tempQueue = waitingQueue;

        cout << left
             << setw(8) << "ID"
             << setw(20) << "Name"
             << setw(8) << "Age"
             << setw(15) << "Severity"
             << "Arrival Time\n";

        cout << string(75, '-') << endl;

        while (!tempQueue.empty()) {

            Patient p = tempQueue.top();

            cout << left
                 << setw(8) << p.id
                 << setw(20) << p.name
                 << setw(8) << p.age
                 << setw(15) << p.severityCode
                 << formatTime(p.arrivalTime) << endl;

            tempQueue.pop();
        }
    }

    void searchPatient() {

        cout << "\n========== SEARCH PATIENT ==========\n";

        int searchID =
            readInteger("Enter Patient ID: ", 1,
                        numeric_limits<int>::max());

        auto tempQueue = waitingQueue;

        while (!tempQueue.empty()) {

            Patient p = tempQueue.top();

            if (p.id == searchID) {

                cout << "\nPatient Found!\n";
                cout << "Name: " << p.name << endl;
                cout << "Age: " << p.age << endl;

                cout << "Severity: "
                     << getSeverityName(p.severityCode) << endl;

                cout << "Arrival Time: "
                     << formatTime(p.arrivalTime) << endl;

                cout << "Status: Waiting\n";
                return;
            }

            tempQueue.pop();
        }

        for (const Doctor& d : doctors) {

            if (!d.isAvailable &&
                d.currentPatient.id == searchID) {

                cout << "\nPatient Found!\n";
                cout << "Name: "
                     << d.currentPatient.name << endl;

                cout << "Doctor: " << d.name << endl;

                cout << "Status: Under Treatment\n";
                return;
            }
        }

        for (const TreatmentRecord& r : treatmentHistory) {

            if (r.patientID == searchID) {

                cout << "\nPatient Found!\n";
                cout << "Name: " << r.patientName << endl;
                cout << "Doctor: " << r.doctorName << endl;
                cout << "Status: Treatment Completed\n";
                return;
            }
        }

        cout << "\nPatient Not Found!\n";
    }

    void addDoctor() {

        cout << "\n========== ADD NEW DOCTOR ==========\n";

        Doctor d;

        d.id = nextDoctorID++;
        d.name = readString("Enter Doctor Name: ");
        d.isAvailable = true;

        doctors.push_back(d);

        cout << "\nDoctor Added Successfully!\n";
        cout << "Doctor ID: " << d.id << endl;
        cout << "Doctor Name: " << d.name << endl;
        cout << "Status: Available\n";
    }

    void displayDoctors() {

        cout << "\n========== DOCTORS LIST ==========\n";

        if (doctors.empty()) {
            cout << "No Doctors Registered.\n";
            return;
        }

        for (const Doctor& d : doctors) {

            cout << "\nDoctor ID: " << d.id;
            cout << "\nName: " << d.name;

            if (d.isAvailable) {
                cout << "\nStatus: Available\n";
            }
            else {
                cout << "\nStatus: Busy";

                cout << "\nCurrent Patient: "
                     << d.currentPatient.name;

                cout << "\nPatient ID: "
                     << d.currentPatient.id << endl;
            }

            cout << string(35, '-') << endl;
        }
    }

    void assignDoctor() {

        cout << "\n========== DOCTOR ASSIGNMENT ==========\n";

        if (waitingQueue.empty()) {
            cout << "No Patients Waiting!\n";
            return;
        }

        int doctorIndex = findAvailableDoctor();

        if (doctorIndex == -1) {
            cout << "No Available Doctors!\n";
            return;
        }

        Patient p = waitingQueue.top();
        waitingQueue.pop();

        doctors[doctorIndex].isAvailable = false;
        doctors[doctorIndex].currentPatient = p;
        doctors[doctorIndex].treatmentStartTime = time(nullptr);

        cout << "\nDoctor Assigned Successfully!\n";

        cout << "Patient: " << p.name << endl;
        cout << "Patient ID: " << p.id << endl;

        cout << "Severity: "
             << getSeverityName(p.severityCode) << endl;

        cout << "Doctor: "
             << doctors[doctorIndex].name << endl;

        cout << "Doctor ID: "
             << doctors[doctorIndex].id << endl;

        cout << "Treatment Start Time: "
             << formatTime(doctors[doctorIndex].treatmentStartTime)
             << endl;

        cout << "Status: Under Treatment\n";
    }

    void displayTreatmentPatients() {

        cout << "\n========== PATIENTS UNDER TREATMENT ==========\n";

        bool found = false;

        for (const Doctor& d : doctors) {

            if (!d.isAvailable) {

                found = true;

                cout << "\nDoctor: " << d.name;
                cout << "\nDoctor ID: " << d.id;

                cout << "\nPatient: "
                     << d.currentPatient.name;

                cout << "\nPatient ID: "
                     << d.currentPatient.id;

                cout << "\nSeverity: "
                     << getSeverityName(
                            d.currentPatient.severityCode
                        );

                cout << "\nTreatment Start: "
                     << formatTime(d.treatmentStartTime);

                cout << "\nStatus: Under Treatment\n";

                cout << string(40, '-') << endl;
            }
        }

        if (!found) {
            cout << "No Patients Under Treatment.\n";
        }
    }

    void completeTreatment() {

        cout << "\n========== COMPLETE TREATMENT ==========\n";

        bool found = false;

        for (const Doctor& d : doctors) {

            if (!d.isAvailable) {

                found = true;

                cout << "\nDoctor ID: " << d.id;
                cout << "\nDoctor: " << d.name;

                cout << "\nPatient: "
                     << d.currentPatient.name << endl;
            }
        }

        if (!found) {
            cout << "\nNo Doctors Are Currently Busy!\n";
            return;
        }

        int doctorID =
            readInteger("Enter Doctor ID: ", 1,
                        numeric_limits<int>::max());

        for (Doctor& d : doctors) {

            if (d.id == doctorID && !d.isAvailable) {

                Patient p = d.currentPatient;

                time_t endTime = time(nullptr);

                TreatmentRecord record;

                record.patientID = p.id;
                record.patientName = p.name;
                record.patientAge = p.age;
                record.severityCode = p.severityCode;

                record.doctorID = d.id;
                record.doctorName = d.name;

                record.arrivalTime = p.arrivalTime;

                record.treatmentStartTime =
                    d.treatmentStartTime;

                record.treatmentEndTime = endTime;

                record.waitingTime =
                    difftime(d.treatmentStartTime,
                             p.arrivalTime);

                record.treatmentDuration =
                    difftime(endTime,
                             d.treatmentStartTime);

                treatmentHistory.push_back(record);

                d.isAvailable = true;
                d.treatmentStartTime = 0;

                cout << "\nTreatment Completed Successfully!\n";

                cout << "Patient: " << p.name << endl;
                cout << "Doctor: " << d.name << endl;

                cout << "Waiting Time: "
                     << record.waitingTime << " seconds\n";

                cout << "Treatment Duration: "
                     << record.treatmentDuration << " seconds\n";

                cout << "Doctor Status: Available\n";

                return;
            }
        }

        cout << "\nDoctor Not Found or Doctor Is Not Busy!\n";
    }

    void displayTreatmentHistory() {

        cout << "\n========== TREATMENT HISTORY ==========\n";

        if (treatmentHistory.empty()) {
            cout << "No Completed Treatments Yet.\n";
            return;
        }

        for (const TreatmentRecord& r : treatmentHistory) {

            cout << "\nPatient ID: " << r.patientID;
            cout << "\nPatient Name: " << r.patientName;
            cout << "\nPatient Age: " << r.patientAge;

            cout << "\nSeverity: "
                 << getSeverityName(r.severityCode);

            cout << "\nDoctor ID: " << r.doctorID;
            cout << "\nDoctor Name: " << r.doctorName;

            cout << "\nArrival Time: "
                 << formatTime(r.arrivalTime);

            cout << "\nTreatment Start: "
                 << formatTime(r.treatmentStartTime);

            cout << "\nTreatment End: "
                 << formatTime(r.treatmentEndTime);

            cout << "\nWaiting Time: "
                 << fixed << setprecision(2)
                 << r.waitingTime << " seconds";

            cout << "\nTreatment Duration: "
                 << r.treatmentDuration << " seconds\n";

            cout << string(45, '-') << endl;
        }
    }

    void displayWaitingRoomStatistics() {

        cout << "\n========== WAITING ROOM STATISTICS ==========\n";

        if (waitingQueue.empty()) {

            cout << "\nWaiting Room Is Empty.\n";
            cout << "Total Waiting Patients: 0\n";
            return;
        }

        auto tempQueue = waitingQueue;

        int severityCounts[6] = {0};

        int totalWaiting = waitingQueue.size();

        double totalWaitingTime = 0;

        double longestWaitingTime = 0;

        double shortestWaitingTime =
            numeric_limits<double>::max();

        time_t currentTime = time(nullptr);

        cout << "\nTotal Patients Waiting: "
             << totalWaiting << endl;

        while (!tempQueue.empty()) {

            Patient p = tempQueue.top();

            double waitingTime =
                difftime(currentTime, p.arrivalTime);

            severityCounts[p.severityCode]++;

            totalWaitingTime += waitingTime;

            if (waitingTime > longestWaitingTime) {
                longestWaitingTime = waitingTime;
            }

            if (waitingTime < shortestWaitingTime) {
                shortestWaitingTime = waitingTime;
            }

            tempQueue.pop();
        }

        cout << "\n========== SEVERITY DISTRIBUTION ==========\n";

        for (int i = 1; i <= 5; i++) {

            cout << "Severity " << i
                 << " (" << getSeverityName(i) << "): "
                 << severityCounts[i]
                 << " patients\n";
        }

        cout << "\n========== WAITING TIME STATISTICS ==========\n";

        cout << fixed << setprecision(2);

        cout << "Average Waiting Time: "
             << totalWaitingTime / totalWaiting
             << " seconds\n";

        cout << "Longest Waiting Time: "
             << longestWaitingTime
             << " seconds\n";

        cout << "Shortest Waiting Time: "
             << shortestWaitingTime
             << " seconds\n";

        cout << "\n========== PRIORITY INFORMATION ==========\n";

        cout << "Highest Priority Patient: "
             << waitingQueue.top().name << endl;

        cout << "Patient ID: "
             << waitingQueue.top().id << endl;

        cout << "Severity: "
             << getSeverityName(
                    waitingQueue.top().severityCode
                ) << endl;

        cout << "\n============================================\n";
    }

    void displayStatistics() {

        cout << "\n========== HOSPITAL STATISTICS ==========\n";

        int waitingCount = waitingQueue.size();

        int treatmentCount = 0;

        int availableDoctors = 0;

        int busyDoctors = 0;

        double totalWaitingTime = 0;

        double totalTreatmentDuration = 0;

        for (const Doctor& d : doctors) {

            if (d.isAvailable) {
                availableDoctors++;
            }
            else {
                busyDoctors++;
                treatmentCount++;
            }
        }

        for (const TreatmentRecord& r : treatmentHistory) {

            totalWaitingTime += r.waitingTime;

            totalTreatmentDuration += r.treatmentDuration;
        }

        int completedCount = treatmentHistory.size();

        cout << "\nTotal Registered Patients: "
             << totalRegisteredPatients << endl;

        cout << "Waiting Patients: "
             << waitingCount << endl;

        cout << "Patients Under Treatment: "
             << treatmentCount << endl;

        cout << "Completed Treatments: "
             << completedCount << endl;

        cout << "\nTotal Doctors: "
             << doctors.size() << endl;

        cout << "Available Doctors: "
             << availableDoctors << endl;

        cout << "Busy Doctors: "
             << busyDoctors << endl;

        cout << fixed << setprecision(2);

        cout << "\nAverage Waiting Time (Completed Patients): ";

        if (completedCount > 0) {

            cout << totalWaitingTime / completedCount
                 << " seconds\n";
        }
        else {
            cout << "No completed treatment records.\n";
        }

        cout << "Average Treatment Duration: ";

        if (completedCount > 0) {

            cout << totalTreatmentDuration / completedCount
                 << " seconds\n";
        }
        else {
            cout << "No completed treatment records.\n";
        }

        cout << "\n========================================\n";
    }

    void run() {

        int choice;

        do {

            cout << "\n\n";
            cout << "============================================\n";
            cout << "      HOSPITAL TRIAGE MANAGEMENT SYSTEM\n";
            cout << "============================================\n";

            cout << "1. Add New Patient\n";
            cout << "2. Display Waiting Patients\n";
            cout << "3. Search Patient\n";
            cout << "4. Add Doctor\n";
            cout << "5. Display Doctors\n";
            cout << "6. Assign Doctor To Patient\n";
            cout << "7. Display Patients Under Treatment\n";
            cout << "8. Complete Treatment\n";
            cout << "9. Display Treatment History\n";
            cout << "10. Waiting Room Statistics\n";
            cout << "11. Hospital Statistics\n";
            cout << "0. Exit\n";

            cout << "============================================\n";

            choice = readInteger("Enter Your Choice: ", 0, 11);

            switch (choice) {

                case 1:
                    addPatient();
                    break;

                case 2:
                    displayWaitingPatients();
                    break;

                case 3:
                    searchPatient();
                    break;

                case 4:
                    addDoctor();
                    break;

                case 5:
                    displayDoctors();
                    break;

                case 6:
                    assignDoctor();
                    break;

                case 7:
                    displayTreatmentPatients();
                    break;

                case 8:
                    completeTreatment();
                    break;

                case 9:
                    displayTreatmentHistory();
                    break;

                case 10:
                    displayWaitingRoomStatistics();
                    break;

                case 11:
                    displayStatistics();
                    break;

                case 0:
                    cout << "\nThank You For Using Hospital System!\n";
                    break;
            }

        } while (choice != 0);
    }
};

int main() {

    HospitalSystem hospital;

    hospital.run();

    return 0;
}
