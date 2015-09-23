#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <Vector>
#include <boost/shared_ptr.hpp>

class File;

class FileSystem
{
    public:
        FileSystem();
        virtual ~FileSystem();

    private:
        typedef std::vector<boost::shared_ptr<File> > fileVector;
        fileVector mFiles;
};

#endif // FILESYSTEM_H
