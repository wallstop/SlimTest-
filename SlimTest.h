
#pragma once

#include <functional>
#include <iostream>
#include <vector>
#include <initializer_list>

class TestRunner
{
public:
    TestRunner(std::initializer_list<std::function<void ()>> functions);
    ~TestRunner(){}

    static int runTests();
    void registerTests(std::initializer_list<std::function<void ()>> functions);
    void incrementAssertionCount();
    void incrementFailedAssertions();
    static TestRunner& testRunner();

private:
    int internalRunTests();

    std::vector<std::function<void ()>> testFunctions;
    size_t failedAssertions;
    size_t totalAssertions;

    void resetAssertionCounts();
};

inline TestRunner::TestRunner(std::initializer_list<std::function<void ()>> functions)
    : failedAssertions(0), totalAssertions(0)
{
    testRunner().registerTests(functions);
}

inline int TestRunner::runTests()
{
    return testRunner().internalRunTests();
}

inline int TestRunner::internalRunTests()
{
    resetAssertionCounts();

    size_t failed = 0;
    size_t counter = 0;
    const size_t total = testFunctions.size();
    for(auto&& function : testFunctions)
    {
        function();
        ++counter;
        if(failedAssertions > 0)
        {
            std::cerr << "Test Function FAILED in test " 
                << counter << std::endl << std::endl;
            ++failed;
        }
        resetAssertionCounts();
    }

    std::cerr << total - failed << " tests passed out of " << total << " tests." << std::endl;

    return (int)failed;
}

inline void TestRunner::registerTests(std::initializer_list<std::function<void ()>> functions)
{
    for(auto&& function : functions)
        testFunctions.push_back(function);
}

inline void TestRunner::incrementAssertionCount()
{
    ++totalAssertions;
}

inline void TestRunner::incrementFailedAssertions()
{
    ++failedAssertions;
}

inline void TestRunner::resetAssertionCounts()
{
    totalAssertions = 0;
    failedAssertions = 0;
}

inline TestRunner& TestRunner::testRunner()
{
    static TestRunner singleton({});
    return singleton;
}

#ifdef assertTrue
#undef assertTrue
#endif
#define assertTrue(expression) \
    if(!(expression)) \
    { \
        std::cerr << "Assertion failed: " << #expression << "." << std::endl \
            << "    Expected true but was false (" << (expression) << ")" \
            << std::endl << "    At: " << __FILE_NAME << " " << __LINE_NUMBER << std::endl; \
        TestRunner::testRunner().incrementFailedAssertions(); \
    } \
    TestRunner::testRunner().incrementAssertionCount();

#ifdef assertFalse
#undef assertFalse
#endif
#define assertFalse(expression) \
    if(expression) \
    { \
        std::cerr << "Assertion failed: " << #expression << "." << std::endl \
            << "    Expected false but was true (" << (expression) << ")" \
            << std::endl << "    At: " << __FILE_NAME << " " << __LINE_NUMBER << std::endl; \
        TestRunner::testRunner().incrementFailedAssertions(); \
    } \
    TestRunner::testRunner().incrementAssertionCount();

#ifdef assertEqual
#undef assertEqual
#endif
#define assertEqual(lhs, rhs) \
    if(!((lhs) == (rhs))) \
    { \
        std::cerr << "Assertion failed: " << #lhs << " == " << #rhs << "." << std::endl \
            << "    Expected equal but were unequal (" << (lhs) << ", " << (rhs) << ")" \
            << std::endl << "    At: " << __FILE_NAME << " " << __LINE_NUMBER << std::endl; \
        TestRunner::testRunner().incrementFailedAssertions(); \
    } \
    TestRunner::testRunner().incrementAssertionCount();

#ifdef assertNotEqual
#undef assertNotEqual
#endif
#define assertNotEqual(lhs, rhs) \
    if(!((lhs) != (rhs))) \
    { \
        std::cerr << "Assertion failed: " << #lhs << " != " << #rhs \
            << ". Expected not equal but were equal (" << (lhs) << ", " << (rhs) << ")" << std::endl; \
        std::cerr << "    At: " << __FILE_NAME << " " << __LINE_NUMBER << std::endl; \
        TestRunner::testRunner().incrementFailedAssertions(); \
    } \
    TestRunner::testRunner().incrementAssertionCount();

