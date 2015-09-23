#ifndef TEXTREADER_H
#define TEXTREADER_H
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "CLArguments.h"

namespace cppag
{

    class Textreader
    {
        public:
            Textreader(std::string loc);
            bool read ();

            std::string getContent ();

            ~Textreader();

        protected:
            std::string mLocation;
            std::vector<std::string> mContent; //Zeilenweise gespeicherter Inhalt

        private:

    };

}

#endif // TEXTREADER_H
