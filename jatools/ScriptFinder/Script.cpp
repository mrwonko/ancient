#include "Script.h"

Script::Script(const std::string& filename) : File(filename + ".icarus"), Parsed(false)
{
    //ctor
    if(GetContent() == "Error reading file") mPath = filename + ".txt";
}

Script::~Script()
{
    //dtor
}
