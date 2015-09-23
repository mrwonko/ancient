#ifndef CSVPARSER_H
#define CSVPARSER_H

#include "textreader.h"
#include "csvline.h"

namespace cppag
{
    class CSVParser : public cppag::Textreader
    {
        public:
            //Ort der Datei, Separator der Werte, Kommentarzeilen-Indikator
            CSVParser(std::string loc, std::string separator, std::string comment="//");

            //Parsen, true bei Erfolg
            bool parse();
            bool parseLine(std::string line);
            int size() const {return mLines.size();}

            CSVLine operator [] (int num);

            virtual ~CSVParser();
        protected:
            std::string mSeparator;
            std::string mComment;
            std::vector<CSVLine> mLines;
    };
}


#endif // CSVPARSER_H
