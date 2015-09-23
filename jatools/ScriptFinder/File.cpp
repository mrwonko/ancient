#include "File.h"
#include "TextReader.h"
#include "CLArguments.h"

File::File(const std::string& filename) :
    mPath(cppag::CLArguments::GetSingleton().MatchPath(filename))
{
    //ctor
}

File::~File()
{
    //dtor
}

std::string File::GetContent() const
{
    cppag::TextReader textReader(mPath);
    if(!textReader.Read())
    {
        return "Error reading file";
    }

    return textReader.GetContent();
}

const std::string File::GetFilename() const
{
    std::string filename = mPath;
    filename.erase(0, filename.find_last_of("/\\")+1);
    return filename;
}

const std::string File::GetExtension() const
{
    std::string filename = GetFilename();
    std::string::size_type dotPos = filename.find_last_of(".");
    //if there is no dot then there is no extension - return nothing
    if(dotPos == std::string::npos)
    {
        return "";
    }

    return(filename.substr(dotPos+1));
}
