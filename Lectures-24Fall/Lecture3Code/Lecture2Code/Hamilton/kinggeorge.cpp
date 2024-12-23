
/*******************************************************************
kinggeorge.cpp
Cynthia Bailey
25-09-2024
A program to generate lyrics like those from Hamilton. Lyrics, for
reference:

"You'll Be Back"
(from "Hamilton: An American Musical" soundtrack)

...[Verse 1]...
And when push comes to shove
I will send a fully armed battalion to remind you of my love!

Da da da dat da dat da da da da ya da
Da da dat dat da ya da!
Da da da dat da dat da da da da ya da
Da da dat dat da…

...[Verse 2]...

Da da da dat da dat da da da da ya da
Da da dat dat da ya da!
Da da da dat da dat da da da da ya da
Da da dat—
Everybody!

[Full Ensemble:]
Da da da dat da dat da da da da ya da
Da da dat dat da ya da!
Da da da dat da dat da da da da ya da da da da
Dat dat da ya da!
*******************************************************************/
#include <iostream>
#include <string>
#include "console.h"
#include "testing/SimpleTest.h"
using namespace std;

string generateLyrics(int daAmount);

const int DAT_FREQ = 3;
const int YA_FREQ  = 8;

int main()
{
    if (runSimpleTests(SELECTED_TESTS)) {
        return 0;
    }
    cout << "all done, exiting" << endl;
    return 0;
}

/* Function: generateLyrics()
 *
 * Generates lyrics in the style of Hamilton's King Geroge.
 * Takes an integer length of lyrics to generate (number of
 * syllables). Returns a string containing the lyrics.
 *
 * Parameter daAmount should be non-negative.
 */
string generateLyrics(int daAmount)
{
    string lyrics = "";
    // start with 1 so we get "Da" first, not "Dat"
    for (int i = 1; i <= daAmount; i++) {
        if (i % DAT_FREQ == 0) {
            lyrics += "Dat ";
        } else if (i % YA_FREQ == 0) {
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

STUDENT_TEST("generates Dat syllable on 3rd time") {
    EXPECT_EQUAL(generateLyrics(3), "Da Da Dat "); // test "Dat" syllable
}

STUDENT_TEST("generates Ya Da syllable on 8th time") {
    EXPECT_EQUAL(generateLyrics(8), "Da Da Dat Da Da Dat Da Ya Da "); // test "Ya Da" syllable
}

STUDENT_TEST("special case: no generation") {
    EXPECT_EQUAL(generateLyrics(0), ""); // special case: no generation
}

/* Since non-negative input is specified in the spec (header comment), we don't
 * really need to worry what the behavior is here. But of course it's good in
 * general not to crash under any circumstances.
 */
STUDENT_TEST("special case: make sure it doesn't crash") {
    EXPECT_EQUAL(generateLyrics(-10), ""); // special case: make sure it doesn't crash
}

