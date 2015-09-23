#include "ShaderFinder.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Helpers.h"
#include "CLArguments.h"
#include "Directory.h"
#include "File.h"

ShaderFinder::ShaderFinder()
{
    //ctor
}

ShaderFinder::~ShaderFinder()
{
    //dtor
}

std::pair<bool, std::string> ShaderFinder::GetFileContent(const std::string& filename)
{
    std::pair<bool, std::string> result;
    result.first = false;
    std::ifstream filestream(filename.c_str());
    if(filestream.fail())
    {
        return result;
    }
    while(!filestream.eof())
    {
        result.second += filestream.get();
    }
    filestream.close();
    result.first = true;
    return result;
}

bool ShaderFinder::LoadInputListFromFile(const std::string& filename)
{
    std::pair<bool, std::string> result = GetFileContent(filename);
    if(!result.first) return false;
    std::string& content = result.second;
    std::string curline;
    for(std::string::iterator it = content.begin(); it != content.end(); ++it)
    {
        if(*it == '\n')
        {
            if(curline != "") mInputList.insert(curline);
            curline = "";
            continue;
        }
        curline += *it;
    }
    if(curline != "") mInputList.insert(curline);
    return true;
}

void ShaderFinder::ParseShaderFiles()
{
    Directory shaderdir(mShaderpath);

    //for every file in the shaderpath directory...
    for(Directory::fileVector::const_iterator it = shaderdir.GetFiles().begin(); it != shaderdir.GetFiles().end(); ++it)
    {
        //if this is no shader continue
        if(it->get()->GetExtension() != "shader") continue;
        std::string content = Helpers::RemoveCStyleComments(it->get()->GetContent());
        std::string::size_type match = std::string::npos;
        //find every start of a shader
        while((match = content.find("{")) != std::string::npos)
        {
            //everything up to there is the name
            std::string name = Helpers::Trim(Helpers::Replace(content.substr(0, match), "\n", ""));
            std::set<std::string> textures;
            //erase everything up to and including the {
            content.erase(0, match+1);
            //keey track of how many { there are
            unsigned int counter = 1;
            unsigned int pos = 0;
            for(std::string::iterator it2 = content.begin(); it2 != content.end() && counter > 0; ++it2, ++pos)
            {
                if((*it2) == '{') ++counter;
                else if((*it2) == '}') --counter;
            }
            if(counter > 0)
            {
                std::cout<<"Warning: "<<it->get()->GetFilename()<<" is invalid!"<<std::endl;
                break;
            }
            std::string curShader = content.substr(0, pos);
            content.erase(0, pos);

            std::string::size_type next = std::min(curShader.find("textures/"), curShader.find("models/"));
            while(next != std::string::npos)
            {
                curShader.erase(0, next);
                std::string::size_type end = curShader.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_-./()&+");
                textures.insert(curShader.substr(0, end));
                curShader.erase(0, end);

                next = std::min(curShader.find("textures/"), curShader.find("models/"));
            }
            if(!textures.empty())
            {
                textures.insert("shaders/" + it->get()->GetFilename());
                mShaders[name] = textures;
            }
        }
    }
}

bool ShaderFinder::Init()
{
    std::cout   << "This program parses all the .shader files in the directory set in the config file shaderfinder.cfg and then outputs a list of .shader files containing shaders for the textures you supplied and which images are used in them." << std::endl
                << "Usage: shaderfinder.exe list_from_resourcelister.txt or simply drag-n-drop a file on this" <<std::endl;

    if(!mConfig.LoadFromFile(cppag::CLArguments::GetSingleton().GetWorkingDirectory() + "shaderfinder.cfg"))
    {
         Error("Could not open shaderfinder.cfg!");
         return false;
    }

    mShaderpath = mConfig.GetString("shaderpath");
    mListpath = mConfig.GetString("listpath");
    if(mShaderpath == "")
    {
        Error("No shaderpath set in shaderfinder.cfg!");
        return false;
    }

    if(cppag::CLArguments::GetSingleton().NumArguments() < 1)
    {
         Error("No list supplied!");
         return false;
    }

    //load list
    if(!LoadInputListFromFile(cppag::CLArguments::GetSingleton().GetArgument(0)))
    {
        Error("Could not open file!");
        return false;
    }

    ParseShaderFiles();

    return true;
}

void ShaderFinder::Go()
{
    if(!Init()) return;

    for(std::set<std::string>::iterator it = mInputList.begin(); it != mInputList.end(); ++it)
    {
        std::map<std::string, std::set<std::string> >::iterator find = mShaders.find(*it);
        if(find == mShaders.end())
        {
            mOutputList.insert(*it);
        }
        else
        {
            mOutputList.insert(find->second.begin(), find->second.end());
        }
    }

    //n = name(old)
    const std::string& n = cppag::CLArguments::GetSingleton().GetArgument(0);
    std::string::size_type pos = n.find_last_of("/\\");
    std::string filename;
    if(pos == std::string::npos)
    {
        filename = n;
    }
    else
    {
        filename = n.substr(pos, n.length()-pos);
    }
    filename = mListpath + filename + ".shadersparsed.txt";

    std::ofstream out (filename.c_str());
    if(out.fail())
    {
        Error("Could not write list! Here it is:");
        for(std::set<std::string>::iterator it = mOutputList.begin(); it != mOutputList.end(); ++it)
        {
            std::cout<<*it<<std::endl;
        }
    }
    else
    {
        for(std::set<std::string>::iterator it = mOutputList.begin(); it != mOutputList.end(); ++it)
        {
            out<<*it<<std::endl;
        }
        out.close();
    }

    std::cout<<"Press Enter to exit";
    std::fflush(stdin);
    std::getchar();
}

void ShaderFinder::Error(const std::string& message)
{
    std::cout<<"Error: "<<message<<std::endl;
    std::cout<<"Press Enter to exit";
    std::fflush(stdin);
    std::getchar();
}
