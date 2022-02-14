#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

#include "Utils.hpp"

#include <ESN.hpp>

#include <windows.h>

#define PathSeparator '\\'

inline std::string GetExeFilename();

inline std::string GetExeParentPath();

std::string JoinPath(std::string P1, std::string P2);
std::string JoinPath(std::vector<std::string> Paths);

void SetGlobalFilePath();

void ReplaceAllSubstringInString(std::string& str, const std::string& from, const std::string& to);

extern const std::string ExeBasePath;
extern std::string TemplatePath;
extern std::string ProjPath;