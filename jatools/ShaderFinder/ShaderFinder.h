#ifndef SHADERFINDER_H
#define SHADERFINDER_H

#include <string>
#include <set>
#include <map>
#include <utility>
#include "Configfile.h"

class ShaderFinder
{
    public:
        /** Default constructor */
        ShaderFinder();
        /** Default destructor */
        virtual ~ShaderFinder();

        bool Init();

        bool LoadInputListFromFile(const std::string& filename);



        void ParseShaderFiles();

        std::pair<bool, std::string> GetFileContent(const std::string& filename);

        void Go();

        void Error(const std::string& message);
    protected:
        Configfile mConfig;
        std::string mListpath;
        std::string mShaderpath;
        std::set<std::string> mInputList;
        std::set<std::string> mOutputList;
        std::map<std::string, std::set<std::string> > mShaders;
};

#endif // SHADERFINDER_H
