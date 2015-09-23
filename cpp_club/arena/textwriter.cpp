#include "textwriter.h"
#include "CLArguments.h"
#include "vector"
#include <sstream>

namespace cppag
{
    textWriter::textWriter(std::string location, bool countLines)
    {
        mLoc=cppag::CLArguments::getWorkingDirectory()+location;
        mCount=countLines;
        mCurrentLine=1;
        FILE* myFile=fopen(mLoc.c_str(), "w");
        if(myFile && mCount)
        {
            std::string temp = "1\t";
            fprintf(myFile, temp.c_str());
            mCurrentLine++;
        }
        fclose(myFile);
    }
    void textWriter::write(std::string text)
    {
        FILE* myFile=fopen(mLoc.c_str(), "a");
        if(myFile)
        {
            if(mCount)
            {
                std::string newText="";
                if(text.find("\n")==std::string::npos)
                {
                    newText=text;
                }
                else
                {
                    int temp;
                    while(text.find("\n")!=std::string::npos)
                    {
                        temp=text.find("\n");
                        newText+=text.substr(0,temp+1);
                        std::ostringstream s;
                        if (s << mCurrentLine)
                        {
                            newText+=s.str()+"\t";
                        }
                        else
                        {
                            newText+=" ***ERROR 1*** ";
                        }
                        mCurrentLine++;
                        text.erase(0,temp+1);
                    }
                    newText+=text;
                }
                fprintf(myFile, newText.c_str());
            }
            else
                fprintf(myFile, text.c_str());
        }
        else
        {
            std::cout<<"Error writing "<<mLoc<<std::endl;
        }
        fclose(myFile);
    }
}
