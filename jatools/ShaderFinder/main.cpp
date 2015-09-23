#include "ShaderFinder.h"
#include "CLArguments.h"

int main(int argc, char** argv)
{
    cppag::CLArguments args(argc, argv);
    ShaderFinder sf;
    sf.Go();
    return EXIT_SUCCESS;
}
