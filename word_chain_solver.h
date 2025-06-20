#pragma once
#ifndef WORD_CHAIN_SOLVER_H
#define WORD_CHAIN_SOLVER_H
#include <string>
using namespace std;
// класс для узла  списка
template <typename T>
class Node 
{
public:
    T data;         
    Node* next;     
    Node(const T& data) : data(data), next(nullptr) {}
};

// класс для реализации  списка
template <typename T>
class MyList 
{
private:
    Node<T>* head; 
    Node<T>* tail;  
    size_t size;    

public:
    MyList() : head(nullptr), tail(nullptr), size(0) {}
    ~MyList();
    void push_back(const T& value);
    bool empty() const { return size == 0; }
    size_t getSize() const { return size; }
    void remove_if(bool (*predicate)(const T&));
    // Класс итератора для списка
    class Iterator 
    {
    private:
        Node<T>* current;  
    public:
        // Конструктор инициализирует итератор с узла
        Iterator(Node<T>* node) : current(node) {}
        Iterator& operator++() { current = current->next; return *this; }
        bool operator!=(const Iterator& other) const { return current != other.current; }
        T& operator*() { return current->data; }
        const T& operator*() const { return current->data; }
    };

   
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }

  
    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }
};

// класс для реализации двусторонней очереди
template <typename T>
class MyDeque
{
private:
    Node<T>* front; 
    Node<T>* back; 
    size_t size;     

public:
    MyDeque() : front(nullptr), back(nullptr), size(0) {}
    ~MyDeque();
    void push_back(const T& value);
    bool empty() const { return size == 0; }
    size_t getSize() const { return size; }
    T& front_element() { return front->data; }
    const T& front_element() const { return front->data; }
    T& back_element() { return back->data; }
    const T& back_element() const { return back->data; }

    // Класс итератора для очереди
    class Iterator 
    {
    private:
        Node<T>* current;  
    public:
        Iterator(Node<T>* node) : current(node) {}
        Iterator& operator++() { if (current) current = current->next; return *this; }
        bool operator!=(const Iterator& other) const { return current != other.current; }
        T& operator*() { return current->data; }
        const T& operator*() const { return current->data; }
    };

    
    Iterator begin() { return Iterator(front); }
    Iterator end() { return Iterator(nullptr); }
    Iterator begin() const { return Iterator(front); }
    Iterator end() const { return Iterator(nullptr); }
};

//  класс для реализации динамического массива
template <typename T>
class MyVector 
{
private:
    T* data;            
    size_t capacity;    
    size_t current_size; 

    // Вспомогательная функция для увеличения размера массива
    void resize(size_t new_capacity) 
    {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < current_size; ++i)
        {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    using iterator = T*;
    using const_iterator = const T*;
    MyVector() : data(new T[1]), capacity(1), current_size(0) {}
    ~MyVector() { delete[] data; }

    void push_back(const T& value)
    {
        if (current_size == capacity)
        {
            resize(capacity * 2);  // Увеличиваем емкость при необходимости
        }
        data[current_size++] = value;
    }

 
    size_t size() const { return current_size; }
    bool empty() const { return current_size == 0; }
    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }

   
    iterator begin() { return data; }
    iterator end() { return data + current_size; }
    const_iterator begin() const { return data; }
    const_iterator end() const { return data + current_size; }
};

// Класс для решения задачи
class WordChainSolver
{
private:
    MyList<string> words;  
    // Получение последней буквы слова
    char getLastChar(const string& word) const;
    // Проверка валидности цепочки слов
    bool isValidChain(const MyDeque<string>& chain) const;
    // Поиск валидной перестановки слов
    bool findValidPermutation(MyDeque<string>& resultChain);

public:
    WordChainSolver(const MyList<string>& inputWords);
    bool solve(MyDeque<string>& resultChain);
};

bool isRussianWord(const string& word);
bool validateInput(const string& input);

#endif // WORD_CHAIN_SOLVER_H
