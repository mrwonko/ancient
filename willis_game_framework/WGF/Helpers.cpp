#include "Helpers.h"
#include <string>
#include <sstream>
#include <cctype>

namespace WGF
{
namespace Helpers
{
    // removew whitespaces from beginning and end
    std::string Trim(const std::string& string)
    {
        //this is the trimmed version of the string
        std::string trimmedString = string;

        //now remove the whitespaces from the beginning
        trimmedString.erase(0, trimmedString.find_first_not_of(" \t"));

        //and remove the whitespaces from the end
        trimmedString.erase(trimmedString.find_last_not_of(" \t")+1);

        return trimmedString;
    }

    std::string IntToString(int integer)
    {
        std::stringstream ss;
        ss<<integer;
        return ss.str();
    }

    std::string FloatToString(float number)
    {
        std::stringstream ss;
        ss<<number;
        return ss.str();
    }

    int StringToInt(const std::string& string)
    {
        std::stringstream ss;
        ss<<string;
        int result;
        ss>>result;
        return result;
    }

    float StringToFloat(const std::string& string)
    {
        std::stringstream ss;
        ss<<string;
        float result;
        ss>>result;
        return result;
    }

    std::string RemoveCStyleComments(const std::string& textWithComments)
    {
        std::string textWithoutComments = textWithComments;

        std::string::size_type commentStart, commentEnd;

        //remove multi line comments first because else a // could hide a following */

        //while you can find mutli-line-comment-starts
        while( (commentStart = textWithoutComments.find("/*")) != std::string::npos)
        {
            //search for the end of the commend - if you can't find any, stop searching for any other multi-line-comments.
            if( (commentEnd = textWithoutComments.find("*/", commentStart)) == std::string::npos) break;

            //remove the found multi-line-comment
            textWithoutComments.erase(commentStart, commentEnd - commentStart + 2);
        }

        //remove one line comments
        while( (commentStart = textWithoutComments.find("//")) != std::string::npos)
        {
            commentEnd = textWithoutComments.find("\n", commentStart);
            textWithoutComments.erase(commentStart, commentEnd - commentStart);
        }

        return textWithoutComments;
    }

    std::string ToLower(const std::string& text)
    {
        std::string result;
        for(unsigned int i = 0; i < text.size(); ++i)
        {
            const char lower = tolower(text.at(i));
            //append lower once
            result.append(1, lower);
        }
        return result;
    }

    std::string Replace(const std::string& text, const std::string& pattern, const std::string& replace)
    {
        //if the replace string contains the pattern do nothing as it would only result in an endless loop
        if(replace.find(pattern) != std::string::npos)
        {
            return text;
        }

        std::string result = text;
        std::string::size_type match = result.find(pattern);


        //as long as the string still contains the search pattern
        while( match != std::string::npos)
        {
            //replace it
            result.erase(match, pattern.length());
            result.insert(match, replace);

            //search next
            match = result.find(pattern);
        }
        return result;
    }

    int Round(float f)
    {
        return((int)(f+0.5));
    }
}
}
