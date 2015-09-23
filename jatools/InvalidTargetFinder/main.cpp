#include "CLArguments.h"
#include "InvalidTargetFinder.h"

using namespace std;

int main(int argc, char** argv)
{
    cppag::CLArguments args(argc, argv);
    InvalidTargetFinder itf;
    itf.Go();
    return EXIT_SUCCESS;
}
