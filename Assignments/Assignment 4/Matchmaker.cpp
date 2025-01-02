#include "Matchmaker.h"
using namespace std;

// 用于判断某个节点是否有多个孤立邻居（竞争同一个伙伴，必定无法完美匹配）
bool isConflict(const Map<string, Set<string>>& possibleLinks, const string &key) {
    if (possibleLinks.size() < 2) return false;

    int singleCount = 0;
    for (auto neighbor : possibleLinks[key]) {
        if (possibleLinks[neighbor].size() == 1)
            singleCount++;

        if (singleCount > 1)
            return true;
    }

    return false;
}

bool hasPerfectMatching(const Map<string, Set<string>>& possibleLinks, Set<Pair>& matching) {
    // 所有人都匹配成功
    if (possibleLinks.isEmpty())
        return true;

    // 若总节点数为奇数，不可能存在完美匹配
    if (possibleLinks.size() % 2 != 0)
        return false;

    // 用于记录已经匹配过的人
    Set<Pair> havePaired;
    for (string key : possibleLinks.keys()) {
        // 判断孤立节点，无法完美匹配
        if (possibleLinks[key].isEmpty())
            return false;
        // 判断是否存在两个以上的孤立邻居
        if (isConflict(possibleLinks, key))
            return false;

        for (string partner : possibleLinks[key]) {
            Pair matchRev(partner, key);

            // 已经匹配过了，跳过
            if (havePaired.contains(matchRev))
                continue;

            if (!possibleLinks.containsKey(partner))
                continue;

            // 剔除已经匹配了的节点
            auto auxMap = possibleLinks;
            auxMap.remove(key);
            auxMap.remove(partner);

            // 保存匹配结果
            Pair match(key, partner);
            matching.add(match);
            havePaired.add(matchRev);

            // 记录在该对匹配的条件下是否存在完美匹配
            bool isTrue = hasPerfectMatching(auxMap, matching);
            if (isTrue) return true;
            matching.remove(match);
        }
    }
    return false;
}


// 辅助函数，用于计算选择出来的pair集合的weight之和
int weightCount(const Map<string, Map<string, int>>& links, const Set<Pair> &matched) {
    int ans = 0;
    if (!matched.isEmpty()) {
        for (auto match : matched) {
            ans += links[match.first()][match.second()];
        }
    }
    return ans;
}

// helper function
Set<Pair> maximumWeightMatchingHelper(const Map<string, Map<string, int>>& possibleLinks, const Set<Pair> &matched) {
    // 没有更多的pair
    if (possibleLinks.size() < 2) {
        return matched;
    }

    // 记录记录所有pair和weight和
    Map<Set<Pair>, int> weightPairs;

    // 1. 不考虑第一个key

    // 取出第一个key
    auto firstKey = possibleLinks.firstKey();

    // 创建副本，并将第一个key剔除
    auto aux = possibleLinks;
    aux.remove(firstKey);

    // 剔除其他人与第一个key的关系
    for (auto key : possibleLinks) {
        if (possibleLinks[key].containsKey(firstKey)) {
            aux[key].remove(firstKey);
        }
    }

    // 递归得到剔除掉第一个key之后的最大权重集合
    auto matchWithOutThis = maximumWeightMatchingHelper(aux, matched);

    // 将其加入weightPairs中
    weightPairs[matchWithOutThis] = weightCount(possibleLinks, matchWithOutThis);

    // 2. 考虑第一个key
    for (auto secondKey : possibleLinks[firstKey].keys()) {
        // 剪枝，剔除对权重和没有帮助的pair
        if (possibleLinks[firstKey][secondKey] <= 0)
            continue;

        // 考虑第一个key与所有邻居的可能性
        aux = possibleLinks;
        aux.remove(firstKey);
        aux.remove(secondKey);

        // 剔除这已匹配的两个结点与其他结点的关系
        for (auto key : aux.keys()) {
            if (aux[key].containsKey(firstKey))
                aux[key].remove(firstKey);
            if (aux[key].containsKey(secondKey))
                aux[key].remove(secondKey);
        }

        // 获取匹配集合并将其权重和加入weightPairs
        Pair newMatch = {firstKey, secondKey};
        auto matchWithThis = maximumWeightMatchingHelper(aux, matched + newMatch);
        weightPairs[matchWithThis] = weightCount(possibleLinks, matchWithThis);
    }

    // 从weightPairs中取出权重和最大的匹配集合
    Set<Pair> bestMatch = weightPairs.firstKey();
    for (auto pairs : weightPairs) {
        if (weightPairs[bestMatch] < weightPairs[pairs])
            bestMatch = pairs;
    }
    return bestMatch;
}

