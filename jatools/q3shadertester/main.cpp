#include <iostream>
#include <string>
#include "CLArguments.h"
#include "File.h"
#include "Directory.h"
#include "Helpers.h"
#include <fstream>

/**
    Tests all .shader file in the directory of the .exe to see if the number of { is equal to the number of }
**/

int main(int argc, char** argv)
{
    cppag::CLArguments args(argc, argv);

    Directory exeDir = Directory(cppag::CLArguments::GetSingleton().GetWorkingDirectory());

    const Directory::fileVector& files = exeDir.GetFiles();

    for(Directory::fileVector::const_iterator it = files.begin(); it != files.end(); ++it)
    {
        if(it->get()->GetExtension() == "shader")
        {
            std::cout << "checking \"" << it->get()->GetFilename() << "\"" << std::endl;
            int counter = 0;

            std::string content = Helpers::RemoveCStyleComments(it->get()->GetContent());
            for(std::string::const_iterator it2 = content.begin(); it2 != content.end(); ++it2)
            {
                if( (*it2) == '{' )
                {
                    ++counter;
                }
                else if( (*it2) == '}' )
                {
                    --counter;
                }
            }

            if(counter != 0)
            {
                std::cout<<"WARNING: Shader \"" << it->get()->GetFilename() << "\" is invalid!" <<std::endl;
            }
        }
    }
    std::cout<<"Press Enter to exit";
    std::fflush(stdin);
    std::getchar();

    return 0;
}
