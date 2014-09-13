SlimTest-
=========

Very light header-only Unit-Testing framework for C++ projects

<h2>Usage</h2>

SlimTest's use case is to test assertions that will cause a unit test to pass or fail and in doing so, notify the build process (or the user) exactly what assertions failed with what values. While doing this, it should be incredibly simple and easy to use.

```C++
#include "SlimTest.h"
#include "MyClassToTest.h"

DEFINE_TEST_FUNCTION
(
    MyClassToTest testInstance;
    assertTrue(testInstance.isValid());
    
    const std::string testName = "TestInstance";
    testInstance.setName(testName);
    assertEqual(testName, testInstance.getName());
)

RUN_TESTS_MAIN("MyClassTest")

```

<h2>Core Macros</h2>
SlimTest is implimented via a combination of preprocessor macros and a single class called TestRunner. As a user, you will only need to interact with the macro portion of SlimTest.

There are three core macros that lie at the base of SlimTest.

```C++
DEFINE_TEST_FUNCTION(/* Function contents go here */)
```

This macro allows you to declare a test function. This test function is automatically registered with the test harness.

```C++
void myTestFunction()
{
    // Do stuff
}

void myTestFunction2()
{
    // Do more stuff
}

REGISTER_TEST_FUNCTIONS(myTestFunction, myTestFunction2)
```

This macro allows you to take already declared test functions and register them with the test harness. Test functions must conform to:
```C++
std::function<void ()>
```

Finally, somewhere in a single source file in the project, you must place:
```C++
RUN_TESTS_MAIN("Some string describing your test project; usually the project name")
```

This will cause the source file that the macro is placed in to act as a main.cpp for the project.

<h2>Integrating with Visual Studio</h2>
The RUN_TESTS_MAIN() macro enables the project that it is placed in to compile to a running executable that will return an error code if any assertions fail in any of the tests. This allows us to link it into the Visual Studio build process seemlessly, as an error code on an excecution step will cause the build to fail.

On the test project properties, navigate to Configuration Properties -> Build Events -> Post Build Event (make sure Configuration is set to "All Configurations" and Platform is set to "All Platforms"). Paste the following into the "Command Line" box:
```
"$(OutDir)$(TargetFileName)"
```

<h2>Assertion Macros</h2>
SlimTest allows you to test the "truthiness" of a number of expressions. There are four unary assertions and a number of binary assertions. Unary assertions require no "extra work" from you, as a software developer. The binary assertions have some additional operator and function requirements.
<h3>Unary Assertions</h3>
<h4>assertTrue</h4>
```C++
assertTrue(expression)
```
expression must be a boolean expression returning true or false. If the expression is false, the test assertion fails.
<h4>assertFalse</h4>
```C++
assertFalse(expression)
```
expression must be a boolean expression returning true or false. If the expression is true, the test assertion fails.
<h4>assertNull</h4>
```C++
assertNull(pointer)
```
pointer should refer to a pointer to an object. If !(nullptr == pointer), the test assertion fails.
<h4>assertNotNull</h4>
```C++
assertNotNull(pointer)
```
pointer should refer to a pointer to an object. If (nullptr == pointer), the test assertion fails.
<h3>Binary Assertions</h3>
Binary assertions REQUIRE that the ostream operator above is implemented. These will not compile without it.
<h4>assertEqual</h4>
```C++
assertEqual(lhs, rhs)

std::ostream& <<(std::ostream&, const lhs&); // required
std::ostream& <<(std::ostream&, const rhs&); // required
bool operator==(const lhs&, const rhs&); // required
```
If !(lhs == rhs), the test assertion fails.
<h4>assertNotEqual</h4>
```C++
std::ostream& <<(std::ostream&, const lhs&); // required
std::ostream& <<(std::ostream&, const rhs&); // required
bool operator!=(const lhs&, const rhs&); // required

assertNotEqual(lhs, rhs)
```
If !(lhs != rhs), the test assertion fails.

<h4>Other binary assertions</h4>
Following the above format the following have been implemented:
* assertGreaterThan
* assertLessThan
* assertGreaterThanOrEqual
* assertLessThanOrEqual

<h2>Lacking (but wanted) Features</h2>
* Currently no moc'ing support
* No exception assertions
* Line / branch coverage






