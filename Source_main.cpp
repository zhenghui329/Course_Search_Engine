//
//  2019 Winter 22C Group_Project
//
//  Topic: N-ary Tree（Course searching）
//  This Program searches for all CIS courses in De Anza College.
//  The information of the courses is stored in a N-ary Tree.
//  The user is able to search courses by entering the course name(or part of a course name).
//  The results will provide full details  of the course, including section info.
//
//  Group member: (Alan)Lee Sing Chan Yau, Dennis Zhao, Yue Tan, Zhenghui Li, Anthony Tran

#include <iostream>
#include "NAryTree.h"
#include "Course.h"
#include "Process.h"
#include "LinkedList.h"

using namespace std;

int main(int argc, const char * argv[])
{
    bool stop = false;
    string choice;
    char input;
    string userInput;
    
    //Pulling Data and Building Tree
    LinkedList<Course> courseList;
    Process test;
    test.readFile(courseList);
    test.buildTree(courseList);
    LinkedList<Course> rawResult;
    
    //Display options and ask for what user would like to do
    cout << "===================================================================\n";
    cout << "This is a program to search for De Anza Computer Science Courses.\n";
    cout << "===================================================================\n";
    while (stop == false){
        cout << "What would you like to do?\n";
        cout << "1: Search for classes.\n";
        cout << "2: Quit program.\n";
        cout << "Enter your input here: ";
        cin >> choice;
        input = choice[0];
        
        if(input =='1'){
            cout << "Enter the word you would like to search: ";
            cin.ignore();
            getline(cin, userInput);
            //Code to grab data from tree
            rawResult = test.searchCourse(userInput);
            
            if(rawResult.head == nullptr){
                cout<<"No course record!\n";
            }else{
                test.sortResult(rawResult.head);
                test.print(rawResult);
            }
        }
        else if(input == '2'){
            stop = true;
            break;
        }
        else{
            cout << "ERROR: Please try another input.\n";
        }
        cout << endl;
    }
    return 0;
}
