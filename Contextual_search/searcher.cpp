#include "searcher.h"

Searcher::Searcher()
{
    filename = "data.txt";
    counter = 0;
}

bool Searcher::setFilename()
{
    std::cout << "Enter filename:" << std::endl;
    std::cin >> filename;
    bool isAlive = false;
    file.open(filename);
    file.is_open() ? isAlive = true : isAlive = false;
    file.close();
    getchar();
    return isAlive;
}

void Searcher::setNecessarySequence()
{
    std::cout << "Enter what you want to find:" << std::endl;
    std::getline(std::cin, necessarySequence);
}

void Searcher::findSentences()
{
    file.open(filename,std::ios::in);

    int cnt =1;
    while(!file.eof())
    {
        std::string strTmp;
        file >> strTmp;

        if (strTmp.find('.') == std::string::npos)
        {
            currentSentence += strTmp;
            currentSentence += " ";
        } else {
            currentSentence += strTmp;
            if(currentSentence.find(necessarySequence) != std::string::npos)
            {
                std::cout << cnt << ":  " << currentSentence << std::endl;
                cnt++;
            }
            currentSentence = "";
        }
    }

    file.close();
}

bool Searcher::compare(std::string tmp)
{
    if (necessarySequence == tmp)
        return true;
    else
        return false;
}

void Searcher::findEntrences()
{
    file.open(filename,std::ios::in);

    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    for(unsigned long i=0; i<fileSize-necessarySequence.size(); i++)
    {
        std::string stringTmp;
        if (necessarySequence.size() >= 1)
        {
            for (size_t c=0; c<necessarySequence.size(); c++)
            {
                stringTmp.push_back(file.get());
            }
            file.seekg(i,std::ios::beg);
        }

        if (compare(stringTmp))
            counter++;
    }

    if (counter)
        std::cout << "Number of coincidence: " << counter << std::endl;
    else
        std::cout << "It looks like there is no sequence which you want to find." << std::endl;

    file.close();
}

void Searcher::search()
{
    if(!setFilename())
    {
        std::cout << "Unable to open file." << std::endl;
        return;
    }
    setNecessarySequence();
    findEntrences();
    findSentences();
}
