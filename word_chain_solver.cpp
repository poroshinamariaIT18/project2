#include "word_chain_solver.h"  
#include <algorithm>           
#include <cctype>            
using namespace std;  

// Функция проверки, состоит ли слово только из русских букв
bool isRussianWord(const string& word) 
{
    if (word.empty()) return false;
    for (char c : word) 
    {
        c = tolower(c);
        if (!((c >= 'а' && c <= 'я') || c == 'ё' || c == 'ь')) 
        {
            return false;  
        }
    }
    return true;
}

// Функция валидации введенной пользователем строки
bool validateInput(const string& input) 
{
    if (input.empty()) return false;
    size_t start = 0;  
    size_t end = input.find(' ');  // Поиск первого пробела
    bool hasValidWords = false; 
    // Цикл по всем словам, разделенным пробелами
    while (end != string::npos)
    {
        string word = input.substr(start, end - start);
        // Проверка слова на валидность, если оно не пустое
        if (!word.empty() && !isRussianWord(word)) 
        {
            return false;  
        }
        
        if (!word.empty()) hasValidWords = true;
        
        start = end + 1;
        end = input.find(' ', start);
    }

    
    string lastWord = input.substr(start);
    if (!lastWord.empty())
    {
        if (!isRussianWord(lastWord)) return false;
        hasValidWords = true;
    }
    return hasValidWords;
}

// Деструктор MyList - освобождение памяти
template <typename T>
MyList<T>::~MyList() 
{
    Node<T>* current = head;
    while (current != nullptr)
    {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
}

// Добавление элемента в конец списка
template <typename T>
void MyList<T>::push_back(const T& value) 
{
    Node<T>* newNode = new Node<T>(value);
    if (tail == nullptr) 
    {
        head = tail = newNode;
    }
    else 
    {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

// Удаление элементов по условию
template <typename T>
void MyList<T>::remove_if(bool (*predicate)(const T&))
{
    Node<T>** current = &head;
    while (*current != nullptr) 
    {
        Node<T>* entry = *current;
        if (predicate(entry->data)) 
        {
            *current = entry->next;
            if (entry == tail) tail = *current ? tail : nullptr;
            delete entry;
            size--;
        }
        else 
        {
            current = &entry->next;
        }
    }
}

// Деструктор MyDeque - освобождение памяти
template <typename T>
MyDeque<T>::~MyDeque() 
{
    Node<T>* current = front;
    while (current != nullptr) 
    {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
}

// Добавление элемента в конец дека
template <typename T>
void MyDeque<T>::push_back(const T& value) 
{
    Node<T>* newNode = new Node<T>(value);
    if (back == nullptr)
    {
        front = back = newNode;
    }
    else 
    {
        back->next = newNode;
        back = newNode;
    }
    size++;
}

template class MyList<string>;   // Создание MyList для string
template class MyDeque<string>;  // Создание MyDeque для string
template class MyVector<string>; // Создание MyVector для string

// Конструктор WordChainSolver
WordChainSolver::WordChainSolver(const MyList<string>& inputWords)
    : words(inputWords)
{  // Инициализация списка слов и удаление пустых строк из списка
    words.remove_if([](const string& s) { return s.empty(); });
}

// Получение последнего значимого символа слова
char WordChainSolver::getLastChar(const string& word) const 
{
    char last = word.back();
    if (last == 'ь' && word.size() > 1) 
    {
        last = word[word.size() - 2];
    }
    return tolower(last);
}

// Проверка валидности цепочки слов
bool WordChainSolver::isValidChain(const MyDeque<string>& chain) const 
{
    if (chain.empty()) return false;
    // Итераторы для последовательного прохода по цепочке
    auto it = chain.begin();
    auto next_it = it;
    ++next_it;
    // Проверка последовательных пар слов
    while (next_it != chain.end()) 
    {
        if (getLastChar(*it) != tolower((*next_it)[0]))
        {
            return false; 
        }
        ++it;
        ++next_it;
    }

    // Проверка замкнутости цепочки 
    return tolower(chain.front_element()[0]) == getLastChar(chain.back_element());
}

// Поиск валидной перестановки слов
bool WordChainSolver::findValidPermutation(MyDeque<string>& resultChain)
{
    // Временный вектор для перестановок
    MyVector<string> tempVector;
    for (const auto& word : words) 
    {
        tempVector.push_back(word);
    }
    sort(tempVector.begin(), tempVector.end());
    do 
    {
        MyDeque<string> currentChain;
        for (const auto& word : tempVector) 
        {
            currentChain.push_back(word);
        }
      
        if (isValidChain(currentChain))
        {
            resultChain = currentChain;
            return true;  
        }
    } while (next_permutation(tempVector.begin(), tempVector.end()));

    return false;
}
bool WordChainSolver::solve(MyDeque<string>& resultChain) 
{
    return findValidPermutation(resultChain);
}
