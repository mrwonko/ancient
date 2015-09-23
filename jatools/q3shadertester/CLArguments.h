//  cppag::CLArguments
//
//  a class for dealing with command line arguments passed to the program
//
//  Last modified 2009-02-17 by Willi

#ifndef CLARGUMENTS_H_INCLUDED
#define CLARGUMENTS_H_INCLUDED
#include <string>
#include <vector>
#include "GxSingleton.h"

///Stuff from the "C++ AG" at school
namespace cppag
{
    /**
     *  \brief a class keeping track of the <b>C</b>ommand <b>L</b>ine <b>Arguments</b> the program got at startup
     *
     *  Also parses the first argument to get the path to the program
     *
     **/
    class CLArguments : public GX::Singleton<CLArguments>
    {
        public:
            /**
            *
            *   \brief constructor for the argument thingy
            *
            *   \param argc number of arguments given, equals the first parameter of main
            *   \param argv arguments given, equals the second parameter of main
            *
            **/
            CLArguments(int argc, char** argv);


            /**
            *
            *   \brief returns the directory containing the executable
            *
            *   \return the directory containing the executable
            *
            **/
            const std::string& GetWorkingDirectory() const;


            /**
            *
            *   \brief constructor for the argument thingy
            *
            *   \param argc number of arguments given, equals the first parameter of main
            *   \param argv arguments given, equals the second parameter of main
            *
            **/
            std::string MatchPath(const std::string& dir) const;

            /**
             *
             *  \brief gives you all arguments
             *
             *  not including the first argument which is the path.
             *
             **/
            const std::vector <std::string>& GetArguments() const { return mArguments; }

            const std::string& GetArgument(const int index) const { return mArguments.at(index); }

            /**
             *  \brief  Finds a given argument
             *  \param  caseSensitive   whether "ARG" differs from "arg", default false
             *  \return position or -1 if the argument does not exist
             */
            const int FindArgument(const std::string& requestedArgument, bool caseSensitive = false) const;
        private:
            /// All the arguments (except the path)
            std::vector < std::string > mArguments;

            /// The path to the executable
            std::string mWorkingDir;

            /// Operating System
            bool mWindows;
    };

}
#endif // CLARGUMENTS_H_INCLUDED
