#include <stdio.h>
#include "enet.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#ifdef _WIN32
#define ASSERT_SLEEP(ms) Sleep(ms)
#else
#define ASSERT_SLEEP(ms) usleep(ms * 1000);
#endif

#define GET_MACRO(_1, _2, _3, NAME, ...) NAME
#define ASSERT_THAT(...) GET_MACRO(__VA_ARGS__, ASSERT_THAT_IMPL3, ASSERT_THAT_IMPL2)(__VA_ARGS__)

#define ASSERT_THAT_IMPL3(a, b, m) do { \
    if ((a) != (b)) { \
        fprintf(stderr, "%s\n", m); \
        fprintf(stderr, "ASSERT_THAT(%s, %s)\n", #a, #b); \
        fprintf(stderr, "  Expected: %s\n", #b); \
        fprintf(stderr, "  But was: %s\n", #a); \
        fprintf(stderr, "at %s:%d\n", __FILE__, __LINE__); \
    } \
} while (0)

#define ASSERT_THAT_IMPL2(a, b) do { \
    if ((a) != (b)) { \
        fprintf(stderr, "ASSERT_THAT(%s, %s)\n", #a, #b); \
        fprintf(stderr, "  Expected: %s\n", #b); \
        fprintf(stderr, "  But was: %s\n", #a); \
        fprintf(stderr, "at %s:%d\n", __FILE__, __LINE__); \
    } \
} while (0)

void Test_ENET_TIME_LESS() {
    enet_uint32 a = 1000;
    enet_uint32 b = 2000;
    // Normal cases
    ASSERT_THAT(ENET_TIME_LESS(a, b), true, "ENET_TIME_LESS should return true for a < b");
    ASSERT_THAT(ENET_TIME_LESS(a, a), false, "ENET_TIME_LESS should return false for a == b");
    ASSERT_THAT(ENET_TIME_LESS(b, a), false, "ENET_TIME_LESS should return false for a > b");

    // Cases involving ENET_TIME_OVERFLOW constant
    ASSERT_THAT(ENET_TIME_LESS(a, ENET_TIME_OVERFLOW), true,
                "ENET_TIME_LESS with a < ENET_TIME_OVERFLOW and b == ENET_TIME_OVERFLOW should be true");
    ASSERT_THAT(ENET_TIME_LESS(ENET_TIME_OVERFLOW, a), false,
                "ENET_TIME_LESS with a == ENET_TIME_OVERFLOW and b < ENET_TIME_OVERFLOW should be false");
    ASSERT_THAT(ENET_TIME_LESS(ENET_TIME_OVERFLOW, ENET_TIME_OVERFLOW), false,
                "ENET_TIME_LESS with a == ENET_TIME_OVERFLOW and b == ENET_TIME_OVERFLOW should be false");
}

void Test_ENET_TIME_GREATER() {
    enet_uint32 a = 1000;
    enet_uint32 b = 2000;
    // Normal cases
    ASSERT_THAT(ENET_TIME_GREATER(b, a), true, "ENET_TIME_GREATER should return true for a > b");
    ASSERT_THAT(ENET_TIME_GREATER(a, a), false, "ENET_TIME_GREATER should return false for a == b");
    ASSERT_THAT(ENET_TIME_GREATER(a, b), false, "ENET_TIME_GREATER should return false for a < b");

    // Cases involving ENET_TIME_OVERFLOW constant
    ASSERT_THAT(ENET_TIME_GREATER(a, ENET_TIME_OVERFLOW), false,
                "ENET_TIME_GREATER with a < ENET_TIME_OVERFLOW and b == ENET_TIME_OVERFLOW should be false");
    ASSERT_THAT(ENET_TIME_GREATER(ENET_TIME_OVERFLOW, a), true,
                "ENET_TIME_GREATER with a == ENET_TIME_OVERFLOW and b < ENET_TIME_OVERFLOW should be true");
    // ENET_TIME_GREATER is !ENET_TIME_LESS_EQUAL
    ASSERT_THAT(ENET_TIME_GREATER(ENET_TIME_OVERFLOW, ENET_TIME_OVERFLOW), false,
                "ENET_TIME_GREATER with a == ENET_TIME_OVERFLOW and b == ENET_TIME_OVERFLOW should be false");
}

void Test_ENET_TIME_LESS_EQUAL() {
    enet_uint32 a = 1000;
    enet_uint32 b = 2000;
    // Normal cases
    ASSERT_THAT(ENET_TIME_LESS_EQUAL(a, b), true, "ENET_TIME_LESS_EQUAL should return true for a <= b");
    ASSERT_THAT(ENET_TIME_LESS_EQUAL(a, a), true,
                "ENET_TIME_LESS_EQUAL should return true for a <= b (equal)");
    ASSERT_THAT(ENET_TIME_LESS_EQUAL(b, a), false,
                "ENET_TIME_LESS_EQUAL should return false for a <= b (greater)");

    // Cases involving ENET_TIME_OVERFLOW constant
    ASSERT_THAT(ENET_TIME_LESS_EQUAL(a, ENET_TIME_OVERFLOW), true,
                "ENET_TIME_LESS_EQUAL with a < ENET_TIME_OVERFLOW and b == ENET_TIME_OVERFLOW should be true");
    ASSERT_THAT(ENET_TIME_LESS_EQUAL(ENET_TIME_OVERFLOW, a), false,
                "ENET_TIME_LESS_EQUAL with a == ENET_TIME_OVERFLOW and b < ENET_TIME_OVERFLOW should be false");
    ASSERT_THAT(ENET_TIME_LESS_EQUAL(ENET_TIME_OVERFLOW, ENET_TIME_OVERFLOW), true,
                "ENET_TIME_LESS_EQUAL with a == ENET_TIME_OVERFLOW and b == ENET_TIME_OVERFLOW should be true");
}

void Test_ENET_TIME_GREATER_EQUAL() {
    enet_uint32 a = 1000;
    enet_uint32 b = 2000;
    // Normal cases
    ASSERT_THAT(ENET_TIME_GREATER_EQUAL(b, a), true, "ENET_TIME_GREATER_EQUAL should return true for a >= b");
    ASSERT_THAT(ENET_TIME_GREATER_EQUAL(a, a), true,
                "ENET_TIME_GREATER_EQUAL should return true for a >= b (equal)");
    ASSERT_THAT(ENET_TIME_GREATER_EQUAL(a, b), false,
                "ENET_TIME_GREATER_EQUAL should return false for a >= b (less)");

    // Cases involving ENET_TIME_OVERFLOW constant (based on ENET_TIME_GREATER logic)
    ASSERT_THAT(ENET_TIME_GREATER_EQUAL(a, ENET_TIME_OVERFLOW), false,
                "ENET_TIME_GREATER_EQUAL with a < ENET_TIME_OVERFLOW and b == ENET_TIME_OVERFLOW should be false");
    ASSERT_THAT(ENET_TIME_GREATER_EQUAL(ENET_TIME_OVERFLOW, a), true,
                "ENET_TIME_GREATER_EQUAL with a == ENET_TIME_OVERFLOW and b < ENET_TIME_OVERFLOW should be true");
    ASSERT_THAT(ENET_TIME_GREATER_EQUAL(ENET_TIME_OVERFLOW, ENET_TIME_OVERFLOW), true,
                "ENET_TIME_GREATER_EQUAL with a == ENET_TIME_OVERFLOW and b == ENET_TIME_OVERFLOW should be true");
}

void Test_ENET_TIME_DIFFERENCE() {
    // Normal cases
    enet_uint32 a = 2000;
    enet_uint32 b = 1000;
    ASSERT_THAT(ENET_TIME_DIFFERENCE(a, b), 1000,
                "ENET_TIME_DIFFERENCE should return the absolute difference for a > b");
    ASSERT_THAT(ENET_TIME_DIFFERENCE(b, a), 1000,
                "ENET_TIME_DIFFERENCE should return the absolute difference for a < b");
    ASSERT_THAT(ENET_TIME_DIFFERENCE(a, a), 0u, "ENET_TIME_DIFFERENCE should return 0 for a == b");

    // Case involving ENET_TIME_OVERFLOW constant as per user's example
    enet_uint32 c = 1000;
    enet_uint32 d = ENET_TIME_OVERFLOW;
    ASSERT_THAT(ENET_TIME_DIFFERENCE(c, d), d - c,
                "ENET_TIME_DIFFERENCE should return the difference involving ENET_TIME_OVERFLOW");
}

void Test_enet_time_get() {
    enet_uint32 firstTime = enet_time_get();
    ASSERT_SLEEP(100);
    enet_uint32 secondTime = enet_time_get();

    ASSERT_THAT(secondTime >= firstTime, true, "enet_time_get should return increasing time");
    ASSERT_THAT(secondTime - firstTime > 90, true, "Time difference should be at least ~100ms");
}

void test_time() {
    Test_ENET_TIME_LESS();
    Test_ENET_TIME_GREATER();
    Test_ENET_TIME_LESS_EQUAL();
    Test_ENET_TIME_GREATER_EQUAL();
    Test_ENET_TIME_DIFFERENCE();
    Test_enet_time_get();
}
