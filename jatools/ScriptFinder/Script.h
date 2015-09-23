#ifndef SCRIPT_H
#define SCRIPT_H

#include "File.h"

class Script : public File
{
    public:
        /** Default constructor */
        Script(const std::string& filename);
        /** Default destructor */
        virtual ~Script();

        bool Parsed;

        bool operator==(const Script& rhs) const { return mPath == rhs.GetFullName(); }

        bool operator <(const Script& rhs) const { return mPath < rhs.GetFullName(); }

};

#endif // SCRIPT_H
