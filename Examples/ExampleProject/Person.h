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

#pragma warning(push)
#pragma warning(disable : 4251)

#include "Exports.h"

#include <string>
#include <ostream>

class EXAMPLE_LIB_EXPORT Person
{
public:
    Person();
    Person(const std::string& name, unsigned short age, float weight);
    virtual ~Person();

    bool operator==(const Person&) const;
    bool operator!=(const Person&) const;
    bool operator>(const Person&) const;
    bool operator<(const Person&) const;
    friend std::ostream& operator<<(std::ostream&, const Person&);

    virtual std::string getName() const;
    virtual void setName(const std::string& name);

    virtual unsigned short getAge() const;
    virtual void setAge(unsigned short age);

    virtual float getWeight() const;
    virtual void setWeight(float);

    virtual void verify();

protected:

    std::string     m_name;
    unsigned short  m_age;
    float           m_weight;
};

inline std::ostream& operator<<(std::ostream& stream, const Person& person)
{
    return (stream << person.getName() << " " << person.getAge() << " " << person.getWeight());
}

#pragma warning(pop)
