#include "Callback.hpp"

// global variable for project name
std::string *gProjName = new std::string("Project");

bool HelpCmdCallback(std::vector<std::string> ArgsList, int Index)
{
    std::cout << 
    "-n [name] : [optional] : Your Project Folder Name. Default is {Project}/ {Project (num)}\n" <<
    "-T : [optional] : List all template available with their id\n" <<
    "-t [id] : [optional] : Will create template of the id\n" <<
    "-s : [optional] : Silent mode, doesn't open the editor\n"<<
    "--help, -h : List command option\n";
    return true;
}

bool TemplateCmdCallback(std::vector<std::string> ArgsList, int Index)
{
    SetConsoleColor(C_BLUE | C_LIGHT);
    std::cout <<   "Finding valid template, please wait...";
    std::vector<std::string> TemplatesList = ListTemplate();
    std::cout << "\r                                      ";
    SetConsoleColor(C_GREEN | C_LIGHT);
    std::cout << "\rFound valid template\n";
    SetConsoleColor();
    PrintTemplate(TemplatesList);
    return true;
}

bool TypeCmdCallback(std::vector<std::string> ArgsList, int Index)
{
    // check if option flag not at the end
    if ( Index + 1 < static_cast<int>(ArgsList.size()) )
    {
        // check if argument after is a flag or parameter
        if ( ArgsList[Index + 1].at(0) != '-' )
        {
            SetConsoleColor(C_BLUE | C_LIGHT);
            std::cout <<   "Finding valid template, please wait...";
            std::vector<std::string> TemplatesList = ListTemplate();
            std::cout << "\r                                      ";
            SetConsoleColor(C_GREEN | C_LIGHT);
            std::cout << "\rFound valid template\n";
            SetConsoleColor();

            unsigned int TemplatesType;

            // try to convert parameter into integer
            try
            {
                TemplatesType = std::stoi(ArgsList[Index + 1]);
            }
            catch (std::invalid_argument &ex)
            {
                // parameter has non-integer value
                std::cout << ex.what() << "\nPlease specify template in integer";
                return false;
            }

            // check if parameter given exceed template list
            if ( TemplatesType < TemplatesList.size() )
            {
                // current template file selection
                std::string CurTemplatePath = JoinPath(TemplatePath, TemplatesList[TemplatesType]);

                // get the top level template name
                std::vector<std::string> TemplateNameSplit = StringSplit(TemplatesList[TemplatesType], PathSeparator);
                std::string TopLevelTemplateName = TemplateNameSplit[0];
                std::string ProjTemplatePath = JoinPath(ProjPath, TopLevelTemplateName);

                // create the top level template if didn't exist
                if ( !std::filesystem::exists(ProjTemplatePath) )
                {
                    std::filesystem::create_directory(ProjTemplatePath);
                }

                // check if user specified name
                FindArgsCallback(ArgsList, "-n", NameCmdCallback);

                // check for silent command
                bool SilentMode = FindArgsCallback(ArgsList, "-s", SilentCmdCallback);

                // generate project
                CreateProject(CurTemplatePath, ProjTemplatePath, *gProjName, TopLevelTemplateName, SilentMode);
                delete gProjName;
            }
            else{
                SetConsoleColor(C_RED);
                std::cout << "Unknown template" << "\n";
                SetConsoleColor();
                return false;
            }
        }
    }
    else
    {
        SetConsoleColor(C_RED);
        std::cout << "Template not specified\n";
        SetConsoleColor();
        return false;
    }
    return true;
}

bool NameCmdCallback(std::vector<std::string> ArgsList, int Index)
{
    // check if option flag not at the end
    if (  Index + 1 < (int)ArgsList.size() )
    {
        // check if argument after is a flag or parameter
        if ( ArgsList[Index + 1].at(0) != '-' )
        {
            *gProjName = ArgsList[Index + 1];
        }
    }
    return true;
}

bool SilentCmdCallback(std::vector<std::string> ArgsList, int Index)
{
    return true;
}

