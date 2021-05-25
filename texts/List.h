#pragma once

#include<iostream>

using namespace std;


template<class T>
class listIterator;



template<class T>
struct Link {
    T value;
    Link<T>* prev;
    Link<T>* next;

    Link(T val = (T)0, Link<T>* p = nullptr, Link<T>* n = nullptr) : value(val), prev(p), next(n) {};
};

template<class T>
class List {
private:
    Link<T>* first;
    Link<T>* last;
    Link<T>* afterLast;
    int size;

public:
    List();
    List(const List<T>& l);
    ~List();

    List<T>& operator=(const List<T>& l);

    const T& front() const;
    const T& back() const;

    listIterator<T> begin() const;
    listIterator<T> end() const;

    bool empty() const;
    int getSize() const;

    listIterator<T> insert(const listIterator<T>& pos, const T& l);
    listIterator<T> erase(const listIterator<T>& pos);
    void push_back(const T& l);
    void pop_back();
    void push_front(const T& l);
    void pop_front();

    template<class T>
    friend ostream& operator<<(ostream& stream, const List<T>& x);

};

template<class T>
List<T>::List()
{
    first = nullptr;
    last = nullptr;
    Link<T>* link = new Link<T>((T)0, nullptr, nullptr);
    afterLast = link;
    size = 0;
}

template<class T>
List<T>::List(const List<T>& l)
{
    first = nullptr;
    last = nullptr;
    Link<T>* link = new Link<T>(0, nullptr, nullptr);
    afterLast = link;
    size = 0;
    Link<T>* tmpLink = l.first;
    while (tmpLink != l.afterLast) {
        push_back(tmpLink->value);
        tmpLink = tmpLink->next;
    }
}


template<class T>
List<T>::~List()
{
    while (!empty()) {
        this->pop_back();
    }
    delete afterLast;
}

template<class T>
List<T>& List<T>::operator=(const List<T>& l) {
    if (first != l.first) {
        while (!empty()) {
            this->pop_back();
        }
    }
    Link<T>* tmpLink = l.first;
    while (tmpLink != l.afterLast) {
        push_back(tmpLink->value);
        tmpLink = tmpLink->next;
    }
    return *this;
}

template<class T>
const T& List<T>::front() const
{
    if (empty()) throw logic_error("list_is_empty");
    return first->value;
}

template<class T>
const T& List<T>::back() const
{
    if (empty()) throw logic_error("list_is_empty");
    return last->value;
}

template<class T>
listIterator<T> List<T>::begin() const {
    listIterator<T> iter;
    if (size != 0) iter.currLink = first;
    else iter.currLink = afterLast;
    return iter;
}

template<class T>
listIterator<T> List<T>::end() const {
    listIterator<T> iter;
    iter.currLink = afterLast;
    return iter;
}

template<class T>
bool List<T>::empty() const
{
    if (first == nullptr) return true;
    return false;
}

template<class T>
int List<T>::getSize() const
{
    return size;
}

template<class T>
listIterator<T> List<T>::insert(const listIterator<T>& pos, const T& l) {
    listIterator<T> iter;
    if (empty() || pos.currLink == first) {
        push_front(l);
        iter.currLink = first;
    }
    else if (pos.currLink == afterLast) {
        push_back(l);
        iter.currLink = last;
    }
    else {
        Link<T>* link = new Link<T>(l, pos.currLink->prev, pos.currLink);
        pos.currLink->prev->next = link;
        pos.currLink->prev = link;
        iter.currLink = link;
        size++;
    }
    return iter;
}

template<class T>
listIterator<T> List<T>::erase(const listIterator<T>& pos) {
    listIterator<T> iter;
    if (empty()) throw logic_error("List is empty");
    if (pos.currLink == afterLast) throw logic_error("Iterator outside the list boundary");
    if (pos.currLink == first) {
        pop_front();
        iter.currLink = first;
    }
    else if (pos.currLink == last) {
        pop_back();
        iter.currLink = last;
    }
    else {
        Link<T>* tmpLink = pos.currLink;
        tmpLink->prev->next = tmpLink->next;
        tmpLink->next->prev = tmpLink->prev;
        iter.currLink = tmpLink->next;
        size--;
        delete tmpLink;
    }
    return iter;
}

template<class T>
void List<T>::push_back(const T& l)
{
    Link<T>* link = new Link<T>{ l, last, afterLast };
    afterLast->prev = link;
    if (size == 0) {
        first = link;
        last = link;
    }
    else {
        last->next = link;
        last = link;
    }
    size++;
}

template<class T>
void List<T>::pop_back()
{
    if (empty()) throw logic_error("list_is_empty");
    if (size == 1) {
        delete last;
        last = nullptr;
        first = nullptr;
        afterLast->prev = nullptr;
    }
    else {
        Link<T>* tmpLink = last->prev;
        delete tmpLink->next;
        last = tmpLink;
        last->next = afterLast;
        afterLast->prev = last;
    }
    size--;
}

template<class T>
void List<T>::push_front(const T& l)
{
    Link<T>* link = new Link<T>{ l, nullptr, first };
    if (size == 0) {
        first = link;
        last = link;
        last->next = afterLast;
        afterLast->prev = last;

    }
    else {
        first->prev = link;
        first = link;
    }
    size++;
}

template<class T>
void List<T>::pop_front()
{
    if (empty()) throw logic_error("list_is_empty");
    if (size == 1) {
        delete first;
        first = nullptr;
        last = nullptr;
        afterLast->prev = nullptr;
    }
    else
    {
        Link<T>* tmpLink = first->next;
        delete tmpLink->prev;
        tmpLink->prev = nullptr;
        first = tmpLink;
    }
    size--;
}

template<class T>
ostream& operator<<(ostream& ostr, const List<T>& list)
{
    cout << '(';
    Link<T>* tmpLink = list.first;
    while (tmpLink != list.afterLast) {
        if (tmpLink->next != list.afterLast) cout << tmpLink->value << ", ";
        else cout << tmpLink->value;
        tmpLink = tmpLink->next;
    }
    cout << ')';
    return ostr;
}



template<class T>
class listIterator {
    friend class List<T>;
private:
    Link<T>* currLink;
public:
    listIterator();

    listIterator& operator=(const listIterator& iter);

    bool operator==(const listIterator& m) const;
    bool operator!=(const listIterator& m) const;

    bool hasNext() const;
    bool hasPrev() const;

    T& getValue() const;

    void next();
    void prev();
};

template<class T>
listIterator<T>::listIterator() : currLink(nullptr) {}

template<class T>
listIterator<T>& listIterator<T>::operator=(const listIterator& iter) {
    currLink = iter.currLink;
    return *this;
}

template<class T>
bool listIterator<T>::operator==(const listIterator& m) const {
    return (currLink == m.currLink);
}

template<class T>
bool listIterator<T>::operator!=(const listIterator& m) const {
    return (currLink != m.currLink);
}

template<class T>
bool listIterator<T>::hasNext() const {
    return currLink->next != nullptr;
}

template<class T>
bool listIterator<T>::hasPrev() const {
    return currLink->prev != nullptr;
}

template<class T>
T& listIterator<T>::getValue() const {
    if (!hasNext()) throw logic_error("Going outside the list");
    return currLink->value;
}

template<class T>
void listIterator<T>::next() {
    if (!hasNext()) throw logic_error("Going outside the list");
    currLink = currLink->next;
}

template<class T>
void listIterator<T>::prev() {
    if (!hasPrev()) throw logic_error("Going outside the list");
    currLink = currLink->prev;
}