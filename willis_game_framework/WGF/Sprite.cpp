#include "Sprite.h"

#include "ImageManager.h"

namespace WGF
{

    Sprite::Sprite() :
        mFilename("")
    {
        //ctor
    }

    Sprite::~Sprite()
    {
        //dtor
        if(mFilename != "")
        {
            ImageManager::GetSingleton().Unload(mFilename);
        }
    }

    Sprite::Sprite(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& scale, float rotation, const sf::Color& col):
        sf::Sprite(ImageManager::GetSingleton().Load(filename), position, scale, rotation, col),
        mFilename(filename)
    {
    }
}
