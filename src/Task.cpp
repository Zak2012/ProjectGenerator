#include "Task.hpp"

bool FindArgsCallback (std::vector<std::string> ArgsList, std::string Target, std::function<bool (std::vector<std::string>, int)> Callback)
{
    auto Iterator = std::find(ArgsList.begin(), ArgsList.end(), Target);
    if (Iterator != ArgsList.end())
    {
        int index = Iterator - ArgsList.begin();
        return Callback(ArgsList, index);
    }
    return false;
}

bool FindArgsCallback (std::vector<std::string> ArgsList, std::vector<std::string> Targets, std::function<bool (std::vector<std::string>, int)> Callback)
{
    for (unsigned int i = 0; i < Targets.size(); i++){
        auto Iterator = std::find(ArgsList.begin(), ArgsList.end(), Targets[i]);
        if (Iterator != ArgsList.end())
        {
            int index = Iterator - ArgsList.begin();
            return Callback(ArgsList, index);
        }
    }
    return false;
}