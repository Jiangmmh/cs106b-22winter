#include <iostream>
#include <string>
#include "console.h"
#include "testing/SimpleTest.h"
using namespace std;

const int DAT_AMOUNT = 3;
const int  YA_AMOUNT = 8;

string generateLyrics(int daAmount);


int main()
{
    if (runSimpleTests(SELECTED_TESTS)) {
        return 0;
    }

    cout << "All done, exiting" << endl;
    return 0;
}


string generateLyrics(int daAmount)
{
    string lyrics = "";
    for (int i = 1; i <= daAmount; i++) {
        if (i % DAT_AMOUNT == 0) {
            lyrics += "Dat ";
        } else if (i % YA_AMOUNT == 0) {
            lyrics += "Ya Da ";
        } else {
            lyrics += "Da ";
        }
    }
    return lyrics;
}



/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("Basic short lyric generation") {
    EXPECT_EQUAL(generateLyrics(1), "Da ");
    EXPECT_EQUAL(generateLyrics(2), "Da Da ");
}

STUDENT_TEST("test additional cases not covered by the provided tests") {
    EXPECT_EQUAL(generateLyrics(3), "Da Da Dat "); // test "Dat" syllable
    EXPECT_EQUAL(generateLyrics(8), "Da Da Dat Da Da Dat Da Ya Da "); // test "Ya Da" syllable
    EXPECT_EQUAL(generateLyrics(0), ""); // special case: no generation
    EXPECT_EQUAL(generateLyrics(-10), ""); // special case: make sure it doesn't crash
}
