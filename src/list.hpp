#pragma once
#include <iostream>
#include <memory>

#include "merge.hpp"

template <typename T>
class List {
protected:
    struct Node {
        Node(const T& data, Node* prevP = nullptr, Node* nextP = nullptr)
            : data(data), prevP(prevP), nextP(nextP) {}
        Node* prevP = nullptr;
        Node* nextP = nullptr;
        T data;
    };
    
    void swapThis(List& copy);

    Node* head = nullptr;
    Node* tail = nullptr;
    size_t _size = 0;
    
public:
    explicit List();
    explicit List(size_t count, const T& alloc_elem);
    List(std::initializer_list<T> initList);
    List(typename List<T>::Iterator from, typename List<T>::Iterator to);

    /// правило пяти
    ~List();
    List(const List<T>& other);
    List(List<T>&& other);
    List<T>& operator=(const List<T>& other);
    List<T>& operator=(List<T>&& other);
    
    struct Iterator {
        friend class List;
        
        explicit Iterator(Node* node) : node(node) {}
        Iterator operator+(size_t shift) const;
        Iterator operator-(size_t shift) const;

        Iterator& operator++();
        Iterator operator++(int);
        
        Iterator& operator--();
        Iterator operator--(int);

        Iterator& operator=(const Iterator& it);

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

        T operator*();
    
        Node* getNodePtr() const {return node;}
    protected:
        Node* node = nullptr;
    };

    List<T>& operator=(std::initializer_list<T> initList);
    bool operator==(const List& other) const;
    bool operator!=(const List& other) const;

    T front() const;
    T back() const;

    void push_front(const T& data);
    void push_back(const T& data);

    void pop_front();
    void pop_back();

    void insert(const Iterator& pos, const T& value);
    void insert(const Iterator& pos, std::initializer_list<T> initList);

    Iterator erase(const Iterator& pos);    
    Iterator erase(const Iterator& first, const Iterator& last);
    
    void merge(const List<T>& other);
    void merge(List<T>&& other);
    void sort();
    void reverse();

    void clear();

    bool empty() const;
    size_t size() const;    

    Iterator begin() const;
    Iterator end() const;
};

template <typename T>
List<T>::List() : head(nullptr), tail(nullptr), _size(0) {}

template <typename T>
List<T>::List(size_t count, const T& alloc_elem) {
    for (size_t i = 0; i < count; ++i) {
        push_back(alloc_elem);
    }
}

template <typename T>
List<T>::List(std::initializer_list<T> initList) {
    for (const T& elem : initList) {
        push_back(elem);
    }
}

template <typename T>
List<T>::List(typename List<T>::Iterator from, typename List<T>::Iterator to) {
    for (auto it = from; it != to; ++it) {
        this->push_back(*it);
    }
}

template <typename T>
List<T>::~List()
{
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->nextP;
        delete current;
        current = next;
    }
    head = tail = nullptr;
    this->_size = 0;  
}

template <typename T>
List<T>::List(const List<T> &other) {
    // std::cout << "copy cons\n";
    if (other._size == 0) {
        return;
    }
    for (Iterator other_it = other.begin(); other_it != other.end(); ++other_it) {
        push_back(other_it.node->data);
    }
}

template <typename T>
List<T>::List(List<T>&& other) {
    // std::cout << "move cons\n";
    this->head = other.head;
    this->tail = other.tail;
    this->_size = other._size;

    other.head = nullptr;
    other.tail = nullptr;
    other._size = 0;
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& other) {
    // std::cout << "copy operator=\n";
    if (this != &other) {
        List<T> tmp(other);
        swapThis(tmp);
    }
    return *this;
}

template <typename T>
List<T>& List<T>::operator=(List<T>&& other) {
    // std::cout << "move operator=\n";
    if (this != &other) {
        this->clear();

        this->head = other.head;
        this->tail = other.tail;
        this->_size = other._size;

        other.head = nullptr;
        other.tail = nullptr;
        other._size = 0;        
    }
    return *this;
}

template <typename T>
void List<T>::swapThis(List& copy) {
    std::swap(this->head, copy.head);
    std::swap(this->tail, copy.tail);
    std::swap(this->_size, copy._size);
}

template <typename T>
List<T>& List<T>::operator=(std::initializer_list<T> initList) {
    *this = List<T>(initList);
    return *this;
}

template <typename T>
bool List<T>::operator==(const List& other) const {
    if (this == &other) {
        return true;
    }
    if (size() != other.size()) {
        return false;
    }
    auto this_it = begin();
    auto other_it = other.begin();
    while (this_it != end() && other_it != other.end()) {
        if (*this_it != *other_it) {
            return false;
        }
        ++this_it;
        ++other_it;
    }
    return true;
}

template <typename T>
bool List<T>::operator!=(const List& other) const {
    return !(*this == other); 
}
template <typename T>
T List<T>::front() const {
    if (!head) {
        throw std::out_of_range("List is empty!");
    }
    return head->data;
}

template <typename T>
T List<T>::back() const {
    if (!tail) {
        throw std::out_of_range("List is empty!");  
    }
    return tail->data;
}

template <typename T>
void List<T>::push_front(const T& data) {
    Node* new_node = new Node(data, nullptr, head);

    if (tail == nullptr) {
        tail = new_node;
    }
    else {
        head->prevP = new_node;
    }
    head = new_node;
    _size++;
}

