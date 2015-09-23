#include "textreader.h"
#include <fstream>

namespace cppag
{

    Textreader::Textreader(std::string loc)
    {
        mLocation = cppag::CLArguments::matchPath (loc);
    }

    bool Textreader::read ()
    {
        //alten Inhalt löschen
        mContent.clear();

        //filestream für Datei
        std::ifstream fileStream(mLocation.c_str());

        //öffnen erfolgreich?
        if(fileStream.bad())
            return false;

        //lies Buchstabe
        std::string line;

        while(std::getline(fileStream, line))
        {
            mContent.push_back(line);
        }

        return (true);
    }


    Textreader::~Textreader()
    {
        //dtor
    }

    std::string Textreader::getContent()
    {
        std::stringstream ss;
        for(std::vector<std::string>::iterator it=mContent.begin(); it != mContent.end(); ++it)
        {
            ss<<*it<<"\n";
        }
        //TODO: letztes \n am Ende löschen
        return(ss.str());
    }

}
