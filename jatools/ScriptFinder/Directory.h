#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

class File;

class Directory
{
    public:
        typedef std::vector<boost::shared_ptr<File> > fileVector;

        Directory(const std::string& path);
        virtual ~Directory();

        ///Returns the path of this directory
        const std::string& GetPath() { return mPath; }

        ///Returns the files in this directory
        const fileVector& GetFiles() const { return mFiles; }

    private:
        std::string mPath;
        ///the files in this directory
        fileVector mFiles;

};

#endif // DIRECTORY_H
