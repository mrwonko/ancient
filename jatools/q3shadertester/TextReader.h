//  StringFileReader
//
//  A class for reading a file
//
//  Last modified 2009-02-17 by Willi

#ifndef TextReader_H
#define TextReader_H
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "CLArguments.h"

///Stuff from the "C++ AG" at school
namespace cppag
{
    ///A class for reading \b one text file
    class TextReader
    {
        public:
            /**
             *
             *  \brief Constructor - creates a Text Reader
             *
             *  \param loc the filename, either relative or absolute
             *
             **/
            TextReader(const std::string& loc);
            ///reads the content of the file
            bool Read ();

            /**
             *  \brief returns the content of the file
             *
             *  Don't forget to read() it first!
             *
             *  \return content of the file
             *
             **/
            std::string GetContent () const;

            virtual ~TextReader();

        protected:
            ///Which file to read
            std::string mLocation;
            ///The content of the file, saved as a vector of lines.
            std::vector<std::string> mContent; //Zeilenweise gespeicherter Inhalt
    };

}

#endif // TextReader_H
