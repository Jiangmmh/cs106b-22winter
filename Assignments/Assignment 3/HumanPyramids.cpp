#include "HumanPyramids.h"
#include "error.h"
#include "grid.h"
using namespace std;

// version 1
// double weightOnBackOf(int row, int col, int pyramidHeight) {

//     if (col > row || col < 0 || row < 0 || row >= pyramidHeight)
//         error("weightOnBackOf: wrong parameters");

//     // topmost guy
//     if (row == 0 && col == 0)
//         return 0.0;

//     // leftmost guy any row except for the topmost guy
//     if (col == 0)
//         return 80.0 + 0.5 * weightOnBackOf(row - 1, col, pyramidHeight);

//     // rightmost guy any row except for the topmost guy
//     if (col == row)
//         return 80.0 + 0.5 * weightOnBackOf(row - 1, col - 1, pyramidHeight);

//     // others
//     return 160.0
//            + 0.5 * weightOnBackOf(row - 1, col - 1, pyramidHeight)
//            + 0.5 * weightOnBackOf(row - 1, col, pyramidHeight);
// }


double helper(int row, int col, int pyramidHeight, Grid<double> &table) {
    // topmost guy
    if (row == 0 && col == 0)
        return 0.0;

    if (table[row][col] > 0.0)
        return table[row][col];

    // leftmost guy any row except for the topmost guy
    if (col == 0) {
        double tmp = helper(row - 1, col, pyramidHeight, table);
        table[row][col] = tmp;
        return 80.0 + 0.5 * tmp;
    }

    // rightmost guy any row except for the topmost guy
    if (col == row) {
        double tmp = helper(row - 1, col - 1, pyramidHeight, table);
        table[row][col] = tmp;
        return 80.0 + 0.5 * tmp;
    }

    double upLeft = helper(row - 1, col - 1, pyramidHeight, table);
    double upRight = helper(row - 1, col, pyramidHeight, table);
    table[row-1][col-1] = upLeft;
    table[row-1][col] = upRight;

    // others
    return 160.0 + 0.5 * upLeft + 0.5 * upRight;
}


// version 2
double weightOnBackOf(int row, int col, int pyramidHeight) {

    if (col > row || col < 0 || row < 0 || row >= pyramidHeight)
        error("weightOnBackOf: wrong parameters");

    Grid<double> table(pyramidHeight, pyramidHeight);
    table.fill(0);
    return helper(row, col, pyramidHeight, table);
}


/* * * * * * Test Cases * * * * * */
#include "GUI/SimpleTest.h"
/* * * * * * Test cases from the starter files below this point. * * * * * */

PROVIDED_TEST("Check Person E from the handout.") {
    /* Person E is located at row 2, column 1. */
    double result = weightOnBackOf(2, 1, 5);
    EXPECT_EQUAL(result, 240);
}

PROVIDED_TEST("Function reports errors in invalid cases.") {
    EXPECT_ERROR(weightOnBackOf(-1, 0, 10));
    EXPECT_ERROR(weightOnBackOf(10, 10, 5));
    EXPECT_ERROR(weightOnBackOf(-1, 10, 20));
}

PROVIDED_TEST("Stress test: Memoization is implemented (should take under a second)") {
    /* TODO: Yes, we are asking you to make a change to this test case! Delete the
     * line immediately after this one - the one that starts with SHOW_ERROR - once
     * you have implemented memoization to test whether it works correctly.
     */
    // SHOW_ERROR("This test is configured to always fail until you delete this line from\n         HumanPyramids.cpp. Once you have implemented memoization and want\n         to check whether it works correctly, remove the indicated line.");

    /* Do not delete anything below this point. :-) */

    /* This will take a LONG time to complete if memoization isn't implemented.
     * We're talking "heat death of the universe" amounts of time. :-)
     *
     * If you did implement memoization but this test case is still hanging, make
     * sure that in your recursive function (not the wrapper) that your recursive
     * calls are to your new recursive function and not back to the wrapper. If you
     * call the wrapper again, you'll get a fresh new memoization table rather than
     * preserving the one you're building up in your recursive exploration, and the
     * effect will be as if you hadn't implemented memoization at all.
     */
    EXPECT(weightOnBackOf(100, 50, 200) >= 10000);
}

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */
