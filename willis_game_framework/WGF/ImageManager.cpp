#include "ImageManager.h"
#include "GameFramework.h"
#include "Logfile.h"
#include <stdexcept>

namespace WGF
{
    ImageManager::ImageManager()
    {
        //ctor
        GameFramework::GetSingleton().GetLogfile().Log("The ImageManager greets the World: \"Hello World!\"");
    }

    ImageManager::~ImageManager()
    {
        //dtor
    }

    sf::Image& ImageManager::Load(const std::string& filename)
    {
        if(mImages.find(filename) == mImages.end())
        {
            mImages[filename] = new ImageInfo(new sf::Image());
            if(!mImages[filename]->Image->LoadFromFile(filename))
            {
                std::string error = "unable to load ";
                error += filename;
                WGF_LOG(error);
                throw(std::runtime_error(error));
            }
        }
        else
        {
            ++mImages[filename]->numUsers;
        }
        return *mImages[filename]->Image;
    }

    void ImageManager::Unload(const std::string& filename)
    {
        //if the image isn't even loaded don't bother.
        if(mImages.find(filename) == mImages.end()) return;
        --mImages[filename]->numUsers;
        if(mImages[filename]->numUsers <= 0)
        {
            mImages.erase(filename);
        }
    }

    //Initialize the static pointer to this class through which it can easily be accessed - also known as Singleton
    template<> ImageManager* GX::Singleton<ImageManager>::ms_Singleton = NULL;
} // namespace WGF
