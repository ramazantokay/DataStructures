#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <iostream>
#include "Node.hpp"

template <class T>
class LinkedList
{
public:
    LinkedList();
    LinkedList(const LinkedList &obj);

    ~LinkedList();

    Node<T> *getFirstNode() const; //
    Node<T> *getHead() const;
    Node<T> *getTail() const;
    int getNumberOfNodes();
    bool isEmpty(); //

    void insertAtTheFront(const T &data);
    void insertAtTheEnd(const T &data);
    void insertAfterGivenNode(const T &data, Node<T> *prev);

    void removeNode(Node<T> *node);
    void removeAllNodes();

    Node<T> *findNode(const T &data);

    void printAllNodes();
    void printReversed();

    LinkedList &operator=(const LinkedList &rhs);

private:
    Node<T> *head;
    Node<T> *tail;
};

template <class T>
LinkedList<T>::LinkedList()
{
    head = new Node<T>();
    tail = new Node<T>();
    head->next = tail;
    tail->prev = head;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList &obj)
{
    head = new Node<T>();
    tail = new Node<T>();
    head->next = tail;
    tail->prev = head;

    Node<T> *c = obj.getHead()->next;
    while (c)
    {
        insertAtTheEnd(c->element);
        c = c->next;

        if (c == obj.getTail())
        {
            break;
        }
    }
}

template <class T>
LinkedList<T>::~LinkedList()
{
    removeAllNodes();
    delete head;
    delete tail;
}

template <class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
    if (head->next != tail)
    {
        return head->next;
    }
    else
    {
        return NULL;
    }
}

template <class T>
Node<T> *LinkedList<T>::getHead() const
{
    return head;
}

template <class T>
Node<T> *LinkedList<T>::getTail() const
{
    return tail;
}

template <class T>
int LinkedList<T>::getNumberOfNodes()
{
    int size = 0;
    Node<T> *curr = getFirstNode();
    while (curr)
    {
        size++;
        curr = curr->next;
        if (curr == getTail())
        {
            break;
        }
    }
    return size;
}

template <class T>
bool LinkedList<T>::isEmpty()
{
    return getFirstNode() == NULL;
}

template <class T>
void LinkedList<T>::insertAtTheFront(const T &data)
{
    Node<T> *temp = new Node<T>(data, NULL, NULL);
    if (isEmpty())
    {
        head->next = temp;
        tail->prev = temp;
        temp->next = tail;
        temp->prev = head;
    }
    else
    {
        temp->next = head->next;
        head->next->prev = temp;
        head->next = temp;
        temp->prev = head;
    }
}

template <class T>
void LinkedList<T>::insertAtTheEnd(const T &data)
{
    Node<T> *temp = new Node<T>(data, NULL, NULL);
    if (isEmpty())
    {
        head->next = temp;
        tail->prev = temp;
        temp->next = tail;
        temp->prev = head;
    }
    else
    {
        tail->prev->next = temp;
        temp->prev = tail->prev;
        tail->prev = temp;
        temp->next = tail;
    }
}

template <class T>
void LinkedList<T>::insertAfterGivenNode(const T &data, Node<T> *prev)
{
    Node<T> *newNode = new Node<T>(data, prev, prev->next);
    prev->next->prev = newNode;
    prev->next = newNode;
}

template <class T>
void LinkedList<T>::removeNode(Node<T> *node)
{
    if (findNode(node->element) == NULL)
    {
        return;
    }

    Node<T> *temp = node;

    if (head->next == temp)
    {

        temp->next->prev = head;
        head->next = temp->next;
        delete temp;
    }
    else if (tail->prev == temp)
    {
        tail->prev = temp->prev;
        temp->prev->next = tail;
        delete temp;
    }
    else
    {

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
        /* code */
    }
}

template <class T>
void LinkedList<T>::removeAllNodes()
{

    Node<T> *curr = head->next, *temp;

    while (curr != tail)
    {
        temp = curr;
        curr = curr->next;

        delete temp;
    }
    head->next = tail;
    tail->prev = head;
}

template <class T>
Node<T> *LinkedList<T>::findNode(const T &data)
{
    /*  */
    Node<T> *curr = getHead()->next;
    while (curr != tail)
    {
        if (curr->element == data)
        {
            return curr;
            break;
        }

        curr = curr->next;
    }
    return NULL;
}

template <class T>
void LinkedList<T>::printAllNodes()
{

    Node<T> *curr = head->next;
    while (curr->next != NULL)
    {
        std::cout << curr->element << std::endl;
        curr = curr->next;
    }
}

template <class T>
void LinkedList<T>::printReversed()
{
    Node<T> *curr = tail->prev;
    while (curr->prev != NULL)
    {
        std::cout << curr->element << std::endl;
        curr = curr->prev;
    }
}

template <class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList &rhs)
{
    if (this != &rhs)
    {
        removeAllNodes();
        Node<T> *temp = rhs.getHead()->next;
        while (temp)
        {
            insertAtTheEnd(temp->element);
            temp = temp->next;
            if (temp == rhs.getTail())
            {
                break;
            }
        }
    }
    return *this;
}

#endif //LINKED_LIST_HPP