Set<Pair> maximumWeightMatching(const Map<string, Map<string, int>>& possibleLinks) {
    return maximumWeightMatchingHelper(possibleLinks, Set<Pair>({}));
}

/* * * * * Test Cases Below This Point * * * * */

namespace {
    /* Utility to go from a list of triples to a world. */
    struct WeightedLink {
        string from;
        string to;
        int cost;
    };
    Map<string, Map<string, int>> fromWeightedLinks(const Vector<WeightedLink>& links) {
        Map<string, Map<string, int>> result;
        for (const auto& link: links) {
            result[link.from][link.to] = link.cost;
            result[link.to][link.from] = link.cost;
        }
        return result;
    }

    /* Pairs to world. */
    Map<string, Set<string>> fromLinks(const Vector<Pair>& pairs) {
        Map<string, Set<string>> result;
        for (const auto& link: pairs) {
            result[link.first()].add(link.second());
            result[link.second()].add(link.first());
        }
        return result;
    }

    /* Checks if a set of pairs forms a perfect matching. */
    bool isPerfectMatching(const Map<string, Set<string>>& possibleLinks,
                           const Set<Pair>& matching) {
        /* Need to check that
         *
         * 1. each pair is indeed a possible link,
         * 2. each person appears in exactly one pair.
         */
        Set<string> used;
        for (Pair p: matching) {
            /* Are these folks even in the group of people? */
            if (!possibleLinks.containsKey(p.first())) return false;
            if (!possibleLinks.containsKey(p.second())) return false;

            /* If these people are in the group, are they linked? */
            if (!possibleLinks[p.first()].contains(p.second()) ||
                !possibleLinks[p.second()].contains(p.first())) {
                return false;
            }

            /* Have we seen them before? */
            if (used.contains(p.first()) || used.contains(p.second())) {
                return false;
            }

            /* Add them both. */
            used += p.first();
            used += p.second();
        }

        /* Confirm that's everyone. */
        return used.size() == possibleLinks.size();
    }
}

#include "GUI/SimpleTest.h"

PROVIDED_TEST("hasPerfectMatching works on a world with just one person.") {
    /* The world is just a single person A, with no others. How sad. :-(
     *
     *                 A
     *
     * There is no perfect matching.
     */

    Set<Pair> unused;
    EXPECT(!hasPerfectMatching({ { "A", {} } }, unused));
}

PROVIDED_TEST("hasPerfectMatching works on an empty set of people.") {
    /* There actually is a perfect matching - the set of no links meets the
     * requirements.
     */
    Set<Pair> unused;
    EXPECT(hasPerfectMatching({}, unused));
}

PROVIDED_TEST("hasPerfectMatching works on a world with two linked people.") {
    /* This world is a pair of people A and B. There should be a perfect matching.
     *
     *               A -- B
     *
     * The matching is {A, B}
     */
    auto links = fromLinks({
        { "A", "B" }
    });

    Set<Pair> unused;
    EXPECT(hasPerfectMatching(links, unused));
}

PROVIDED_TEST("hasPerfectMatching works on a world with two linked people, and produces output.") {
    /* This world is a pair of people A and B. There should be a perfect matching.
     *
     *               A -- B
     *
     * The matching is {A, B}
     */
    auto links = fromLinks({
        { "A", "B" }
    });

    Set<Pair> expected = {
        { "A", "B" }
    };

    Set<Pair> matching;
    EXPECT(hasPerfectMatching(links, matching));
    EXPECT_EQUAL(matching, expected);
}

