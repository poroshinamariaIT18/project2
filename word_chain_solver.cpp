#include "word_chain_solver.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>

using namespace std;

// ��������� ���������� ��������� ������� � ����� (��������� ������ ���� � �����)
char WordChainSolver::getLastChar(const string& word) const
{
    char last = word.back();
    if (last == '�' && word.size() > 1)
    {
        last = word[word.size() - 2];
    }
    return tolower(last); 
}

// ��������, �������� �� ������� ���� ����������
bool WordChainSolver::isValidChain(const deque<string>& chain) const
{
    if (chain.empty()) return false; 
    // ��������� ���������������� ������������ ���� � �������
    for (size_t i = 0; i < chain.size() - 1; ++i)
    {
        char last = getLastChar(chain[i]); 
        char first = tolower(chain[i + 1][0]); 
        if (last != first) {
            return false; 
        }
    }

    // ��������� ������� ����������� ������� (������ ����� ������� ����� = ��������� ����� ���������� �����)
    char first_word_first = tolower(chain.front()[0]);
    char last_word_last = getLastChar(chain.back());
    return first_word_first == last_word_last;
}

// ����� ���������� ������������ ���� ������� ������� ��������
bool WordChainSolver::findValidPermutation(deque<string>& resultChain)
{
    // ������� ��������� ������ �� ������ ���� ��� ������������
    vector<string> tempVector(words.begin(), words.end());
    sort(tempVector.begin(), tempVector.end()); 

    do
    {
        deque<string> currentChain(tempVector.begin(), tempVector.end());
        if (isValidChain(currentChain)) // ���� ������� ��������
        {
            resultChain = currentChain; // ��������� ���������
            return true; 
        }
    } while (next_permutation(tempVector.begin(), tempVector.end()));

    return false; 
}

// ����������� ������, ��������� ������ ���� � ������� ��� �� ������ �����
WordChainSolver::WordChainSolver(const list<string>& inputWords) : words(inputWords)
{
    words.remove_if([](const string& s) { return s.empty(); });
}

// �������� ����� ������� ������
bool WordChainSolver::solve(deque<string>& resultChain)
{
    return findValidPermutation(resultChain); // �������� ����� ���������� ������������
}

// �������� �������� �� ����� �������
bool isRussianWord(const string& word)
{
    if (word.empty()) return false; 
    for (char c : word)
    {
        c = tolower(c);
        if (!((c >= '�' && c <= '�') || c == '�' || c == '�'))
        {
            return false;
        }
    }
    return true;
}

// ��������� ������� ������ (������ ����)
bool validateInput(const string& input)
{
    if (input.empty())
    {
        cout << "������: ������ ����." << endl;
        return false;
    }

    size_t start = 0;
    size_t end = input.find(' ');
    bool hasValidWords = false;

    // ��������� ������ �� ����� �� ��������
    while (end != string::npos)
    {
        string word = input.substr(start, end - start);
        if (!word.empty()) {
            if (!isRussianWord(word))
            {
                cout << "������: ������� �������� ������������ �������." << endl;
                return false;
            }
            hasValidWords = true;
        }
        start = end + 1;
        end = input.find(' ', start);
    }

    // ��������� ��������� ����� � ������
    string lastWord = input.substr(start);
    if (!lastWord.empty())
    {
        if (!isRussianWord(lastWord))
        {
            cout << "������: ����� '" << lastWord << "' �������� ������������ �������." << endl;
            return false;
        }
        hasValidWords = true;
    }

    
    if (!hasValidWords)
    {
        cout << "������: �� ������� �� ������ ����������� �����." << endl;
        return false;
    }

    return true;
}