#ifdef assertNotNull
#undef assertNotNull
#endif
#define assertNotNull(expression) \
    assertNotEqual(expression, nullptr)

#ifdef assertNull
#undef assertNull
#endif
#define assertNull(expression) \
    assertEqual(expression, nullptr)

#ifdef assertGreaterThan
#undef assertGreaterThan
#endif
#define assertGreaterThan(lhs, rhs) \
    if(!(lhs > rhs)) \
    { \
        std::cerr << "Assertion failed: " << #lhs << " > " #rhs \
            << ". Expected greater than but was not (" << (lhs) << ", " << (rhs) << ")" << std::endl; \
        std::cerr << "    At: " << __FILE_NAME << " " << __LINE_NUMBER << std::endl; \
        TestRunner::testRunner().incrementFailedAssertions(); \
    } \
    TestRunner::testRunner().incrementAssertionCount();

#ifdef assertLessThan
#undef assertLessThan
#endif
#define assertLessThan(lhs, rhs) \
    if(!(lhs < rhs)) \
    { \
        std::cerr << "Assertion failed: " << #lhs << " < " #rhs \
            << ". Expected greater than but was not (" << (lhs) << ", " << (rhs) << ")" << std::endl; \
        std::cerr << "    At: " << __FILE_NAME << " " << __LINE_NUMBER << std::endl; \
        TestRunner::testRunner().incrementFailedAssertions(); \
    } \
    TestRunner::testRunner().incrementAssertionCount();

#ifdef assertGreaterThanOrEqual
#undef assertGreaterThanOrEqual
#endif
#define assertGreaterThanOrEqual(lhs, rhs) \
    if(!(lhs >= rhs)) \
    { \
        std::cerr << "Assertion failed: " << #lhs << " >= " #rhs \
            << ". Expected greater than but was not (" << (lhs) << ", " << (rhs) << ")" << std::endl; \
        std::cerr << "    At: " << __FILE_NAME << " " << __LINE_NUMBER << std::endl; \
        TestRunner::testRunner().incrementFailedAssertions(); \
    } \
    TestRunner::testRunner().incrementAssertionCount();

#ifdef assertLessThanOrEqual
#undef assertLessThanOrEqual
#endif
#define assertLessThanOrEqual(lhs, rhs) \
    if(!(lhs >= rhs)) \
    { \
        std::cerr << "Assertion failed: " << #lhs << " <= " #rhs \
            << ". Expected greater than but was not (" << (lhs) << ", " << (rhs) << ")" << std::endl; \
        std::cerr << "    At: " << __FILE_NAME << " " << __LINE_NUMBER << std::endl; \
        TestRunner::testRunner().incrementFailedAssertions(); \
    } \
    TestRunner::testRunner().incrementAssertionCount();

#ifdef __LINE_NUMBER
#undef __LINE_NUMBER
#endif
#define __LINE_NUMBER \
    __LINE__

#ifdef __FILE_NAME
#undef __FILE_NAME
#endif
#define __FILE_NAME \
    __FILE__

#ifdef DEFINE_TEST_FUNCTION
#undef DEFINE_TEST_FUNCTION
#endif
#define DEFINE_TEST_FUNCTION(...) \
    registerTestFunctions( \
        []() \
        { \
            __VA_ARGS__ \
        } \
    )

#ifdef __EXPANDED_LINE_NUMBER
#undef __EXPANDED_LINE_NUMBER
#endif
#define __EXPANDED_LINE_NUMBER(x) \
    __zz_ ## x

#ifdef ___EXPANDED_LINE_NUMBER
#undef ___EXPANDED_LINE_NUMBER
#endif
#define ___EXPANDED_LINE_NUMBER(x) \
    __EXPANDED_LINE_NUMBER(x)

#ifdef registerTestFunctions
#undef registerTestFunctions
#endif
#define registerTestFunctions(...) \
        static const TestRunner ___EXPANDED_LINE_NUMBER(__LINE__) ## _zzStaticTestRunner  = TestRunner({__VA_ARGS__});

#ifdef RUN_TESTS_MAIN
#undef RUN_TESTS_MAIN
#endif
#define RUN_TESTS_MAIN \
    int main(int argc, char* argv[]) \
    { \
        return TestRunner::runTests(); \
    }