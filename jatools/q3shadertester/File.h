#ifndef FILE_H
#define FILE_H

#include <string>

class File
{
    public:
        File(const std::string& filename);
        virtual ~File();

        ///Returns the full name including path
        const std::string& GetFullName() const { return mPath; }

        ///Returns only the filename
        const std::string GetFilename() const;

        ///Returns the extension of the file or an empty string if it has none.
        const std::string GetExtension() const;

        std::string GetContent() const;
    protected:
    private:
        std::string mPath;
};

#endif // FILE_H
