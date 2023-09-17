#include "Util.h"

#include <string>
#include <fstream>
#include <cctype>
#include <cstring>

std::vector<std::string> Split(std::string str, char separator)
{
    std::vector<std::string> strings;
    int startIndex = 0, endIndex = 0;
    for (int i = 0; i <= str.size(); i++)
    {
        if (str[i] != separator && i != str.size()) continue;

        endIndex = i;
        std::string temp;
        temp.append(str, startIndex, endIndex - startIndex);
        strings.push_back(temp);
        startIndex = endIndex + 1;
    }

    return strings;
}

std::vector<char> Split(std::string str)
{
    std::vector<char> chars;
    int index = 0;
    for (char c : str)
    {
        chars.push_back(c);
        index++;
    }

    return chars;
}

void PrintTitle()
{
    std::fstream fTitle;
    fTitle.open("assets\\title.txt", std::ios::in);//read
    if (!fTitle.is_open()) return;
    std::string line;
    while (std::getline(fTitle, line))
    {
        std::cout << line << std::endl;
    }
    fTitle.close();
    std::cout << std::endl;
}

bool IsFirstRank(int index)
{
    return index % 8 == 0;
}

bool IsEighthRank(int index)
{
    return (index + 1) % 8 == 0;
}

int GetIndexOf(char file, int index)
{
    std::vector<int> a{ 56, 48, 40, 32, 24, 16, 8, 0 };
    std::vector<int> b{ 57, 49, 41, 33, 25, 17, 9, 1 };
    std::vector<int> c{ 58, 50, 42, 34, 26, 18, 10, 2 };
    std::vector<int> d{ 59, 51, 43, 35, 27, 19, 11, 3 };
    std::vector<int> e{ 60, 52, 44, 36, 28, 20, 12, 4 };
    std::vector<int> f{ 61, 53, 45, 37, 29, 21, 13, 5 };
    std::vector<int> g{ 62, 54, 46, 38, 30, 22, 14, 6 };
    std::vector<int> h{ 63, 55, 47, 39, 31, 23, 15, 7 };

    if (file == 'a')
    {
        return a[index];
    }
    else if (file == 'b')
    {
        return b[index];
    }
    else if (file == 'c')
    {
        return c[index];
    }
    else if (file == 'd')
    {
        return d[index];
    }
    else if (file == 'e')
    {
        return e[index];
    }
    else if (file == 'f')
    {
        return f[index];
    }
    else if (file == 'g')
    {
        return g[index];
    }
    return h[index];
}

int ParseSquare(std::string str)
{
    std::vector<char> files{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

    char file = ' ';

    for (char symbol : str)
    {
        if (std::find(files.begin(), files.end(), symbol) != files.end()) file = symbol;

        if (isdigit(symbol))
        {
            if (file == ' ') break;

            int index = std::stoi(std::string(1, symbol))-1;
            if (index < 0 || index+1 > 8) break;

            return GetIndexOf(file, index);
        }
    }

    std::cout << "Invalid Algebraic Notation" << std::endl;
    return -1;
}