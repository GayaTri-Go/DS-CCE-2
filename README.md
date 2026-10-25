# Student Marks Analysis System — DS CCE-II

A static HTML/CSS/JavaScript webpage paired with a C++ console program.

## Features
- Parallel arrays / fixed capacity of 50 students
- Linear search by roll number
- Maths, DS, and DELD marks out of 100
- Total out of 300 and PASS/FAIL result
- Class average, highest and lowest totals, pass percentage, and subject averages
- Sample data included in both implementations

## Run the website
Open `index.html` in a browser. For Vercel, use Framework Preset **Other**, leave Build Command and Install Command empty, and set Output Directory to `.`. Keep `index.html` in the repository root.

## Compile C++
```bash
g++ -std=c++17 main.cpp -o marks
./marks
```

The browser UI demonstrates the same core logic as the C++ program; it does not run C++ directly in the browser.
