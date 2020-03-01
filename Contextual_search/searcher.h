#ifndef SEARCHER_H
#define SEARCHER_H

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <wchar.h>

class Searcher
{
private:
    std::string filename;
    std::fstream file;
    std::string necessarySequence;
    std::string currentSentence;
    int counter;
public:
    Searcher();
    bool setFilename();
    void setNecessarySequence();
    void findSentences();
    bool compare(std::string);
    void findEntrences();
    void search();
};

#endif // SEARCHER_H
