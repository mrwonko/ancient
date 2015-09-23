#include "CLArguments.h"
#include <iostream>

namespace cppag
{

std::vector <std::string> CLArguments::mArguments;
CLArguments::CLArguments(int argc, char** argv)
{
    for(int i = 0; i < argc; ++i)
    {
        if(i==0)
        {
            std::string temp=argv[0];
			//Windows or Unix style?
            if(temp.find('/', 0)!=std::string::npos) //found /, search for /
            {
                temp.erase(temp.find_last_of("/", temp.length())+1, temp.length());
            }
            else //didn't find /, search for \.
            {
                temp.erase(temp.find_last_of("\\", temp.length())+1, temp.length());
            }
            mArguments.push_back(temp);
        }
        else
        {
            mArguments.push_back(argv[i]);
        }
    }
}

std::string CLArguments::getWorkingDirectory()
{
    return (mArguments[0]);
}

std::string CLArguments::matchPath(std::string dir)
{
    if(dir.find_first_of("/")==0
    || dir.find(":")!=std::string::npos)
    {
        return (dir);
    }
    std::string result=getWorkingDirectory()+dir;
    return(result);
}

}
