/* File: OnlyConnect.cpp
 *
 * TODO: Edit these comments to describe anything interesting or noteworthy in your implementation.
 *
 * TODO: Edit these comments to leave a puzzle for your section leader to solve!
 */
#include "OnlyConnect.h"
#include "GUI/SimpleTest.h"
#include "strlib.h"
#include <cstring>
#include <cctype>
using namespace std;

// 判断是否是辅音字母
bool isConsonants(char ch) {
    if (!isalpha(ch))
        return false;
    ch = toupper(ch);
    if (ch == 'A' || ch == 'E' || ch == 'I'
            || ch == 'O' || ch == 'U')
        return false;
    return true;
}

// string onlyConnectize(string phrase) {
//     /* TODO: The next few lines just exist to make sure you don't get compiler warning messages
//      * when this function isn't implemented. Delete these lines, then implement this function.
//      */
//     if (phrase == "") {
//         return "";
//     }

//     // 若字符串的第一个字符为辅音字母则转换将其为大写
//     if (isConsonants(phrase[0])) {
//         return toUpperCase(charToString(phrase[0])) + onlyConnectize(phrase.substr(1, phrase.size()-1));
//     } else {
//         return onlyConnectize(phrase.substr(1, phrase.size()-1));
//     }
// }


string helper(string phrase, int index) {
    if (index == phrase.size()) {
        return "";
    }

    if (isConsonants(phrase[index])) {
        return toUpperCase(charToString(phrase[index])) + helper(phrase, index + 1);
    } else {
        return helper(phrase, index + 1);
    }
}

string onlyConnectize(string phrase) {
    if (phrase == "") {
        return "";
    }

    return helper(phrase, 0);
}



/* * * * * * Provided Test Cases * * * * * */

PROVIDED_TEST("Converts lower-case to upper-case.") {
    EXPECT_EQUAL(onlyConnectize("lowercase"), "LWRCS");
    EXPECT_EQUAL(onlyConnectize("uppercase"), "PPRCS");
}

PROVIDED_TEST("Handles non-letter characters properly.") {
    EXPECT_EQUAL(onlyConnectize("2.718281828459045"), "");
    EXPECT_EQUAL(onlyConnectize("'Hi, Mom!'"), "HMM");
}

PROVIDED_TEST("Handles single-character inputs.") {
    EXPECT_EQUAL(onlyConnectize("A"), "");
    EXPECT_EQUAL(onlyConnectize("+"), "");
    EXPECT_EQUAL(onlyConnectize("Q"), "Q");
}

/* TODO: You will need to add your own tests into this suite of test cases. Think about the sorts
 * of inputs we tested here, and, importantly, what sorts of inputs we *didn't* test here. Some
 * general rules of testing:
 *
 *    1. Try extreme cases. What are some very large cases to check? What are some very small cases?
 *
 *    2. Be diverse. There are a lot of possible inputs out there. Make sure you have tests that account
 *       for cases that aren't just variations of one another.
 *
 *    3. Be sneaky. Don't just try standard inputs. Try weird ones that you wouldn't expect anyone to
 *       actually enter, but which are still perfectly legal.
 *
 * Happy testing!
 */

STUDENT_TEST("Handles mix-character inputs.") {
    EXPECT_EQUAL(onlyConnectize("A1b2c3d4E5f6g"), "BCDFG");
    EXPECT_EQUAL(onlyConnectize("UI21,:O?AASD"), "SD");
}


