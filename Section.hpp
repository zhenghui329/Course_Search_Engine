//
//  Section.hpp
//  Group_Project
//
//  Created by Dennis Zhao on 3/6/19.
//  Copyright © 2019 Dennis Zhao. All rights reserved.
//

#ifndef Section_hpp
#define Section_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <cctype>

using std :: ostream;
using std :: string;

class Section
{
   
private:
    string CRN; // 00428
    string sectionName; // 64Z
    string teacher; // Karina G Dundurs (P)
    string classroom; // AT312 or ONLINE
    string days; // MW or TR or TBA
    string time; // 01:30 pm-03:20 pm
    
public:
    
    Section()
    {
        CRN = "";
        sectionName = "";
        teacher = "";
        classroom = "";
        days = "";
        time = "";
    }
    
    
    Section(string CRN, string sectionName, string days, string time, string teacher, string classroom )
    {
        this->CRN = CRN;
        this->sectionName = sectionName;
        this->days = days;
        this->time = time;
        this->teacher = teacher;
        this->classroom = classroom;
    }
    
    bool operator== (const Section &other);
    
    friend ostream& operator<<(ostream& os, const Section &data);

};


bool Section :: operator== (const Section &other)
{
    return (CRN == other.CRN );
}

ostream& operator<<(ostream& os, const Section &data)
{
    os << "\t\t\t" << std::left << std::setw(6) << data.CRN;
    os << std::setw(4) << data.sectionName;
    os << std::setw(5) << data.days;
    os << std::setw(20) << data.time;
    os << std::setw(28) << data.teacher;
    os << data.classroom;
    
    return os;
}

#endif /* Section_hpp */
