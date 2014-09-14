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

#include "Person.h"

Person::Person()
{
    verify();
}

Person::Person(const std::string& name, unsigned short age, float weight)
    : m_name(name), m_age(age), m_weight(weight)
{
    verify();
}

Person::~Person()
{
}

bool Person::operator==(const Person& rhs) const
{
    return (m_age == rhs.m_age) && 
        (m_weight == rhs.m_weight) &&
        (m_name == rhs.m_name);
}

bool Person::operator!=(const Person& rhs) const
{
    return !(*this == rhs);
}

bool Person::operator>(const Person& rhs) const
{
    return m_age > rhs.m_age;
}

bool Person::operator<(const Person& rhs) const
{
    return m_age < rhs.m_age;
}

std::string Person::getName() const
{
    return m_name;
}

void Person::setName(const std::string& name)
{
    m_name = name;
    verify();
}

unsigned short Person::getAge() const
{
    return m_age;
}

void Person::setAge(unsigned short age)
{
    m_age = age;
    verify();
}

float Person::getWeight() const
{
    return m_weight;
}

void Person::setWeight(float weight)
{
    m_weight = weight;
    verify();
}

void Person::verify()
{
    // No-op
}
