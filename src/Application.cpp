// Include standard libraries
#include <iostream>
#include <string>
#include <vector>

// Include application header file
#include "Utils.hpp"
#include "Template.hpp"
#include "Task.hpp"
#include "File.hpp"
#include "Callback.hpp"
#include "Color.hpp"

/*

-n [name] : [optional] : Your Project Folder Name. Default is {Project}/ {Project (num)}
-T : [optional] : List all template available with their id
-t [id] : [optional] : Will create template of the id
-s : [optional] : Silent mode, doesn't open the editor
--help, -h : List command option

*/

// Entry Point
int main (int argc, char* argv[])
{
    SetConsoleColor();
    SetGlobalFilePath();

    std::vector<std::string> ArgsList(argv + 1, argv + argc);
    volatile bool IsCmdRan = false;

    if ( !IsCmdRan )
    {
        if ( FindArgsCallback(ArgsList, std::vector<std::string>({"-h","--help"}), HelpCmdCallback) )
        {
            IsCmdRan = true;
        }
    }
    if ( !IsCmdRan )
    {
        if ( FindArgsCallback(ArgsList, "-T", TemplateCmdCallback) )
        {
            IsCmdRan = true;
        }
    }

    if ( FindArgsCallback(ArgsList, "-t", TypeCmdCallback))
    {
        IsCmdRan = true;
    }

    if ( !IsCmdRan )
    {
        HelpCmdCallback(ArgsList,1);
        IsCmdRan = true;
    }


    //End Program
    return 0;
}