// A class template for holding a linked list.
// The node type is also a class template.
//
// Write by Dennis Zhuo & (Alan)Lee Sing Chan Yau
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

//*********************************************
// The ListNode class creates a type used to  *
// store a node of the linked list.           *
//*********************************************
template <class T>
class ListNode
{
public:
    T value;           // Node value
    ListNode<T> *next; // Pointer to the next node
    ListNode<T> *previous; // Poiner to previous node
    
    // Constructor
    ListNode (const T& nodeValue) : value(nodeValue)
    {
        next = nullptr;
        previous = nullptr;
    }
};

//*********************************************
// LinkedList class                           *
//*********************************************
template <class T>
class LinkedList
{
public:
    ListNode<T> *head;   // List head pointer
    ListNode<T> *tail;
    int size;
    // Constructor
    LinkedList()
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    
    // Destructor
    ~LinkedList();
    
    // Linked list operations
    void appendNode(const T&);
    void insertNode(const T&);
    void deleteNode(const T&);
    void displayList() const;
    void removeAfter(ListNode<T> *curNode);
    ListNode<T>* search(const T&);
    bool isEmpty(){return head == nullptr;}
    LinkedList<T>& operator=(const LinkedList<T> &other);
    // copy constructor
    LinkedList<T> (const LinkedList<T> &other);
    int length() const {return size;}
    // Accesser function
//    ListNode<T>* getTail() const
//    {
//        return tail;
//    }
//    
//    ListNode<T>* getHead() const
//    {
//        return head;
//    }
    
};

//**************************************************
// appendNode appends a node containing the value  *
// pased into newValue, to the end of the list.    *
//**************************************************

template <class T>
void LinkedList<T>::appendNode(const T& newValue)
{
    ListNode<T> *newNode;  // To point to a new node
    ListNode<T> *nodePtr;  // To move through the list
    
    // Allocate a new node and store newValue there.
    newNode = new ListNode<T>(newValue);
    size++;
    // If there are no nodes in the list
    // make newNode the first node.
    if (!head)
    {
        head = newNode;
        tail = newNode;
    }
    else  // Otherwise, insert newNode at end.
    {
        // Initialize nodePtr to head of list.
        nodePtr = head;
        
        // It is designed to not append any duplicate
        // Specifically designed for the lab
        while (nodePtr->next)
        {
            if(nodePtr->value == newValue)
            {
                return;
            }
            nodePtr = nodePtr->next;
        }
        
        tail->next = newNode;
        newNode->previous = tail;
        tail = tail->next;
    }
}

//**************************************************
// displayList shows the value stored in each node *
// of the linked list pointed to by head.          *
//**************************************************
template <class T>
void LinkedList<T>::displayList() const
{
    ListNode<T> *nodePtr;  // To move through the list
    
    // Position nodePtr at the head of the list.
    nodePtr = head;
    
    // While nodePtr points to a node, traverse
    // the list.
    while (nodePtr)
    {
        // Display the value in this node.
        std::cout << nodePtr->value;
        
        // Move to the next node.
        nodePtr = nodePtr->next;
    }
}

//**************************************************
// The insertNode function inserts a node with     *
// newValue copied to its value member.            *
//**************************************************
template <class T>
void LinkedList<T>::insertNode(const T& newValue)
{
    ListNode<T> *newNode;                // A new node
    ListNode<T> *nodePtr;                // To traverse the list
    ListNode<T> *previousNode = nullptr; // The previous node

    // Allocate a new node and store newValue there.
    newNode = new ListNode<T>(newValue);
    size++;
    // If there are no nodes in the list
    // make newNode the first node
    if (!head)
    {
        head = newNode;
        newNode->next = nullptr;
    }
    else  // Otherwise, insert newNode
    {
        // Position nodePtr at the head of list.
        nodePtr = head;

        // Initialize previousNode to nullptr.
        previousNode = nullptr;

        // Skip all nodes whose value is less than newValue.
        while (nodePtr != nullptr && nodePtr->value < newValue)
        {
            previousNode = nodePtr;
            nodePtr = nodePtr->next;
        }

        // If the new node is to be the 1st in the list,
        // insert it before all other nodes.
        if (previousNode == nullptr)
        {
            head = newNode;
            newNode->next = nodePtr;
        }
        else  // Otherwise insert after the previous node.
        {
            previousNode->next = newNode;
            newNode->next = nodePtr;
        }
    }
}

