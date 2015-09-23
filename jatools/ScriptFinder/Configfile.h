#ifndef WGF_CONFIGFILE_H
#define WGF_CONFIGFILE_H

#include <map>
#include <string>

/** \brief A configuration file containing infos as key = value

Optionally with comments in C-style. NOT ";"! Values can be strings, integers or floats.
\note use lower-case on keys as those from the config file will be stored as lower case anyway **/
class Configfile
{
    public:
        /** Default constructor */
        Configfile();
        /** Default destructor */
        virtual ~Configfile();

        /** Load the values from a file
        \return success   **/
        bool LoadFromFile(const std::string& filename);

        /** Parse one line to get key & value if possible
        \note can be parsed if there is at least one = but that doesn't guarantee it will make sense! **/
        void ParseLine(const std::string& line);

        /** Save the values to a file
        \return success **/
        bool SaveToFile(const std::string& filename);

        /** set a key to a string value
        \note removes values of other type with same key**/
        void SetString(const std::string& key, const std::string& value);

        /** set a key to an integer value
        \note removes values of other type with same key**/
        void SetInt(const std::string& key, int value);

        /** set a key to a float value
        \note removes values of other type with same key**/
        void SetFloat(const std::string& key, float value);

        /** gets a string value for a given key
        \note Logs to Framework-Logfile if the value does not exist.
        \note Automatically converts floats and ints.
        \return value or defaultvalue if it does not exist **/
        const std::string GetString(const std::string& key, const std::string& defaultvalue = "");

        /** gets an int value for a given key
        \note Logs to Framework-Logfile if the value does not exist or is of wrong type.
        \note Float is automatically converted to int
        \return value or defaultvalue if it does not exist **/
        const int GetInt(const std::string& key, int defaultvalue = -1);

        /** gets a float value for a given key
        \note Logs to Framework-Logfile if the value does not exist or is of wrong type.
        \note Int is automatically converted to float
        \return value or defaultvalue if it does not exist **/
        const float GetFloat(const std::string& key, float defaultvalue = -1.0);

    protected:
        /** All the strings saved **/
        std::map<std::string, std::string> mStrings;
        /** All the integers saved **/
        std::map<std::string, int> mInts;
        /** All the floats saved **/
        std::map<std::string, float> mFloats;
};

#endif // WGF_CONFIGFILE_H
