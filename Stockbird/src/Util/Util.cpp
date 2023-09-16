#include "Util.h"

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