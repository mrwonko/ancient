#include "Directory.h"

//TODO: find out why lua does not want to open files found by windows code (but takes the unix files - "/" okay and "\" not?), fix it and delete the DELETEME - is it already fixed?
#ifdef _WIN32

    #define WIN32_LEAN_AND_MEAN
    #include "windows.h"

#else

    #include <sys/types.h>
    #include <dirent.h>
    #include <sys/stat.h>

#endif

#include <sstream>
#include "File.h"
#include "CLArguments.h"

Directory::Directory(const std::string& path):
    mPath(cppag::CLArguments::GetSingleton().MatchPath(path))
{
    //ctor
//TODO: delete DELETEME as soon as bug mentioned above is fixed
#ifdef _WIN32


    WIN32_FIND_DATA findFileData;

    HANDLE hFind = FindFirstFile( (mPath+"*").c_str(), &findFileData);
    //ignore the first result, it's "."

    if(hFind  == INVALID_HANDLE_VALUE)
    {
        return;
    }

    while(FindNextFile(hFind, &findFileData))
    {
        if( !(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
        {
            boost::shared_ptr<File> newFile( new File(mPath + findFileData.cFileName) );
            mFiles.push_back(newFile);
        }
    }

    FindClose(hFind);

#else //_WIN32

    // not WIN32, so probably Linux or sth.

    //try to open
    DIR* dir = opendir(mPath.c_str());
    //if the directory could not be opened
    if(dir == NULL)
    {
        //Log Error
        std::stringstream errorInfo;
        errorInfo<<"Error ("<<errno<<") opening "<<mPath<<"!";
        //Ogre::LogManager::getSingleton().logMessage(errorInfo.str().c_str());
        std::cout<<errorInfo.str()<<std::endl;
        //and return
        return;
    }

    dirent *curDir;

    while( (curDir = readdir(dir) ) != NULL)
    {
        std::string filename = curDir->d_name;

        std::string fullName(mPath + filename);

        //skip . and ..
        if(filename == "." || filename == "..") continue;

        struct stat* info;
        stat(fullName.c_str(), info);

        if(info == NULL)
        {
            std::cout<<"Error getting info about "<<fullName<<std::endl;
            continue;
        }

        if(info->st_size != 0) // size is 0 for directories
        {

            boost::shared_ptr<File> newFile ( new File(fullName) );
            mFiles.push_back( newFile );
        }
    }

    closedir(dir);

#endif
}

Directory::~Directory()
{
    //dtor
}
