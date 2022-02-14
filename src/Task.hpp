#pragma once 

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

// Function, (argsList, index)
bool FindArgsCallback (std::vector<std::string> ArgsList, std::string Target, std::function<bool (std::vector<std::string>, int)> Callback);

bool FindArgsCallback (std::vector<std::string> ArgsList, std::vector<std::string> Targets, std::function<bool (std::vector<std::string>, int)> Callback);