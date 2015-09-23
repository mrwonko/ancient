#ifndef WGF_IMAGEMANAGER_H
#define WGF_IMAGEMANAGER_H

#include "GxSingleton.h"
#include <string>
#include <map>
#include <SFML/Graphics/Image.hpp>

namespace WGF
{

    class ImageManager : public GX::Singleton<ImageManager>
    {
        public:
            /** Default constructor */
            ImageManager();
            /** Default destructor */
            virtual ~ImageManager();
            /** \brief Load an Image and return a pointer to it

            throws an std::runtime_error if the file is not available **/
            sf::Image& Load(const std::string& filename);
            /** remove one user for the image and delete if possible
            \return if it was removed **/
            void Unload(const std::string& filename);
        private:
            /** kind of a little shared pointer - now that I think about it, why don't I use them? Ah right because one would always remain here **/
            struct ImageInfo
            {
                int numUsers;
                sf::Image* Image;

                ImageInfo(sf::Image* image) : numUsers(1), Image(image)
                    {}
                ~ImageInfo()
                {
                    delete Image;
                }
            };
            std::map<std::string, ImageInfo*> mImages;
    };

} // namespace WGF

#endif // WGF_IMAGEMANAGER_H
