#include "word_chain_solver.h"
#include <iostream>
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
        cout << "Ошибка ввода данных" << endl;
        return 1;
    }

    // Создаем список для хранения слов
    MyList<string> words;
    size_t start = 0;
    size_t end = input.find(' ');

    // Разбиваем введенную строку на отдельные слова
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

    // Добавляем последнее слово (после последнего пробела)
    string lastWord = input.substr(start);
    if (!lastWord.empty()) 
    {
        words.push_back(lastWord);
    }

    
    if (words.getSize() < 2) 
    {
        cout << "Для составления цепочки нужно минимум 2 слова" << endl;
        return 1;
    }

    WordChainSolver solver(words);
    MyDeque<string> chain;

    if (solver.solve(chain)) 
    {
        // Если цепочка найдена, выводим ее
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