template <typename T>
void List<T>::push_back(const T& data) {
    Node* new_node = new Node(data, tail);
    
    if (head == nullptr) {
        head = new_node;
    }    
    else {
        tail->nextP = new_node;
    }

    tail = new_node;
    this->_size++;
}

template <typename T>
void List<T>::pop_front() {
    if (!empty()) {
        erase(begin());
    }
    else {
        throw std::out_of_range("List is empty!");
    }
}

template <typename T>
void List<T>::pop_back() {
    if (!empty()) {
        erase(Iterator{tail});
    }
    else {
        throw std::out_of_range("List is empty!");
    }
}

template <typename T>
void List<T>::insert(const Iterator& pos, const T& value) {
    Iterator prev_node_iter = pos-1;
    Iterator next_node_iter = pos;

    Node* new_node = new Node(value, prev_node_iter.node, next_node_iter.node);
    prev_node_iter.node->nextP = new_node;
    next_node_iter.node->prevP = new_node;

    _size++;
}

template <typename T>
void List<T>::insert(const Iterator& pos, std::initializer_list<T> initList) {
    for (size_t i = 0; i < initList.size(); ++i) {
        insert(pos, *(initList.begin() + i));
    }
}

template <typename T>
typename List<T>::Iterator List<T>::erase(const Iterator& pos) {
    if (empty()) {
        throw std::out_of_range("Trying to erase in empty list!");
    }
    Node* node = pos.node;
    if (node != nullptr) {
        if (node->prevP != nullptr) { //если не первый
            node->prevP->nextP = node->nextP;
        }    
        else {
            head = node->nextP;
        }
        if (node->nextP != nullptr) { //если не последний
            node->nextP->prevP = node->prevP;
        }
        else {
            tail = node->prevP;
        }
        Iterator next_iter = Iterator(node->nextP);

        delete node;
        _size--;
        return next_iter;
    }
    else {
        throw std::out_of_range("Invalid erasing");
    }
}

template <typename T>
typename List<T>::Iterator List<T>::erase(const Iterator& first, const Iterator& last) {
    if (empty()) {
        throw std::out_of_range("Trying to erase in empty list!");
    }
    Iterator it = first;
    while (it != last) {
        it = erase(it);        
    }
    return it;
}

template <typename T>
void List<T>::merge(const List<T>& other) {
    if (this != &other) {
        List<T> tmp(other);
        merge(std::move(tmp));
    }
}

template <typename T>
void List<T>::merge(List<T>&& other) {
    if (!this->empty()) {
        this->tail->nextP = other.head;
        other.head->prevP = this->tail;
        this->tail = other.tail;
    }
    else {
        this->head = other.head;
        this->tail = other.tail;
    }

    this->_size += other._size;        

    other._size = 0;
    other.head = other.tail = nullptr;
}

template <typename T>
void List<T>::sort() {
    if (!empty()) {
        *this = mergeSort(*this);
    }
}

template <typename T>
void List<T>::reverse() {
    if (!empty()) {
        Node* current = head;
        while (current != nullptr) {
            std::swap(current->nextP, current->prevP);
            current = current->prevP;
        }
        std::swap(head, tail);
    }
}

template <typename T>
void List<T>::clear() {
    if (!empty()) {
        erase(begin(), end());
        if (_size != 0) {
            _size = 0;
        }
    }
}

template <typename T>
bool List<T>::empty() const {
    return this->_size == 0;
}

template <typename T>
size_t List<T>::size() const {
    return this->_size;
}

template <typename T>
typename List<T>::Iterator List<T>::begin() const {
    return Iterator(head);
}

template <typename T>
typename List<T>::Iterator List<T>::end() const {
    return Iterator(nullptr);
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator+(size_t shift) const {
    Iterator curr_it = *this;
    for (size_t i = 0; i < shift; ++i) {
        if (node->nextP != nullptr) {
            curr_it.node = curr_it.node->nextP;
        }
        else {
            throw std::out_of_range("Iterating+ out of range");
        }
    }
    return curr_it;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator-(size_t shift) const {
    Iterator curr_it = *this;
    for (size_t i = 0; i < shift; ++i) {
        if (node->prevP != nullptr) {
            curr_it.node = curr_it.node->prevP;
        }
        else {
            throw std::out_of_range("Iterating- out of range");
        }
    }
    return curr_it;
}

template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++() {
    this->node = this->node->nextP;
    return *this;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int) {
    Iterator new_it = *this;
    if (this->node) {
        this->node = this->node->nextP;
    }
    return new_it;
}


template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator--() {
    this->node = this->node->prevP;
    return *this;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator--(int) {
    Iterator new_it = *this;
    if (this->node->prevP != nullptr) {
        this->node = this->node->prevP;
    }
    return new_it;
}

template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator=(const Iterator& right) {
    if (right.node != this->node) {
         this->node = right.node;
    }
    return *this;
}

template <typename T>
bool List<T>::Iterator::operator==(const Iterator& other) const {
    return this->node == other.node;
}

template <typename T>
bool List<T>::Iterator::operator!=(const Iterator& other) const {
    return this->node != other.node;
}

template <typename T>
T List<T>::Iterator::operator*() {
    return this->node->data;
}
