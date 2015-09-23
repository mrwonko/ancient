#include "ScriptFinder.h"
#include "CLArguments.h"

int main(int argc, char** argv)
{
    cppag::CLArguments args(argc, argv);
    ScriptFinder sf;
    sf.Go();
    return EXIT_SUCCESS;
}