PROVIDED_TEST("hasPerfectMatching works on a triangle of people.") {
    /* Here's the world:
     *
     *               A --- B
     *                \   /
     *                 \ /
     *                  C
     *
     * There is no perfect matching here, unfortunately.
     */
    auto links = fromLinks({
        { "A", "B" },
        { "B", "C" },
        { "C", "A" }
    });

    Set<Pair> unused;
    EXPECT(!hasPerfectMatching(links, unused));
}

PROVIDED_TEST("hasPerfectMatching works on a square of people.") {
    /* Here's the world:
     *
     *               A --- B
     *               |     |
     *               |     |
     *               D --- C
     *
     * There are two different perfect matching here: AB / CD, and AD/BD.
     * Either will work.
     */
    auto links = fromLinks({
        { "A", "B" },
        { "B", "C" },
        { "C", "D" },
        { "D", "A" }
    });

    Set<Pair> unused;
    EXPECT(hasPerfectMatching(links, unused));
}

PROVIDED_TEST("hasPerfectMatching works on a square of people, and produces output.") {
    /* Here's the world:
     *
     *               A --- B
     *               |     |
     *               |     |
     *               C --- D
     *
     * There are two different perfect matching here: AB / CD, and AC/BC.
     * Either will work.
     */
    auto links = fromLinks({
        { "A", "B" },
        { "B", "C" },
        { "C", "D" },
        { "D", "A" }
    });

    Set<Pair> matching;
    EXPECT(hasPerfectMatching(links, matching));
    EXPECT(isPerfectMatching(links, matching));
}

PROVIDED_TEST("hasPerfectMatching works on a pentagon of people.") {
    /* Here's the world:
     *
     *               A --- B
     *             /       |
     *            E        |
     *             \       |
     *               D --- C
     *
     * There is no perfect matching here, since the cycle has odd
     * length.
     */
    auto links = fromLinks({
        { "A", "B" },
        { "B", "C" },
        { "C", "D" },
        { "D", "E" },
        { "E", "A" }
    });

    Set<Pair> unused;
    bool result = hasPerfectMatching(links, unused);
    EXPECT(!result);
}

PROVIDED_TEST("hasPerfectMatching works on a line of six people.") {
    /* Because Map and Set internally store items in sorted order, the order
     * in which you iterate over people when making decisions is sensitive
     * to the order of those peoples' names. This test looks at a group like
     * this one, trying out all possible orderings of peoples' names:
     *
     *
     *
     *        * -- * -- * -- * -- * -- *
     *
     *
     *
     * There are 6! = 720 possible permutations of the ordering of these six
     * people. If your code is able to solve the problem correctly for all of
     * those orderings, there's a good chance that you're correctly tracking
     * who is matched at each step. On the other hand, if your code runs into
     * issues here, it may indicate that there's a bug in how you mark who's
     * paired and who isn't.
     */
    Vector<string> people = { "A", "B", "C", "D", "E", "F" };
    do {
        Map<string, Set<string>> links = fromLinks({
            { people[0], people[1] },
            { people[1], people[2] },
            { people[2], people[3] },
            { people[3], people[4] },
            { people[4], people[5] }
        });

        Set<Pair> matching;
        EXPECT(hasPerfectMatching(links, matching));
        EXPECT(isPerfectMatching(links, matching));
    } while (next_permutation(people.begin(), people.end()));
}

PROVIDED_TEST("hasPerfectMatching works on a more complex negative example.") {
    /* Because Map and Set internally store items in sorted order, the order
     * in which you iterate over people when making decisions is sensitive
     * to the order of those peoples' names. This test looks at a group like
     * this one, trying out all possible orderings of peoples' names:
     *
     *
     *         *        *
     *          \      /
     *           * -- *
     *          /      \
     *         *        *
     *
     * There are 6! = 720 possible permutations of the ordering of these six
     * people. If your code is able to solve the problem correctly for all of
     * those orderings, there's a good chance that you're correctly tracking
     * who is matched at each step. On the other hand, if your code runs into
     * issues here, it may indicate that there's a bug in how you mark who's
     * paired and who isn't.
     */
    Vector<string> people = { "A", "B", "C", "D", "E", "F" };
    do {
        Map<string, Set<string>> links = fromLinks({
            { people[0], people[2] },
            { people[1], people[2] },
            { people[2], people[3] },
            { people[3], people[4] },
            { people[3], people[5] },
        });

        Set<Pair> matching;
        EXPECT(!hasPerfectMatching(links, matching));
    } while (next_permutation(people.begin(), people.end()));
}

