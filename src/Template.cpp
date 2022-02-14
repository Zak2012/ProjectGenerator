#include "Template.hpp"

// list template relative to Template folder
std::vector<std::string> ListTemplate()
{
    std::vector<std::string> vsTemplateDir;

    // loops through every file inside template folder
    for( const std::filesystem::directory_entry &fsdePath: std::filesystem::recursive_directory_iterator(TemplatePath) )
    {
        // convert current path to string
        std::string sPath = fsdePath.path().string();

        // split path
        std::vector<std::string> vsParsedPath = StringSplit(sPath,PathSeparator);
        // make current path relative to template folder
        std::string sRelativePath = sPath.substr(TemplatePath.size()+1);
        // split relative path
        std::vector<std::string> RelativeParsedPath = StringSplit(sRelativePath,PathSeparator);

        // only list as valid template if have a folder called "".proj"
        if ( RelativeParsedPath.back() == ".proj" && std::filesystem::is_directory(sPath) )
        {
            // make a copy of curent relative path and remove ".proj" to get parent folder path
            std::vector<std::string> vsTemplateName = RelativeParsedPath;
            vsTemplateName.pop_back();
            std::string sTemplateName = StringJoin(vsTemplateName, PathSeparator);

            // add the valid template path to template list
            vsTemplateDir.push_back(sTemplateName);
        }
    }
    return vsTemplateDir;
}

void PrintTemplate(std::vector<std::string> TemplateList)
{
    for ( unsigned int i = 0; i < TemplateList.size(); i++ )
    {
        std::cout << i << "\t" << TemplateList[i] << "\n";
    }
}