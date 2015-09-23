#include "csvline.h"
#include <iostream>

namespace cppag
{
    CSVLine::CSVLine()
    {

    }

    CSVLine::~CSVLine()
    {
        //dtor
    }

    const std::string& CSVLine::operator [] (int num) const
    {
        return (mCells[num]);
    }

    bool CSVLine::add(std::string cell)
    {
        // Zelle zum Array hinzufügen
        mCells.push_back(cell);
    }
}


