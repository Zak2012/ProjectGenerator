#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <unordered_map>

#include "Template.hpp"
#include "Utils.hpp"
#include "Task.hpp"
#include "File.hpp"
#include "Color.hpp"

#include <ESN.hpp>

#include <windows.h>

void CreateProject(std::string TemplatePath, std::string ParentFolder, std::string ProjName, std::string ProjType, bool SilentMode);

bool HelpCmdCallback(std::vector<std::string> ArgsList, int Index);
bool TemplateCmdCallback(std::vector<std::string> ArgsList, int Index);
bool TypeCmdCallback(std::vector<std::string> ArgsList, int Index);
bool NameCmdCallback(std::vector<std::string> ArgsList, int Index);
bool SilentCmdCallback(std::vector<std::string> ArgsList, int Index);