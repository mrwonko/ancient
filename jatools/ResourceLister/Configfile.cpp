#include "Configfile.h"
#include "Helpers.h"
#include <sstream>
#include <fstream>
#include <iostream>

namespace WGF
{

    Configfile::Configfile()
    {
        //ctor
    }

    Configfile::~Configfile()
    {
        //dtor
    }

    bool Configfile::LoadFromFile(const std::string& filename)
    {
        //Get the contents of filename
        std::string fileContent;
        std::ifstream fileStream(filename.c_str());
        if(fileStream.fail())
        {
            return false;
        }
        char tempChar;
        while(fileStream.get(tempChar) )
        {
            fileContent += tempChar;
        }

        //remove all c-style comments
        fileContent = Helpers::RemoveCStyleComments(fileContent);

        //Now use a stream as it can easily be gone through line by line
        std::stringstream fileContentStream;
        fileContentStream<<fileContent;

        std::string curLine;
        while(std::getline(fileContentStream, curLine))
        {
            ParseLine(curLine);
        }
        return true;
    }

    void Configfile::ParseLine(const std::string& line)
    {
        //find the = in the line
        std::string::size_type equalsPos = line.find_first_of("=");
        //none there?
        if(equalsPos == std::string::npos)
        {
            //return
            return;
        }

        //get key and value as strings
        std::string key = Helpers::ToLower(Helpers::Trim(line.substr(0, equalsPos)));

        std::string value = Helpers::ToLower(line);
        value.erase(0, equalsPos+1);
        value = Helpers::Trim(value);

        //is every character of the value either a caracter or a dot? find out by removing everything else and if anything remains.
        std::string valueNoNumbersOrDots = value;
        std::string removeMe = "0123456789.";
        for(std::string::iterator iter = removeMe.begin(); iter != removeMe.end(); ++iter)
        {
            std::string::size_type pos = std::string::npos;
            while( ( pos = valueNoNumbersOrDots.find(*iter) ) != std::string::npos)
            {
                valueNoNumbersOrDots.erase(pos, 1);
            }
        }
        //if a number
        if (valueNoNumbersOrDots == "")
        {
            //is it an int?
            if(value.find('.') == std::string::npos)
            {
                SetInt(key, Helpers::StringToInt(value));
            }
            else //else float
            {
                SetFloat(key, Helpers::StringToFloat(value));
            }
        }
        else //no number - string!
        {
                SetString(key, value);
        }
    }

    bool Configfile::SaveToFile(const std::string& filename)
    {
        std::ofstream file(filename.c_str());
        if(file.fail()) return false;

        file << "//Automatically created config file, comments will be removed on next save! " << std::endl << std::endl <<
                "// String Values"<<std::endl << std::endl;
        for(std::map<std::string, std::string>::iterator it = mStrings.begin(); it != mStrings.end(); ++it)
        {
            file << it->first << " = " << it->second <<std::endl;
        }
        file << std::endl << "// Integer Values"<<std::endl << std::endl;
        for(std::map<std::string, int>::iterator it = mInts.begin(); it != mInts.end(); ++it)
        {
            file << it->first << " = " << it->second <<std::endl;
        }
        file << std::endl << "// Float Values"<<std::endl << std::endl;
        for(std::map<std::string, float>::iterator it = mFloats.begin(); it != mFloats.end(); ++it)
        {
            file << it->first << " = " << it->second <<std::endl;
        }
        file.close();
        return true;
    }

    void Configfile::SetString(const std::string& key, const std::string& value)
    {
        if(mInts.find(key) != mInts.end())
        {
            mInts.erase(key);
        }
        if(mFloats.find(key) != mFloats.end())
        {
            mFloats.erase(key);
        }
        mStrings[key] = value;
    }

    void Configfile::SetInt(const std::string& key, int value)
    {
        if(mStrings.find(key) != mStrings.end())
        {
            mStrings.erase(key);
        }
        if(mFloats.find(key) != mFloats.end())
        {
            mFloats.erase(key);
        }
        mInts[key] = value;
    }

    void Configfile::SetFloat(const std::string& key, float value)
    {
        if(mInts.find(key) != mInts.end())
        {
            mInts.erase(key);
        }
        if(mStrings.find(key) != mStrings.end())
        {
            mStrings.erase(key);
        }
        mFloats[key] = value;
    }

    const std::string Configfile::GetString(const std::string& key, const std::string& defaultvalue)
    {
        //first try to find a string with this name
        if(mStrings.find(key) == mStrings.end())
        {
            //if there is none fall back to integers
            if(mInts.find(key) == mInts.end())
            {
                //if there is none fall back to floats
                if(mFloats.find(key) == mFloats.end())
                {
                    //if there is none: ERROR!
                    std::string error = "WARNING: Unable to retrieve ";
                    error += key;
                    error += " from configuration!";
                    std::cout<<error<<std::endl;
                    return defaultvalue;
                }
                return(Helpers::FloatToString(mFloats[key]));
            }
            return(Helpers::IntToString(mInts[key]));
        }
        return mStrings[key];
    }

    const int Configfile::GetInt(const std::string& key, int defaultvalue)
    {
        //first try to find n int with this name
        if(mInts.find(key) == mInts.end())
        {
            //if there is none fall back to integers
            if(mFloats.find(key) == mFloats.end())
            {
                //if there is none: ERROR!
                std::string error = "WARNING: Unable to retrieve ";
                error += key;
                error += " from configuration!";
                    std::cout<<error<<std::endl;
                return defaultvalue;
            }
            return(Helpers::Round(mFloats[key]));
        }
        return mInts[key];
    }

    const float Configfile::GetFloat(const std::string& key, float defaultvalue)
    {
        //first try to find n int with this name
        if(mFloats.find(key) == mFloats.end())
        {
            //if there is none fall back to integers
            if(mInts.find(key) == mInts.end())
            {
                //if there is none: ERROR!
                std::string error = "WARNING: Unable to retrieve ";
                error += key;
                error += " from configuration!";
                std::cout<<error<<std::endl;
                return defaultvalue;
            }
            return(mInts[key]);
        }
        return mFloats[key];
    }

} // namespace WGF
