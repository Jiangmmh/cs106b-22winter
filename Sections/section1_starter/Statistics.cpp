/*
 * CS106B Section Handout Test Harness: Section 1
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified for Qt and Ed by Neel
 * Kishnani for Winter 2022.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include <iostream>
#include <fstream>
#include <string>
#include "testing/SimpleTest.h"
using namespace std;

struct Statistics {
    double min;     // Smallest value in the file
    double max;     // Largest value in the file
    double average; // Average value in the file
};

/*
 * Function: documentStatisticsFor
 * -------------------------------
 * Reads in a file of numbers via istream and calculates statistics on
 * it (i.e. min, max, average). Represents stats in form of struct 
 * defined above.
 */
Statistics documentStatisticsFor(istream& input) {
    double min, max, sum, val;
    int count = 1;

    input >> val;
    max = sum = min = val;
    while (input >> val) {
        if (max < val)
            max = val;
        if (min > val)
            min = val;
        sum += val;
        count++;
    }
    return {min, max, sum / count};
}

/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("Provided Test: Use sample text file to compute statistics.") {
    ifstream input;
    input.open("res/stats.txt");
    Statistics s = documentStatisticsFor(input);
    EXPECT_EQUAL(s.min, -4.2);
    EXPECT_EQUAL(s.max, 30.12);
    EXPECT_EQUAL(s.average, 5.802);
}