void CreateProject(std::string TemplatePath, std::string ParentFolder, std::string ProjName, std::string ProjType, bool SilentMode)
{
    std::string FinalProjName;

    // check projects available name if name isn't available
    std::string DefaultProjName = ProjName;
    int ProjNum = 0;
    while ( std::filesystem::exists(JoinPath(ParentFolder,DefaultProjName)) )
    {
        ProjNum++;
        /* 
        Project (5)
        Project (6)
        Project (7)
        */
        DefaultProjName = ProjName + " (" + std::to_string(ProjNum) + ")";
    }

    // check if project already exist
    if ( std::filesystem::exists(JoinPath(ParentFolder, ProjName)) )
    {
        std::cout << 
        "-------------------------\n" <<
        "Project already exist\n" <<
        "Do you want to rename it?\n" <<
        "Default [N]\n";
        SetConsoleColor(C_GREEN | C_LIGHT);
        std::cout << "[y] : Yes\n";
        SetConsoleColor();
        SetConsoleColor(C_RED | C_LIGHT);
        std::cout << "[N] : No, will default to \"" << DefaultProjName << "\"\n";
        SetConsoleColor();

        // get answer
        std::string IsRenamed;
        std::getline(std::cin, IsRenamed);

        // capitalize string
        std::transform(IsRenamed.begin(), IsRenamed.end(),IsRenamed.begin(), ::toupper);

        if ( IsRenamed == "Y" )
        {
            // user input new name and check if name is already exist
            std::string NewProjName = ProjName;
            while ( std::filesystem::exists(JoinPath(ParentFolder, NewProjName)) )
            {
                std::cout << "Enter new project name\n";
                std::getline(std::cin, NewProjName);
            }
            FinalProjName = NewProjName;
        }
        else
        {
            FinalProjName = DefaultProjName;
        }
    }
    else
    {
        FinalProjName = ProjName;
    }

    std::string FinalProjFullPath = JoinPath(ParentFolder, FinalProjName);

    // copy the template
    SetConsoleColor(C_BLUE | C_LIGHT);
    std::cout << "Copying files, please wait...";
    SetConsoleColor();
    std::filesystem::copy(TemplatePath, FinalProjFullPath, std::filesystem::copy_options::recursive);
    std::cout << "\r                             ";
    SetConsoleColor(C_GREEN | C_LIGHT);
    std::cout << "\rDone copying file\n";
    SetConsoleColor();

    // read proj setting file
    std::string ProjSettingDir = JoinPath(FinalProjFullPath, ".proj");
    std::string ProjSettingPath = JoinPath(ProjSettingDir, "settings.esn");
    std::string ProjSettingString;
    ESN::ReadFile(ProjSettingPath, ProjSettingString);

    std::unordered_map<std::string, std::string> ProjSetting = ESN::Parse(ProjSettingString);

    // set the variable
    std::unordered_map<std::string, std::string> ProjVariable;
    ProjVariable["${ProjPath}"] = FinalProjFullPath;

    ESN::SetVariable(ProjSetting, ProjVariable);

    // extract value
    std::string EditorFullPath = ProjSetting["EditorFullPath"];
    std::string EditorArgs = ProjSetting["Args"];

    if ( !SilentMode )
    {
        char *EditorCmd = EditorArgs.data();

        // start code editor
        SetConsoleColor(C_BLUE | C_LIGHT);
        std::cout << "Opening editor";
        STARTUPINFOA info={sizeof(info)};
        PROCESS_INFORMATION processInfo;
        if ( CreateProcessA(EditorFullPath.c_str(), EditorCmd, NULL, NULL, false, 0, NULL, NULL, &info, &processInfo) )
        {
            std::cout << "\r              ";
            SetConsoleColor(C_GREEN | C_LIGHT);
            std::cout << "\rDone opening editor";
            SetConsoleColor();
            WaitForSingleObject(processInfo.hProcess, INFINITE);
            CloseHandle(processInfo.hProcess);
            CloseHandle(processInfo.hThread);
        }
        else
        {
            std::cout << "\r              ";
            SetConsoleColor(C_RED);
            std::cout << "\rFailed to open editor\n";
            SetConsoleColor();
            std::cerr << "Create Process Failed " << GetLastError() << std::endl;
        }
    }

    // cleaning project file
    SetConsoleColor(C_BLUE | C_LIGHT);
    std::cout << "Cleaning project file";
    SetConsoleColor();

    std::filesystem::remove_all(ProjSettingDir);
    SetConsoleColor(C_GREEN | C_LIGHT);
    std::cout << "\r                     ";
    std::cout << "\rDone cleaning project file\n";
    SetConsoleColor();

    // print project properties
    std::cout << "-------------+\n" << "Project Name : ";
    SetConsoleColor(C_BLUE | C_GREEN | C_LIGHT);
    std::cout << FinalProjName;
    SetConsoleColor();
    std::cout << "\n" << "Project Type : ";
    SetConsoleColor(C_BLUE | C_GREEN | C_LIGHT);
    std::cout << ProjType;
    SetConsoleColor();
    std::cout << "\n" << "Full path    : ";
    SetConsoleColor(C_BLUE | C_GREEN | C_LIGHT);
    std::cout << FinalProjFullPath;
    SetConsoleColor();
    std::cout << "\n" << "Editor args  : ";
    SetConsoleColor(C_BLUE | C_GREEN | C_LIGHT);
    std::cout << EditorArgs;
    SetConsoleColor();
    std::cout << "\n" << "-------------+\n";
}