#pragma once

#include <string>
#include <vector>
#include <sstream>

std::vector<std::string> StringSplit (const std::string &s, char delim);

std::string StringJoin (const std::vector<std::string>& s, char join);
