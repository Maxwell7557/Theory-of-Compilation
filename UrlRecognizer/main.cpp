#include <iostream>

using namespace std;

bool analysis(string inputString)
{
    string alphabet = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"}; // Допустимые буквы
    string numbers = {"1234567890"}; // Допустимые цифры
    string specialSymbols = {".+=!?&:#@-_/%~"}; // Специальные символы

    char protocols[25][10] = {"https://","http://","ftp://","pop3://","smtp://","telnet://","dtn://","adc://","ssh://","dns://",
                             "irc://","nntp://","ntp://","rtp://","rtsp://","mime://","sip://","smtp://","snmp://","stun://",
                             "tftp://","map://","msnp://","imap://","rsync://"}; // Допустимые протоколы передачи данных

    char commonDomains[40][13] = {".accademy",".actor",".aero",".agency",".apartments",".app",".associates",".asia",".audio",".biz",
                                  ".cat",".com",".coop",".edu",".gov",".info",".int",".jobs",".mobi",".museum",
                                  ".name",".net",".online",".org",".pharmacy",".photography",".pics",".feedback",".post",".press",
                                  ".pro",".properties",".recipes",".repair",".report",".republican",".review",".tel",".travel",".art"}; // Допустимые общие домены

    char countryDomains[79][4] = {".ae",".af",".am",".ao",".aq",".ar",".at",".au",".az",".bd",
                                 ".be",".bg",".bn",".bo",".br",".by",".ca",".ch",".ci",".cl",
                                 ".cn",".co",".cu",".cv",".cy",".cz",".de",".dk",".do",".dz",
                                 ".ee",".eg",".es",".eu",".fi",".fr",".ge",".gr",".hr",".hu",
                                 ".id",".il",".in",".io",".iq",".ir",".is",".it",".jp",".kp",
                                 ".kz",".lu",".lv",".md",".me",".nl",".no",".nz",".pe",".ph",
                                 ".pl",".pr",".ro",".rs",".ru",".sa",".se",".sg",".si",".sk",
                                 ".su",".sy",".th",".tr",".ua",".uk",".us",".ve",".vn"}; // Допустимые домены по странам

    string buf;
    string buf2;
    string domain;

    int undefinedSymbols = 0;
    int positionOfWebsiteName = 0;

    bool isProtocolFound = false;
    bool isProtocolFirst = false;
    bool isNameFound = false;
    bool isThatName = false;

    for (int i = 0; i < inputString.size(); i++)
    {
        if (inputString[i] == ':' && inputString[i+1] == '/' && inputString[i+2] == '/')
        {
            buf = inputString.substr(0,i+3);
            positionOfWebsiteName = i+3;
            isProtocolFound = true;
            break;
        }
    }

    for (int i = 0; i < 25; i++)
    {
        if (buf.compare(protocols[i]) == 0)
            isProtocolFirst = true;
    }

    if (isProtocolFirst == true)
        for (int i = positionOfWebsiteName; i < inputString.size(); i++)
        {

            if (inputString[i] == '/')
            {
                buf = inputString.substr(positionOfWebsiteName,i-1);
                buf.erase(i-positionOfWebsiteName);
                buf2 = inputString.substr(i+1,inputString.size());
                isNameFound = true;
                break;
            }
            if (i+1 == inputString.size())
            {
                buf = inputString.substr(positionOfWebsiteName,i);
                isNameFound = true;
                break;
            }
        }

    for (int i = 0; i < buf.size(); i++)
    {
        bool isSymbolAllowed = false;
        for (int j = 0; j < alphabet.size(); j++)
        {
            if (buf[i] == alphabet[j])
            {
                isSymbolAllowed = true;
                break;
            }
        }
        for (int k = 0; k < numbers.size(); k++)
        {
            if (buf[i] == numbers[k])
            {
                isSymbolAllowed = true;
                break;
            }
        }

        if (buf[i] == '.' && isSymbolAllowed == false)
            isSymbolAllowed = true;

        if (isSymbolAllowed == false)
            undefinedSymbols++;
    }


    if (isNameFound == true)
    {
        for (int i = 0; i < buf.size(); i++)
        {
            if (buf[i] == '.')
            {
                domain = buf.substr(i,buf.size()-i);
                for (int k = 0; k < 40; k++)
                {
                    if (domain.compare(commonDomains[k]) == 0)
                    {
                        isThatName = true;
                        break;
                    }
                }
                for (int j = 0; j < 79; j++)
                {
                    if (domain.compare(countryDomains[j]) == 0)
                    {
                        isThatName = true;
                        break;
                    }
                }
            } else {
                continue;
            }
        }
    }

    if (isThatName == true)
        for(int i = 0; i < buf2.size() ; i++)
        {
            bool isFound = false;
            for (int j = 0; j < alphabet.size() ; j++)
            {
                if (buf2[i] == alphabet[j] && isFound == false)
                {
                    isFound = true;
                    break;
                }
            }
            for (int k = 0; k < numbers.size() ; k++)
            {
                if (buf2[i] == numbers[k] && isFound == false)
                {
                    isFound = true;
                    break;
                }
            }
            for (int h = 0; h < specialSymbols.size() ; h++)
            {
                if (buf2[i] == specialSymbols[h] && isFound == false)
                {
                    isFound = true;
                    break;
                }
            }
            if (isFound == false)
                undefinedSymbols++;
        }

    if (undefinedSymbols == 0 && isThatName == true)
        return true;
    else
        return false;
}

int main()
{
    string inputString;

    cout << "Enter string for recognition:" << endl;
    cin >> inputString;

    if (analysis(inputString))
        cout << "This is URL." << endl;
    else
        cout << "This is not URL." << endl;

    return 0;
}
