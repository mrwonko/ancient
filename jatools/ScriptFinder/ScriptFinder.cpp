#include "ScriptFinder.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Helpers.h"
#include "CLArguments.h"
#include "Directory.h"
#include "File.h"
#include "Script.h"

ScriptFinder::ScriptFinder()
{
    //ctor
}

ScriptFinder::~ScriptFinder()
{
    //dtor
}

std::pair<bool, std::string> ScriptFinder::GetFileContent(const std::string& filename)
{
    std::pair<bool, std::string> result;
    result.first = false;
    std::ifstream filestream(filename.c_str());
    if(filestream.fail())
    {
        return result;
    }
    while(!filestream.eof())
    {
        result.second += filestream.get();
    }
    filestream.close();
    result.first = true;
    return result;
}

bool ScriptFinder::LoadInputListFromFile(const std::string& filename)
{
    std::pair<bool, std::string> result = GetFileContent(filename);
    if(!result.first) return false;
    std::string& content = result.second;
    std::string curline;
    for(std::string::iterator it = content.begin(); it != content.end(); ++it)
    {
        if(*it == '\n')
        {
            if(curline.substr(0, 8) == "scripts/" || curline.substr(0,8) == "scripts\\" ) mScriptList.insert(Script(mScriptpath + curline.substr(8, curline.length()-8)));
            curline = "";
            continue;
        }
        curline += *it;
    }
    if(curline.substr(0, 8) == "scripts/" || curline.substr(0,8) == "scripts\\" ) mScriptList.insert(Script(mScriptpath + curline.substr(8, curline.length()-8)));
    return true;
}

bool ScriptFinder::Init()
{
    std::cout   << "This program parses all the scripts listed in the given resourcelist and finds calls to other scripts in them." << std::endl
                << "Usage: scriptfinder.exe list_from_resourcelister.txt or simply drag-n-drop a file on this" <<std::endl;

    if(!mConfig.LoadFromFile(cppag::CLArguments::GetSingleton().GetWorkingDirectory() + "scriptfinder.cfg"))
    {
         Error("Could not open ScriptFinder.cfg!");
         return false;
    }

    mScriptpath = mConfig.GetString("scriptpath");
    mListpath = mConfig.GetString("listpath");
    if(mScriptpath == "")
    {
        Error("No Basepath set in scriptfinder.cfg!");
        return false;
    }

    if(cppag::CLArguments::GetSingleton().NumArguments() < 1)
    {
         Error("No list supplied!");
         return false;
    }

    //load list
    if(!LoadInputListFromFile(cppag::CLArguments::GetSingleton().GetArgument(0)))
    {
        Error("Could not open file!");
        return false;
    }

    return true;
}

bool ScriptFinder::Parse(Script& script)
{
    if(script.Parsed) return false;
    script.Parsed = true;
    std::string content = script.GetContent();
    if(content == "Error reading file")
    {
        std::cout<<"Error reading "<<script.GetFullName()<<std::endl;
        return false;
    }
    bool newScripts = false;
    while(true)
    {
        std::string::size_type nextPos1 = content.find("SCRIPT\", \""); //10 chars
        std::string::size_type nextPos2 = content.find("run ( \""); //7 chars

        if(nextPos1 == std::string::npos && nextPos2==std::string::npos)
        {
            break;
        }
        if(nextPos1 == std::string::npos || nextPos2<nextPos1)
        {
            content.erase(0, nextPos2+7);
            std::string::size_type end = content.find('"');
            if(end == std::string::npos)
            {
                std::cout<<"sudden end of file in "<<script.GetFullName()<<std::endl;
                break;
            }
            if(mScriptList.insert(Script(mScriptpath + content.substr(0, end))).second)
            {
            #ifdef _DEBUG
            std::cout<<"found reference to "<<content.substr(0, end)<<std::endl;
            #endif
                newScripts = true;
            }
            content.erase(0, end);
        }
        else if (nextPos2 == std::string::npos || nextPos1<nextPos2)
        {
            content.erase(0, nextPos1+10);
            std::string::size_type end = content.find('"');
            if(end == std::string::npos)
            {
                std::cout<<"sudden end of file in "<<script.GetFullName()<<std::endl;
                break;
            }
            if(mScriptList.insert(Script(mScriptpath + content.substr(0, end))).second)
            {
            #ifdef _DEBUG
            std::cout<<"found reference to "<<content.substr(0, end)<<std::endl;
            #endif
                newScripts = true;
            }
            content.erase(0, end);
        }
    }
    return newScripts;
}

void ScriptFinder::Go()
{
    std::cout<<"initalizing..."<<std::endl;
    if(!Init()) return;

    unsigned int counter = 0;
    bool unparsedScripts = !mScriptList.empty();
    while (unparsedScripts)
    {
        std::cout<<"parsing scripts ("<<++counter<<")..."<<std::endl;
        unparsedScripts = false;
        for(std::set<Script>::iterator it = mScriptList.begin(); it != mScriptList.end(); ++it)
        {
            if(it->Parsed) continue;
            Script& s = (Script&)*it;
            if(!unparsedScripts)
            {
                unparsedScripts = Parse(s);
            }
            else
            {
                Parse(s);
            }
        }
    }

    //n = name(old)
    const std::string& n = cppag::CLArguments::GetSingleton().GetArgument(0);
    std::string::size_type pos = n.find_last_of("/\\");
    std::string filename;
    if(pos == std::string::npos)
    {
        filename = n;
    }
    else
    {
        filename = n.substr(pos, n.length()-pos);
    }
    filename = mListpath + filename + ".scripts.txt";

    std::ofstream out (filename.c_str());
    if(out.fail())
    {
        Error("Could not write list! Here it is:");
        for(std::set<Script>::iterator it = mScriptList.begin(); it != mScriptList.end(); ++it)
        {
            std::cout<<it->GetFullName()<<std::endl;
        }
    }
    else
    {
        for(std::set<Script>::iterator it = mScriptList.begin(); it != mScriptList.end(); ++it)
        {
            out<<it->GetFullName()<<std::endl;
        }
        out.close();
    }

    std::cout<<"Press Enter to exit";
    std::fflush(stdin);
    std::getchar();
}

void ScriptFinder::Error(const std::string& message)
{
    std::cout<<"Error: "<<message<<std::endl;
    std::cout<<"Press Enter to exit";
    std::fflush(stdin);
    std::getchar();
}
