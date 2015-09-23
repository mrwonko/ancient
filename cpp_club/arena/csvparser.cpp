#include "csvparser.h"
#include <iostream>

namespace cppag
{
    //TODO string für Kommentare übergeben lassen
    CSVParser::CSVParser(std::string loc, std::string separator, std::string comment) : cppag::Textreader(loc)
    {
        mSeparator = separator;
        mComment   = comment;
    }

    CSVParser::~CSVParser()
    {
        //dtor
    }

    bool CSVParser::parse()
    {
        if(!read())
        {
            std::cout<<"Lesefehler\n";
            return(false);
        }

        for(std::vector<std::string>::iterator it = mContent.begin(); it != mContent.end(); ++it)
        {
            parseLine(*it);
        }

        return(true);
    }

    bool CSVParser::parseLine(std::string line)
    {
        //bei Kommentarzeichen am Anfang garnicht erst speichern, sonst gäb's ja einen leeren Eintrag - oder ist das eher wünschenswert? TODO: Markus fragen
        if(line.find_first_of(mComment)==0)
        {
            return(true);
        }

        // Line object
        CSVLine lineobj;

        while(!line.empty())
        {
            // Position, bis zu der geparsed wird - anfangs Separator
            std::string::size_type pos = line.find_first_of(mSeparator);
            // Position eines möglichen Kommentars
            std::string::size_type com = line.find_first_of(mComment);

            // Kein Komma oder Kommentar da, wir nehmen alles
            if(com == pos == std::string::npos)
            {
                pos = line.size();
            }
            else
            {
                //erstes Komma/Kommentar als Endpunkt nehmen
                pos = (com > pos) ? pos : com;
            }

            // Den Wert der Zelle kopieren
            std::string value = line.substr(0, pos);

            // Zelle speichern
            lineobj.add(value);

            if(com == pos) //Ende wegen Kommentar?
            {
                break; //aufhören zu Parsen
            }

            // Originalstring kürzen
            line.erase(0, pos + 1);
        }

        // Zeile speichern
        mLines.push_back(lineobj);

        return (true);
    }

    CSVLine CSVParser::operator [] (int num)
    {
        return (mLines[num]);
    }
}
