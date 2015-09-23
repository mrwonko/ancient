#ifndef WGF_LOGFILE_H
#define WGF_LOGFILE_H

#include <string>
#include "GxSingleton.h"

namespace WGF
{

    class Logfile
    {
        public:
            /** Default constructor */
            Logfile(const std::string& filename = "log.txt");
            /** Default destructor */
            virtual ~Logfile();
            /** Log text to the logfile **/
            void Log(const std::string& text);
            /** Empties the log file **/
            void Empty();
        protected:
            const std::string mFilename;
    };

} // namespace WGF

#endif // WGF_LOGFILE_H
