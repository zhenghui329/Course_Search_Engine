//
//  Process.h
//  Process class generates the steps through reading file,
//  build of tree, searching course, dealing with results,
//  to print results.

//  Created by Yue Tan on 3/7/19.
//  Copyright © 2019 Yue Tan. All rights reserved.
//  Write by all members
//

#ifndef Process_h
#define Process_h

#include <string>
#include <sstream>
#include <fstream>
#include "Course.h"
#include "LinkedList.h"
#include "NAryTree.h"
#include "Sort.h"

using std::string;
using std::stringstream;
using std::ifstream;

class Process{
private:
    NAryTree<Course*,Course::hash> tree;
public:
    Process(){}
    ~Process(){}
    void readFile(LinkedList<Course> & courseList);
    void buildTree(LinkedList<Course> & courseList);
    LinkedList<Course> searchCourse(string courseInput);
    void sortResult(ListNode<Course>*& head);
    void print(const LinkedList<Course>& result);
};

//**********************************************************
// readDataToFile read the data file and
// return a linked list of Course object
//**********************************************************
void Process::readFile(LinkedList<Course> & courseList)
{
    ifstream myfile("Course.csv");
    
    string courseID, CRN, courseName, units, sectionName, classroom, teacher, days, time;
    string line;
    
    if(!myfile.is_open())
    {
        std::cout <<"File failed to open." << std::endl;
        exit(EXIT_FAILURE);
    }
    
    while(getline(myfile,line))
    {
        stringstream ss(line);
        getline(ss, courseID, ',');
        getline(ss, units, ',');
        getline(ss, CRN, ',');
        getline(ss, sectionName, ',');
        getline(ss, courseName, ',');
        getline(ss, days, ',');
        getline(ss, time, ',');
        getline(ss, teacher, ',');
        getline(ss, classroom, ',');
        
        Section section(CRN, sectionName, days, time, teacher, classroom);
        Course course(courseName, units, courseID);
        
        ListNode<Course>* lastNode = courseList.tail;
        if(lastNode == nullptr){
            course.addSection(section);
            courseList.appendNode(course);
        }else if(course == lastNode->value){
            lastNode->value.addSection(section);
        }else{
            course.addSection(section);
            courseList.appendNode(course);
        }
    }
}

//**********************************************************
// for each course in the Course array,
// parse the course name to several single word.
// Call insert function of NAryTree class,
// pass the word  and the pointer of Course object to
// build the tree
//**********************************************************
void Process::buildTree(LinkedList<Course>& courseList){
    
    ListNode<Course>* curListNode = courseList.head;
    
    while(curListNode){
        stringstream inputStr(curListNode->value.getCourseName());
        string word;
        
        while (inputStr >> word){
            // convert string to uppercase
            transform(word.begin(), word.end(), word.begin(), ::toupper);
            // insert the word and the ptr to the tree
            // the ptr points to object that the word belongs to
            Course* curCourse = &(curListNode->value);
            tree.insert(word, curCourse);
        }
        curListNode = curListNode->next;
    }
}

//**********************************************************
// For each string user input,
// searchCourse will parse the string to several single words,
// then search each word in the N-ary tree.
// return correspondent sets of Course objects,
// then find the intersection of all sets.
//**********************************************************
LinkedList<Course> Process::searchCourse(string userInput){
    stringstream userInStr(userInput);
    string word;
    LinkedList<Course> rawResult;
    unordered_set<Course*, Course::hash> tempResult1, tempResult2;
    unordered_set<Course*, Course::hash> intersectionSet;
    unordered_set<Course*, Course::hash>:: iterator Is;
    
    if (userInStr >> word){
        // convert string to uppercase
        transform(word.begin(), word.end(), word.begin(), ::toupper);
        // save the result set to tempResult1
        tempResult1 = tree.findResultSet(tree.search(word));
    }
    // user input more than one word
    while (userInStr >> word){
        transform(word.begin(), word.end(), word.begin(), ::toupper);
        tempResult2 = tree.findResultSet(tree.search(word));
        
        // find the smaller set
        unordered_set<Course*, Course::hash>* smaller = (tempResult1.size() < tempResult2.size())? &tempResult1 : &tempResult2;
        unordered_set<Course*, Course::hash>* bigger = (tempResult1.size() < tempResult2.size())? &tempResult2 : &tempResult1;
        
        for (auto it = smaller->begin(); it != smaller->end(); it++){
            Is = bigger->find(*it);
            // if course in tempResult1 is found in tempResult2
            // add the course ptr in the intersection set
            if(Is != bigger->end())
                intersectionSet.insert(*it);
        }
        tempResult1 = intersectionSet;
        
    }
    
    for (auto it = tempResult1.begin(); it!= tempResult1.end(); it++){
        
        Course* curCourse = *it;
        // For every course in the result set, update its frequency
        curCourse->updateFrequency();
        Course objCourse = **it;
        // Insert courses into a linked list
        rawResult.appendNode(objCourse); // rawResult collects unsorted results
    }
    
    return rawResult;
}

//**********************************************************
// sort the result based on searching frequency and course ID
//**********************************************************
void Process:: sortResult(ListNode<Course>*& head){
    head = mergeSort(head);
}

//**********************************************************
// Print the result including course info and section info
//**********************************************************
void Process::print(const LinkedList<Course>& result){
    cout<<"\n**********- Course List - *************\n";
    cout<<"Result amount:"<< result.length() <<std::endl;
    result.displayList();
    std::cout << std::endl << std::endl;
    
}
#endif /* Process_h */
