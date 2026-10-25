// CGPA Analyser (console version)
// Based on AVCOE Sangamner (Autonomous) Examination Rules and Regulations
// Features: marks to grade, SGPA calculator, CGPA calculator with class and percentage

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
using namespace std;

const int MAX = 10;

struct GradeRow { const char *letter; int point; int minMarks; const char *desc; };
const GradeRow GRADES[] = {
    {"O", 10, 90, "Outstanding"}, {"A+", 9, 80, "Excellent"}, {"A", 8, 70, "Very Good"},
    {"B+", 7, 60, "Good"},       {"B", 6, 50, "Above Average"}, {"C", 5, 45, "Average"},
    {"P", 4, 40, "Pass"}
};
const int GRADE_COUNT = 7;

double round2(double x) { return floor(x * 100 + 0.5) / 100; }

// Grade point from a letter grade, -1 if invalid
int gradePoint(string g) {
    for (char &c : g) c = toupper(c);
    if (g == "F") return 0;
    for (int i = 0; i < GRADE_COUNT; i++)
        if (g == GRADES[i].letter) return GRADES[i].point;
    return -1;
}

// 1. Marks -> grade (3/4 credit course: CCE 40 + ESE 60)
void marksToGrade() {
    double ct1, ct2, c3, ese;
    cout << "CCE-I class test (out of 32): ";  cin >> ct1;
    cout << "CCE-II class test (out of 32): "; cin >> ct2;
    cout << "CCE-III (out of 8): ";            cin >> c3;
    cout << "ESE (out of 60): ";               cin >> ese;
    double cce = ct1 / 2 + ct2 / 2 + c3;
    double total = cce + ese;
    cout << fixed << setprecision(2) << "\nCCE " << cce << "/40, ESE " << ese
         << "/60, Total " << total << "/100\n";
    if (ese < 24) { cout << "Grade F (Fail): ESE is below 40% (24/60)\n"; return; }
    for (int i = 0; i < GRADE_COUNT; i++)
        if (total >= GRADES[i].minMarks) {
            cout << "Grade " << GRADES[i].letter << " (" << GRADES[i].desc << "), "
                 << GRADES[i].point << " grade points\n";
            return;
        }
    cout << "Grade F (Fail): total is below 40\n";
}

// 2. SGPA = sum(credit * grade point) / sum(credit)
void sgpaCalc() {
    int n;
    cout << "Number of courses (max " << MAX * 2 << "): "; cin >> n;
    if (n < 1 || n > MAX * 2) { cout << "Invalid number.\n"; return; }
    double credits[MAX * 2], sumC = 0, sumP = 0;
    for (int i = 0; i < n; i++) {
        string g; int gp;
        cout << "Course " << i + 1 << " credits: "; cin >> credits[i];
        do { cout << "Course " << i + 1 << " grade (O, A+, A, B+, B, C, P, F): "; cin >> g; gp = gradePoint(g); }
        while (gp < 0);
        sumC += credits[i];
        sumP += credits[i] * gp;
    }
    cout << fixed << setprecision(2) << "\nTotal credits: " << sumC
         << "\nSGPA: " << round2(sumP / sumC) << "\n";
}

// Class awarded from CGPA
string classOf(double c) {
    if (c >= 7.75) return "First Class with Distinction";
    if (c >= 6.75) return "First Class";
    if (c >= 6.25) return "Higher Second Class";
    if (c >= 5.5)  return "Second Class";
    return "Below 5.5 (class not listed in the rules)";
}

// Percentage from CGPA (SPPU slabs)
double percentOf(double c) {
    if (c >= 9.5)  return 20 * c - 100;
    if (c >= 8.25) return 12 * c - 25;
    if (c >= 6.75) return 10 * c - 7.5;
    if (c >= 5.75) return 5 * c + 26.25;
    if (c >= 4.75) return 10 * c - 2.5;
    if (c >= 4.0)  return 6.6 * c + 13.6;
    return -1;
}

// 3. CGPA = sum(credit * SGPA) / sum(credit)
void cgpaCalc() {
    int n;
    cout << "Number of semesters (max 8): "; cin >> n;
    if (n < 1 || n > 8) { cout << "Invalid number.\n"; return; }
    double credit[8], sgpa[8], sumC = 0, sumP = 0;
    for (int i = 0; i < n; i++) {
        cout << "Semester " << i + 1 << " credits: "; cin >> credit[i];
        cout << "Semester " << i + 1 << " SGPA: ";    cin >> sgpa[i];
        sumC += credit[i];
        sumP += credit[i] * sgpa[i];
    }
    double cgpa = round2(sumP / sumC);
    double p = percentOf(cgpa);
    cout << fixed << setprecision(2) << "\nTotal credits: " << sumC << "\nCGPA: " << cgpa
         << "\nClass: " << classOf(cgpa) << "\n";
    if (p >= 0) cout << "Percentage: " << p << "%\n";
    else        cout << "Percentage: not defined below CGPA 4.00\n";

    double target, nextC;
    cout << "\nTarget CGPA (0 to skip): "; cin >> target;
    if (target > 0) {
        cout << "Next semester credits: "; cin >> nextC;
        double need = (target * (sumC + nextC) - sumP) / nextC;
        if (need > 10)      cout << "Not achievable: would need SGPA " << need << "\n";
        else if (need <= 0) cout << "Target already secured.\n";
        else                cout << "You need an SGPA of at least " << need << " next semester.\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\n===== CGPA Analyser =====\n"
             << "1. Marks to grade\n2. SGPA calculator\n3. CGPA calculator\n4. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: marksToGrade(); break;
            case 2: sgpaCalc();     break;
            case 3: cgpaCalc();     break;
            case 4: cout << "Thank you!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 4 && cin);
    return 0;
}
