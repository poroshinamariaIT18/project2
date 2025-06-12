#include "word_chain_solver.h"  
#include <iostream>             
#include <list>                 
#include <string>               
using namespace std;

int main()
{
    cout << "Введите слова через пробел: ";
    string input;
    getline(cin, input);  
    // Проверяем корректность введенных данных
    if (!validateInput(input))
    {
        return 1;  
    }

    // Разбиваем введенную строку на отдельные слова по пробелам
    list<string> words; 
    size_t start = 0;    
    size_t end = input.find(' ');

    while (end != string::npos)  
    {
        string word = input.substr(start, end - start);  
        if (!word.empty())  
        {
            words.push_back(word); 
        }
        start = end + 1;           
        end = input.find(' ', start);
    }

    // Обрабатываем последнее слово в строке (после последнего пробела)
    string lastWord = input.substr(start);
    if (!lastWord.empty())
    {
        words.push_back(lastWord);
    }
    
    if (words.size() < 2)
    {
        cout << "Ошибка: Для составления цепочки нужно как минимум 2 слова." << endl;
        return 1; 
    }

    WordChainSolver solver(words);
    deque<string> chain;  
    if (solver.solve(chain))
    {
        cout << "Цепочка найдена: ";
        for (const auto& word : chain)  
        {
            cout << word << " ";  
        }
        cout << endl;
    }
    else
    {
        cout << "Невозможно составить цепочку" << endl;
    }

    return 0;  
}