// Student Marks Analysis System
// Data Structures Mini Project - Arrays and Linear Search
// Amrutvahini College of Engineering, Sangamner | Dept. of IT | 2026-27

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX_STUDENTS = 50;
const int SUBJECTS = 3;
const int PASS_MARKS = 40;
const string SUBJECT_NAME[SUBJECTS] = {"Maths", "DS", "DELD"};

// Parallel arrays: index i holds the record of one student
int    rollNo[MAX_STUDENTS];
string name[MAX_STUDENTS];
int    marks[MAX_STUDENTS][SUBJECTS];
int    total[MAX_STUDENTS];
int    count = 0;

// Linear Search: check each element one by one, return index or -1
int linearSearch(int key) {
    for (int i = 0; i < count; i++) {
        if (rollNo[i] == key)
            return i;
    }
    return -1;
}

bool isPass(int i) {
    for (int s = 0; s < SUBJECTS; s++)
        if (marks[i][s] < PASS_MARKS)
            return false;
    return true;
}

void addStudent(int r, const string &n, int m1, int m2, int m3) {
    if (count == MAX_STUDENTS) {
        cout << "Array is full. Cannot add more students.\n";
        return;
    }
    if (linearSearch(r) != -1) {
        cout << "Roll number " << r << " already exists.\n";
        return;
    }
    rollNo[count] = r;
    name[count] = n;
    marks[count][0] = m1;
    marks[count][1] = m2;
    marks[count][2] = m3;
    total[count] = m1 + m2 + m3;
    count++;
}

void addStudentFromInput() {
    int r, m[SUBJECTS];
    string n;
    cout << "Enter roll number: ";
    cin >> r;
    cout << "Enter name (single word): ";
    cin >> n;
    for (int s = 0; s < SUBJECTS; s++) {
        do {
            cout << "Enter marks in " << SUBJECT_NAME[s] << " (0-100): ";
            cin >> m[s];
        } while (m[s] < 0 || m[s] > 100);
    }
    int before = count;
    addStudent(r, n, m[0], m[1], m[2]);
    if (count > before)
        cout << "Student added successfully.\n";
}

void searchStudent() {
    int key;
    cout << "Enter roll number to search: ";
    cin >> key;
    int i = linearSearch(key);
    if (i == -1) {
        cout << "Student not found.\n";
        return;
    }
    cout << "\nRoll No : " << rollNo[i] << "\nName    : " << name[i] << "\n";
    for (int s = 0; s < SUBJECTS; s++)
        cout << left << setw(8) << SUBJECT_NAME[s] << ": " << marks[i][s] << "\n";
    cout << "Total   : " << total[i] << "/" << SUBJECTS * 100
         << "\nPercent : " << fixed << setprecision(2) << total[i] / (double)SUBJECTS << "%"
         << "\nResult  : " << (isPass(i) ? "PASS" : "FAIL") << "\n";
}

void displayAll() {
    if (count == 0) {
        cout << "No records to display.\n";
        return;
    }
    cout << "\n" << left << setw(6) << "Roll" << setw(12) << "Name";
    for (int s = 0; s < SUBJECTS; s++)
        cout << setw(7) << SUBJECT_NAME[s];
    cout << setw(7) << "Total" << "Result\n";
    cout << string(50, '-') << "\n";
    for (int i = 0; i < count; i++) {
        cout << left << setw(6) << rollNo[i] << setw(12) << name[i];
        for (int s = 0; s < SUBJECTS; s++)
            cout << setw(7) << marks[i][s];
        cout << setw(7) << total[i] << (isPass(i) ? "PASS" : "FAIL") << "\n";
    }
}

void analyzeMarks() {
    if (count == 0) {
        cout << "No records to analyze.\n";
        return;
    }
    int hi = 0, lo = 0, passed = 0, sum = 0;
    for (int i = 0; i < count; i++) {
        sum += total[i];
        if (total[i] > total[hi]) hi = i;
        if (total[i] < total[lo]) lo = i;
        if (isPass(i)) passed++;
    }
    cout << "\n--- Class Analysis ---\n";
    cout << "Total students : " << count << "\n";
    cout << "Class average  : " << fixed << setprecision(2)
         << sum / (double)(count * SUBJECTS) << " per subject\n";
    cout << "Highest total  : " << total[hi] << " (" << name[hi] << ", Roll " << rollNo[hi] << ")\n";
    cout << "Lowest total   : " << total[lo] << " (" << name[lo] << ", Roll " << rollNo[lo] << ")\n";
    cout << "Passed         : " << passed << "\n";
    cout << "Failed         : " << count - passed << "\n";
    cout << "Pass percentage: " << passed * 100.0 / count << "%\n";
    for (int s = 0; s < SUBJECTS; s++) {
        int subSum = 0;
        for (int i = 0; i < count; i++)
            subSum += marks[i][s];
        cout << SUBJECT_NAME[s] << " average" << string(8 - SUBJECT_NAME[s].size(), ' ')
             << ": " << subSum / (double)count << "\n";
    }
}

int main() {
    // Sample data so the program can be demonstrated immediately
    addStudent(101, "Aarav",  78, 85, 72);
    addStudent(102, "Isha",   92, 88, 95);
    addStudent(103, "Rohan",  35, 48, 52);
    addStudent(104, "Meera",  66, 59, 71);
    addStudent(105, "Kabir",  45, 38, 60);

    int choice;
    do {
        cout << "\n===== Student Marks Analysis System =====\n"
             << "1. Add student\n2. Search student by roll number\n"
             << "3. Display all students\n4. Analyze class marks\n5. Exit\n"
             << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addStudentFromInput(); break;
            case 2: searchStudent();       break;
            case 3: displayAll();          break;
            case 4: analyzeMarks();        break;
            case 5: cout << "Thank you!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5 && cin);
    return 0;
}
