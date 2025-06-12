#pragma once
#ifndef WORD_CHAIN_SOLVER_H
#define WORD_CHAIN_SOLVER_H

#include <list>
#include <deque>
#include <string>
using namespace std;
class WordChainSolver {
private:
    list<string> words;

    char getLastChar(const string& word) const;
    bool isValidChain(const deque<string>& chain) const;
    bool findValidPermutation(deque<string>& resultChain);

public:
    WordChainSolver(const list<string>& inputWords);
    bool solve(deque<string>& resultChain);
};

bool isRussianWord(const string& word);
bool validateInput(const string& input);

#endif // WORD_CHAIN_SOLVER_H