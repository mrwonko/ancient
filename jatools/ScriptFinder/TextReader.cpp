#include "TextReader.h"
#include <fstream>

namespace cppag
{

    TextReader::TextReader(const std::string& loc)
    {
        mLocation = cppag::CLArguments::GetSingleton().MatchPath (loc);
    }

    bool TextReader::Read()
    {
        //remove old content
        mContent.clear();

        //filestream for file
        std::ifstream fileStream(mLocation.c_str());

        //opened succesfull?
        if(fileStream.fail())
            return false;
        std::string line;

        while(std::getline(fileStream, line))
        {
            mContent.push_back(line);
        }

        return (true);
    }


    TextReader::~TextReader()
    {
        //dtor
    }

    std::string TextReader::GetContent() const
    {
        std::stringstream ss;
        for(std::vector<std::string>::const_iterator it=mContent.begin(); it != mContent.end(); ++it)
        {
            ss<<*it;
            //Add an endline if this is not the last argument
            if(it +1 != mContent.end()) ss<<"\n";
        }
        return(ss.str());
    }

}
