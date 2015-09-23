#ifndef ScriptFinder_H
#define ScriptFinder_H

#include <string>
#include <set>
#include <map>
#include <utility>
#include "Configfile.h"

class Script;

class ScriptFinder
{
    public:
        /** Default constructor */
        ScriptFinder();
        /** Default destructor */
        virtual ~ScriptFinder();

        bool Init();

        bool LoadInputListFromFile(const std::string& filename);



        void ParseShaderFiles();

        std::pair<bool, std::string> GetFileContent(const std::string& filename);

        void Go();

        void Error(const std::string& message);

        /// \return if new scripts were found
        bool Parse(Script& script);
    protected:
        Configfile mConfig;
        std::string mListpath;
        std::string mScriptpath;
        std::set<Script> mScriptList;
        std::map<std::string, std::set<std::string> > mShaders;
};

#endif // ScriptFinder_H
