//
//  Course.hpp
//  Group_Project
//
//  Created by Dennis Zhao on 3/6/19.
//  Copyright © 2019 Dennis Zhao. All rights reserved.
//

#ifndef Course_h
#define Course_h

#include "LinkedList.h"
#include "Section.hpp"
#include <string>
#include <cctype>
#include <iomanip>

using std :: string;

class Course
{
private:
    
    // This courseID is used to compare two Course object to test if they are the same
    
    string courseID; // Example:CIS D22C
    string courseName; // Data Abstract & Structures
    double units; // 4.5
    int frequency;// The frequency ba
    LinkedList<Section> listOfSections;
    
public:
    struct hash
    {
        std::size_t operator()(const Course* cPtr) const;
    };
    
    Course();
    Course(string courseName, string units, string courseID);
    
    void addSection(Section& add);
    
    bool operator== (const Course &other) const;
    
    Course& operator= (const Course &other);
    
    Course(const Course& other);
    
    friend ostream& operator<<(ostream& os, const Course &data);
    
    void updateFrequency()
    {
        frequency ++;
    }
    
    string getCourseName() const
    {
        return courseName;
    }
    
    string getCourseID() const
    {
        return courseID;
    }
    
    double getUnits()
    {
        return units;
    }
    
    int getFrequency()
    {
        return frequency;
    }
    
    LinkedList<Section>* getListOfSection()
    {
        return &listOfSections;
    }
};

Course :: Course()
{
    courseID = "";
    courseName = "";
    units = 0.00;
    frequency = 0;
}


Course :: Course(string courseName, string units, string courseID)
{
    this->courseID = courseID;
    this->courseName = courseName;
    this->units = stod(units);
    frequency = 0;
}


bool Course :: operator==(const Course &other) const
{
    return this->courseID == other.courseID;
}

/*
 The append function has been modified so that it does not append any duplicate;
 */
void Course :: addSection(Section& section)
{
    listOfSections.appendNode(section);
}

ostream& operator<<(ostream& os, const Course &c)
{
    os  << std::left << std::setw(10) << c.courseID;
    os  << std::setw(54) << std::left << c.courseName;
    os  << "\tunits (" << c.units << ")";
    os  <<"\t .....Frequency: "<< c.frequency<<"\n";
    c.listOfSections.displayList();
    return os;
}

Course::Course(const Course& other) {
    this->courseID = other.courseID;
    this->courseName = other.courseName;
    this->units = other.units;
    this->frequency = other.frequency;
    this->listOfSections = other.listOfSections;
}

Course& Course :: operator= (const Course &other)
{
    if (this == &other)
    {
        return *this;
    }
    
    this->courseID = other.courseID;
    this->courseName = other.courseName;
    this->units = other.units;
    this->frequency = other.frequency;
    this->listOfSections = other.listOfSections;
    
    return *this;
}


std::size_t Course::hash::operator()(const Course* cPtr) const
{
    //    std::size_t stringHash = 5381;
    //    const std::string& course_name = cPtr->courseID;
    //    for (int i = 0; i < course_name.length(); i++) {
    //        stringHash = (stringHash * 33) + course_name.at(i);
    //    }
    return reinterpret_cast<uint64_t>(cPtr);
    
}


#endif /* Course_h */
