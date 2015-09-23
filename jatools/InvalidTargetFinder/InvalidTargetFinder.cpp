#include "InvalidTargetFinder.h"
#include "CLArguments.h"
#include <fstream>
#include <iostream>
#include "Helpers.h"

InvalidTargetFinder::InvalidTargetFinder()
{
    //ctor
}

InvalidTargetFinder::~InvalidTargetFinder()
{
    //dtor
}

void InvalidTargetFinder::Go()
{
    if(cppag::CLArguments::GetSingleton().NumArguments() < 1)
    {
        Error("Too few arguments.");
        return;
    }
    std::ifstream file(cppag::CLArguments::GetSingleton().GetArgument(0).c_str());
    if(file.fail())
    {
        Error("Could not open file.");
        return;
    }
    std::string content;
    while(!file.eof())
    {
        content += file.get();
    }
    file.close();

    content = Helpers::ToLower(content);

    Extract(content, "\"targetname\" \"", mTargetnames);
    Extract(content, "\"target\" \"", mTargets);
    Extract(content, "\"target2\" \"", mTargets);
    Extract(content, "\"target3\" \"", mTargets);
    Extract(content, "\"target4\" \"", mTargets);
    Extract(content, "\"opentarget\" \"", mTargets);
    Extract(content, "\"closetarget\" \"", mTargets);
    Extract(content, "\"npc_target\" \"", mTargets);

    for(std::set<std::string>::iterator it = mTargets.begin(); it != mTargets.end(); ++it)
    {
        if(mTargetnames.find(*it) == mTargetnames.end()) std::cout<<"Lacking targetname \""<<*it<<"\"!"<<std::endl;
    }

    std::cout<<"Press Enter to exit";
    std::fflush(stdin);
    std::getchar();
}

void InvalidTargetFinder::Extract(std::string content, const std::string& search, std::set<std::string>& output)
{
    std::string::size_type match;
    while( (match = content.find(search)) != std::string::npos)
    {
        content.erase(0, match + search.size());
        match = content.find("\"");
        if(match == std::string::npos) return;
        output.insert(content.substr(0, match));
        //std::cout<<"added \""<<content.substr(0, match)<<"\""<<std::endl;
        content.erase(0, match);
    }
}

void InvalidTargetFinder::Error(const std::string& message)
{
    std::cout<<"Error: "<<message<<" Ask Wonko if necessary."<<std::endl;
    std::cout<<"Press Enter to exit";
    std::fflush(stdin);
    std::getchar();
}
