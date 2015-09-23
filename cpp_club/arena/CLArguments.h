#ifndef CLARGUMENTS_H_INCLUDED
#define CLARGUMENTS_H_INCLUDED
#include <string>
#include <vector>

namespace cppag
{

class CLArguments
{
    public:
        CLArguments(int argc, char** argv);
        static std::string getWorkingDirectory();
        static std::string matchPath(std::string dir);
    private:
        static  std::vector < std::string > mArguments;
};

}
#endif // CLARGUMENTS_H_INCLUDED
