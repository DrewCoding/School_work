#include <iostream>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <cstdlib>

using namespace std;

// Maximum value in the array
const int MAXNUM = 1000;

// Utility function prototypes
void fillRandom(int *, int);
void tableRow(int, double, double);
double calculateExpected(double, double, int, const string);

// bigOtests.cpp - COMSC-210
//
// This program uses the STL timers to time a section of code, while
// increasing the size of the input each time through a loop.
// 
// Instructions:
//
// 1) Set the value of the test parameters START_ARRAY_SIZE and BIG_O_GUESS.
//
//      - START_ARRAY_SIZE is the initial size of the integer array.  Adjust it 
//        to a higher number if the tests run too fast or there is too much error,
//        or a lower number if things run too slowly.
//
//      - BIG_O_GUESS is your "guess" of the big-O time complexity of the
//        code being timed.  This affects the "expected value" in the output.
//        It is a string type.  Example values:  "O(n)", "O(n log n)", etc.
//
// 2) Insert your code to be timed in the section marked 'TIMED SECTION'.  The
//    code should do something with testArray.  The size of testArray (arraySize)
//    will be doubled each time through the loop.  This is the 'n' of your code.
//
// 3) Run the program and observe the timings.  Adjust parameters as needed.
//
int main() {

    // ----------------------------------------------
    // Test parameters:  your customizations go here
    // ----------------------------------------------
  
    const int START_ARRAY_SIZE = 5000;        // The starting size of testArray
    const string BIG_O_GUESS = "O(n squared)";          // Your guess at the big-O of the timed code

    // ----------------------------------------------
    // Fixed parameters:  don't change these
    // ----------------------------------------------
    const int N_RUNS = 4;                               // How many loop iterations

    // ----------------------------------------------
    // Other variables
    // ----------------------------------------------
    int *testArray = 0;
    int arraySize = START_ARRAY_SIZE;
    double baseline = 0;
    double expected = 0;

    cout << fixed << setprecision(4) << left;
    srand(time(0));                                     // Seed the random number generator
    
    // Output the header
    tableRow(-1, 0, 0);

    // ----------------------------------------------
    // Test loop
    // ----------------------------------------------
    for (int cycle = 0; cycle < N_RUNS; cycle++) {
        testArray = new int[arraySize];
        fillRandom(testArray, arraySize);

        auto start = chrono::high_resolution_clock::now();

        // TIMED SECTION START
       
        bool didSwap;
        for(int i = 0; i < arraySize - 1; i++)
        {
            didSwap = false; // swap is false by default

            for(int j = 0; j < arraySize - 1; j++)
            {
                if(testArray[j] > testArray[j+1])       // If first val is bigger than second val
                {
                    int tempVal = testArray[j];         // Put first val into temp val
                    testArray[j] = testArray[j + 1];    // Put second val into first val
                    testArray[j + 1] = tempVal;         // Put temp val (first val) into second val
                    didSwap = true;                     // A swap did happen
                }
            }

            if(!didSwap) // If swap did not happen
            {
                break;  // End sort loop
            }
        }

        // TIMED SECTION END

        auto end = chrono::high_resolution_clock::now();
        double elapsed = chrono::duration<double>(end - start).count();

        // OPTIONAL:  Verify the array is sorted
        
        for (int i = 0; i < arraySize - 1; i++) {
        if (testArray[i] > testArray[i + 1]) {
            cout << "Invalid sort, error index: " << i << endl;
            return -1;
        }
    }

        // Save the timing of the first run as a baseline value
        if (cycle == 0)
            baseline = elapsed;

        // Calculate the expected time from the baseline
        expected = calculateExpected(arraySize, baseline, cycle, BIG_O_GUESS);

        tableRow(arraySize, elapsed, expected);

        delete [] testArray;
        testArray = 0;
        arraySize *= 2;
    }
    return 0;
}

// ----------------------------------------
// Utility Functions
// No need to modify code below this point.
// ----------------------------------------

//
// Fills the array 'array' of length 'len'
// with random integers in the range 0 ... MAXNUM - 1.
//
void fillRandom(int array[], int len) {
    for (int i = 0; i < len; i++) {
        array[i] = rand() % MAXNUM;
    }
}

//
// Outputs a table row for timings.  If 'asize' is -1,
// only the table header is printed.
//
void tableRow(int asize, double elapsed, double expected) {
    const int cw = 16;  // Column width for all columns
    double diff = 0, pct = 0;
    stringstream ss;

    // Print the header
    if (asize == -1) {
        cout << endl;
        cout << setw(cw * 4) << setfill('-') << "" << endl;
        cout << setfill(' ');
        cout << setw(cw)
             << "Array size"
             << setw(cw)
             << "Elapsed (s)"
             << setw(cw)
             << "Expected (s)"
             << setw(cw)
             << "Difference" << endl;

        cout << setw(cw * 4) << setfill('-') << "" << endl;
        cout << setfill(' ');
        return;
    }

    // Print a row of data
    diff = abs(expected - elapsed);
    pct = (diff / expected) * 100;
    ss << fixed;
    ss << setprecision(4) << diff;
    ss << setprecision(2) <<  " (" << pct << "%)";
    cout << setw(cw)
         << asize
         << setw(cw)
         << elapsed
         << setw(cw)
         << expected
         << ss.str()
         << endl;
}

//
// Returns the expected timing according to the big-O guess (guess),
// given the baseline time (baseline), iteration (cycle) and array size (arraySize).
//
double calculateExpected(double arraySize, double baseline, int cycle, const string guess) {
    // Each time through the loop, the input size is doubled
    double factor = pow(2, cycle);

    // First run case, expected and baseline are the same
    if (cycle == 0)
        return (baseline);

    if (guess == "O(n)")
        return (factor * baseline);

    if (guess == "O(n log n)") 
        return (factor * log(double(arraySize)) / log(arraySize / factor) * baseline);

    if (guess == "O(n squared)")
        return (factor * factor * baseline);

    // Unknown case -- if we get here, check the value of BIG_O_GUESS above. 
    cout << "WARNING:  calculateExpected() with unkown big-O value: " << guess << endl;
    return 0;
}