PROVIDED_TEST("hasPerfectMatching works on a more complex positive example.") {
    /* Because Map and Set internally store items in sorted order, the order
     * in which you iterate over people when making decisions is sensitive
     * to the order of those peoples' names. This test looks at a group like
     * this one, trying out all possible orderings of peoples' names:
     *
     *               *
     *               |
     *               *
     *              / \
     *             *---*
     *            /     \
     *           *       *
     *
     * There are 6! = 720 possible permutations of the ordering of these
     * people. If your code is able to solve the problem correctly for all of
     * those orderings, there's a good chance that you're correctly tracking
     * who is matched at each step. On the other hand, if your code runs into
     * issues here, it may indicate that there's a bug in how you mark who's
     * paired and who isn't.
     */
    Vector<string> people = { "A", "B", "C", "D", "E", "F" };
    do {
        Map<string, Set<string>> links = fromLinks({
            { people[0], people[1] },
            { people[1], people[2] },
            { people[2], people[3] },
            { people[3], people[1] },
            { people[2], people[4] },
            { people[3], people[5] },
        });

        Set<Pair> matching;
        EXPECT(hasPerfectMatching(links, matching));
        EXPECT(isPerfectMatching(links, matching));
    } while (next_permutation(people.begin(), people.end()));
}

PROVIDED_TEST("hasPerfectMatching works on a caterpillar.") {
    /* Because Map and Set internally store items in sorted order, the order
     * in which you iterate over people when making decisions is sensitive
     * to the order of those peoples' names. This test looks at a group like
     * this one, trying out all possible orderings of peoples' names:
     *
     *         *---*---*
     *         |   |   |
     *         *   *   *
     *
     * There are 6! = 720 possible permutations of the ordering of these six
     * people. If your code is able to solve the problem correctly for all of
     * those orderings, there's a good chance that you're correctly tracking
     * who is matched at each step. On the other hand, if your code runs into
     * issues here, it may indicate that there's a bug in how you mark who's
     * paired and who isn't.
     */
    Vector<string> people = { "A", "B", "C", "D", "E", "F" };
    do {
        Map<string, Set<string>> links = fromLinks({
            { people[0], people[1] },
            { people[1], people[2] },
            { people[0], people[3] },
            { people[1], people[4] },
            { people[2], people[5] },
        });

        Set<Pair> matching;
        EXPECT(hasPerfectMatching(links, matching));
        EXPECT(isPerfectMatching(links, matching));
    } while (next_permutation(people.begin(), people.end()));
}

PROVIDED_TEST("hasPerfectMatching stress test: negative example (should take under a second).") {
    /* Here, we're giving a "caterpillar" of people, like this:
     *
     *    *   *   *   *     *   *
     *    |   |   |   |     |   |
     *    *---*---*---* ... *---*
     *    |   |   |   |     |   |
     *    *   *   *   *     *   *
     *
     * This doesn't have a perfect matching, However, it may take some searching
     * to confirm this is the case. At this size, however, it should be
     * almost instanteous to find the solution, since the search space is fairly
     * small and most "wrong" decisions can be detected quickly.
     *
     * On the other hand, if your implementation repeatedly constructs the same
     * matchings over and over again, or keeps exploring even when a person who
     * couldn't be paired with the current setup is found, then the number of
     * options you need to consider will be too large for your computer to handle
     * in any reasonable time.
     *
     * If you're passing the other tests and this test hangs, double-check your
     * code to make sure you aren't repeatedly constructing the same matchings
     * multiple times.
     */

    /* Number of "body segments". */
    const int kRowSize = 10;

    Vector<Pair> links;
    for (int i = 0; i < kRowSize - 1; i++) {
        links.add({ to_string(i), to_string(i + 1) });
    }
    for (int i = 0; i < kRowSize; i++) {
        links.add({ to_string(i), to_string(i + kRowSize) });
    }
    for (int i = 0; i < kRowSize; i++) {
        links.add({ to_string(i), to_string(i + 2 * kRowSize) });
    }

    Set<Pair> matching;
    bool result = hasPerfectMatching(fromLinks(links), matching);
    EXPECT(!result);
}

