/*
    The MIT License (MIT)
    
    Copyright (c) 2014 wallstop

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>

class TestRunner
{
public:
    TestRunner(std::initializer_list<std::function<void ()>> functions);
    ~TestRunner(){}

    static int runTests(const std::string& = "");
    void registerTests(std::initializer_list<std::function<void ()>> functions);
    void incrementAssertionCount();
    void incrementFailedAssertions();
    
    static TestRunner& testRunner();

private:
    int internalRunTests(const std::string& name);
    void resetAssertionCounts();

    std::vector<std::function<void ()>> testFunctions;
    size_t failedAssertions;
    size_t totalAssertions;
};

inline TestRunner::TestRunner(std::initializer_list<std::function<void ()>> functions)
    : failedAssertions(0), totalAssertions(0)
{
    testRunner().registerTests(functions);
}

inline int TestRunner::runTests(const std::string& name)
{
    return testRunner().internalRunTests(name);
}

inline int TestRunner::internalRunTests(const std::string& name)
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
            std::cout << "Test Function FAILED in test " 
                << counter << std::endl << std::endl;
            ++failed;
        }
        resetAssertionCounts();
    }

    std::cout << total - failed << " tests passed out of " << total << " tests in " 
        << name << "." << std::endl;

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
        std::cout << "Assertion failed: " << #expression << "." << std::endl \
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
        std::cout << "Assertion failed: " << #expression << "." << std::endl \
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
        std::cout << "Assertion failed: " << #lhs << " == " << #rhs << "." << std::endl \
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
        std::cout << "Assertion failed: " << #lhs << " != " << #rhs \
            << ". Expected not equal but were equal (" << (lhs) << ", " << (rhs) << ")" << std::endl; \
        std::cout << "    At: " << __FILE_NAME << " " << __LINE_NUMBER << std::endl; \
        TestRunner::testRunner().incrementFailedAssertions(); \
    } \
    TestRunner::testRunner().incrementAssertionCount();

#ifdef assertNotNull
#undef assertNotNull
#endif
#define assertNotNull(expression) \
    assertFalse(nullptr == (expression))

#ifdef assertNull
#undef assertNull
#endif
#define assertNull(expression) \
    assertTrue(nullptr == (expression))

#ifdef assertGreaterThan
#undef assertGreaterThan
#endif
#define assertGreaterThan(lhs, rhs) \
    if(!((lhs) > (rhs))) \
    { \
        std::cout << "Assertion failed: " << #lhs << " > " #rhs \
            << ". Expected greater than but was not (" << (lhs) << ", " << (rhs) << ")" << std::endl; \
        std::cout << "    At: " << __FILE_NAME << " " << __LINE_NUMBER << std::endl; \
        TestRunner::testRunner().incrementFailedAssertions(); \
    } \
    TestRunner::testRunner().incrementAssertionCount();

#ifdef assertLessThan
#undef assertLessThan
#endif
#define assertLessThan(lhs, rhs) \
    if(!((lhs) < (rhs))) \
    { \
        std::cout << "Assertion failed: " << #lhs << " < " #rhs \
            << ". Expected less than but was not (" << (lhs) << ", " << (rhs) << ")" << std::endl; \
        std::cout << "    At: " << __FILE_NAME << " " << __LINE_NUMBER << std::endl; \
        TestRunner::testRunner().incrementFailedAssertions(); \
    } \
    TestRunner::testRunner().incrementAssertionCount();

#ifdef assertGreaterThanOrEqual
#undef assertGreaterThanOrEqual
#endif
#define assertGreaterThanOrEqual(lhs, rhs) \
    if(!((lhs) >= (rhs))) \
    { \
        std::cout << "Assertion failed: " << #lhs << " >= " #rhs \
            << ". Expected greater than but was not (" << (lhs) << ", " << (rhs) << ")" << std::endl; \
        std::cout << "    At: " << __FILE_NAME << " " << __LINE_NUMBER << std::endl; \
        TestRunner::testRunner().incrementFailedAssertions(); \
    } \
    TestRunner::testRunner().incrementAssertionCount();

#ifdef assertLessThanOrEqual
#undef assertLessThanOrEqual
#endif
#define assertLessThanOrEqual(lhs, rhs) \
    if(!((lhs) <= (rhs))) \
    { \
        std::cout << "Assertion failed: " << #lhs << " <= " #rhs \
            << ". Expected less than but was not (" << (lhs) << ", " << (rhs) << ")" << std::endl; \
        std::cout << "    At: " << __FILE_NAME << " " << __LINE_NUMBER << std::endl; \
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
    REGISTER_TEST_FUNCTIONS( \
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

#ifdef REGISTER_TEST_FUNCTIONS
#undef REGISTER_TEST_FUNCTIONS
#endif
#define REGISTER_TEST_FUNCTIONS(...) \
        static const TestRunner ___EXPANDED_LINE_NUMBER(__LINE__) ## _zzStaticTestRunner \
            = TestRunner({__VA_ARGS__});

#ifdef RUN_TESTS_MAIN
#undef RUN_TESTS_MAIN
#endif
#define RUN_TESTS_MAIN(name) \
    int main(int argc, char* argv[]) \
    { \
        return TestRunner::runTests(name); \
    }