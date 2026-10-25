# CGPA Analyser 🎓

*Because "I think I'm doing okay" is not a grade point.*

Your exam rules PDF is 7 pages long and has a formula that looks like it lost a fight with a PDF reader. This project reads it so you don't have to, and then does the math: marks to grade, grades to SGPA, SGPA to CGPA, CGPA to class and percentage.

Built on the **Amrutvahini College of Engineering, Sangamner** (Autonomous) Examination Rules and Regulations.

## What it does

- **Marks to grade:** Enter CCE-I, CCE-II, CCE-III and ESE marks. It tells you the total, the letter grade, and whether you passed. It also tells you how many ESE marks you need for each grade, handy for the night before the exam.
- **SGPA calculator:** Credits and letter grades in, SGPA out.
- **CGPA calculator:** Semester credits and SGPAs in. Out come your CGPA, your class (First Class with Distinction, and so on) and your percentage.
- **"What if" mode:** Type a target CGPA and the next semester's credits. It tells you the SGPA you need. If the answer is 15.58, it will say so, and you can stop dreaming.

## The rules it follows

| Rule | What the code does |
|---|---|
| CCE = CCE-I ÷ 2 + CCE-II ÷ 2 + CCE-III | Gives 40 marks. ESE adds 60 for a total out of 100 |
| Pass needs total ≥ 40 **and** ESE ≥ 24 | A great CCE can't rescue a failed ESE. Sorry |
| Grades: O (90+), A+, A, B+, B, C, P (40+), F | Grade points from 10 down to 0 |
| SGPA = Σ(credits × grade point) ÷ Σ credits | Rounded to two decimals |
| CGPA = Σ(credits × SGPA) ÷ Σ credits | Same recipe, bigger pot |
| Class: 7.75+ Distinction, 6.75+ First, 6.25+ Higher Second, 5.5+ Second | Below 5.5 the rules go quiet, and so does the tool |

## Files

| File | What it is |
|---|---|
| `cgpa_analyser.cpp` | Console version. For when you want to feel like a hacker |
| `cgpa_analyser.html` | Browser version. Open it, no install needed, works on your phone |

## Running it

**C++** (needs g++):

```
g++ cgpa_analyser.cpp -o cgpa
./cgpa            # Windows: cgpa.exe
```

**Web:** Double-click `cgpa_analyser.html`. That's the whole setup guide.

## Sanity check

The sample in the rules PDF: six semesters, 144 credits.

| Semester | Credits | SGPA |
|---|---|---|
| I | 20 | 8.45 |
| II | 22 | 7.8 |
| III | 25 | 5.6 |
| IV | 26 | 6.0 |
| V | 26 | 6.3 |
| VI | 25 | 8.0 |

The tool says **CGPA 6.95, First Class, 62.00%**. The PDF prints 6.94. The exact value is 6.947, and the rules say to round off, so 6.95 it is. If your department insists on 6.94, take it up with the department, not the compiler.

## Fine print

- The percentage uses SPPU's slab formulas. The PDF's version of them is garbled, so treat the percentage as a very good estimate, not a legal document.
- Marks to grade covers 3/4 credit courses (CCE 40 + ESE 60). Courses with 50 marks follow their own BOS scheme and aren't included.
- This is a student project. Your official grade card is the only thing the university will believe.

## Team

Gayatri Giri (137), Sneha Gade (126), Samyak Gawale (133), Siddhi Dolas (121)

Sub Teacher: Prof. N. P. Kurhade

*May your SGPA be high and your backlogs be none.*
