#pragma once
#include <iostream>
#include <memory>

#include "merge.hpp"

/**
 * @brief Класс двусвязного списка, аналогичный std::list<T>
 * @author eyevievv
 * @attention Класс создан для проработки понимания стандартной библиотеки C++.
 * В дальнейших комментариях термин "список" относится к данному классу ```List```, а
 *      "список инициализации" к ```std::initializer_list<T>```
 */
template <typename T>
class List {
protected:
    /**
     * @name Узел (Node)
     * @brief Класс узла матрицы
     */
    struct Node {
        /// @brief Указатель на предыдущий узел
        Node* prevP = nullptr;

        /// @brief Указатель на следующий узел
        Node* nextP = nullptr;

        /// @brief Хранящиеся данные
        T data;

        /**
         * @brief Конструктор узла
         * @param data Хранящиеся данные
         * @param prevP Указатель на предыдущий узел
         * @param nextP Указатель на следующий узел
         */
        Node(const T& data, Node* prevP = nullptr, Node* nextP = nullptr)
            : data(data), prevP(prevP), nextP(nextP) {}

    };

    
    /**
     * @brief Функция обмена данными между ```copy``` и текущим списком
     * @param copy Список, с которым обменивается данными текущий
     */
    void swapThis(List& copy);

    /// @brief Указатель на первый укел списка
    Node* head = nullptr;

    /// @brief Указатель на последний укел списка
    Node* tail = nullptr;

    /// @brief Количество элементов списка
    size_t _size = 0;
    
public:

    /// @brief Заполняет поля класса базовыми значениями
    List();

    /**
     * @brief Заполненяет список ```count``` элементами значения ```alloc_elem```
     * @param count Количество элементов
     * @param alloc_elem Элемент для заполнения списка
     */
    List(size_t count, const T& alloc_elem);

    /**
     * @brief Заполненяет список значениями из ```std::initializer_list<T>```
     * @param initList Список инициализации
     */
    List(std::initializer_list<T> initList);

    /**
     * @brief Заполняет список с помощью итераторов
     * @param from Итератор на первый принимаемый элемент
     * @param to Итератор на последний принимаемый элемент
     */
    List(typename List<T>::Iterator from, typename List<T>::Iterator to);


    /// правило пяти

    /// @brief Дектруктор класса
    ~List();

    /// @brief Конструктор копирования (глубинное)
    /// @param other Копируемый список
    List(const List<T>& other);

    /// @brief Контруктор перемещения
    /// @param other Перемещаемый объект
    List(List<T>&& other);

    /// @brief Оператор копирующего присваивания
    /// @param other Копируемый список
    /// @return Ссылка на текущий список
    List<T>& operator=(const List<T>& other);

    /// @brief Оператор перемещающего присваивания
    /// @param other Перемещаемый список
    /// @return Ссылка на текущий список
    List<T>& operator=(List<T>&& other);

    /// @brief Двунаправленный итератор для обхода списка
    struct Iterator {
        friend class List;
        
        /// @brief Конструирование на основе узла
        /// @param node Указатель на узел
        explicit Iterator(Node* node) : node(node) {}
        
        /// @brief Оператор сложения; сдвиг на ```shift``` элементов влево
        /// @param shift На сколько элементов сдвинуть итератор влево
        /// @return Итератор, указывающий на элемент в позиции ``` позиция текущего узла + shift```
        /// @exception При попытке выйти за пределы списка
        Iterator operator+(size_t shift) const;
        
        /// @brief Оператор вычитания; сдвиг на ```shift``` элементов вправо
        /// @param shift На сколько элементов сдвинуть итератор вправо
        /// @return Итератор, указывающий на элемент в позиции ``` позиция текущего узла - shift```
        /// @exception При попытке выйти за пределы списка
        Iterator operator-(size_t shift) const;

        
        /// @brief Пре-инктрементный сдвиг на один элемент влево
        /// @return Итератор, указывающий на следующий элемент
        Iterator& operator++();
        
        /// @brief Пост-инктрементный сдвиг на один элемент влево
        /// @return Итератор, указывающий на следующий элемент
        Iterator operator++(int);
        
        
        /// @brief Пре-инктрементный сдвиг на один элемент вправо
        /// @return Итератор, указывающий на следующий элемент
        Iterator& operator--();
        
        /// @brief Пост-инктрементный сдвиг на один элемент вправо
        /// @return Итератор, указывающий на следующий элемент
        Iterator operator--(int);
        
