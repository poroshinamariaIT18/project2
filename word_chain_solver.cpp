#include "word_chain_solver.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>

using namespace std;

// получение последнего значимого символа в слове (игнорируя мягкий знак в конце)
char WordChainSolver::getLastChar(const string& word) const
{
    char last = word.back();
    if (last == 'ь' && word.size() > 1)
    {
        last = word[word.size() - 2];
    }
    return tolower(last); 
}

// Проверка, является ли цепочка слов подходящей
bool WordChainSolver::isValidChain(const deque<string>& chain) const
{
    if (chain.empty()) return false; 
    // Проверяем последовательное соответствие слов в цепочке
    for (size_t i = 0; i < chain.size() - 1; ++i)
    {
        char last = getLastChar(chain[i]); 
        char first = tolower(chain[i + 1][0]); 
        if (last != first) {
            return false; 
        }
    }

    // Проверяем условие замкнутости цепочки (первая буква первого слова = последняя буква последнего слова)
    char first_word_first = tolower(chain.front()[0]);
    char last_word_last = getLastChar(chain.back());
    return first_word_first == last_word_last;
}

// Поиск подходящей перестановки слов методом полного перебора
bool WordChainSolver::findValidPermutation(deque<string>& resultChain)
{
    // Создаем временный вектор из списка слов для перестановок
    vector<string> tempVector(words.begin(), words.end());
    sort(tempVector.begin(), tempVector.end()); 

    do
    {
        deque<string> currentChain(tempVector.begin(), tempVector.end());
        if (isValidChain(currentChain)) // Если цепочка подходит
        {
            resultChain = currentChain; // Сохраняем результат
            return true; 
        }
    } while (next_permutation(tempVector.begin(), tempVector.end()));

    return false; 
}

// Конструктор класса, принимает список слов и очищает его от пустых строк
WordChainSolver::WordChainSolver(const list<string>& inputWords) : words(inputWords)
{
    words.remove_if([](const string& s) { return s.empty(); });
}

// Основной метод решения задачи
bool WordChainSolver::solve(deque<string>& resultChain)
{
    return findValidPermutation(resultChain); // Пытаемся найти подходящую перестановку
}

// Проверка является ли слово русским
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

// Валидация входных данных (строка слов)
bool validateInput(const string& input)
{
    if (input.empty())
    {
        cout << "Ошибка: Пустой ввод." << endl;
        return false;
    }

    size_t start = 0;
    size_t end = input.find(' ');
    bool hasValidWords = false;

    // Разбиваем строку на слова по пробелам
    while (end != string::npos)
    {
        string word = input.substr(start, end - start);
        if (!word.empty()) {
            if (!isRussianWord(word))
            {
                cout << "Ошибка: Цепочка содержит недопустимые символы." << endl;
                return false;
            }
            hasValidWords = true;
        }
        start = end + 1;
        end = input.find(' ', start);
    }

    // Проверяем последнее слово в строке
    string lastWord = input.substr(start);
    if (!lastWord.empty())
    {
        if (!isRussianWord(lastWord))
        {
            cout << "Ошибка: Слово '" << lastWord << "' содержит недопустимые символы." << endl;
            return false;
        }
        hasValidWords = true;
    }

    
    if (!hasValidWords)
    {
        cout << "Ошибка: Не введено ни одного допустимого слова." << endl;
        return false;
    }

    return true;
}