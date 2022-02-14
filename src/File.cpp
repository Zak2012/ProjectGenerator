#include "File.hpp"

inline std::string GetExeFilename()
{
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    return (std::string) path;
}

inline std::string GetExeParentPath()
{
    std::string f = GetExeFilename();
    return f.substr(0, f.find_last_of( "\\/" ));
}

std::string JoinPath(std::string P1, std::string P2)
{
    std::stringstream ss;
    ss << P1;

    if ( P1.back() != PathSeparator )
    {
        ss << PathSeparator;
    }

    if ( P2.back() == PathSeparator )
    {
        P2.pop_back();
    }

    ss << P2;
    return ss.str();
}

void ReplaceAllSubstringInString(std::string& str, const std::string& from, const std::string& to)
{
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}


std::string JoinPath(std::vector<std::string> Paths)
{
    std::stringstream ss;
    for (std::string i : Paths)
    {
        if ( i.back() != PathSeparator )
        {
                ss << i;
            if ( i != Paths.back() )
            {
                ss << PathSeparator;
            }
        }
        else
        {
            if ( i == Paths.back() )
            {
                i.pop_back();
                ss << i;
            }
            else
            {
                ss << i;
            }
        }
    }
    return ss.str();
}

const std::string ExeBasePath = GetExeParentPath();
std::string TemplatePath;
std::string ProjPath;

void SetGlobalFilePath()
{
    std::unordered_map<std::string, std::string> Variable;
    Variable["${ExeBasePath}"] = ExeBasePath;

    std::string SettingsFile;
    ESN::ReadFile(JoinPath(ExeBasePath,"settings.esn"),SettingsFile);

    std::unordered_map<std::string, std::string> PathsUmap;

    PathsUmap = ESN::Parse(SettingsFile);
    ESN::SetVariable(PathsUmap,Variable);

    TemplatePath = PathsUmap["TemplatePath"];
    ProjPath = PathsUmap["ProjPath"];
}