//*****************************************************
// The deleteNode function searches for a node        *
// with searchValue as its value. The node, if found, *
// is deleted from the list and from memory.          *
//*****************************************************
template <class T>
void LinkedList<T>::deleteNode(const T& searchValue)
{
    ListNode<T> *nodePtr;       // To traverse the list
    ListNode<T> *previousNode;  // To point to the previous node
    
    // If the list is empty, do nothing.
    if (!head)
        return;
    
    // Determine if the first node is the one.
    if (head->value == searchValue)
    {
        nodePtr = head->next;
        delete head;
        head = nodePtr;
    }
    else
    {
        // Initialize nodePtr to head of list
        nodePtr = head;
        
        // Skip all nodes whose value member is
        // not equal to num.
        while (nodePtr != nullptr && nodePtr->value != searchValue)
        {
            previousNode = nodePtr;
            nodePtr = nodePtr->next;
        }
        
        // If nodePtr is not at the end of the list,
        // link the previous node to the node after
        // nodePtr, then delete nodePtr.
        if (nodePtr)
        {
            previousNode->next = nodePtr->next;
            delete nodePtr;
        }
    }
    size--;
}

//*****************************************************
// Search function search for a node.
//*****************************************************
template <class T>
ListNode<T>* LinkedList<T> :: search(const T& searchValue)
{
    ListNode<T> *nodePtr;       // To traverse the list
    if(!head)
    {
        return nullptr;
    }
    
    nodePtr = head;
    while (nodePtr != nullptr)
    {
        if(nodePtr->value == searchValue)
        {
            return nodePtr;
        }
        nodePtr = nodePtr->next;
    }
    
    return nullptr;
}

//*****************************************************
// The removeAfter function remove a node after the
// given current node.
// If the current node is nullptr, remove head.
//*****************************************************
template <class T>
void LinkedList<T>::removeAfter(ListNode<T> *curNode) {
    ListNode<T> *sucNode;
    if (curNode == nullptr && head != nullptr) { // remove head
        ListNode<T> *temp = head;
        sucNode = head->next;
        head = sucNode;
        if (sucNode == nullptr) { // removed last item
            tail = nullptr;
        }else{
            sucNode->previous = nullptr;
        }
        delete temp;
        size--;
    } else if (curNode->next != nullptr) {
        ListNode<T> *temp = curNode->next;
        sucNode = curNode->next->next;
        curNode->next = sucNode;
        if (sucNode == nullptr) { // Removed tail
            tail = curNode;
        }else{
            sucNode->previous = curNode;
        }
        delete temp;
        size--;
    }
}

//**************************************************
// Overload assignment operator                                
//**************************************************
template <class T>
LinkedList<T>& LinkedList<T> :: operator=(const LinkedList<T> &other)
{
    if (this == &other)
    {
        return *this;
    }
    
    this->~LinkedList<T>();
    
    ListNode<T> *otherHead = other.head;
    while (otherHead != nullptr)
    {
        this->appendNode(otherHead->value);
        otherHead = otherHead->next;
    }
    
    return *this;
    
}

//**************************************************
// Copy constructor                                *
//**************************************************
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &other)
{
    ListNode<T> *otherHead = other.head;
    while (otherHead != nullptr)
    {
        this->appendNode(otherHead->value);
        otherHead = otherHead->next;
    }
}


//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
//**************************************************
template <class T>
LinkedList<T>::~LinkedList()
{
    // std :: cout << "Destructor called" << std :: endl;
    
    ListNode<T> *nodePtr;   // To traverse the list
    ListNode<T> *nextNode;  // To point to the next node
    
    // Position nodePtr at the head of the list.
    nodePtr = head;
    
    // While nodePtr is not at the end of the list...
    while (nodePtr != nullptr)
    {
        // std :: cout << "The one being deleted:------------------------- \n " << nodePtr->value;
        
        // Save a pointer to the next node.
        nextNode = nodePtr->next;
        
        // Delete the current node.
        delete nodePtr;
        
        // Position nodePtr at the next node.
        nodePtr = nextNode;
    }
    
    head = nullptr;
    tail = nullptr;
    size = 0;
}


#endif
