#include "Logfile.h"

#include <fstream>
#ifdef _DEBUG
    #include <iostream>
#endif

namespace WGF
{

    Logfile::Logfile(const std::string& filename) : mFilename(filename)
    {
        //ctor
    }

    Logfile::~Logfile()
    {
        //dtor
    }

    void Logfile::Log(const std::string& text)
    {
        std::ofstream logstream(mFilename.c_str(), std::ios::app);
        logstream<<text<<std::endl;
        logstream.close();
        #ifdef _DEBUG
            std::cout<<text<<std::endl;
        #endif
    }

    void Logfile::Empty()
    {
        std::ofstream of(mFilename.c_str(), std::ios::trunc);
        of.close();
    }

} // namespace WGF