PROVIDED_TEST("hasPerfectMatching stress test: positive example (should take under a second).") {
    /* Here, we're giving a "millipede" of people, like this:
     *
     *    *---*---*---* ... *---*
     *    |   |   |   |     |   |
     *    *   *   *   *     *   *
     *
     * This always has a perfect matching, which is found by pairing each person
     * with the person directly below them. However, it may take some searching
     * to find this particular configuration. At this size, however, it should be
     * almost instanteous to find the solution, since the search space is fairly
     * small and most "wrong" decisions can be detected quickly.
     *
     * On the other hand, if your implementation repeatedly constructs the same
     * matchings over and over again, or keeps exploring even when a person who
     * couldn't be paired with the current setup is found, then the number of
     * options you need to consider will be too large for your computer to handle
     * in any reasonable time.
     *
     * If you're passing the other tests and this test hangs, double-check your
     * code to make sure you aren't repeatedly constructing the same matchings
     * multiple times.
     */

    /* Number of "body segments". */
    const int kRowSize = 10;

    Vector<Pair> links;
    for (int i = 0; i < kRowSize - 1; i++) {
        links.add({ to_string(i), to_string(i + 1) });
    }
    for (int i = 0; i < kRowSize; i++) {
        links.add({ to_string(i), to_string(i + kRowSize) });
    }

    Set<Pair> matching;
    bool result = hasPerfectMatching(fromLinks(links), matching);
    EXPECT(result);
    EXPECT(isPerfectMatching(fromLinks(links), matching));
}

PROVIDED_TEST("maximumWeightMatching: Works for empty group.") {
    EXPECT_EQUAL(maximumWeightMatching({}), {});
}

PROVIDED_TEST("maximumWeightMatching: Works for group of one person.") {
    Map<string, Map<string, int>> links = {
        { "A", {} }
    };

    EXPECT_EQUAL(maximumWeightMatching(links), {});
}

PROVIDED_TEST("maximumWeightMatching: Works for a single pair of people.") {
    /* This world:
     *
     *  A --- B
     *     1
     *
     * Best option is to pick A -- B.
     */
    auto links = fromWeightedLinks({
        { "A", "B", 1 }
    });

    /* Should pick A--B. */
    EXPECT_EQUAL(maximumWeightMatching(links), {{"A", "B"}});
}

PROVIDED_TEST("maximumWeightMatching: Won't pick a negative edge.") {
    /* This world:
     *
     *  A --- B
     *     -1
     *
     * Best option is to not match anyone!
     */
    auto links = fromWeightedLinks({
        { "A", "B", -1 }
    });

    /* Should pick A--B. */
    EXPECT_EQUAL(maximumWeightMatching(links), {});
}

PROVIDED_TEST("maximumWeightMatching: Works on a line of three people.") {
    /* This world:
     *
     *  A --- B --- C
     *     1     2
     *
     * Best option is to pick B -- C.
     */
    auto links = fromWeightedLinks({
        { "A", "B", 1 },
        { "B", "C", 2 },
    });

    /* Should pick B--C. */
    EXPECT_EQUAL(maximumWeightMatching(links), { {"B", "C"} });
}

PROVIDED_TEST("maximumWeightMatching: Works on a triangle.") {
    /* This world:
     *
     *         A
     *      1 / \ 2
     *       B---C
     *         3
     *
     * Best option is to pick B -- C.
     */
    auto links = fromWeightedLinks({
        { "A", "B", 1 },
        { "B", "C", 3 },
        { "A", "C", 2 }
    });

    /* Should pick B--C. */
    EXPECT_EQUAL(maximumWeightMatching(links), { {"B", "C"} });
}

