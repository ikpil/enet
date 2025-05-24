#include <stdio.h>

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

