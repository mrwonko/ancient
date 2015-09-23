#ifndef INVALIDTARGETFINDER_H
#define INVALIDTARGETFINDER_H

#include <string>
#include <set>

class InvalidTargetFinder
{
    public:
        /** Default constructor */
        InvalidTargetFinder();
        /** Default destructor */
        virtual ~InvalidTargetFinder();

        void Go();
    private:
        void Error(const std::string& message);
        void Extract(std::string content, const std::string& search, std::set<std::string>& output);
        std::set<std::string> mTargets;
        std::set<std::string> mTargetnames;
};

#endif // INVALIDTARGETFINDER_H
