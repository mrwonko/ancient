#ifndef WGF_HIGHSCORE_H
#define WGF_HIGHSCORE_H

#include <string>

namespace WGF
{
    struct HighScoreEntry
    {
        int Score;
        std::string Name;
    };

    //TODO HighScore
    class HighScore
    {
        public:
            /** Default constructor */
            HighScore();
            /** Default destructor */
            virtual ~HighScore();
        protected:
        private:
    };

} // namespace WGF

#endif // WGF_HIGHSCORE_H
