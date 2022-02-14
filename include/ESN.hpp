#pragma once

// Include standard libraries
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>


namespace ESN
{
    typedef std::unordered_map<std::string, std::string> Map;

    // Read the file
    bool ReadFile(const std::string &Path, std::string &Dest);

    // Set Variable
    // Variable["${Foo}"] = "Name"
    // AA : ${Foo}
    // AA : Name
    void SetVariable(Map &Umap, const Map &Variables);

    // Parse the string
    Map Parse(std::string String);

    // Return string from unordered map
    std::string ToString(const Map &Umap);

    // Return a pretty-printed string
    std::string PrettyPrint(const Map &Umap);
}