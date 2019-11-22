//
// Created by altair on 20.11.2019.
//

#ifndef STACKIMP_QUEUE_H
#define STACKIMP_QUEUE_H

#include "QueueException.h"

const int MAX_QUEUE = 100;

template<class T>
class Queue
{
public:
    Queue();                       

    bool isEmpty() const;           
    void enqueue(const T &newItem); 
    T dequeue();                    
    T peek() const;               
    int size() const;            

private:
    T items[MAX_QUEUE];             
    int front;                      
    int back;                       
    int count;                      
};

template<class T>
Queue<T>::Queue():front(0), back(MAX_QUEUE - 1), count(0)
{ 

}

template<class T>
bool Queue<T>::isEmpty() const
{ 

    return count == 0;
}

template<class T>
void Queue<T>::enqueue(const T &newItem)
{ 

    if (count == MAX_QUEUE)
        throw QueueException("QueueException: queue full on enqueue");
    else
    { 
        back = (back + 1) % MAX_QUEUE;
        items[back] = newItem;
        ++count;
    }
}

template<class T>
T Queue<T>::dequeue()
{ 

    if (isEmpty())
        throw QueueException("QueueException: empty queue, cannot dequeue");
    else
    { 
        T val = items[front];
        front = (front + 1) % MAX_QUEUE;
        --count;
        return val;
    }
}

template<class T>
T Queue<T>::peek() const
{ 

    if (isEmpty())
        throw QueueException("QueueException: empty queue, cannot getFront");
    else 
        return (items[front]);
}

template<class T>
int Queue<T>::size() const
{
    return count;
}

#endif //STACKIMP_QUEUE_H
