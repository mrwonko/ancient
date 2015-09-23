#ifndef WGF_HELPERS_H_INCLUDED
#define WGF_HELPERS_H_INCLUDED

#include <string>
namespace WGF
{
namespace Helpers
{
    /**
     *
     *  \brief  removes spaces and tabs from the beginning and the end of a string
     *
     *  \param  string  string to trim
     *
     *  \return string without spaces and tabs at beginning and end
     *
     **/
    std::string Trim(const std::string& string);

    /**
     *
     *  \brief  converts an integer to a string
     *
     *  \param  integer the integer to convert
     *
     *  \return string containing the number
     *
     *  \see FloatToString
     *  \see StringToInt
     *  \see StringToFloat
     *
     **/
    std::string IntToString(int integer);

    /**
     *
     *  \brief  converts a float to a string
     *
     *  \param  number the float to convert
     *
     *  \return string containing the number
     *
     *  \see IntToString
     *  \see StringToInt
     *  \see StringToFloat
     *
     **/
    std::string FloatToString(float number);

    /**
     *
     *  \brief  converts a string to an integer
     *
     *  \param  string  string to convert
     *
     *  \return string as an int
     *
     *  \see StringToFloat
     *  \see FloatToString
     *  \see IntToString
     *
     **/
    int StringToInt(const std::string& string);

    /**
     *
     *  \brief  converts an integer to a string
     *
     *  \param  integer the integer to convert
     *
     *  \return string containing the number
     *
     *  \see StringToInt
     *  \see FloatToString
     *  \see IntToString
     *
     **/
    float StringToFloat(const std::string& string);

    /**
     *
     *  \brief  removes c-style comments from a given string
     *
     *  C-Style means // and / * * / style
     *
     *  \param  textWithComments the text containing comments
     *
     *  \return the text without the comments
     *
     **/
    std::string RemoveCStyleComments(const std::string& textWithComments);

    /// Converts a string to lower case
    std::string ToLower(const std::string& text);

    /**
     *  \brief replaces something in a string with something else.
     *  \param  text    the text in which to search
     *  \param  pattern the text to find
     *  \param  replace the text to replace the matches with
     *  \return the string with everything replaced
     **/
    std::string Replace(const std::string& text, const std::string& pattern, const std::string& replace);

    int Round(float f);
}
}

#endif // WGF_HELPERS_H_INCLUDED
