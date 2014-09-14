
#include "../../SlimTest.h"
#include "ExampleProject/OldPerson.h"
#include "ExampleProject/YoungPerson.h"

#include <sstream>
#include <memory>

DEFINE_TEST_FUNCTION
(
    const Person testPersonPete("Pete", 24, 180.0F);
    const Person testPersonJoe("Joe", 25, 199.5F);

    assertNotEqual(testPersonPete, testPersonJoe);
)

DEFINE_TEST_FUNCTION
(
    const Person testPersonPete1("Pete", 24, 180.0F);
    const Person testPersonPete2("Pete", 24, 180.0F);

    assertEqual(testPersonPete1, testPersonPete2);
    assertEqual(testPersonPete1, testPersonPete1);
    assertEqual(testPersonPete2, testPersonPete2);

    assertTrue(testPersonPete1 == testPersonPete2);
)

DEFINE_TEST_FUNCTION
(
    const Person testPersonPete("Pete", 24, 180.0F);

    std::ostringstream stringStream;
    stringStream << testPersonPete;
    const std::string& peteString1 = stringStream.str();
    const std::string peteString2 = "Pete 24 180";

    assertEqual(peteString1, peteString2);
)

DEFINE_TEST_FUNCTION
(
    const OldPerson oldPersonPete("Pete", 400, 180.0F);

    assertGreaterThanOrEqual(oldPersonPete.getAge(), 0);
    // Make sure verification process is working
    assertLessThan(oldPersonPete.getAge(), 200);
)

DEFINE_TEST_FUNCTION
(
    const YoungPerson youngPersonPete("Pete", 400, 180.0F);

    assertGreaterThanOrEqual(youngPersonPete.getAge(), 0);
    // Make sure verification process is working
    assertLessThanOrEqual(youngPersonPete.getAge(), 30);
)

DEFINE_TEST_FUNCTION
(
    std::shared_ptr<YoungPerson> youngPersonPete = std::make_shared<YoungPerson>("Pete", 200, 300.0F);

    std::shared_ptr<OldPerson> oldPersonPete = std::dynamic_pointer_cast<OldPerson>(youngPersonPete);

    assertNotNull(youngPersonPete);
    assertNull(oldPersonPete);
)

void testOldPersonComparisonYoungPerson()
{
    const YoungPerson youngGuy("Pete", 23, 400.0F);
    const OldPerson oldDude("Pete", 23, 400.0F);

    assertTrue(youngGuy < oldDude);
    assertTrue(oldDude > youngGuy);
    assertLessThan(youngGuy, oldDude);
    assertGreaterThan(oldDude, youngGuy);
}

void testOldPeopleVerify()
{
    const OldPerson oldPersonPete("Pete", 40, 130.24F);
    const Person personPete("Pete", 40, 130.24F);

    assertNotEqual(oldPersonPete, personPete);
    assertGreaterThan(oldPersonPete, personPete);
}

void testYoungPeopleVerify()
{
    const YoungPerson youngPersonPete("Pete", 40, 130.24F);
    const Person personPete("Pete", 40, 130.24F);

    assertNotEqual(youngPersonPete, personPete);
    assertLessThan(youngPersonPete, personPete);
}

void testEquality()
{
    const OldPerson oldPersonPete("Pete", 83, 130.243F);
    const Person personPete(oldPersonPete);

    assertEqual(oldPersonPete, personPete);
    assertEqual(personPete, oldPersonPete);

    const YoungPerson youngPersonPete("Pete", 13, 99.3F);
    const Person personPete2(youngPersonPete);

    assertEqual(youngPersonPete, personPete2);
    assertEqual(personPete2, youngPersonPete);
}

void testAssertionFailure()
{
    std::shared_ptr<YoungPerson> youngPersonPete = std::make_shared<YoungPerson>("Pete", 200, 300.0F);

    assertNotNull(youngPersonPete); // passes
    assertNull(youngPersonPete); // fails
}

void testAssertionFailureAgeCompare()
{
    const OldPerson oldPersonPete("Pete", 83, 130.243F);
    const YoungPerson youngPersonPete("Pete", 13, 94.5F);

    assertLessThan(youngPersonPete, oldPersonPete); // passes
    assertGreaterThan(youngPersonPete, oldPersonPete); // fails
}

REGISTER_TEST_FUNCTIONS(testOldPersonComparisonYoungPerson, testOldPeopleVerify, testYoungPeopleVerify, testEquality, testAssertionFailure, testAssertionFailureAgeCompare)
