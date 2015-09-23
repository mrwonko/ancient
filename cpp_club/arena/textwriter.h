#ifndef TEXTWRITER_H_INCLUDED
#define TEXTWRITER_H_INCLUDED

#include <string>
#include <stdio.h>
#include <iostream>

namespace cppag
{
    class textWriter
    {
        public:
            textWriter(std::string location, bool countLines);
            void write(std::string text);
        private:
            std::string mLoc;
            bool mCount;
            int mCurrentLine;
    };
}


#endif // TEXTWRITER_H_INCLUDED