        /// @brief Оператор копирующего присваиваний
        /// @param it Копируемый итератор
        /// @return Ссылка на текущий итератор
        Iterator& operator=(const Iterator& it);

        
        /// @brief Сравнение двух итераторов (указателей на их элементы)
        /// @param other Сравниваемый итератор
        /// @return Результат сравнения
        bool operator==(const Iterator& other) const;
        
        /// @brief Проверка на неравенство двух итераторов (указателей на их элементы)
        /// @param other Сравниваемый итератор
        /// @return Результат сравнения
        bool operator!=(const Iterator& other) const;

        /// @brief Даёт доступ к элементу, на который указывает итератор
        /// @return Элемент, на который указывает итератор
        T operator*();
    
        /// @brief Даёт доступ к указателю на текущий узел извне
        /// @return Указатель на текущий узел
        Node* getNodePtr() const {return node;}
    
    protected:
        /// @brief Текущий узел
        Node* node = nullptr;
    };
    

    /// @brief Инициализация списка через ```std::initializer_list<T>```
    /// @param initList Список инициализации
    /// @return Ссылка на текущий список
    List<T>& operator=(std::initializer_list<T> initList);
    
    /// @brief Поэлементное сравнение двух списков 
    /// @param other Сравниваемый элемент
    /// @return Результат сравнения
    bool operator==(const List& other) const;
    
    /// @brief Поэлементная проверка на неравенство двух списков 
    /// @param other Сравниваемый элемент
    /// @return Результат сравнения 
    bool operator!=(const List& other) const;


    /// @brief Доступ к первому элементу списка
    /// @return Первый элемент
    T front() const;

    /// @brief Доступ к последнему элементу списка
    /// @return Последний элемент
    T back() const;

    /// @brief Добавления в начало списка
    /// @param data Добавляемые данные
    void push_front(const T& data);
    
    /// @brief Добавления в конец списка
    /// @param data Добавляемые данные
    void push_back(const T& data);
    
    /// @brief Удаление из начала списка
    void pop_front();
    
    /// @brief Удаление из конца списка
    void pop_back();


    /// @brief Вставка элемента в позицию
    /// @param pos Итератор, указывающий на позицию для вставки
    /// @param value Вставляемое значение
    void insert(const Iterator& pos, const T& value);

    /// @brief Вставка нескольких элементов в позицию
    /// @param pos Итератор, указывающий на позицию для вставки
    /// @param initList Вставляемые значения
    void insert(const Iterator& pos, std::initializer_list<T> initList);

    /// @brief Удаление элемента в позиции
    /// @param pos Позиция удаляемого элемента
    /// @return Итератор на следующий элемент
    Iterator erase(const Iterator& pos);    
    
    /// @brief Удаление элементов в диапазоне [```first```, ```last```)
    /// @param first Первый удаляемый элемент
    /// @param last Элемент, до которого идёт удаление
    /// @return Итератор на элемент last
    Iterator erase(const Iterator& first, const Iterator& last);
    

    /// @brief Соединение списков копированием
    /// @param other Добавляемый в конец список
    void merge(const List<T>& other);
    
    /// @brief Соединение списков перемещением
    /// @param other Добавляемый в конец список
    void merge(List<T>&& other);
    
    /// @brief Сортирует элементов в списке 
    /// @details Используется сортировка слиянием
    void sort();
    
    /// @brief Оборачиваени списка (элементы в обратном порядке)
    void reverse();

    /// @brief Удаляет все элементы списка 
    void clear();

    /// @brief Проверка на наличие элементов в списке
    /// @return ```true```, если список пустой, иначе ```false```
    bool empty() const;
    
    /// @brief Возвращает размер списка
    /// @return Количество элементов списка
    size_t size() const;    

    /// @brief Возвращает итератор на первый элемент списка
    /// @return Итератор на первый элемент списка
    Iterator begin() const;
    
    /// @brief Возвращает итератор на последний элемент списка
    /// @return Итератор на последний элемент списка
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
    if (this == &other) return true;
    if (size() != other.size()) return false;
    if (size() == 0 && other.size() == 0) return true;
    
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
    if (pos == begin()) {
        push_front(value);
    }
    else if (pos == end()) {
        push_back(value);
    }
    else {
        Iterator prev_node_iter = pos-1;
        Iterator next_node_iter = pos;

        Node* new_node = new Node(value, prev_node_iter.node, next_node_iter.node);
        prev_node_iter.node->nextP = new_node;
        next_node_iter.node->prevP = new_node;
        _size++;
    }
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
    if (pos.getNodePtr() == nullptr) {
        throw std::out_of_range("Invalid erasing");
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
