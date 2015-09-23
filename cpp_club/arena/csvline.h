#ifndef CSVLINE_H
#define CSVLINE_H
#include <string>
#include <vector>

namespace cppag
{
    class CSVParser;

    class CSVLine
    {
        public:
            CSVLine();
            virtual ~CSVLine();

            const std::string& operator [] (int num) const;

            int size() const {return mCells.size();}

        private:
            bool add(std::string cell);

            std::vector<std::string> mCells;


        friend class CSVParser;
    };
}

#endif // CSVLINE_H
