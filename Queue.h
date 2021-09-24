//
//  Queue.h
//  A class template of a queue that inherits from LinkedList class.
//  Write by Zhenghui Li

#ifndef Queue_h
#define Queue_h

#include "LinkedList.h"

template <typename T>
class Queue : public LinkedList<T> {
    // the list's head node being the queue's top
public:
    void push(T data);
    T pop();
    T peek();
    T top(){ return LinkedList<T>::head->value;}
    bool isEmpty();
};

template <typename T>
void Queue<T>::push(T data) {
    LinkedList<T>::appendNode(data); // Insert as list head (top of queue)
}

template <typename T>
T Queue<T>::pop() {
    T popedItem = LinkedList<T>::head->value;
    LinkedList<T>::removeAfter(nullptr);
    return popedItem;
}

template <typename T>
T Queue<T>::peek() {
    return LinkedList<T>::head->value;
}

template <typename T>
bool Queue<T>::isEmpty(){
    return LinkedList<T>::isEmpty();
}

#endif /* Queue_h */
