#include "CLArguments.h"
#include "Helpers.h"

namespace cppag
{
    //Singleton
    template<> CLArguments* GX::Singleton<CLArguments>::ms_Singleton = NULL;

    CLArguments::CLArguments(int argc, char** argv)
    {
        //Loop through the arguments
        for(int i = 0; i < argc; ++i)
        {
            //First argument contains the executable path: C:\Path\program.exe
            if(i==0)
            {
                //Strip everything until the last \ or /
                mWorkingDir=argv[0];

                //Windows or Unix style? Windows has \, Unix /
                mWindows = mWorkingDir.find('/', 0)==std::string::npos;
                if(mWindows)
                {
                    mWorkingDir.erase(mWorkingDir.find_last_of("\\", mWorkingDir.length())+1, mWorkingDir.length());
                }
                else //didn't find /, search for \.
                {
                    mWorkingDir.erase(mWorkingDir.find_last_of("/", mWorkingDir.length())+1, mWorkingDir.length());
                }
            }
            else
            {
                mArguments.push_back(argv[i]);
            }
        }
    }

    const std::string & CLArguments::GetWorkingDirectory() const
    {
        return (mWorkingDir);
    }

    std::string CLArguments::MatchPath(const std::string& dir) const
    {
        //if the given path is already absolute, do nothing to it
        if(dir.find_first_of("/")==0
        || dir.find(":")!=std::string::npos)
        {
            return (dir);
        }
        //else make it an absolute path
        std::string result=GetWorkingDirectory()+dir;

        //if we are on a windows machine make sure to use backslashes
        if(mWindows)
        {
            //as long as slashes can be found
            std::string::size_type pos = std::string::npos;
            while( (pos = result.find("/")) != std::string::npos)
            {
                //replace the slash with a backslash
                result[pos] = '\\';
            }
        }
        return(result);
    }

    const int CLArguments::FindArgument(const std::string& requestedArgument, bool caseSensitive) const
    {
        // the position of the argument, stays -1 if nothing is found
        int position = -1;
        std::string pattern = caseSensitive ? requestedArgument : Helpers::ToLower(requestedArgument);
        //loop through the arguments, looking for the specified argument
        for(unsigned int i = 0; i < mArguments.size(); ++i)
        {
            //if this argument is the one which was requested
            if(
                (caseSensitive && mArguments.at(i) == pattern ) ||
                (!caseSensitive && Helpers::ToLower(mArguments.at(i)) == pattern )
              )
            {
                //save its position and exit the loop
                position = i;
                break;
            }
        }
        //return the position of the requested argument
        return position;
    }

}
