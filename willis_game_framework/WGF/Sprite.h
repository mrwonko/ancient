#ifndef WGF_SPRITE_H
#define WGF_SPRITE_H

#include <SFML/Graphics/Sprite.hpp>
#include <string>

namespace WGF
{
    class Sprite : public sf::Sprite
    {
        public:
            /** Default constructor */
            Sprite();
            Sprite(const std::string& filename, const sf::Vector2f& position = sf::Vector2f(0, 0), const sf::Vector2f& scale = sf::Vector2f(1, 1), float rotation = 0.f, const sf::Color& col = sf::Color(255, 255, 255, 255));
            /** Default destructor */
            virtual ~Sprite();
        protected:
            const std::string mFilename;
    };

}

#endif // WGF_SPRITE_H
