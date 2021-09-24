//
//  Sort.h
//  groupProject
//
//  Created by Anthony Tran on 3/18/19.
//

#ifndef Sort_h
#define Sort_h

#include "LinkedList.h"
#include "Course.h"
#include <iostream>

using namespace std;

//Bool function that compares the two parameter nodes and returns true if
//the first parameter node is larger than the second parameter node
//Otherwise the function returns false
bool compare(ListNode<Course> *first, ListNode<Course> *second)
{
    if(first->value.getCourseID()> second->value.getCourseID())
        return true;
    else
        return false;
}


//Splits Linked List in Half
ListNode<Course> *split(ListNode<Course> *head)
{
    //    if(head->next == nullptr){
    //        return head;
    //    }
    ListNode<Course> *fast = head;
    ListNode<Course> *slow = head;
    while (fast->next && fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    ListNode<Course> *temp = slow->next;
    slow->next = nullptr;
    return temp;
}


//Merges the split Linked List back together while ordering it
//by frequency and Course ID
ListNode<Course> *merge(ListNode<Course> *first, ListNode<Course> *second)
{
    // If first linked list is empty, retur
    if (!first)
        return second;
    
    // If second linked list is empty
    if (!second)
        return first;
    
    // Pick the smaller value
    //If first value is greater than second value
    if (first->value.getFrequency() > second->value.getFrequency())
    {
        first->next = merge(first->next,second);
        first->next->previous = first;
        first->previous = NULL;
        return first;
    }
    //If first value is equal to second value
    else if (first->value.getFrequency() == second->value.getFrequency())
    {
        if(compare(first, second))
        {
            second->next = merge(first,second->next);
            second->next->previous = second;
            second->previous = NULL;
            return second;
        }
        else
        {
            first->next = merge(first->next,second);
            first->next->previous = first;
            first->previous = NULL;
            return first;
        }
    }
    //If first value is less than second value
    else
    {
        second->next = merge(first,second->next);
        second->next->previous = second;
        second->previous = NULL;
        return second;
    }
}

//Merge sort function that recursively goes through list
//and returns sorted list.
ListNode<Course> *mergeSort(ListNode<Course> *head)
{
    if (!head || !head->next)
        return head;
    ListNode<Course> *second = split(head);
    
    // Recur for left and right halves
    head = mergeSort(head);
    second = mergeSort(second);
    
    // Merge the two sorted halves
    return merge(head,second);
}

#endif /* Sort_h */