PROVIDED_TEST("maximumWeightMatching: Works on a square.") {
    /* This world:
     *
     *         1
     *      A --- B
     *      |     |
     *    8 |     | 2
     *      |     |
     *      D --- C
     *         4
     *
     * Best option is to pick BC/AD.
     */
    auto links = fromWeightedLinks({
        { "A", "B", 1 },
        { "B", "C", 2 },
        { "C", "D", 4 },
        { "D", "A", 8 },
    });

    EXPECT_EQUAL(maximumWeightMatching(links), { {"A", "D"}, {"B", "C"} });
}

PROVIDED_TEST("maximumWeightMatching: Works on a line of four people.") {
    /* This world:
     *
     *  A --- B --- C --- D
     *     1     3     1
     *
     * Best option is to pick B -- C, even though this is not a perfect
     * matching.
     */
    auto links = fromWeightedLinks({
        { "A", "B", 1 },
        { "B", "C", 3 },
        { "C", "D", 1 },
    });

    /* Should pick B--C. */
    EXPECT_EQUAL(maximumWeightMatching(links), { {"B", "C"} });
}

PROVIDED_TEST("maximumWeightMatching: Small stress test (should take at most a second or two).") {
    /* Because Map and Set internally store items in sorted order, the order
     * in which you iterate over people when making decisions is sensitive
     * to the order of those peoples' names. This test looks at a group like
     * this one, trying out all possible orderings of peoples' names:
     *
     *               *
     *               | 1
     *               *
     *            1 / \ 5
     *             *---*
     *          1 /  1  \ 1
     *           *       *
     *
     * (Best option is to pick the 5-cost edge and the opposite-side 1-cost
     * edge.)
     *
     * There are 6! = 720 possible permutations of the ordering of these
     * people. If your code is able to solve the problem correctly for all of
     * those orderings, there's a good chance that you're correctly tracking
     * who is matched at each step. On the other hand, if your code runs into
     * issues here, it may indicate that there's a bug in how you mark who's
     * paired and who isn't.
     */
    Vector<string> people = { "A", "B", "C", "D", "E", "F" };
    do {
        auto links = fromWeightedLinks({
            { people[0], people[1], 5 },
            { people[1], people[2], 1 },
            { people[2], people[0], 1 },
            { people[3], people[0], 1 },
            { people[4], people[1], 1 },
            { people[5], people[2], 1 },
        });

        Set<Pair> expected = {
            { people[0], people[1] },
            { people[2], people[5] }
        };

        EXPECT_EQUAL(maximumWeightMatching(links), expected);
    } while (next_permutation(people.begin(), people.end()));
}

PROVIDED_TEST("maximumWeightMatching: Large stress test (should take at most a second or two).") {
    /* Here, we're giving a chain of people, like this:
     *
     *    *---*---*---*---*---*---*---* ... *---*
     *      1   1   1   1   1   1   1         1
     *
     * The number of different matchings in a chain of n people is given by the
     * nth Fibonacci number. (Great exercise - can you explain why?) This means
     * that if we have a chain of 21 people, there are F(21) = 10,946 possible
     * matchings to check. If your program tests every single one of them exactly
     * once, then it should be pretty quick to determine what the best matching
     * here is. (It's any matching that uses exactly floor(21 / 2) = 10 edges.
     *
     * On the other hand, if your implementation repeatedly constructs the same
     * matchings over and over again, then the number of options you need to consider
     * will be too large for your computer to handle in any reasonable time.
     *
     * If you're passing the other tests and this test hangs, double-check your
     * code to make sure you aren't repeatedly constructing the same matchings
     * multiple times.
     */
    const int kNumPeople = 21;
    Vector<WeightedLink> links;
    for (int i = 0; i < kNumPeople - 1; i++) {
        links.add({ to_string(i), to_string(i + 1), 1 });
    }

    auto matching = maximumWeightMatching(fromWeightedLinks(links));
    EXPECT_EQUAL(matching.size(), kNumPeople / 2);

    /* Confirm it's a matching. */
    Set<string> used;
    for (Pair p: matching) {
        /* No people paired more than once. */
        EXPECT(!used.contains(p.first()));
        EXPECT(!used.contains(p.second()));
        used += p.first();
        used += p.second();

        /* Must be a possible links. */
        EXPECT_EQUAL(abs(stringToInteger(p.first()) - stringToInteger(p.second())), 1);
    }
}
