#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX_STUDENTS = 50;
const int SUBJECTS = 3;
const int PASS_MARKS = 40;
const string SUBJECT_NAME[SUBJECTS] = {"Maths", "DS", "DELD"};

int rollNo[MAX_STUDENTS];
string studentName[MAX_STUDENTS];
int marks[MAX_STUDENTS][SUBJECTS];
int totalMarks[MAX_STUDENTS];
int countStudents = 0;

int linearSearch(int key) {
    for (int i = 0; i < countStudents; i++)
        if (rollNo[i] == key) return i;
    return -1;
}

bool isPass(int i) {
    for (int s = 0; s < SUBJECTS; s++)
        if (marks[i][s] < PASS_MARKS) return false;
    return true;
}

bool addStudent(int roll, const string& name, int m1, int m2, int m3) {
    if (countStudents == MAX_STUDENTS || roll <= 0 || linearSearch(roll) != -1) return false;
    if (m1 < 0 || m1 > 100 || m2 < 0 || m2 > 100 || m3 < 0 || m3 > 100) return false;
    rollNo[countStudents] = roll;
    studentName[countStudents] = name;
    marks[countStudents][0] = m1;
    marks[countStudents][1] = m2;
    marks[countStudents][2] = m3;
    totalMarks[countStudents] = m1 + m2 + m3;
    countStudents++;
    return true;
}

void displayAll() {
    if (!countStudents) { cout << "No records to display.\n"; return; }
    cout << left << setw(8) << "Roll" << setw(18) << "Name";
    for (int s = 0; s < SUBJECTS; s++) cout << setw(8) << SUBJECT_NAME[s];
    cout << setw(10) << "Total" << "Result\n";
    for (int i = 0; i < countStudents; i++) {
        cout << left << setw(8) << rollNo[i] << setw(18) << studentName[i];
        for (int s = 0; s < SUBJECTS; s++) cout << setw(8) << marks[i][s];
        cout << setw(10) << totalMarks[i] << (isPass(i) ? "PASS" : "FAIL") << '\n';
    }
}

void searchStudent() {
    int key;
    cout << "Enter roll number: ";
    if (!(cin >> key)) return;
    int i = linearSearch(key);
    if (i == -1) { cout << "Student not found.\n"; return; }
    cout << "Name: " << studentName[i] << "\nRoll: " << rollNo[i] << '\n';
    for (int s = 0; s < SUBJECTS; s++)
        cout << SUBJECT_NAME[s] << ": " << marks[i][s] << '\n';
    cout << "Total: " << totalMarks[i] << "/300 (" << fixed << setprecision(2)
         << totalMarks[i] / 3.0 << "%)\nResult: " << (isPass(i) ? "PASS" : "FAIL") << '\n';
}

void analyzeMarks() {
    if (!countStudents) { cout << "No records to analyze.\n"; return; }
    int high = 0, low = 0, passedCount = 0, sum = 0, subjectSum[SUBJECTS] = {};
    for (int i = 0; i < countStudents; i++) {
        sum += totalMarks[i];
        if (totalMarks[i] > totalMarks[high]) high = i;
        if (totalMarks[i] < totalMarks[low]) low = i;
        if (isPass(i)) passedCount++;
        for (int s = 0; s < SUBJECTS; s++) subjectSum[s] += marks[i][s];
    }
    cout << fixed << setprecision(2);
    cout << "Students: " << countStudents << "\nAverage per subject: "
         << sum / double(countStudents * SUBJECTS) << '\n';
    cout << "Highest: " << studentName[high] << " (" << totalMarks[high] << ")\n";
    cout << "Lowest: " << studentName[low] << " (" << totalMarks[low] << ")\n";
    cout << "Passed: " << passedCount << ", Failed: " << countStudents-passedCount << '\n';
    cout << "Pass percentage: " << passedCount*100.0/countStudents << "%\n";
    for (int s = 0; s < SUBJECTS; s++)
        cout << SUBJECT_NAME[s] << " average: " << subjectSum[s]/double(countStudents) << '\n';
}

int main() {
    addStudent(101, "Aarav", 78, 85, 72);
    addStudent(102, "Isha", 92, 88, 95);
    addStudent(103, "Rohan", 35, 48, 52);
    addStudent(104, "Meera", 66, 59, 71);
    addStudent(105, "Kabir", 45, 38, 60);

    int choice;
    do {
        cout << "\n===== Student Marks Analysis System =====\n"
             << "1. Add student\n2. Search by roll number\n3. Display all\n4. Analyze marks\n5. Exit\nChoice: ";
        if (!(cin >> choice)) break;
        if (choice == 1) {
            int r, a, b, c; string n;
            cout << "Roll number: "; cin >> r;
            cout << "Name (single word): "; cin >> n;
            cout << "Maths, DS, DELD marks: "; cin >> a >> b >> c;
            cout << (addStudent(r,n,a,b,c) ? "Student added.\n" : "Invalid marks, duplicate roll, or array full.\n");
        } else if (choice == 2) searchStudent();
        else if (choice == 3) displayAll();
        else if (choice == 4) analyzeMarks();
        else if (choice != 5) cout << "Invalid choice.\n";
    } while (choice != 5);
    cout << "Thank you!\n";
    return 0;
}
