#include "Utils.hpp"

std::vector<std::string> StringSplit (const std::string &s, char delim)
{
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while ( getline (ss, item, delim) )
    {
        result.push_back (item);
    }

    return result;
}

std::string StringJoin (const std::vector<std::string>& s, char join)
{
    std::string result;
    
    for ( unsigned int i = 0; i < s.size(); i++ )
    {
        result += s[i] + std::string(i < s.size() - 1, join);
    }

    return result;
}